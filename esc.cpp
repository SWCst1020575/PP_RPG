#include "esc.h"

typedef struct esc_img{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool state=0; // the state of character 0=normal 1=onmouse
    //int a[1000000];
    ALLEGRO_BITMAP *img = NULL;
    ALLEGRO_BITMAP *img_onmouse = NULL;
}Esc_img;
Esc_img esc_bg;
Esc_img savegame_text;
Esc_img loadgame_text;
Esc_img item_text;
Esc_img skill_text;
Esc_img setting_text;
Esc_img backtomenu_text;
Esc_img cancel_img;
Esc_img onmouse_shadow;

void esc_init(){

    esc_bg.img = al_load_bitmap("./image/menu/esc/esc_bg.png");
    onmouse_shadow.img = al_load_bitmap("./image/menu/esc/esc_onmouseshadow.png");

    savegame_text.img = al_load_bitmap("./image/menu/esc/esc_savegame.png");
    savegame_text.img_onmouse = al_load_bitmap("./image/menu/esc/esc_savegameonmouse.png");
    loadgame_text.img = al_load_bitmap("./image/menu/esc/esc_loadgame.png");
    loadgame_text.img_onmouse = al_load_bitmap("./image/menu/esc/esc_loadgameonmouse.png");
    item_text.img = al_load_bitmap("./image/menu/esc/esc_item.png");
    item_text.img_onmouse = al_load_bitmap("./image/menu/esc/esc_itemonmouse.png");
    skill_text.img = al_load_bitmap("./image/menu/esc/esc_skill.png");
    skill_text.img_onmouse = al_load_bitmap("./image/menu/esc/esc_skillonmouse.png");
    setting_text.img = al_load_bitmap("./image/menu/esc/esc_setting.png");
    setting_text.img_onmouse = al_load_bitmap("./image/menu/esc/esc_settingonmouse.png");
    backtomenu_text.img = al_load_bitmap("./image/menu/esc/esc_backtomenu.png");
    backtomenu_text.img_onmouse = al_load_bitmap("./image/menu/esc/esc_backtomenuonmouse.png");
    cancel_img.img = al_load_bitmap("./image/menu/esc/escCancel.png");
    cancel_img.img_onmouse = al_load_bitmap("./image/menu/esc/escCancelonmouse.png");

    savegame_text.width = al_get_bitmap_width(savegame_text.img);
    savegame_text.height = al_get_bitmap_height(savegame_text.img);
    loadgame_text.width = al_get_bitmap_width(loadgame_text.img);
    loadgame_text.height = al_get_bitmap_height(loadgame_text.img);
    item_text.width = al_get_bitmap_width(item_text.img);
    item_text.height = al_get_bitmap_height(item_text.img);
    skill_text.width = al_get_bitmap_width(skill_text.img);
    skill_text.height = al_get_bitmap_height(skill_text.img);
    setting_text.width = al_get_bitmap_width(setting_text.img);
    setting_text.height = al_get_bitmap_height(setting_text.img);
    backtomenu_text.width = al_get_bitmap_width(backtomenu_text.img);
    backtomenu_text.height = al_get_bitmap_height(backtomenu_text.img);
    cancel_img.width = al_get_bitmap_width(cancel_img.img);
    cancel_img.height = al_get_bitmap_height(cancel_img.img);
}

