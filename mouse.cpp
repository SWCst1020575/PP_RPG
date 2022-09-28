#include "mouse.h"

ALLEGRO_MOUSE_STATE mouse_state; // catch mouse position

void mouse_update(){
    al_get_mouse_state(&mouse_state);
}
int get_mouse_x(){
    return mouse_state.x;
}
int get_mouse_y(){
    return mouse_state.y;
}
int get_mouse_z(){
    return mouse_state.z;
}

bool img_onmouse(int img_x,int img_y,int img_width,int img_heigth){
    int now_mouse_x=get_mouse_x();
    int now_mouse_y=get_mouse_y();

    if(now_mouse_x >= img_x && now_mouse_x <= img_x+img_width && now_mouse_y >= img_y && now_mouse_y <= img_y+img_heigth)
        return 1;
    else
        return 0;
}
