#include "monster.h"

enum {STOP = 0, MOVE, ATK, DIE};
typedef struct Monster_stable{ // at most 10

    int width, height; // the width and height of image (stop type)

    ALLEGRO_BITMAP *img_move[3];
    ALLEGRO_BITMAP *img_die[3];
    ALLEGRO_BITMAP *img_atk[6];
    ALLEGRO_BITMAP *img_hp = NULL;
    ALLEGRO_BITMAP *img_hp_slot = NULL;
    ALLEGRO_SAMPLE *sample_monster_se = NULL;
    int img_hp_width,img_hp_slot_width;
    int wait_for_move;// after atk
    int move_time;

    //status
    int LV;
    int max_hp;
    int atk;
    int def;
    int speed;

}monster_stable;
typedef struct Monster_individual{ // at most 10
    int x, y;
    int standing_y;// use to judge damage
    bool dir; // left: false, right: true
    int state; // the state of character
    bool show;

    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;

    int num;

    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
    int move_time;
    int atk_time;
    int HP;
    int win_money;
    int win_EXP;
    int atk_on_chara_x, atk_on_chara_y;//random value

    bool atk_on_chara_show;

    int atk_on_chara_anime; // counting the time of animation
}monster_individual;
typedef struct Monster_atk_img_character{ // at most 10

}Monster_atk_img_character;
monster_stable stage2_monster1_status;
monster_individual stage2_monster1[10];
ALLEGRO_BITMAP *atk_on_character_img[4];
int time_count_spawn = 0;
int spawn_time = 60;//get_rand(420,780);
int now_monster_num;
int total_spawn_num;
void monster_init(int chara_LV){
    if(now_stage == 2){
        for(int i = 1 ; i <= 3 ; i++){
            char temp[50];
            sprintf( temp, "./image/monster/stage2/stage2_monster1_move%d.png", i );
            stage2_monster1_status.img_move[i-1] = al_load_bitmap(temp);
        }
        for(int i = 1 ; i <= 4 ; i++){
            char temp[50];
            sprintf( temp, "./image/monster/stage2/stage2_monster1_atk%d.png", i );
            stage2_monster1_status.img_atk[i-1] = al_load_bitmap(temp);
        }
        for(int i = 1 ; i <= 3 ; i++){
            char temp[50];
            sprintf( temp, "./image/monster/stage2/stage2_monster1_die%d.png", i );
            stage2_monster1_status.img_die[i-1] = al_load_bitmap(temp);
        }
        for(int i = 1 ; i <= 4 ; i++){
            char temp[70];
            sprintf( temp, "./image/monster/stage2/stage1_monster1_atk_on_character%d.png", i );
            atk_on_character_img[i-1] = al_load_bitmap(temp);
        }
        stage2_monster1_status.img_hp = al_load_bitmap("./image/monster/monster_hp_full.png");
        stage2_monster1_status.img_hp_slot = al_load_bitmap("./image/monster/monster_hp_slot.png");
        total_spawn_num = 0;
        now_monster_num = 0;
        // status init
        stage2_monster1_status.LV = chara_LV;
        stage2_monster1_status.max_hp = ceil(stage2_monster1_status.LV*sqrt(stage2_monster1_status.LV)*300);
        stage2_monster1_status.atk = ceil((double)stage2_monster1_status.LV*sqrt(stage2_monster1_status.LV)*30)+250;
        stage2_monster1_status.def = ceil(stage2_monster1_status.LV*stage2_monster1_status.LV*8);

        stage2_monster1_status.speed = 5;

        stage2_monster1_status.width = al_get_bitmap_width(stage2_monster1_status.img_move[0]);
        stage2_monster1_status.height = al_get_bitmap_height(stage2_monster1_status.img_move[0]);
        stage2_monster1_status.img_hp_width = al_get_bitmap_width(stage2_monster1_status.img_hp);
        stage2_monster1_status.img_hp_slot_width = al_get_bitmap_width(stage2_monster1_status.img_hp_slot);
        stage2_monster1_status.wait_for_move = 80;
        stage2_monster1_status.move_time = 80;

        stage2_monster1_status.sample_monster_se = al_load_sample("./sound/archer/archer_normal_atk.mp3");
        for(int i=0;i<10;i++){
            stage2_monster1[i].atk_Sound  = al_create_sample_instance(stage2_monster1_status.sample_monster_se);
            al_set_sample_instance_gain(stage2_monster1[i].atk_Sound, (float)sevolume/100);
            al_set_sample_instance_playmode(stage2_monster1[i].atk_Sound, ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(stage2_monster1[i].atk_Sound, al_get_default_mixer());

            stage2_monster1[i].state = STOP;
            stage2_monster1[i].dir = true;
            stage2_monster1[i].show = 0;
            stage2_monster1[i].anime = 0;
            stage2_monster1[i].anime_time = 120;
            stage2_monster1[i].move_time = 0;
            stage2_monster1[i].atk_time = 0;
            stage2_monster1[i].atk_on_chara_show = 0;
        }
    }
}

void monster_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps){
            time_count_spawn++;
            for(int i=0;i<10;i++){
                if(stage2_monster1[i].show){
                    stage2_monster1[i].anime++;
                    stage2_monster1[i].move_time++;
                    stage2_monster1[i].anime %= stage2_monster1[i].anime_time;
                    if(stage2_monster1[i].state == DIE && stage2_monster1[i].anime == stage2_monster1[i].anime_time-1){
                        stage2_monster1[i].show = 0;
                        stage2_monster1[i].atk_on_chara_show = 0;
                        now_monster_num--;
                    }
                    if(stage2_monster1[i].state != ATK)
                        stage2_monster1[i].atk_on_chara_show =0;
                    if(stage2_monster1[i].state == ATK || stage2_monster1[i].atk_time>60) {
                        if(stage2_monster1[i].atk_time==0){
                            stage2_monster1[i].atk_on_chara_x = get_rand(-25,25);
                            stage2_monster1[i].atk_on_chara_y = get_rand(20,30);
                        }
                        stage2_monster1[i].atk_time++;
                        if(stage2_monster1[i].atk_time >= 36 && stage2_monster1[i].atk_time <= 86){
                            stage2_monster1[i].atk_on_chara_show =1;
                            stage2_monster1[i].atk_on_chara_anime = stage2_monster1[i].atk_time-36;
                        }
                        else
                            stage2_monster1[i].atk_on_chara_show =0;
                        if(stage2_monster1[i].atk_time == 50 && get_chara_hp()>0)
                            damage_monster1_to_character(stage2_monster1[i].x,stage2_monster1[i].standing_y,stage2_monster1_status.width,170,stage2_monster1_status.atk-get_chara_def());
                        if(stage2_monster1[i].atk_time>= 154)
                            stage2_monster1[i].atk_time=0;
                    }
                }
            }
        }
    }
}

