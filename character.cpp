#include "character.h"

// the state of character
enum {STOP = 0, MOVE, RUN, ATK,DIE};
typedef struct character
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    int standing_y;
    int height_fix;
    bool dir; // left: false, right: true
    int state; // the state of character
    int stop_time;

    bool if_normal_atk;

    bool check_atk;
    bool if_atk_complete;
    ALLEGRO_BITMAP *img_stand;
    ALLEGRO_BITMAP *img_move[3];
    ALLEGRO_BITMAP *img_atk[6];
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    Character_status *status = create_new_status();

    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation

    int potion_cooldown;
    bool if_drink_potion;
    long long int totle_time;
}Character;
Character chara;
ALLEGRO_SAMPLE *sample = NULL;
void character_init(){
    //initiate character status(newgame loadgame)
    if(enter_game_type == 1){
        if(create_career_type == 1)
            warrior_create_init(chara.status);
        else if(create_career_type == 2)
            archer_create_init(chara.status);
        else
            wizard_create_init(chara.status);
    }
    else{
        else_career_init(chara.status);
    }

    // load character images
    if(chara.status->career == 1){
        chara.img_stand = al_load_bitmap("./image/character/warrior/warrior_rest.png");
        for(int i = 1 ; i <= 3 ; i++){
            char temp[50];
            sprintf( temp, "./image/character/warrior/warrior_walk_%d.png", i );
            chara.img_move[i-1] = al_load_bitmap(temp);
        }
        for(int i = 1 ; i <= 3 ; i++){
            char temp[50];
            sprintf( temp, "./image/character/warrior/warrior_attack_%d.png", i );
            chara.img_atk[i-1] = al_load_bitmap(temp);
        }
    }
    else if(chara.status->career == 2){
        chara.img_stand = al_load_bitmap("./image/character/archer/archer_rest.png");
        for(int i = 1 ; i <= 3 ; i++){
            char temp[50];
            sprintf( temp, "./image/character/archer/archer_walk_%d.png", i );
            chara.img_move[i-1] = al_load_bitmap(temp);
        }
        for(int i = 1 ; i <= 6 ; i++){
            char temp[50];
            sprintf( temp, "./image/character/archer/archer_attack_%d.png", i );
            chara.img_atk[i-1] = al_load_bitmap(temp);
        }
    }
    // load effective sound
    if(chara.status->career == 1)
        sample = al_load_sample("./sound/warrior/warrior_normal_atk.wav");
    else if(chara.status->career == 2)
        sample = al_load_sample("./sound/archer/archer_normal_atk.mp3");


    chara.atk_Sound  = al_create_sample_instance(sample);
    al_set_sample_instance_gain(chara.atk_Sound, (float)sevolume/100);
    al_set_sample_instance_playmode(chara.atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(chara.atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    chara.width = al_get_bitmap_width(chara.img_move[0]);
    chara.height = al_get_bitmap_height(chara.img_move[0]);
    if(enter_game_type == 1){
        chara.x = get_stage_avail_lefttop_x()+50;
        chara.y = get_stage_avail_lefttop_y()+get_stage_avail_heigth()/2-chara.height;
    }
    chara.dir = true;
    chara.stop_time = 0;
    chara.if_atk_complete = 1;
    chara.height_fix = 0;
    chara.check_atk = 1;
    chara.if_normal_atk = 0;
    chara.if_drink_potion =0;
    chara.potion_cooldown =0;

    // initial the animation component
    chara.state = STOP;
    chara.anime = 0;
    chara.anime_time = 20;
    chara.totle_time = 0;
}
void character_process(ALLEGRO_EVENT event){
    // process the animation

    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            chara.anime++;
            chara.anime %= chara.anime_time;
        }
        if(chara.state == STOP)
            chara.stop_time++;

        chara.totle_time++;
        if(chara.status->career == 1 && chara.state == ATK && chara.anime==chara.anime_time-8)
            chara.if_normal_atk = 1;
    // process the keyboard event
        if(chara.if_drink_potion){
            chara.potion_cooldown++;
            if(chara.potion_cooldown == 30){
                chara.potion_cooldown=0;
                chara.if_drink_potion=0;
            }
        }
    }
    else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;

    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }



}
void character_update(){
    // use the idea of finite state machine to deal with different state
    int item_use =0;

    if(game_stop){
        chara.state = STOP;
        return;
    }
    if(chara.status->HP<=0){
        chara.state = DIE;
        return;
    }
    if( chara.state == MOVE )
        chara.stop_time = 0;
    else if (chara.state == RUN)
        chara.stop_time = 11;



    if((key_state[ALLEGRO_KEY_W] || key_state[ALLEGRO_KEY_A] || key_state[ALLEGRO_KEY_S] || key_state[ALLEGRO_KEY_D]) && chara.if_atk_complete && !key_state[ALLEGRO_KEY_SPACE]){

            if(chara.stop_time >0 && chara.stop_time <= 10 )
               chara.state = RUN;
            if(chara.status->SP <= 0)
                chara.state = MOVE;
            if(chara.state == RUN){
                if( key_state[ALLEGRO_KEY_W] ){
                    if(chara.y>get_stage_avail_lefttop_y() - chara.height)
                        chara.y -= chara.status->run_speed;
                    chara.state = RUN;
                }
                else if( key_state[ALLEGRO_KEY_S] ){
                    if(chara.y<get_stage_avail_lefttop_y() + get_stage_avail_heigth() - chara.height)
                        chara.y += chara.status->run_speed;
                    chara.state = RUN;
                }
                if( key_state[ALLEGRO_KEY_A] ){
                    chara.dir = false;
                    if(chara.x>get_stage_avail_lefttop_x())
                        chara.x -= chara.status->run_speed;
                    chara.state = RUN;
                }
                else if( key_state[ALLEGRO_KEY_D] ){
                    chara.dir = true;
                    if(chara.x<get_stage_avail_lefttop_x() + get_stage_avail_width() - chara.width)
                        chara.x += chara.status->run_speed;
                    chara.state = RUN;
                }
            }
            else{
                if( key_state[ALLEGRO_KEY_W] ){
                    if(chara.y>get_stage_avail_lefttop_y() - chara.height)
                        chara.y -= chara.status->speed;
                    chara.state = MOVE;
                }
                else if( key_state[ALLEGRO_KEY_S] ){
                    if(chara.y<get_stage_avail_lefttop_y() + get_stage_avail_heigth() - chara.height)
                        chara.y += chara.status->speed;
                    chara.state = MOVE;
                }
                if( key_state[ALLEGRO_KEY_A] ){
                    chara.dir = false;
                    if(chara.x>get_stage_avail_lefttop_x())
                        chara.x -= chara.status->speed;
                    chara.state = MOVE;
                }
                else if( key_state[ALLEGRO_KEY_D] ){
                    chara.dir = true;
                    if(chara.x<get_stage_avail_lefttop_x() + get_stage_avail_width() - chara.width)
                        chara.x += chara.status->speed;
                    chara.state = MOVE;
                }
            }

    }
    else{
        if( key_state[ALLEGRO_KEY_SPACE] && chara.if_atk_complete){
            chara.anime = 0;
            chara.state = ATK;
            chara.if_atk_complete = 0;
            chara.check_atk = 1;
            if(chara.status->career == 1)
                chara.height_fix = 105;
            else if(chara.status->career == 2)
                chara.height_fix = 35;
        }
        else if( chara.anime == chara.anime_time-1){
            chara.anime = 0;
            chara.state = STOP;
            chara.if_atk_complete =1 ;
            chara.height_fix = 0;
        }
        else if ( chara.anime == 0){
            chara.state = STOP;
            chara.if_atk_complete =1 ;
        }
    }

    if( key_state[ALLEGRO_KEY_1] && chara.if_drink_potion==0){
        item_use = 0;
        chara.if_drink_potion = 1;
    }
    else if( key_state[ALLEGRO_KEY_2] && chara.if_drink_potion==0){
        item_use = 1;
        chara.if_drink_potion = 1;
    }
    else if( key_state[ALLEGRO_KEY_3] && chara.if_drink_potion==0){
        item_use = 2;
        chara.if_drink_potion = 1;
    }
    else if( key_state[ALLEGRO_KEY_4] && chara.if_drink_potion==0){
        item_use = 3;
        chara.if_drink_potion = 1;
    }
    else if( key_state[ALLEGRO_KEY_5] && chara.if_drink_potion==0){
        item_use = 4;
        chara.if_drink_potion = 1;
    }
    else if( key_state[ALLEGRO_KEY_6] && chara.if_drink_potion==0){
        item_use = 5;
        chara.if_drink_potion = 1;
    }
    else if( key_state[ALLEGRO_KEY_7] && chara.if_drink_potion==0){
        item_use = 6;
        chara.if_drink_potion = 1;
    }
    else if( key_state[ALLEGRO_KEY_8] && chara.if_drink_potion==0){
        item_use = 7;
        chara.if_drink_potion = 1;
    }
    else if( key_state[ALLEGRO_KEY_9] && chara.if_drink_potion==0){
        item_use = 8;
        chara.if_drink_potion = 1;
    }
    if( key_state[ALLEGRO_KEY_Y])
        skill_key_call(0);
    else if( key_state[ALLEGRO_KEY_U])
        skill_key_call(1);
    else if( key_state[ALLEGRO_KEY_I])
        skill_key_call(2);
    else if( key_state[ALLEGRO_KEY_O])
        skill_key_call(3);
    else if( key_state[ALLEGRO_KEY_P])
        skill_key_call(4);
    else if( key_state[ALLEGRO_KEY_H])
        skill_key_call(5);
    else if( key_state[ALLEGRO_KEY_J])
        skill_key_call(6);
    else if( key_state[ALLEGRO_KEY_K])
        skill_key_call(7);
    else if( key_state[ALLEGRO_KEY_L])
        skill_key_call(8);


    // status update(nature)
    character_nature_recovering();
    chara.standing_y = chara.y+chara.height;
    if(now_stage == 2){
        if(chara.if_normal_atk && chara.status->career == 1){
            if(chara.dir)
                damage_to_monster1(chara.x+196,chara.standing_y,209,30,3,chara.status->atk + get_equipment_total_atk());
            else
                damage_to_monster1(chara.x+5,chara.standing_y,209,30,3,chara.status->atk + get_equipment_total_atk());
            chara.if_normal_atk = 0;
        }
        else if(chara.status->career == 2){
            remote_atk_damage(chara.status->atk + get_equipment_total_atk());
        }
        atk_skill_damage(chara.status->atk + get_equipment_total_atk());
    }
    if(chara.potion_cooldown == 0 && chara.if_drink_potion && !get_item_using_ifempty(item_use))
        use_item(get_item_using_index(item_use),1,1);
    // attack



    // here be the damage, mp cost, special effect, item using function

    character_status_check();
    check_lv_up(chara.status);

}

