#include "menu.h"

ALLEGRO_FONT *font = NULL;
ALLEGRO_BITMAP *background_menu[4];

typedef struct menu_text
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool state=0; // the state of character 0=normal 1=onmouse
    ALLEGRO_BITMAP *img = NULL;
    ALLEGRO_BITMAP *img_onmouse = NULL;
}Menu_text;
Menu_text menu_newgame;
Menu_text menu_loadgame;
Menu_text menu_setting;
Menu_text menu_exitgame;
int menu_bg_time;
int display_bg_num;

void menu_init(){
    font = al_load_ttf_font("./font/pirulen.ttf",12,0);

    background_menu[0] = al_load_bitmap("./image/menu/bg/bg_1.png");
    background_menu[1] = al_load_bitmap("./image/menu/bg/bg_2.png");
    background_menu[2] = al_load_bitmap("./image/menu/bg/bg_3.png");
    background_menu[3] = al_load_bitmap("./image/menu/bg/bg_4.png");
    menu_newgame.img = al_load_bitmap("./image/menu/newgame.png");
    menu_loadgame.img = al_load_bitmap("./image/menu/loadgame.png");
    menu_setting.img = al_load_bitmap("./image/menu/setting.png");
    menu_exitgame.img = al_load_bitmap("./image/menu/exitgame.png");
    menu_newgame.img_onmouse = al_load_bitmap("./image/menu/newgameonmouse.png");
    menu_loadgame.img_onmouse = al_load_bitmap("./image/menu/loadgameonmouse.png");
    menu_setting.img_onmouse = al_load_bitmap("./image/menu/settingonmouse.png");
    menu_exitgame.img_onmouse = al_load_bitmap("./image/menu/exitgameonmouse.png");
    menu_bg_time=0;
    display_bg_num=0;
    menu_newgame.width = al_get_bitmap_width(menu_newgame.img);
    menu_newgame.height = al_get_bitmap_height(menu_newgame.img);
    menu_loadgame.width = al_get_bitmap_width(menu_loadgame.img);
    menu_loadgame.height = al_get_bitmap_height(menu_loadgame.img);
    menu_setting.width = al_get_bitmap_width(menu_setting.img);
    menu_setting.height = al_get_bitmap_height(menu_setting.img);
    menu_exitgame.width = al_get_bitmap_width(menu_exitgame.img);
    menu_exitgame.height = al_get_bitmap_height(menu_exitgame.img);
}
// function of menu

void menu_process(ALLEGRO_EVENT event){
    /*if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            judge_next_window = true;*/
    if(click_newgame(event)){
        judge_next_window = true;
        target_window = 3;
    }
    if(click_loadgame(event)){
        judge_next_window = true;
        target_window = 4;
    }
    if(click_exitgame(event))
        exit_game = true;
    if(click_setting(event)){
        judge_next_window = true;
        target_window = 2;
    }
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            menu_bg_time++;
            menu_bg_time%=20;
            if(menu_bg_time == 0){
                if(display_bg_num==0)
                    display_bg_num = 1;
                else if(display_bg_num == 3)
                    display_bg_num = 2;
                else{
                    if(get_rand(0,1))
                        display_bg_num++;
                    else
                        display_bg_num--;
                }
            }
        }
    }
}


void menu_draw(){
    al_draw_bitmap(background_menu[display_bg_num], 0, 0, 0);


    if(menu_newgame.state==0)
        al_draw_bitmap(menu_newgame.img, 100, 650, 0);
    else
        al_draw_bitmap(menu_newgame.img_onmouse, 100, 650, 0);

    if(menu_loadgame.state==0)
        al_draw_bitmap(menu_loadgame.img, 440, 650, 0);
    else
        al_draw_bitmap(menu_loadgame.img_onmouse, 440, 650, 0);

    if(menu_setting.state==0)
        al_draw_bitmap(menu_setting.img, 850, 650, 0);
    else
        al_draw_bitmap(menu_setting.img_onmouse, 850, 650, 0);

    if(menu_exitgame.state==0)
        al_draw_bitmap(menu_exitgame.img, 1090, 650, 0);
    else
        al_draw_bitmap(menu_exitgame.img_onmouse, 1090, 650, 0);


}

void menu_text_onmouse_check(){
    menu_newgame.state = img_onmouse(100,650,menu_newgame.width,menu_newgame.height);
    menu_loadgame.state = img_onmouse(440,650,menu_loadgame.width,menu_loadgame.height);
    menu_setting.state = img_onmouse(850,650,menu_setting.width,menu_setting.height);
    menu_exitgame.state = img_onmouse(1090,650,menu_exitgame.width,menu_exitgame.height);
}

bool click_newgame(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            return menu_newgame.state;
    }
    return 0;
}
bool click_loadgame(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            return  menu_loadgame.state;
    }
    return 0;
}
bool click_setting(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            return  menu_setting.state;
    }
    return 0;
}
bool click_exitgame(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            return  menu_exitgame.state;
    }
    return 0;
}

void menu_destroy(){
    al_destroy_font(font);
    for(int i=0;i<4;i++)
        al_destroy_bitmap(background_menu[i]);
    al_destroy_bitmap(menu_newgame.img);
    al_destroy_bitmap(menu_loadgame.img);
    al_destroy_bitmap(menu_setting.img);
    al_destroy_bitmap(menu_exitgame.img);
    al_destroy_bitmap(menu_newgame.img_onmouse);
    al_destroy_bitmap(menu_loadgame.img_onmouse);
    al_destroy_bitmap(menu_setting.img_onmouse);
    al_destroy_bitmap(menu_exitgame.img_onmouse);

}
