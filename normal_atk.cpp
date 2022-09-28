#include "normal_atk.h"

typedef struct Remote_atk{
    int x[2], y[2]; // the position of image
    int width, height; // the width and height of image
    bool show[2];// 0=hide 1=display
    bool dir[2];
    int display_time[2];
    int flying_time;
    int flying_speed;

    int effective_y;
    int standing_y[2];
    ALLEGRO_BITMAP *img = NULL;
}Remote_atk;
Remote_atk remote_atk;

void remote_atk_init(int career){
    if(career == 2){
        remote_atk.img = al_load_bitmap("./image/character/archer/archer_attack_arrow.png");
        remote_atk.flying_time = 40;
        remote_atk.flying_speed = 30;
    }

    remote_atk.width = al_get_bitmap_width(remote_atk.img);
    remote_atk.height = al_get_bitmap_height(remote_atk.img);
    for(int i=0;i<2;i++){
        remote_atk.display_time[i] = 0;
        remote_atk.show[i] = 0;
    }

}
void remote_atk_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_TIMER )
        if( event.timer.source == fps)
            for(int i=0;i<2;i++)
                if(remote_atk.show[i])
                    remote_atk.display_time[i]++;

}
void remote_atk_update(){
    for(int i=0;i<2;i++){
        if(remote_atk.show[i]){
            if(remote_atk.dir[i])
                remote_atk.x[i] += remote_atk.flying_speed;
            else
                remote_atk.x[i] -= remote_atk.flying_speed;
            if(remote_atk.display_time[i]>=remote_atk.flying_time){
                remote_atk.show[i]=0;
                remote_atk.display_time[i]=0;
            }
        }

    }
}
void remote_atk_draw(int camera_x,int camera_y){
    for(int i=0;i<2;i++){
        if(remote_atk.show[i]){
            if(remote_atk.dir[i])
                al_draw_bitmap(remote_atk.img, remote_atk.x[i] - camera_x, remote_atk.y[i] - camera_y, 0);
            else
                al_draw_bitmap(remote_atk.img, remote_atk.x[i] - camera_x, remote_atk.y[i] - camera_y, ALLEGRO_FLIP_HORIZONTAL);
        }
    }
}
void remote_atk_call(int character_x,int character_y,int standing_y,bool dir){
    for(int i=0;i<2;i++){
        if(remote_atk.show[i] == 0){
            if(dir)
                remote_atk.x[i]=character_x+182;
            else
                remote_atk.x[i]=character_x;
            remote_atk.y[i]=character_y+140;
            remote_atk.standing_y[i]=standing_y;
            remote_atk.dir[i]=dir;
            remote_atk.show[i]=1;
            break;
        }
    }
}
void remote_atk_damage(int damage){
    for(int i=0;i<2;i++){
        if(remote_atk.show[i] == 1 && remote_atk.display_time[i]>0){
            if(damage_to_monster1(remote_atk.x[i],remote_atk.standing_y[i],remote_atk.width,50,1,damage)){
                remote_atk.show[i]=0;
                remote_atk.display_time[i]=0;
            }
        }
    }
}
void remote_atk_destroy(){
    al_destroy_bitmap(remote_atk.img);
}