void character_draw(int camera_x,int camera_y){
    if(chara.state == DIE)
        return;
    // with the state, draw corresponding image
    if(chara.status->career == 1)
        warrior_draw(camera_x,camera_y);
    else if (chara.status->career == 2)
        archer_draw(camera_x,camera_y);
}

void character_destory(){
    for(int i=0;i<6;i++)
        al_destroy_bitmap(chara.img_atk[i]);
    for(int i=0;i<3;i++)
        al_destroy_bitmap(chara.img_move[i]);
    al_destroy_bitmap(chara.img_stand);
    al_destroy_sample_instance(chara.atk_Sound);

}


void character_set_sevolume(){
    al_set_sample_instance_gain(chara.atk_Sound, (float)sevolume/100);
}
void set_character_pos(int x,int y){chara.x=x;chara.y=y;}
void character_reborn(){
    chara.status->HP = chara.status->max_HP + get_equipment_total_hp();
    chara.status->MP = chara.status->max_MP + get_equipment_total_mp();
    chara.status->SP = chara.status->max_SP;
    chara.state = STOP;
}
void character_nature_recovering(){
    if(chara.state == RUN && chara.totle_time % 10 == 0 && chara.status->SP > 0)
        chara.status->SP -= 5;
    if(chara.state == STOP || chara.state == MOVE || chara.state == ATK)
        if(chara.totle_time % 10 == 0)
            chara.status->SP += 5;
    if(chara.totle_time % 600 == 0){
        chara.status->HP += (chara.status->max_HP)/20;
        chara.status->MP += (chara.status->max_MP)/20;
    }
}
void character_status_check(){
    if(chara.status->SP > chara.status->max_SP)
        chara.status->SP = chara.status->max_SP;
    if(chara.status->HP > chara.status->max_HP + get_equipment_total_hp())
        chara.status->HP = chara.status->max_HP + get_equipment_total_hp();
    if(chara.status->MP > chara.status->max_MP + get_equipment_total_mp())
        chara.status->MP = chara.status->max_MP + get_equipment_total_mp();
    if(chara.status->SP < 0)
        chara.status->SP = 0;

}
//-----------------------------get value--------------------------
int get_character_x(){return chara.x;}
int get_character_y(){return chara.y;}
int get_character_standing_y(){return chara.standing_y;}
int get_character_width(){return chara.width;}
int get_character_heigth(){return chara.height;}
int get_character_damage_x(){
    if(chara.dir){
        if(chara.status->career == 1)
            return chara.x+19;
        else if(chara.status->career == 2)
            return chara.x+67;
    }
    else{
        if(chara.status->career == 1)
            return chara.x+165;
        else if(chara.status->career == 2)
            return chara.x+84;
    }
}
int get_character_damage_width(){return 145;}