void monster_spawn(){
    if(now_monster_num<=10 && time_count_spawn == spawn_time){
        for(int i=0;i<10;i++){
            if(stage2_monster1[i].show == 0){
                total_spawn_num++;
                stage2_monster1[i].x = get_rand(get_stage_avail_lefttop_x(),get_stage_avail_lefttop_x()+get_stage_avail_width()-stage2_monster1_status.width);
                stage2_monster1[i].y = get_rand(get_stage_avail_lefttop_y()-stage2_monster1_status.height,get_stage_avail_lefttop_y()+get_stage_avail_heigth());
                stage2_monster1[i].standing_y = stage2_monster1[i].y + 418;
                stage2_monster1[i].show = 1;
                stage2_monster1[i].num = total_spawn_num;
                stage2_monster1[i].HP = stage2_monster1_status.max_hp;
                stage2_monster1[i].state = STOP;
                stage2_monster1[i].win_money = stage2_monster1_status.LV*get_rand(270,330);
                stage2_monster1[i].win_EXP = stage2_monster1_status.LV*get_rand(20,30);
                now_monster_num++;
                time_count_spawn = 0;
                spawn_time = get_rand(420,780);
                break;
            }
        }
    }

}

void monster_die(){
    for(int i=0;i<10;i++)
        if(stage2_monster1[i].show && stage2_monster1[i].HP <= 0){
            stage2_monster1[i].state = DIE;
            set_chara_money(get_chara_money()+stage2_monster1[i].win_money);
            set_chara_EXP(get_chara_exp()+stage2_monster1[i].win_EXP);
            stage2_monster1[i].win_money=0;
            stage2_monster1[i].win_EXP=0;
        }
}