void esc_process(ALLEGRO_EVENT event){
    if(esc_click_backtomenu(event)){
        game_stop = 0;
        judge_next_window = true;
        target_window = 1;
    }
    if(esc_click_savegame(event)){
        sl_type = 0;
        judge_next_window = true;
        target_window = 4;
    }
    if(esc_click_loadgame(event)){
        sl_type =1;
        judge_next_window = true;
        target_window = 4;
    }
    if(esc_click_cancel(event)){
        game_stop = 0;
        judge_next_window = true;
        target_window = 5;
    }
    if(esc_click_setting(event)){
        judge_next_window = true;
        target_window = 2;
    }
    if(esc_click_item(event)){
        judge_next_window = true;
        target_window = 7;
    }
    if(esc_click_skill(event)){
        judge_next_window = true;
        target_window = 9;
    }
}
void esc_draw(){
    game_scene_draw();
    al_draw_bitmap(esc_bg.img, 0, 0, 0);

    if(savegame_text.state == 0)
        al_draw_bitmap(savegame_text.img, 627, 80, 0);
    else{
        al_draw_bitmap(onmouse_shadow.img, 588, 50, 0);
        al_draw_bitmap(savegame_text.img_onmouse, 627, 80, 0);
    }
    if(loadgame_text.state == 0)
        al_draw_bitmap(loadgame_text.img, 627, 200, 0);
    else{
        al_draw_bitmap(loadgame_text.img_onmouse, 627, 200, 0);
        al_draw_bitmap(onmouse_shadow.img, 588, 170, 0);
    }
    if(item_text.state == 0)
        al_draw_bitmap(item_text.img, 587, 320, 0);
    else{
        al_draw_bitmap(item_text.img_onmouse, 587, 320, 0);
        al_draw_bitmap(onmouse_shadow.img, 588, 290, 0);
    }
    if(skill_text.state == 0)
        al_draw_bitmap(skill_text.img, 707, 440, 0);
    else{
        al_draw_bitmap(skill_text.img_onmouse, 707, 440, 0);
        al_draw_bitmap(onmouse_shadow.img, 588, 410, 0);
    }
    if(setting_text.state == 0)
        al_draw_bitmap(setting_text.img, 707, 560, 0);
    else{
        al_draw_bitmap(setting_text.img_onmouse, 707, 560, 0);
        al_draw_bitmap(onmouse_shadow.img, 588, 530, 0);
    }
    if(backtomenu_text.state == 0)
        al_draw_bitmap(backtomenu_text.img, 588, 680, 0);
    else{
        al_draw_bitmap(backtomenu_text.img_onmouse, 588, 680, 0);
        al_draw_bitmap(onmouse_shadow.img, 588, 650, 0);
    }
    if(cancel_img.state == 0)
        al_draw_bitmap(cancel_img.img, 1450, 40, 0);
    else
        al_draw_bitmap(cancel_img.img_onmouse, 1450, 40, 0);


}

void esc_text_onmouse_check(){
    if(now_stage == 1)
        savegame_text.state = img_onmouse(627,80,savegame_text.width,savegame_text.height);
    else
        savegame_text.state = 0;
    loadgame_text.state = img_onmouse(627,200,loadgame_text.width,loadgame_text.height);
    item_text.state = img_onmouse(587,320,item_text.width,item_text.height);
    if(get_chara_career() == 1)
        skill_text.state = img_onmouse(707,440,skill_text.width,skill_text.height);
    else
        skill_text.state = 0;
    setting_text.state = img_onmouse(707,560,setting_text.width,setting_text.height);
    backtomenu_text.state = img_onmouse(588,680,backtomenu_text.width,backtomenu_text.height);
    cancel_img.state = img_onmouse(1450,40,cancel_img.width,cancel_img.height);
}

bool esc_click_cancel(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
        return cancel_img.state;
    return 0;
}
bool esc_click_savegame(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
        return savegame_text.state;
    return 0;
}
bool esc_click_loadgame(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
        return loadgame_text.state;
    return 0;
}
bool esc_click_item(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
        return item_text.state;
    return 0;
}
bool esc_click_skill(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
        return skill_text.state;
    return 0;
}
bool esc_click_setting(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
        return setting_text.state;
    return 0;
}
bool esc_click_backtomenu(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
        return backtomenu_text.state;
    return 0;
}

void esc_destroy(){

    al_destroy_bitmap(esc_bg.img);
    al_destroy_bitmap(onmouse_shadow.img);

    al_destroy_bitmap(savegame_text.img);
    al_destroy_bitmap(savegame_text.img_onmouse);
    al_destroy_bitmap(loadgame_text.img);
    al_destroy_bitmap(loadgame_text.img_onmouse);
    al_destroy_bitmap(item_text.img);
    al_destroy_bitmap(item_text.img_onmouse);
    al_destroy_bitmap(skill_text.img);
    al_destroy_bitmap(skill_text.img_onmouse);
    al_destroy_bitmap(setting_text.img);
    al_destroy_bitmap(setting_text.img_onmouse);
    al_destroy_bitmap(backtomenu_text.img);
    al_destroy_bitmap(backtomenu_text.img_onmouse);
    al_destroy_bitmap(cancel_img.img);
    al_destroy_bitmap(cancel_img.img_onmouse);

}
