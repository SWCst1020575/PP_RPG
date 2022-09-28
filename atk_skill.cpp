#include "atk_skill.h"

typedef struct Skill_effect{
    int x,y;
    int standing_y;
    int damage;
    int time;
    int cool_down;
    int mp_cost;
    int skill_level;
    bool show;
    bool dir;

    //static
    int affect_height;//basic
    int atk_num;
    int atk_times;
    int flying_speed;
    int effect_time;
    int skill_cool_down;
    int width;
    ALLEGRO_BITMAP *img[4];
}skill_effect;
skill_effect warrior_skill_1;
skill_effect warrior_skill_2;

void atk_skill_init(){
    warrior_skill_1.show=0;
    warrior_skill_2.show=0;
    if(get_chara_career()==1){
        warrior_skill_1.affect_height = 50;
        warrior_skill_1.atk_times = 2;
        warrior_skill_1.atk_num = 2;
        warrior_skill_1.time= 0;
        warrior_skill_1.cool_down = 0;
        warrior_skill_1.skill_cool_down = 300;
        warrior_skill_1.flying_speed = 30;
        warrior_skill_1.effect_time = 36;
        for(int i=0;i<4;i++){
            char temp[50];
            sprintf( temp, "./image/skill/warrior/warrior_skill1_%d.png", i+1 );
            warrior_skill_1.img[i] = al_load_bitmap(temp);
        }
        warrior_skill_1.width = al_get_bitmap_width(warrior_skill_1.img[0]);


        warrior_skill_2.affect_height = 120;
        warrior_skill_2.atk_times = 4;
        warrior_skill_2.atk_num = 99;
        warrior_skill_2.time= 0;
        warrior_skill_2.cool_down = 0;
        warrior_skill_2.skill_cool_down = 600;
        warrior_skill_2.effect_time = 36;
        for(int i=0;i<4;i++){
            char temp[50];
            sprintf( temp, "./image/skill/warrior/warrior_skill2_%d.png", i+1 );
            warrior_skill_2.img[i] = al_load_bitmap(temp);
        }
        warrior_skill_2.width = al_get_bitmap_width(warrior_skill_2.img[0]);
    }

}
void atk_skill_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_TIMER )
        if( event.timer.source == fps){
            if(get_chara_career() == 1){
                if(warrior_skill_1.cool_down>0)
                    warrior_skill_1.cool_down--;
                if(warrior_skill_2.cool_down>0)
                    warrior_skill_2.cool_down--;
                if(warrior_skill_1.show)
                    warrior_skill_1.time++;
                if(warrior_skill_2.show)
                    warrior_skill_2.time++;
            }
        }
}
void skill_call(int character_x,int character_y,int standing_y,bool dir,int skill_index){
    if(get_chara_career() == 1){
        if(warrior_skill_1.cool_down == 0 && skill_index == 0 && warrior_skill_1.show == 0){
            warrior_skill_1.skill_level=get_chara_skill(0);
            warrior_skill_1.mp_cost = 50 + warrior_skill_1.skill_level * 5;
            warrior_skill_1.x=character_x-30;
            warrior_skill_1.y=character_y+32;
            warrior_skill_1.standing_y=standing_y;
            warrior_skill_1.dir=dir;
            warrior_skill_1.show=1;
            set_chara_MP(get_chara_mp()-warrior_skill_1.mp_cost);
        }
        if(warrior_skill_2.cool_down == 0 && skill_index == 1 && warrior_skill_2.show == 0){
            warrior_skill_2.skill_level=get_chara_skill(1);
            warrior_skill_2.mp_cost = 100 + warrior_skill_2.skill_level * 10;
            warrior_skill_2.x=character_x-417;
            warrior_skill_2.y=character_y-232;
            warrior_skill_2.standing_y=standing_y;
            warrior_skill_2.dir=dir;
            warrior_skill_2.show=1;
            set_chara_MP(get_chara_mp()-warrior_skill_2.mp_cost);
        }
    }
}
void atk_skill_update(){
    if(warrior_skill_1.show){
        if(warrior_skill_1.dir)
            warrior_skill_1.x += warrior_skill_1.flying_speed;
        else
            warrior_skill_1.x -= warrior_skill_1.flying_speed;
        if(warrior_skill_1.time>=warrior_skill_1.effect_time){
            warrior_skill_1.show=0;
            warrior_skill_1.time=0;
            warrior_skill_1.cool_down=warrior_skill_1.skill_cool_down;
        }
    }
    if(warrior_skill_2.show){
        if(get_chara_dir())
            warrior_skill_2.x=get_character_x()-417;
        else
            warrior_skill_2.x=get_character_x()-295;
        warrior_skill_2.y=get_character_y()-232;
        warrior_skill_2.standing_y=get_character_standing_y();
    }
    if(warrior_skill_2.show == 1 && warrior_skill_2.time >= warrior_skill_2.effect_time){
        warrior_skill_2.cool_down=warrior_skill_2.skill_cool_down;
        warrior_skill_2.show=0;
        warrior_skill_2.time=0;
        warrior_skill_2.cool_down=warrior_skill_2.skill_cool_down;
    }
}
void atk_skill_damage(int damage){
    if(get_chara_career()==1){
        if(warrior_skill_1.show == 1 && warrior_skill_1.time>0){
            warrior_skill_1.damage = (1+(double)warrior_skill_1.skill_level*0.4)*damage;
            if(damage_to_monster1(warrior_skill_1.x,warrior_skill_1.standing_y,warrior_skill_1.width,warrior_skill_1.affect_height,warrior_skill_1.atk_num,warrior_skill_1.damage)){
                for(int i=0;i<warrior_skill_1.atk_times-1;i++)
                    damage_to_monster1(warrior_skill_1.x,warrior_skill_1.standing_y,warrior_skill_1.width,warrior_skill_1.affect_height,warrior_skill_1.atk_num,warrior_skill_1.damage);
                warrior_skill_1.cool_down=warrior_skill_1.skill_cool_down;
                warrior_skill_1.show=0;
                warrior_skill_1.time=0;
            }
        }
        if(warrior_skill_2.show == 1 && warrior_skill_2.time == warrior_skill_2.effect_time/2){
            warrior_skill_2.damage = (2+(double)warrior_skill_2.skill_level*0.3)*damage;
            for(int i=0;i<warrior_skill_2.atk_times;i++)
                damage_to_monster1(warrior_skill_2.x,warrior_skill_2.standing_y,warrior_skill_2.width,warrior_skill_2.affect_height,warrior_skill_2.atk_num,warrior_skill_2.damage);
        }
    }

}
void atk_skill_draw(int camera_x,int camera_y){

    if(warrior_skill_1.show){
        if(warrior_skill_1.dir){
            if(warrior_skill_1.time <= warrior_skill_1.effect_time/4)
                al_draw_bitmap(warrior_skill_1.img[0], warrior_skill_1.x - camera_x, warrior_skill_1.y - camera_y, 0);
            else if(warrior_skill_1.time <= warrior_skill_1.effect_time/4*2)
                al_draw_bitmap(warrior_skill_1.img[1], warrior_skill_1.x - camera_x, warrior_skill_1.y - camera_y, 0);
            else if(warrior_skill_1.time <= warrior_skill_1.effect_time/4*3)
                al_draw_bitmap(warrior_skill_1.img[2], warrior_skill_1.x - camera_x, warrior_skill_1.y - camera_y, 0);
            else
                al_draw_bitmap(warrior_skill_1.img[3], warrior_skill_1.x - camera_x, warrior_skill_1.y - camera_y, 0);
        }
        else{
            if(warrior_skill_1.time <= warrior_skill_1.effect_time/4)
                al_draw_bitmap(warrior_skill_1.img[0], warrior_skill_1.x - camera_x, warrior_skill_1.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            else if(warrior_skill_1.time <= warrior_skill_1.effect_time/4*2)
                al_draw_bitmap(warrior_skill_1.img[1], warrior_skill_1.x - camera_x, warrior_skill_1.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            else if(warrior_skill_1.time <= warrior_skill_1.effect_time/4*3)
                al_draw_bitmap(warrior_skill_1.img[2], warrior_skill_1.x - camera_x, warrior_skill_1.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            else
                al_draw_bitmap(warrior_skill_1.img[3], warrior_skill_1.x - camera_x, warrior_skill_1.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
        }
    }
    if(warrior_skill_2.show){
        if(warrior_skill_2.dir){
            if(warrior_skill_2.time <= warrior_skill_2.effect_time/4)
                al_draw_bitmap(warrior_skill_2.img[0], warrior_skill_2.x - camera_x, warrior_skill_2.y - camera_y, 0);
            else if(warrior_skill_2.time <= warrior_skill_2.effect_time/4*2)
                al_draw_bitmap(warrior_skill_2.img[1], warrior_skill_2.x - camera_x, warrior_skill_2.y - camera_y, 0);
            else if(warrior_skill_2.time <= warrior_skill_2.effect_time/4*3)
                al_draw_bitmap(warrior_skill_2.img[2], warrior_skill_2.x - camera_x, warrior_skill_2.y - camera_y, 0);
            else
                al_draw_bitmap(warrior_skill_2.img[3], warrior_skill_2.x - camera_x, warrior_skill_2.y - camera_y, 0);
        }
        else{
            if(warrior_skill_2.time <= warrior_skill_2.effect_time/4)
                al_draw_bitmap(warrior_skill_2.img[0], warrior_skill_2.x - camera_x, warrior_skill_2.y - camera_y, 0);
            else if(warrior_skill_2.time <= warrior_skill_2.effect_time/4*2)
                al_draw_bitmap(warrior_skill_2.img[1], warrior_skill_2.x - camera_x, warrior_skill_2.y - camera_y, 0);
            else if(warrior_skill_2.time <= warrior_skill_2.effect_time/4*3)
                al_draw_bitmap(warrior_skill_2.img[2], warrior_skill_2.x - camera_x, warrior_skill_2.y - camera_y, 0);
            else
                al_draw_bitmap(warrior_skill_2.img[3], warrior_skill_2.x - camera_x, warrior_skill_2.y - camera_y, 0);
        }
    }
}
void atk_skill_destroy(){
    if(get_chara_career()==1){
        for(int i=0;i<4;i++){
            al_destroy_bitmap(warrior_skill_1.img[i]);
            al_destroy_bitmap(warrior_skill_2.img[i]);
        }
    }
}
