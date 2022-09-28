#include "camera.h"


typedef struct Camera{
    int x;
    int y;
    bool character_trace;
    bool camera_lock;
};
Camera camera;

void stage_camera_init(int stage_num){
    camera.camera_lock = 1;
    if(stage_num == 1){
        camera.x = get_stage_avail_lefttop_x();
        camera.y = get_character_y() + get_character_heigth() + 150 - HEIGHT;
        camera.character_trace = true;
    }
    else if(stage_num == 2){
        camera.x = get_stage_avail_lefttop_x();
        camera.y = get_character_y() + get_character_heigth() + 150 - HEIGHT;
        camera.character_trace = true;
    }
}
void camera_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        if(key_state[ALLEGRO_KEY_G]){
            camera.camera_lock = !camera.camera_lock;
            camera.character_trace = !camera.character_trace;
        }
    }
}
void camera_update(){
    trace_character(now_stage);
    if(camera.camera_lock == 0){
        if(key_state[ALLEGRO_KEY_UP])
            camera.y-=20;
        else if(key_state[ALLEGRO_KEY_DOWN])
            camera.y+=20;
        if(key_state[ALLEGRO_KEY_LEFT])
            camera.x-=20;
        else if(key_state[ALLEGRO_KEY_RIGHT])
            camera.x+=20;

        if(camera.x < 0)
            camera.x = 0;
        if(camera.x > get_stage_width() - WIDTH)
            camera.x = get_stage_width() - WIDTH;
        if(camera.y < 0)
            camera.y = 0;
        if(camera.y > get_stage_height() - HEIGHT)
            camera.y = get_stage_height() - HEIGHT;
    }
}
void trace_character(int stage_num){
    if(camera.character_trace){
        if(stage_num == 1){
            if(get_character_x() < (get_stage_avail_lefttop_x() + WIDTH/2) - get_character_width()/2)
                camera.x = get_stage_avail_lefttop_x();
            else if(get_character_x() > (get_stage_avail_lefttop_x() + get_stage_avail_width() - WIDTH/2 - get_character_width()/2 + 400))
                camera.x = get_stage_avail_lefttop_x() + get_stage_avail_width() - WIDTH + 400;
            else
                camera.x = get_character_x() - WIDTH/2  + get_character_width()/2 ;

            if(get_character_y() < get_stage_avail_lefttop_y() + get_stage_avail_heigth() - 150 - get_character_heigth())
                camera.y = get_character_y() + get_character_heigth() + 150 - HEIGHT;
            else
                camera.y = get_stage_avail_lefttop_y() + get_stage_avail_heigth() - HEIGHT;
        }
        else if(stage_num == 2){
            if(get_character_x() < (get_stage_avail_lefttop_x() + WIDTH/2) - get_character_width()/2)
                camera.x = get_stage_avail_lefttop_x();
            else if(get_character_x() > (get_stage_avail_lefttop_x() + get_stage_avail_width() - WIDTH/2 - get_character_width()/2))
                camera.x = get_stage_avail_lefttop_x() + get_stage_avail_width() - WIDTH;
            else
                camera.x = get_character_x() - WIDTH/2  + get_character_width()/2 ;

            if(get_character_y() < get_stage_avail_lefttop_y() + get_stage_avail_heigth() - 150 - get_character_heigth())
                camera.y = get_character_y() + get_character_heigth() + 150 - HEIGHT;
            else
                camera.y = get_stage_avail_lefttop_y() + get_stage_avail_heigth() - HEIGHT;

        }
    }
}

//--------------------get value---------------------
int get_camera_x(){return camera.x;}
int get_camera_y(){return camera.y;}