void set_chara_career(int value){chara.status->career = value;}
void set_chara_LV(int value){chara.status->LV = value;}
void set_chara_maxHP(int value){chara.status->max_HP = value;}
void set_chara_maxMP(int value){chara.status->max_MP = value;}
void set_chara_maxEXP(int value){chara.status->max_exp = value;}
void set_chara_HP(int value){chara.status->HP = value;}
void set_chara_MP(int value){chara.status->MP = value;}
void set_chara_EXP(int value){chara.status->exp = value;}
void set_chara_atk(int value){chara.status->atk = value;}
void set_chara_def(int value){chara.status->def = value;}
void set_chara_atkP(int value){chara.status->atkP = value;}
void set_chara_money(int value){chara.status->money = value;}
void set_chara_skill_point(int value){chara.status->skill_point = value;}
void set_chara_skill(int i,int value){chara.status->skill[i] = value;}
void set_chara_speed(int value){chara.status->speed = value;}
void set_chara_run_speed(int value){chara.status->run_speed = value;}
// interface use
int get_chara_career(){return chara.status->career;}
int get_chara_lv(){return chara.status->LV;}
int get_chara_hp(){return chara.status->HP;}
int get_chara_maxhp(){return chara.status->max_HP+get_equipment_total_hp();}
int get_chara_real_maxhp(){return chara.status->max_HP;}
int get_chara_mp(){return chara.status->MP;}
int get_chara_maxmp(){return chara.status->max_MP+get_equipment_total_mp();}
int get_chara_real_maxmp(){return chara.status->max_MP;}
int get_chara_sp(){return chara.status->SP;}
int get_chara_exp(){return chara.status->exp;}
int get_chara_maxexp(){return chara.status->max_exp;}
int get_chara_atk(){return chara.status->atk+get_equipment_total_atk();}
int get_chara_def(){return chara.status->def+get_equipment_total_def();}
int get_chara_atkP(){return chara.status->atkP+get_equipment_total_atkP();}
int get_chara_real_atk(){return chara.status->atk;}
int get_chara_real_def(){return chara.status->def;}
int get_chara_real_atkP(){return chara.status->atkP;}
int get_chara_speed(){return chara.status->speed;}
int get_chara_run_speed(){return chara.status->run_speed;}
int get_chara_money(){return chara.status->money;}
int get_chara_skill_point(){return chara.status->skill_point;}
int get_chara_skill(int i){return chara.status->skill[i];}
bool get_chara_dir(){return chara.dir;}
//-----------------------------set character draw position--------------------------
void warrior_draw(int camera_x,int camera_y){
    if( chara.state == STOP ){
        if( chara.dir )
            al_draw_bitmap(chara.img_stand, chara.x - camera_x, chara.y - camera_y, 0);
        else
            al_draw_bitmap(chara.img_stand, chara.x - camera_x, chara.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
    }
    else if( chara.state == RUN ){
        chara.anime_time = 20;
        if( chara.dir ){
            if( chara.anime < chara.anime_time/4 ){
                al_draw_bitmap(chara.img_move[0], chara.x - camera_x, chara.y - camera_y, 0);
            }else if( chara.anime < chara.anime_time/4 * 2){
                al_draw_bitmap(chara.img_move[1], chara.x - camera_x, chara.y - camera_y, 0);
            }
            else if( chara.anime < chara.anime_time/4 * 3){
                al_draw_bitmap(chara.img_move[2], chara.x - camera_x, chara.y - camera_y, 0);
            }
            else{
                al_draw_bitmap(chara.img_move[1], chara.x - camera_x, chara.y - camera_y, 0);
            }
        }else{
            if( chara.anime < chara.anime_time/4 ){
                al_draw_bitmap(chara.img_move[0], chara.x - camera_x, chara.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            }else if( chara.anime < chara.anime_time/4 * 2){
                al_draw_bitmap(chara.img_move[1], chara.x - camera_x, chara.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else if( chara.anime < chara.anime_time/4 * 3){
                al_draw_bitmap(chara.img_move[2], chara.x - camera_x, chara.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else{
                al_draw_bitmap(chara.img_move[1], chara.x - camera_x, chara.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }
    }
    else if( chara.state == ATK ){
        chara.anime_time = 36;

        if( chara.dir ){
            if( chara.anime < chara.anime_time/4 ){
                al_draw_bitmap(chara.img_atk[0], chara.x - camera_x, chara.y - camera_y - chara.height_fix, 0);
            }
            else if( chara.anime < chara.anime_time/4*2 ){
                al_draw_bitmap(chara.img_atk[1], chara.x - camera_x, chara.y - camera_y - chara.height_fix, 0);
            }
            else{
                al_draw_bitmap(chara.img_atk[2], chara.x - camera_x, chara.y - camera_y - chara.height_fix, 0);
                al_play_sample_instance(chara.atk_Sound);

            }
        }else{
            if( chara.anime < chara.anime_time/4 ){
                al_draw_bitmap(chara.img_atk[0], chara.x - camera_x, chara.y - camera_y - chara.height_fix, ALLEGRO_FLIP_HORIZONTAL);
            }
            else if( chara.anime < chara.anime_time/4*2 ){
                al_draw_bitmap(chara.img_atk[1], chara.x - camera_x, chara.y - camera_y - chara.height_fix, ALLEGRO_FLIP_HORIZONTAL);
            }
            else{
                al_draw_bitmap(chara.img_atk[2], chara.x - camera_x, chara.y - camera_y - chara.height_fix, ALLEGRO_FLIP_HORIZONTAL);
                al_play_sample_instance(chara.atk_Sound);
            }
        }
    }
    else if(chara.state == MOVE){
        chara.anime_time = 20;
        if( chara.dir ){
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[1], chara.x - camera_x, chara.y - camera_y, 0);
            }else{
                al_draw_bitmap(chara.img_move[2], chara.x - camera_x, chara.y - camera_y, 0);
            }
        }else{
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[1], chara.x - camera_x, chara.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(chara.img_move[2], chara.x - camera_x, chara.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }
    }
}
void archer_draw(int camera_x,int camera_y){
    if( chara.state == STOP ){
        if( chara.dir )
            al_draw_bitmap(chara.img_stand, chara.x - camera_x, chara.y - camera_y, 0);
        else
            al_draw_bitmap(chara.img_stand, chara.x - camera_x, chara.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
    }
    else if( chara.state == RUN ){
        chara.anime_time = 20;
        if( chara.dir ){
            if( chara.anime < chara.anime_time/4 ){
                al_draw_bitmap(chara.img_move[0], chara.x - camera_x, chara.y - camera_y, 0);
            }else if( chara.anime < chara.anime_time/4 * 2){
                al_draw_bitmap(chara.img_move[1], chara.x - camera_x, chara.y - camera_y, 0);
            }
            else if( chara.anime < chara.anime_time/4 * 3){
                al_draw_bitmap(chara.img_move[2], chara.x - camera_x, chara.y - camera_y, 0);
            }
            else{
                al_draw_bitmap(chara.img_move[2], chara.x - camera_x, chara.y - camera_y, 0);
            }
        }else{
            if( chara.anime < chara.anime_time/4 ){
                al_draw_bitmap(chara.img_move[0], chara.x - camera_x, chara.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            }else if( chara.anime < chara.anime_time/4 * 2){
                al_draw_bitmap(chara.img_move[1], chara.x - camera_x, chara.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else if( chara.anime < chara.anime_time/4 * 3){
                al_draw_bitmap(chara.img_move[2], chara.x - camera_x, chara.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else{
                al_draw_bitmap(chara.img_move[2], chara.x - camera_x, chara.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }
    }
    else if( chara.state == ATK ){
        chara.anime_time = 36;

        if( chara.dir ){
            if( chara.anime < chara.anime_time/6 ){
                al_draw_bitmap(chara.img_atk[0], chara.x - camera_x, chara.y - camera_y - chara.height_fix, 0);
            }
            else if( chara.anime < chara.anime_time/6*2 ){
                al_draw_bitmap(chara.img_atk[1], chara.x - camera_x, chara.y - camera_y - chara.height_fix, 0);
            }
            else if( chara.anime < chara.anime_time/6*3 ){
                al_draw_bitmap(chara.img_atk[2], chara.x - camera_x, chara.y - camera_y - chara.height_fix, 0);
            }
            else if( chara.anime < chara.anime_time/6*4 ){
                al_draw_bitmap(chara.img_atk[3], chara.x - camera_x, chara.y - camera_y - chara.height_fix, 0);
            }
            else if( chara.anime < chara.anime_time/6*5 ){
                al_draw_bitmap(chara.img_atk[4], chara.x - camera_x, chara.y - camera_y - chara.height_fix, 0);
                al_play_sample_instance(chara.atk_Sound);
            }
            else{
                al_draw_bitmap(chara.img_atk[5], chara.x - camera_x, chara.y - camera_y - chara.height_fix, 0);
                if(chara.check_atk){
                    remote_atk_call(chara.x , chara.y - chara.height_fix,chara.standing_y,  chara.dir);
                    chara.check_atk= 0;
                }
            }
        }else{
            if( chara.anime < chara.anime_time/6 ){
                al_draw_bitmap(chara.img_atk[0], chara.x - camera_x, chara.y - camera_y - chara.height_fix, ALLEGRO_FLIP_HORIZONTAL);
            }
            else if( chara.anime < chara.anime_time/6*2 ){
                al_draw_bitmap(chara.img_atk[1], chara.x - camera_x, chara.y - camera_y - chara.height_fix, ALLEGRO_FLIP_HORIZONTAL);
            }
            else if( chara.anime < chara.anime_time/6*3 ){
                al_draw_bitmap(chara.img_atk[2], chara.x - camera_x, chara.y - camera_y - chara.height_fix, ALLEGRO_FLIP_HORIZONTAL);
            }
            else if( chara.anime < chara.anime_time/6*4 ){
                al_draw_bitmap(chara.img_atk[3], chara.x - camera_x, chara.y - camera_y - chara.height_fix, ALLEGRO_FLIP_HORIZONTAL);
            }
            else if( chara.anime < chara.anime_time/6*5 ){
                al_draw_bitmap(chara.img_atk[4], chara.x - camera_x, chara.y - camera_y - chara.height_fix, ALLEGRO_FLIP_HORIZONTAL);
                al_play_sample_instance(chara.atk_Sound);
            }
            else{
                al_draw_bitmap(chara.img_atk[5], chara.x - camera_x, chara.y - camera_y - chara.height_fix, ALLEGRO_FLIP_HORIZONTAL);
                if(chara.check_atk){
                    remote_atk_call(chara.x , chara.y - chara.height_fix, chara.standing_y,  chara.dir);
                    chara.check_atk=0;
                }
            }
        }
    }
    else if(chara.state == MOVE){
        chara.anime_time = 20;
        if( chara.dir ){
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[0], chara.x - camera_x, chara.y - camera_y, 0);
            }else{
                al_draw_bitmap(chara.img_move[1], chara.x - camera_x, chara.y - camera_y, 0);
            }
        }else{
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[0], chara.x - camera_x, chara.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(chara.img_move[1], chara.x - camera_x, chara.y - camera_y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }
    }
}
