#include "setting.h"

ALLEGRO_FONT *bgmvolume_text = NULL;
ALLEGRO_FONT *sevolume_text = NULL;
ALLEGRO_FILE *settingfile_write = NULL;
bool setting_origin_window = 0;
typedef struct setting_img{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool state=0; // the state of character 0=normal 1=onmouse
    //int a[1000000];
    ALLEGRO_BITMAP *img = NULL;
    ALLEGRO_BITMAP *img_onmouse = NULL;
}Setting_img;
Setting_img setting_background;
Setting_img bgmtext;
Setting_img setext;
Setting_img bgm_upvolume;
Setting_img bgm_downvolume;
Setting_img se_upvolume;
Setting_img se_downvolume;
Setting_img windowmode;
Setting_img fullscreenmode;
Setting_img backtomenu;

void setting_init(){
    bgmvolume_text = al_load_ttf_font("./font/pirulen.ttf",70,0);
    sevolume_text = al_load_ttf_font("./font/pirulen.ttf",70,0);

    setting_background.img = al_load_bitmap("./image/menu/setting/settingwindow.png");
    bgmtext.img = al_load_bitmap("./image/menu/setting/settingbgmtext.png");
    setext.img = al_load_bitmap("./image/menu/setting/settingsoundeffecttext.png");
    bgm_downvolume.img = al_load_bitmap("./image/menu/setting/settingarrow.png");
    bgm_downvolume.img_onmouse = al_load_bitmap("./image/menu/setting/settingarrowonmouse.png");
    bgm_upvolume.img = al_load_bitmap("./image/menu/setting/settingarrow.png");
    bgm_upvolume.img_onmouse = al_load_bitmap("./image/menu/setting/settingarrowonmouse.png");
    se_downvolume.img = al_load_bitmap("./image/menu/setting/settingarrow.png");
    se_downvolume.img_onmouse = al_load_bitmap("./image/menu/setting/settingarrowonmouse.png");
    se_upvolume.img = al_load_bitmap("./image/menu/setting/settingarrow.png");
    se_upvolume.img_onmouse = al_load_bitmap("./image/menu/setting/settingarrowonmouse.png");
    windowmode.img = al_load_bitmap("./image/menu/setting/windowmode.png");
    windowmode.img_onmouse = al_load_bitmap("./image/menu/setting/windowmodeonmouse.png");
    fullscreenmode.img = al_load_bitmap("./image/menu/setting/fullscreenmode.png");
    fullscreenmode.img_onmouse = al_load_bitmap("./image/menu/setting/fullscreenmodeonmouse.png");
    backtomenu.img = al_load_bitmap("./image/menu/setting/backtomenu.png");
    backtomenu.img_onmouse = al_load_bitmap("./image/menu/setting/backtomenuonmouse.png");

    bgm_downvolume.width = al_get_bitmap_width(bgm_downvolume.img);
    bgm_downvolume.height = al_get_bitmap_height(bgm_downvolume.img);
    bgm_upvolume.width = al_get_bitmap_width(bgm_upvolume.img);
    bgm_upvolume.height = al_get_bitmap_height(bgm_upvolume.img);
    se_downvolume.width = al_get_bitmap_width(se_downvolume.img);
    se_downvolume.height = al_get_bitmap_height(se_downvolume.img);
    se_upvolume.width = al_get_bitmap_width(se_upvolume.img);
    se_upvolume.height = al_get_bitmap_height(se_upvolume.img);
    windowmode.width = al_get_bitmap_width(windowmode.img);
    windowmode.height = al_get_bitmap_height(windowmode.img);
    fullscreenmode.width = al_get_bitmap_width(fullscreenmode.img);
    fullscreenmode.height = al_get_bitmap_height(fullscreenmode.img);
    backtomenu.width = al_get_bitmap_width(backtomenu.img);
    backtomenu.height = al_get_bitmap_height(backtomenu.img);
}