void monster_update(int character_x,int character_width,int character_standing_y){
    if(now_stage == 2){
        monster_die();
        monster_spawn();
        for(int i=0;i<10;i++){
            if(get_chara_hp()<=0 && stage2_monster1[i].state != DIE){
                    stage2_monster1[i].state = STOP;
                    continue;
            }
            if(stage2_monster1[i].show && stage2_monster1[i].state != DIE){
                if(stage2_monster1[i].x+stage2_monster1_status.width>character_x-120 && stage2_monster1[i].x<character_x+character_width+120 && stage2_monster1[i].standing_y>=character_standing_y-100 &&stage2_monster1[i].standing_y<=character_standing_y+100){
                    stage2_monster1[i].move_time = stage2_monster1_status.move_time+1;
                    if(stage2_monster1[i].atk_time<=64  && get_chara_hp()>0)
                        stage2_monster1[i].state = ATK;
                    else
                        stage2_monster1[i].state = STOP;
                }
                else{
                    if(stage2_monster1[i].move_time <= stage2_monster1_status.move_time){
                        if(stage2_monster1[i].x<=character_x-120){
                            stage2_monster1[i].x += stage2_monster1_status.speed;
                            stage2_monster1[i].dir = true;
                            stage2_monster1[i].state = MOVE;
                        }
                        else if(stage2_monster1[i].x+stage2_monster1_status.width>=character_x+character_width+120){
                            stage2_monster1[i].x -= stage2_monster1_status.speed;
                            stage2_monster1[i].dir = false;
                            stage2_monster1[i].state = MOVE;
                        }
                        if(stage2_monster1[i].standing_y<=character_standing_y-100){
                            stage2_monster1[i].y += stage2_monster1_status.speed;
                            stage2_monster1[i].state = MOVE;
                        }
                        else if(stage2_monster1[i].standing_y>=character_standing_y+100){
                            stage2_monster1[i].y -= stage2_monster1_status.speed;
                            stage2_monster1[i].state = MOVE;
                        }
                        stage2_monster1[i].standing_y = stage2_monster1[i].y + 418;
                    }
                    else{
                        if(stage2_monster1[i].move_time <= stage2_monster1_status.move_time+stage2_monster1_status.wait_for_move)
                            stage2_monster1[i].state = STOP;
                        else
                            stage2_monster1[i].move_time = 0;
                    }
                }
            }
        }
        qsort(stage2_monster1,10,sizeof(monster_individual),monster_compare);
        for(;object_count<10;object_count++)
            if(stage2_monster1[object_count].standing_y>character_standing_y)
                break;

    }


    // follow character
}

void monster_draw(int start_draw,int end_draw,int camera_x,int camera_y){
    if(now_stage == 2 ){
        for(int i=start_draw;i<end_draw;i++){
            draw_stage2_monster1(camera_x,camera_y,i);
            monster_hp_draw(camera_x,camera_y,i);
        }
    }
}

void monster_hp_draw(int camera_x,int camera_y,int num){
    if(stage2_monster1[num].show){
        al_draw_bitmap(stage2_monster1_status.img_hp_slot, stage2_monster1[num].x - stage2_monster1_status.img_hp_slot_width/2 + stage2_monster1_status.width/2 - camera_x, stage2_monster1[num].y - camera_y - 30, 0);
        al_draw_bitmap_region(stage2_monster1_status.img_hp, 0, 0, round(((float)stage2_monster1[num].HP/(float)stage2_monster1_status.max_hp)*(float)256), 23,stage2_monster1[num].x - stage2_monster1_status.img_hp_width/2 + stage2_monster1_status.width/2 - camera_x, stage2_monster1[num].y - camera_y - 30,0);
    }
}

