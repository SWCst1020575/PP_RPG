#include "stage.h"

typedef struct Stage{
    int width;
    int height;
    ALLEGRO_BITMAP *bg = NULL;
    int avail_lefttop_x;
    int avail_lefttop_y;
    int avail_width;
    int avail_heigth;
    bool character_trace;
};
Stage stage;
void stage_init(int stage_num){
    if(stage_num == 1){
        stage.bg = al_load_bitmap("./image/stage/stage1.png");
        stage.width = al_get_bitmap_width(stage.bg);
        stage.height = al_get_bitmap_height(stage.bg);
        stage.avail_width = 2374;
        stage.avail_heigth = 482;
        stage.avail_lefttop_x = 0;
        stage.avail_lefttop_y = 1454;
    }
    else if(stage_num == 2){
        stage.bg = al_load_bitmap("./image/stage/stage2.png");
        stage.width = al_get_bitmap_width(stage.bg);
        stage.height = al_get_bitmap_height(stage.bg);
        stage.avail_width = 3200;
        stage.avail_heigth = 638;
        stage.avail_lefttop_x = 0;
        stage.avail_lefttop_y = 1006;
    }
}
void stage_draw(int camera_x,int camera_y){
    al_draw_bitmap(stage.bg, -camera_x, -camera_y, 0);
}

void stage_destroy(){
    al_destroy_bitmap(stage.bg);
}
//------------get value--------------------------
int get_stage_width(){
    return stage.width;
}
int get_stage_height(){
    return stage.height;
}
int get_stage_avail_width(){
    return stage.avail_width;
}
int get_stage_avail_heigth(){
    return stage.avail_heigth;
}
int get_stage_avail_lefttop_x(){
    return stage.avail_lefttop_x;
}
int get_stage_avail_lefttop_y(){
    return stage.avail_lefttop_y;
}