void setting_process(ALLEGRO_EVENT event){
    if(setting_origin_window){
        if(click_backtomenu(event)){
            save_setting();
            judge_next_window = true;
            target_window = 6;
        }
    }
    else{
        if(click_backtomenu(event)){
            save_setting();
            judge_next_window = true;
            target_window = 1;
        }
    }
    set_volume(event);
}
void setting_draw(){
    if(setting_origin_window)
        esc_draw();
    else
        menu_draw();

    al_draw_bitmap(setting_background.img, 144, 50, 0);
    char volume_text[10];
    sprintf(volume_text,"%d",bgmvolume);
    al_draw_text(bgmvolume_text, al_map_rgb(255,255,255), 1045, 223,ALLEGRO_ALIGN_CENTRE ,volume_text);
    sprintf(volume_text,"%d",sevolume);
    al_draw_text(sevolume_text, al_map_rgb(255,255,255), 1045, 333,ALLEGRO_ALIGN_CENTRE ,volume_text);


    al_draw_bitmap(bgmtext.img, 450, 235, 0);
    al_draw_bitmap(setext.img, 450, 338, 0);
    if(bgm_downvolume.state == 0)
        al_draw_bitmap(bgm_downvolume.img, 850, 231, 0);
    else
        al_draw_bitmap(bgm_downvolume.img_onmouse, 850, 231, 0);

    if(bgm_upvolume.state == 0)
        al_draw_bitmap(bgm_upvolume.img, 1170, 231, ALLEGRO_FLIP_HORIZONTAL);
    else
        al_draw_bitmap(bgm_upvolume.img_onmouse, 1170, 231, ALLEGRO_FLIP_HORIZONTAL);

    if(se_downvolume.state == 0)
        al_draw_bitmap(se_downvolume.img, 850, 343, 0);
    else
        al_draw_bitmap(se_downvolume.img_onmouse, 850, 343, 0);

    if(se_upvolume.state == 0)
        al_draw_bitmap(se_upvolume.img, 1170, 343, ALLEGRO_FLIP_HORIZONTAL);
    else
        al_draw_bitmap(se_upvolume.img_onmouse, 1170, 343, ALLEGRO_FLIP_HORIZONTAL);

    if(windowmode.state == 0 && screenmode != 1)
        al_draw_bitmap(windowmode.img, 370, 490, 0);
    else
        al_draw_bitmap(windowmode.img_onmouse, 370, 490, 0);

    if(fullscreenmode.state == 0 && screenmode != 0)
        al_draw_bitmap(fullscreenmode.img, 830, 490, 0);
    else
        al_draw_bitmap(fullscreenmode.img_onmouse, 830, 490, 0);

    if(backtomenu.state == 0)
        al_draw_bitmap(backtomenu.img, 650, 650, 0);
    else
        al_draw_bitmap(backtomenu.img_onmouse, 650, 650, 0);

}

void setting_text_onmouse_check(){
    bgm_downvolume.state = img_onmouse(850,231,bgm_downvolume.width,bgm_downvolume.height);
    bgm_upvolume.state = img_onmouse(1170,231,bgm_upvolume.width,bgm_upvolume.height);
    se_downvolume.state = img_onmouse(850,343,se_downvolume.width,se_downvolume.height);
    se_upvolume.state = img_onmouse(1170,343,se_upvolume.width,se_upvolume.height);
    windowmode.state = img_onmouse(370,490,windowmode.width,windowmode.height);
    fullscreenmode.state = img_onmouse(830,490,fullscreenmode.width,fullscreenmode.height);
    backtomenu.state = img_onmouse(650,650,backtomenu.width,backtomenu.height);
}

void save_setting(){
    ALLEGRO_CONFIG *setting_config = al_create_config();

    char setting_write[10];
    al_add_config_section(setting_config,"SCREEN_MODE");
    al_add_config_section(setting_config,"BGM_VOLUME");
    al_add_config_section(setting_config,"SE_VOLUME");


    itoa(screenmode,setting_write,10);
    al_set_config_value(setting_config,"SCREEN_MODE","MODE", setting_write);
    itoa(bgmvolume,setting_write,10);
    al_set_config_value(setting_config,"BGM_VOLUME","VOLUME", setting_write);
    itoa(sevolume,setting_write,10);
    al_set_config_value(setting_config,"SE_VOLUME","VOLUME", setting_write);

    al_save_config_file("./save/setting.dat", setting_config);
    al_destroy_config(setting_config);
}

bool set_volume(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            if(bgm_downvolume.state && bgmvolume>=5)
                bgmvolume-=5;
            else if(bgm_upvolume.state && bgmvolume<=95)
                bgmvolume+=5;
            else if(se_downvolume.state && sevolume>=5)
                sevolume-=5;
            else if(se_upvolume.state && sevolume<=95)
                sevolume+=5;
            return  1;
    }
    return 0;
}

bool click_windowmode(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            return  windowmode.state;
    }
    return 0;
}
bool click_fullscreenmode(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            return  fullscreenmode.state;
    }
    return 0;
}
bool click_backtomenu(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            return  backtomenu.state;
    }
    return 0;
}

void setting_destroy(){
    setting_origin_window = 0;
    al_destroy_font(bgmvolume_text);
    al_destroy_font(sevolume_text);
    al_destroy_bitmap(setting_background.img);
    al_destroy_bitmap(bgmtext.img);
    al_destroy_bitmap(setext.img);
    al_destroy_bitmap(bgm_upvolume.img);
    al_destroy_bitmap(bgm_downvolume.img);
    al_destroy_bitmap(se_upvolume.img);
    al_destroy_bitmap(se_downvolume.img);
    al_destroy_bitmap(windowmode.img);
    al_destroy_bitmap(fullscreenmode.img);
    al_destroy_bitmap(backtomenu.img);
    al_destroy_bitmap(bgmtext.img_onmouse);
    al_destroy_bitmap(setext.img_onmouse);
    al_destroy_bitmap(bgm_upvolume.img_onmouse);
    al_destroy_bitmap(bgm_downvolume.img_onmouse);
    al_destroy_bitmap(se_upvolume.img_onmouse);
    al_destroy_bitmap(se_downvolume.img_onmouse);
    al_destroy_bitmap(windowmode.img_onmouse);
    al_destroy_bitmap(fullscreenmode.img_onmouse);
    al_destroy_bitmap(backtomenu.img_onmouse);

}