void monster_destory(){
    for(int i=0;i<3;i++)
        al_destroy_bitmap(stage2_monster1_status.img_move[i]);
    for(int i=0;i<3;i++)
        al_destroy_bitmap(stage2_monster1_status.img_die[i]);
    for(int i=0;i<6;i++)
        al_destroy_bitmap(stage2_monster1_status.img_atk[i]);
    for(int i=0;i<4;i++)
        al_destroy_bitmap(atk_on_character_img[i]);
    al_destroy_bitmap(stage2_monster1_status.img_hp);
    al_destroy_bitmap(stage2_monster1_status.img_hp_slot);
}



// status
int get_monster1_hp(int num){return stage2_monster1[num].HP;}
int get_monster1_def(int num){return stage2_monster1_status.def;}
int get_monster1_x(int num){
    if(stage2_monster1[num].dir)
        return stage2_monster1[num].x+16;
    else
        return stage2_monster1[num].x+34;
}//reset
int get_monster1_y(int num){return stage2_monster1[num].y+20;}
int get_monster1_standing_y(int num){return stage2_monster1[num].standing_y;}
int get_monster1_width(){return 260;}//reset
int get_monster1_heigth(){return stage2_monster1_status.height;}
bool get_monster1_show(int num){return stage2_monster1[num].show;}
bool get_monster1_if_die(int num){return (stage2_monster1[num].state == DIE);}

void set_monster1_hp(int value,int num){stage2_monster1[num].HP=value;}

// long code

void set_monster_volume(){
    for(int i=0;i<10;i++)
        al_set_sample_instance_gain(stage2_monster1[i].atk_Sound, (float)sevolume/100);
}

int monster_compare(const void *save1,const void *save2){
	monster_individual a = *(monster_individual *)save1;
	monster_individual b = *(monster_individual *)save2;
	if(a.standing_y==b.standing_y)
        return a.num-b.num;
    else
        return a.standing_y-b.standing_y;
}

