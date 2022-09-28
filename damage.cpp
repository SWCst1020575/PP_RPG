#include "damage.h"
ALLEGRO_FONT *damage_text_font = NULL;
typedef struct Sequence{
        int origin_index;
        int distance;
}sequence;

typedef struct Damage_text{
        bool show;
        int damage;
        int x,y;
        bool atk_from;//0=character 1=monster
        bool if_update;
        unsigned char transparent;
        int anime;
        int origin_monster;
        Damage_text *next;
}damage_text;
damage_text *damage_text_head,*damage_text_last;
void damage_text_init(){
    damage_text_font = al_load_ttf_font("./font/pirulen.ttf",60,0);
    damage_text_last=(damage_text *) malloc(sizeof(damage_text));
    damage_text_last->show=0;
    damage_text_last->next=NULL;
    damage_text_head = damage_text_last;
}
void creat_new_damage(bool atk_from,int damage,int x,int y,int origin_monster){
    if(damage_text_head->show){
        damage_text_last->next=(damage_text *) malloc(sizeof(damage_text));
        damage_text_last = damage_text_last->next;
        damage_text_last->show = 1;
        damage_text_last->atk_from = atk_from;
        damage_text_last->anime = 0;
        damage_text_last->transparent = 1;
        damage_text_last->if_update = 1;
        damage_text_last->origin_monster = origin_monster;
        damage_text_last->damage = damage;
        damage_text_last->x = x;
        damage_text_last->y = y;
        damage_text_last->next = NULL;
    }
    else{
        damage_text_last->show = 1;
        damage_text_last->atk_from = atk_from;
        damage_text_last->anime = 0;
        damage_text_last->transparent = 1;
        damage_text_last->if_update = 1;
        damage_text_last->origin_monster = origin_monster;
        damage_text_last->damage = damage;
        damage_text_last->x = x;
        damage_text_last->y = y;
    }
}
void damage_text_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps){
            damage_text *current = damage_text_head;
            while(current != NULL  && damage_text_head->show){
                current->anime++;
                current = current->next;
            }
        }
    }

}
void damage_text_update(){
    damage_text *current = damage_text_head;
    int seq[10]={0};
    int chara_count=0;
    while(current != NULL && damage_text_head->show){
        if(current->if_update && current->atk_from == 0)
            seq[current->origin_monster]++;
        else if(current->if_update && current->atk_from == 1)
            chara_count++;
        current = current->next;
    }
    current = damage_text_head;
    while(current != NULL && damage_text_head->show){
        if(current->anime >= 200){
            current = current->next;
            if(current == NULL){
                damage_text_head->show =0;
            }
            else{
                free(damage_text_head);
                damage_text_head = current;
            }
        }
        else{
            if(current->if_update && current->atk_from == 0){
                current->x= get_monster1_x(current->origin_monster)+get_monster1_width()/2;
                current->y= get_monster1_y(current->origin_monster)-80 - seq[current->origin_monster]*50;
                seq[current->origin_monster]--;
            }
            else if(current->if_update && current->atk_from == 1){
                current->x= get_character_x()+get_character_width()/2;
                current->y= get_character_y()-40 - chara_count*50;
                chara_count--;
            }
            if(get_monster1_if_die(current->origin_monster) && current->atk_from == 0)
                current->if_update = 0;
            else if(get_chara_hp()<=0 && current->atk_from == 1)
                current->if_update = 0;

            current = current->next;
        }
    }
}

void damage_text_draw(int camera_x,int camera_y){
    damage_text *current = damage_text_head;
    while(current != NULL && damage_text_head->show){
        char dmg_text[10];
        sprintf(dmg_text,"%d",current->damage);
        if(current->atk_from == 0)
            al_draw_text(damage_text_font, al_map_rgb(242,39,48), current->x-camera_x, current->y-camera_y,ALLEGRO_ALIGN_CENTRE ,dmg_text);
        else
            al_draw_text(damage_text_font, al_map_rgb(138,10,97), current->x-camera_x, current->y-camera_y,ALLEGRO_ALIGN_CENTRE ,dmg_text);
        current=current->next;
    }
}

bool damage_to_monster1(int start_x,int standing_y,int availble_width,int atk_heigth,int availble_num,int origin_atk){
    bool check_damage=0;
    sequence atk_sequence[10];
    for(int i=0;i<10;i++){
        atk_sequence[i].origin_index = i;
        atk_sequence[i].distance = abs(standing_y - get_monster1_standing_y(i));
    }
    qsort(atk_sequence,10,sizeof(sequence),compare_distance);

    for(int i=0;i<10;i++){
        if(get_monster1_show(atk_sequence[i].origin_index) && availble_num>0 && get_monster1_if_die(atk_sequence[i].origin_index)==0){
            if(atk_sequence[i].distance<=atk_heigth && get_monster1_x(atk_sequence[i].origin_index)+get_monster1_width() >= start_x && get_monster1_x(atk_sequence[i].origin_index) <= start_x+availble_width){
                availble_num--;
                int def = get_monster1_def(atk_sequence[i].origin_index) - get_chara_atkP();
                if(def<0)
                    def=0;
                int damage = get_rand(origin_atk*0.9,origin_atk*1.1)-def;
                if(damage<0)
                    damage = 0;
                set_monster1_hp(get_monster1_hp(atk_sequence[i].origin_index)-damage,atk_sequence[i].origin_index);
                creat_new_damage(0,damage,get_monster1_x(atk_sequence[i].origin_index)+get_monster1_width()/2,get_monster1_y(atk_sequence[i].origin_index),atk_sequence[i].origin_index);

                check_damage=1;
            }
        }
    }
    return check_damage;
}

void damage_monster1_to_character(int start_x,int standing_y,int availble_width,int atk_distance,int origin_atk){
    bool if_inregion = 0;
    if(get_character_damage_x()+get_character_damage_width()<start_x){
        if(sqrt((start_x-get_character_damage_x()-get_character_damage_width())*(start_x-get_character_damage_x()-get_character_damage_width()) - (get_character_standing_y()-standing_y)*(get_character_standing_y()-standing_y)) <= (double)atk_distance)
            if_inregion = 1;
    }
    else if(get_character_damage_x()+get_character_damage_width()>=start_x && get_character_damage_x()<=start_x+availble_width){
        if(abs(get_character_standing_y()-standing_y)<=atk_distance)
            if_inregion = 1;
    }
    else{
        if(sqrt((start_x+availble_width-get_character_damage_x())*(start_x+availble_width-get_character_damage_x()) - (get_character_standing_y()-standing_y)*(get_character_standing_y()-standing_y)) <= (double)atk_distance)
            if_inregion = 1;
    }

    if(if_inregion && get_chara_hp()>0){
        int damage = get_rand(origin_atk*0.9,origin_atk*1.1)-get_chara_def();
        if(damage<0)
            damage = 0;
        set_chara_HP(get_chara_hp()-damage);
        creat_new_damage(1,damage,get_character_x()+get_character_width()/2,get_character_y(),0);
    }
}

int compare_distance(const void *save1,const void *save2){
	sequence a = *(sequence *)save1;
	sequence b = *(sequence *)save2;
	return a.distance-b.distance;
}
void damage_text_destroy(){
    damage_text *current = damage_text_head;
    while(current != NULL){
        current = current->next;
        free(damage_text_head);
        damage_text_head = current;
    }
    al_destroy_font(damage_text_font);
}
