#include "interface.h"

ALLEGRO_FONT *lv_text = NULL;
ALLEGRO_FONT *hp_text = NULL;
ALLEGRO_FONT *mp_text = NULL;
ALLEGRO_FONT *exp_text = NULL;

ALLEGRO_BITMAP *interface_bg = NULL;
ALLEGRO_BITMAP *interface_exp_empty = NULL;
ALLEGRO_BITMAP *interface_exp_full = NULL;
ALLEGRO_BITMAP *interface_slot_large = NULL;
ALLEGRO_BITMAP *interface_slot_small = NULL;
ALLEGRO_BITMAP *interface_hp = NULL;
ALLEGRO_BITMAP *interface_mp = NULL;
ALLEGRO_BITMAP *interface_sp = NULL;
ALLEGRO_BITMAP *battle_count_text = NULL;

ALLEGRO_BITMAP *die_bg = NULL;

ALLEGRO_FONT *reborn_text_font = NULL;
ALLEGRO_FONT *battle_count_font = NULL;

int die_count;
int battle_count;

void interface_init(){
    lv_text = al_load_ttf_font("./font/pirulen.ttf",25,0);
    hp_text = al_load_ttf_font("./font/pirulen.ttf",16,0);
    mp_text = al_load_ttf_font("./font/pirulen.ttf",16,0);
    exp_text = al_load_ttf_font("./font/pirulen.ttf",16,0);
    reborn_text_font = al_load_ttf_font("./font/pirulen.ttf",140,0);


    interface_bg = al_load_bitmap("./image/interface/interface_bg.png");
    interface_exp_empty = al_load_bitmap("./image/interface/interface_exp_empty.png");
    interface_exp_full = al_load_bitmap("./image/interface/interface_exp_full.png");
    interface_slot_large = al_load_bitmap("./image/interface/interface_slot_large.png");
    interface_slot_small = al_load_bitmap("./image/interface/interface_slot_small.png");
    interface_hp = al_load_bitmap("./image/interface/interface_hp.png");
    interface_mp = al_load_bitmap("./image/interface/interface_mp.png");
    interface_sp = al_load_bitmap("./image/interface/interface_sp.png");
    die_bg = al_load_bitmap("./image/interface/reborn_bg.png");

    al_draw_bitmap(interface_bg, 20, 20, 0);
    al_draw_bitmap(interface_exp_empty, 20, 20, 0);

    die_count=0;

}

void interface_draw(int lv,int hp,int hp_max,int mp,int mp_max,int sp,int exp,int exp_max){
    al_draw_bitmap(interface_bg, 20, 20, 0);
    al_draw_bitmap(interface_exp_empty, 0, 881, 0);
    al_draw_bitmap(interface_slot_large, 100, 135, 0);
    al_draw_bitmap(interface_slot_large, 100, 195, 0);
    al_draw_bitmap(interface_slot_small, 140, 250, 0);

    al_draw_bitmap_region(interface_hp, 0, 0, round(((float)hp/(float)hp_max)*(float)302), 44,118,135,0);
    al_draw_bitmap_region(interface_mp, 0, 0, round(((float)mp/(float)mp_max)*(float)302), 44,118,195,0);
    al_draw_bitmap_region(interface_sp, 0, 0, round(((float)sp/(float)100)*(float)193), 18,152,250,0);
    al_draw_bitmap_region(interface_exp_full, 0, 0, round(((float)exp/(float)exp_max)*(float)1600), 19,0,881,0);

    //text
    char a[20],b[20];
    sprintf(b,"%d",lv);
    strcpy(a,"LV ");
    strcat(a,b);
    al_draw_text(lv_text, al_map_rgb(209,248,251), 430, 80,ALLEGRO_ALIGN_RIGHT , a);
    sprintf(a,"%d",hp);
    sprintf(b,"%d",hp_max);
    strcat(a,"/");
    strcat(a,b);
    al_draw_text(hp_text, al_map_rgb(209,248,251), 400, 118,ALLEGRO_ALIGN_RIGHT , a);
    sprintf(a,"%d",mp);
    sprintf(b,"%d",mp_max);
    strcat(a,"/");
    strcat(a,b);
    al_draw_text(mp_text, al_map_rgb(209,248,251), 400, 178,ALLEGRO_ALIGN_RIGHT , a);
    sprintf(a,"%d",exp);
    sprintf(b,"%d",exp_max);
    strcat(a,"/");
    strcat(a,b);
    al_draw_text(exp_text, al_map_rgb(255,255,255), 800, 880,ALLEGRO_ALIGN_RIGHT , a);
    /*al_destroy_bitmap(interface_hp_save);
    al_destroy_bitmap(interface_mp_save);
    al_destroy_bitmap(interface_sp_save);
    al_destroy_bitmap(interface_exp_save);*/
    if(get_chara_hp()<=0){
        al_draw_bitmap(die_bg,0,0,0);
        char reborn_time[5];
        sprintf(reborn_time,"%d",(10-(die_count/60)));
        al_draw_text(reborn_text_font, al_map_rgb(255,255,255), WIDTH/2, 410,ALLEGRO_ALIGN_CENTER , reborn_time);
    }

}
void interface_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            if(get_chara_hp()<=0)
                die_count++;
            if(now_stage == 2 && battle_count>0){
                battle_count--;
            }
        }
    }
}
void wait_for_respawn(){
    if(die_count == 600 && get_chara_hp()<=0){
        character_reborn();
        die_count=0;
        set_character_pos(get_stage_avail_lefttop_x()+50,get_stage_avail_lefttop_y()+get_stage_avail_heigth()/2-get_character_heigth());
    }
}

void battle_count_init(){
    battle_count_text = al_load_bitmap("./image/interface/interface_battle_time.png");
    battle_count_font = al_load_ttf_font("./font/pirulen.ttf",50,0);
    if(now_stage==2){
        battle_count=30000;
    }
}
void battle_end(){
    if(battle_count<1 &&  now_stage!=1 && if_stage_change ==0){
        now_stage=1;
        if_stage_change =1;
        if_battle = 0;
    }
}
void battle_count_draw(){
    al_draw_bitmap(battle_count_text, 620,20,0);
    char temp[10];
    sprintf(temp,"%d",battle_count/3600);
    al_draw_text(battle_count_font, al_map_rgb(255,255,255), 730, 40,ALLEGRO_ALIGN_RIGHT , temp);
    sprintf(temp,"%d",(battle_count/60)%60);
    al_draw_text(battle_count_font, al_map_rgb(255,255,255), 892, 40,ALLEGRO_ALIGN_RIGHT , temp);
}
void battle_count_destroy(){
    al_destroy_bitmap(battle_count_text);
    al_destroy_font(battle_count_font);
}
void interface_destroy(){
    al_destroy_font(lv_text);
    al_destroy_font(hp_text);
    al_destroy_font(mp_text);
    al_destroy_font(exp_text);
    al_destroy_font(reborn_text_font);
    al_destroy_bitmap(interface_bg);
    al_destroy_bitmap(interface_exp_empty);
    al_destroy_bitmap(interface_exp_full);
    al_destroy_bitmap(interface_slot_large);
    al_destroy_bitmap(interface_slot_small);
    al_destroy_bitmap(interface_hp);
    al_destroy_bitmap(interface_mp);
    al_destroy_bitmap(interface_sp);
    al_destroy_bitmap(die_bg);
}