void draw_stage2_monster1(int camera_x,int camera_y, int i){
    if(stage2_monster1[i].show){
        if( stage2_monster1[i].state == STOP ){
            stage2_monster1[i].anime_time = 120;
            if( stage2_monster1[i].dir )
                al_draw_bitmap(stage2_monster1_status.img_move[0], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, 0);
            else
                al_draw_bitmap(stage2_monster1_status.img_move[0], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
        }
        else if( stage2_monster1[i].state == MOVE ){
            stage2_monster1[i].anime_time = 30;
            if(stage2_monster1[i].dir){
                if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/3)
                    al_draw_bitmap(stage2_monster1_status.img_move[0], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, 0);
                else if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/3*2)
                    al_draw_bitmap(stage2_monster1_status.img_move[1], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, 0);
                else
                    al_draw_bitmap(stage2_monster1_status.img_move[2], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, 0);
            }
            else{
                if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/3)
                    al_draw_bitmap(stage2_monster1_status.img_move[0], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
                else if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/3*2)
                    al_draw_bitmap(stage2_monster1_status.img_move[1], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
                else
                    al_draw_bitmap(stage2_monster1_status.img_move[2], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }
        else if(stage2_monster1[i].state == ATK){
            stage2_monster1[i].anime_time = 64;
            if(stage2_monster1[i].dir){
                if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/8)
                    al_draw_bitmap(stage2_monster1_status.img_move[0], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, 0);
                else if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/8*2)
                    al_draw_bitmap(stage2_monster1_status.img_atk[0], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, 0);
                else if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/8*4)
                    al_draw_bitmap(stage2_monster1_status.img_atk[1], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, 0);
                else if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/8*5)
                    al_draw_bitmap(stage2_monster1_status.img_atk[2], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, 0);
                else
                    al_draw_bitmap(stage2_monster1_status.img_atk[3], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, 0);
            }
            else{
                if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/8)
                    al_draw_bitmap(stage2_monster1_status.img_move[0], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
                else if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/8*2)
                    al_draw_bitmap(stage2_monster1_status.img_atk[0], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
                else if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/8*4)
                    al_draw_bitmap(stage2_monster1_status.img_atk[1], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
                else if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/8*5)
                    al_draw_bitmap(stage2_monster1_status.img_atk[2], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
                else
                    al_draw_bitmap(stage2_monster1_status.img_atk[3], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }
        else if( stage2_monster1[i].state == DIE){
            stage2_monster1[i].anime_time = 80;
            if(stage2_monster1[i].dir){
                if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/8)
                    al_draw_bitmap(stage2_monster1_status.img_move[0], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, 0);
                else if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/8*3)
                    al_draw_bitmap(stage2_monster1_status.img_die[0], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, 0);
                else if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/8*4)
                    al_draw_bitmap(stage2_monster1_status.img_die[1], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, 0);
                else
                    al_draw_bitmap(stage2_monster1_status.img_die[2], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, 0);
            }
            else{
                if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/8)
                    al_draw_bitmap(stage2_monster1_status.img_move[0], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
                else if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/8*3)
                    al_draw_bitmap(stage2_monster1_status.img_die[0], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
                else if(stage2_monster1[i].anime < stage2_monster1[i].anime_time/8*4)
                    al_draw_bitmap(stage2_monster1_status.img_die[1], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
                else
                    al_draw_bitmap(stage2_monster1_status.img_die[2], stage2_monster1[i].x - camera_x, stage2_monster1[i].y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }
    }
}

void monster_atk_on_character_draw(int camera_x,int camera_y){
    for(int i=0;i<10;i++){
        if(stage2_monster1[i].atk_on_chara_show && get_chara_hp()>0){
            if(stage2_monster1[i].atk_on_chara_anime<50){
                    if(stage2_monster1[i].atk_on_chara_anime < 50/5)
                        al_draw_bitmap(atk_on_character_img[0], get_character_damage_x() - camera_x + stage2_monster1[i].atk_on_chara_x , get_character_standing_y() - camera_y - al_get_bitmap_height(atk_on_character_img[0]) + stage2_monster1[i].atk_on_chara_y, 0);
                    else if(stage2_monster1[i].atk_on_chara_anime < 50/5*2)
                        al_draw_bitmap(atk_on_character_img[1], get_character_damage_x()  - camera_x + stage2_monster1[i].atk_on_chara_x , get_character_standing_y() - camera_y - al_get_bitmap_height(atk_on_character_img[0]) + stage2_monster1[i].atk_on_chara_y, 0);
                    else if(stage2_monster1[i].atk_on_chara_anime < 50/5*3)
                        al_draw_bitmap(atk_on_character_img[2], get_character_damage_x()  - camera_x + stage2_monster1[i].atk_on_chara_x , get_character_standing_y() - camera_y - al_get_bitmap_height(atk_on_character_img[0]) + stage2_monster1[i].atk_on_chara_y, 0);
                    else if(stage2_monster1[i].atk_on_chara_anime < 50/5*4)
                        al_draw_bitmap(atk_on_character_img[3], get_character_damage_x()  - camera_x + stage2_monster1[i].atk_on_chara_x , get_character_standing_y() - camera_y - al_get_bitmap_height(atk_on_character_img[0]) + stage2_monster1[i].atk_on_chara_y, 0);
                    else
                        al_draw_bitmap(atk_on_character_img[1], get_character_damage_x()  - camera_x + stage2_monster1[i].atk_on_chara_x , get_character_standing_y() - camera_y - al_get_bitmap_height(atk_on_character_img[0]) + stage2_monster1[i].atk_on_chara_y, 0);

            }
        }
    }
}
