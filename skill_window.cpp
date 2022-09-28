#include "skill_window.h"

typedef struct Skill_window{
    int x,y;
    int height,width;
    int display_height,display_width;// for slide slot using
    int display_x,display_y;// for slide slot using
    bool state; // 0=mouse in region 1=mouse in region
    ALLEGRO_BITMAP *img = NULL;
}skill_window;
typedef struct Skill_icon{
    int x,y;
    int height,width;
    bool state;
    bool available;
    bool if_equip;
    int key;
    int skill_level;
    bool if_drag;
    bool skill_type; //0=active 1=passive
    ALLEGRO_BITMAP *img = NULL;
    ALLEGRO_BITMAP *img_upgrade = NULL;
    ALLEGRO_BITMAP *bg = NULL;
    int icon_x,icon_y;
    int icon_width,icon_height;
    bool icon_show;
    int bg_x,bg_y;
    int bg_width,bg_height;
    int upgrade_x,upgrade_y;
    int upgrade_width,upgrade_height;
    bool upgrade_state;
}skill_icon;
typedef struct Skill_key{
    int x,y;
    int height,width;
    int skill_index;
    bool if_equip;
    bool state;
    bool if_drag;
    ALLEGRO_BITMAP *img = NULL;
}skill_key;
skill_icon skill_window_list[10];
skill_window skill_window_keyboard;
skill_window skill_windows;
skill_key skill_window_key[9];
ALLEGRO_BITMAP *skill_window_bg;
ALLEGRO_BITMAP *skill_window_list_bg;
ALLEGRO_BITMAP *skill_window_upgrade_img;
ALLEGRO_BITMAP *skill_window_equiping_img;
ALLEGRO_FONT *skill_point_font = NULL;
bool skill_window_wheel_state;
int mouse_z_skill_window;
int skill_num;
int if_draging_skill_window;

void skill_window_init(){
    skill_point_font = al_load_ttf_font("./font/pirulen.ttf",18,0);
    skill_windows.img = al_load_bitmap("./image/skill/window/skill_window.png");
    skill_window_keyboard.img = al_load_bitmap("./image/skill/window/skill_window_keyboard.png");
    skill_window_bg = al_load_bitmap("./image/menu/esc/esc_bg.png");
    skill_window_list_bg = al_load_bitmap("./image/skill/window/skill_window_skill_list.png");
    skill_window_upgrade_img = al_load_bitmap("./image/skill/window/skill_window_upgrade.png");
    skill_window_equiping_img = al_load_bitmap("./image/skill/window/skill_window_equiping.png");
    skill_num=2;
    skill_windows.x=830;
    skill_windows.y=97;
    skill_window_keyboard.x=105;
    skill_window_keyboard.y=297;
    skill_windows.width = al_get_bitmap_width(skill_windows.img);
    skill_windows.height = al_get_bitmap_height(skill_windows.img);
    skill_window_keyboard.width = al_get_bitmap_width(skill_window_keyboard.img);
    skill_window_keyboard.height = al_get_bitmap_height(skill_window_keyboard.img);

    for(int i=0;i<skill_num;i++){
        skill_window_list[i].bg = skill_window_list_bg;
        skill_window_list[i].img_upgrade = skill_window_upgrade_img;
        skill_window_list[i].bg_width = al_get_bitmap_width(skill_window_list_bg);
        skill_window_list[i].bg_height = al_get_bitmap_height(skill_window_list_bg);
        skill_window_list[i].x = skill_windows.x+skill_windows.width/2-skill_window_list[i].bg_width/2;
        skill_window_list[i].y = 190+135*i;
        skill_window_list[i].icon_x=skill_window_list[i].x+16;
        skill_window_list[i].icon_y=skill_window_list[i].y+13;
        skill_window_list[i].icon_show=1;
        skill_window_list[i].if_drag=0;
        skill_window_list[i].if_equip=0;
    }
    skill_windows.display_y=0;
    skill_windows.display_height = 590;
    skill_windows.display_width = skill_window_list[0].bg_width;
    if_draging_skill_window=-1;
    mouse_z_skill_window=0;
    al_set_mouse_z(0);
    for(int i=0;i<skill_num;i++){
        //skill_window_list[i].key=get_chara_key(i);
        skill_window_list[i].skill_level=get_chara_skill(i);
        if(get_chara_lv()>i*5)
            skill_window_list[i].available=1;
        if(get_chara_career() == 1){
            char temp[50];
            sprintf( temp, "./image/skill/icon/skill_icon_warrior_%d.png", i+1);
            skill_window_list[i].img = al_load_bitmap(temp);
        }
        skill_window_list[i].img_upgrade = skill_window_upgrade_img;
        skill_window_list[i].icon_height = al_get_bitmap_height(skill_window_list[i].img);
        skill_window_list[i].icon_width = al_get_bitmap_width(skill_window_list[i].img);
        skill_window_list[i].upgrade_x = skill_window_list[i].x+479;
        skill_window_list[i].upgrade_y = skill_window_list[i].y+88;
        skill_window_list[i].upgrade_width = al_get_bitmap_height(skill_window_upgrade_img);
        skill_window_list[i].upgrade_height = al_get_bitmap_height(skill_window_upgrade_img);
        skill_window_list[i].skill_type = 0;
    }
    for(int i=0;i<9;i++){
        skill_window_key[i].skill_index = get_skill_key_skill_index(i);
        skill_window_key[i].if_equip = get_skill_key_if_equip(i);
        skill_window_key[i].if_drag = 0;
        if(skill_window_key[i].if_equip)
            skill_window_list[skill_window_key[i].skill_index].if_equip=1;

        if(skill_window_key[i].if_equip){
            skill_window_key[i].img = skill_window_list[skill_window_key[i].skill_index].img;
        }
        if(i<5){
            skill_window_key[i].x = 160 + 120*i;
            skill_window_key[i].y = 345;
        }
        else{
            skill_window_key[i].x = 220 + 120*(i-5);
            skill_window_key[i].y = 470;
        }
        skill_window_key[i].height = skill_window_list[0].icon_height;
        skill_window_key[i].width = skill_window_list[0].icon_width;
    }
}
void skill_window_process(ALLEGRO_EVENT event){
    skill_window_item_drag(event);
    skill_upgrade(event);
}
void skill_window_draw(){
    al_draw_bitmap(skill_window_bg,0,0,0);
    al_draw_bitmap(skill_windows.img,skill_windows.x,skill_windows.y,0);
    al_draw_bitmap(skill_window_keyboard.img,skill_window_keyboard.x,skill_window_keyboard.y,0);
    char text_point[10];
    sprintf(text_point,"%d",get_chara_skill_point());
    al_draw_text(skill_point_font, al_map_rgb(255,255,255), skill_windows.x+558, skill_windows.y+33,ALLEGRO_ALIGN_CENTER ,text_point);

    for(int i=0;i<skill_num;i++){
        if(skill_window_list[i].y-skill_windows.display_y+skill_window_list[i].bg_height>=skill_window_list[0].y)
            al_draw_bitmap_region(skill_window_list[i].bg, 0, -skill_window_list[i].y+skill_window_list[0].y+skill_windows.display_y, skill_windows.display_width, skill_windows.display_height,skill_window_list[0].x,skill_window_list[0].y,0);
        if(skill_window_list[i].icon_show)
            al_draw_bitmap_region(skill_window_list[i].img, 0, -skill_window_list[i].icon_y+skill_window_list[0].y+skill_windows.display_y, skill_window_list[i].icon_width, skill_windows.display_height,skill_window_list[0].icon_x,skill_window_list[0].y,0);
        sprintf(text_point,"%d",get_chara_skill(i));
        al_draw_text(skill_point_font, al_map_rgb(255,255,255), skill_window_list[i].x+493, skill_window_list[i].y-skill_windows.display_y+52,ALLEGRO_ALIGN_CENTER ,text_point);
        al_draw_bitmap_region(skill_window_list[i].img_upgrade, 0, -skill_window_list[i].upgrade_y+skill_window_list[0].y+skill_windows.display_y, skill_window_list[i].upgrade_width, skill_windows.display_height,skill_window_list[0].upgrade_x,skill_window_list[0].y,0);
        if(skill_window_list[i].if_equip)
            al_draw_bitmap_region(skill_window_equiping_img, 0, -skill_window_list[i].icon_y+skill_window_list[0].y+skill_windows.display_y, skill_window_list[i].icon_width, skill_windows.display_height,skill_window_list[0].icon_x,skill_window_list[0].y,0);
    }
    for(int i=0;i<9;i++)
        if(skill_window_key[i].if_equip)
            al_draw_bitmap(skill_window_key[i].img, skill_window_key[i].x, skill_window_key[i].y,0);
    for(int i=0;i<skill_num;i++)
        if(skill_window_list[i].if_drag)
            al_draw_bitmap(skill_window_list[i].img, get_mouse_x()-skill_window_list[i].icon_width/2, get_mouse_y()-skill_window_list[i].icon_height/2,0);
     for(int i=0;i<9;i++)
        if(skill_window_key[i].if_drag)
            al_draw_bitmap(skill_window_key[i].img, get_mouse_x()-skill_window_key[i].width/2, get_mouse_y()-skill_window_key[i].height/2,0);
}
void skill_window_mouse_check(){
    skill_window_wheel_state = img_onmouse(skill_window_list[0].x-5,skill_window_list[0].y-5,skill_windows.display_width+10,skill_windows.display_height+10);
    for(int i=0;i<skill_num;i++){
        if(skill_window_list[i].upgrade_y-skill_windows.display_y+skill_window_list[i].upgrade_height<skill_window_list[0].y)
            skill_window_list[i].upgrade_state = 0;
        else if(skill_window_list[i].upgrade_y-skill_windows.display_y+skill_window_list[i].upgrade_height>=skill_window_list[0].y && skill_window_list[i].upgrade_y-skill_windows.display_y<skill_window_list[0].y)
            skill_window_list[i].upgrade_state = img_onmouse(skill_window_list[i].upgrade_x,skill_window_list[0].y,skill_window_list[i].bg_width, skill_window_list[i].upgrade_y-skill_windows.display_y+skill_window_list[i].bg_height - skill_window_list[0].y );
        else if(skill_window_list[i].upgrade_y-skill_windows.display_y>=skill_window_list[0].y && skill_window_list[i].upgrade_y-skill_windows.display_y+skill_window_list[i].upgrade_height<=skill_window_list[0].y+skill_windows.display_height)
            skill_window_list[i].upgrade_state = img_onmouse(skill_window_list[i].upgrade_x,skill_window_list[i].upgrade_y-skill_windows.display_y,skill_window_list[i].upgrade_width,skill_window_list[i].upgrade_height);
        else if(skill_window_list[i].upgrade_y-skill_windows.display_y+skill_window_list[i].upgrade_height>skill_window_list[0].y+skill_windows.display_height && skill_window_list[i].upgrade_y-skill_windows.display_y<=skill_window_list[0].y+skill_windows.display_height)
            skill_window_list[i].upgrade_state = img_onmouse(skill_window_list[i].upgrade_x,skill_window_list[i].upgrade_y-skill_windows.display_y,skill_window_list[i].upgrade_width, skill_window_list[0].y+skill_windows.display_height-skill_window_list[i].upgrade_y+skill_windows.display_y );
        else
            skill_window_list[i].upgrade_state = 0;

        if(skill_window_list[i].y-skill_windows.display_y+skill_window_list[i].bg_height<skill_window_list[0].y)
            skill_window_list[i].state = 0;
        else if(skill_window_list[i].y-skill_windows.display_y+skill_window_list[i].height>=skill_window_list[0].y && skill_window_list[i].y-skill_windows.display_y<skill_window_list[0].y)
            skill_window_list[i].state = img_onmouse(skill_window_list[i].x,skill_window_list[0].y,skill_window_list[i].bg_width, skill_window_list[i].y-skill_windows.display_y+skill_window_list[i].bg_height - skill_window_list[0].y );
        else if(skill_window_list[i].y-skill_windows.display_y>=skill_window_list[0].y && skill_window_list[i].y-skill_windows.display_y+skill_window_list[i].bg_height<=skill_window_list[0].y+skill_windows.display_height)
            skill_window_list[i].state = img_onmouse(skill_window_list[i].x,skill_window_list[i].y-skill_windows.display_y,skill_window_list[i].bg_width,skill_window_list[i].bg_height);
        else if(skill_window_list[i].y-skill_windows.display_y+skill_window_list[i].bg_height>skill_window_list[0].y+skill_windows.display_height && skill_window_list[i].y-skill_windows.display_y<=skill_window_list[0].y+skill_windows.display_height)
            skill_window_list[i].state = img_onmouse(skill_window_list[i].x,skill_window_list[i].y-skill_windows.display_y,skill_window_list[i].bg_width, skill_window_list[0].y+skill_windows.display_height-skill_window_list[i].y+skill_windows.display_y );
        else
            skill_window_list[i].state = 0;

        if(skill_window_list[i].upgrade_state)
            skill_window_list[i].state = 0;
    }
    for(int i=0;i<9;i++)
        skill_window_key[i].state = img_onmouse(skill_window_key[i].x,skill_window_key[i].y,skill_window_key[i].width,skill_window_key[i].height);
}
void skill_window_wheel(){

    if(skill_window_wheel_state && mouse_z_skill_window!=get_mouse_z()){
        skill_windows.display_y += -(get_mouse_z()-mouse_z_skill_window)*40;
        if(skill_windows.display_y<0)
            skill_windows.display_y=0;
        else if(skill_windows.display_y+skill_windows.display_height>skill_window_list[skill_num-1].y-skill_window_list[0].y+skill_window_list[skill_num-1].bg_height+10)
            skill_windows.display_y = skill_window_list[skill_num-1].y-skill_window_list[0].y+skill_window_list[skill_num-1].bg_height+10-skill_windows.display_height;
        if(skill_num<5)
            skill_windows.display_y=0;
    }

    mouse_z_skill_window=get_mouse_z();
}

void skill_window_item_drag(ALLEGRO_EVENT event){
    if(if_draging_skill_window == -1 ){
        if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
            for(int i=0;i<skill_num;i++){
                if(skill_window_list[i].icon_show && skill_window_list[i].state && skill_window_list[i].if_equip ==0 && skill_window_list[i].skill_type==0 && skill_window_list[i].skill_level>0){
                    skill_window_list[i].if_drag = 1;
                    skill_window_list[i].icon_show = 0;
                    if_draging_skill_window=i;
                    break;
                }
            }
            for(int i=0;i<9;i++){
                if(skill_window_key[i].state && skill_window_key[i].if_equip){
                    skill_window_key[i].if_equip=0;
                    skill_window_key[i].if_drag=1;
                    skill_window_list[skill_window_key[i].skill_index].if_equip = 0;
                    if_draging_skill_window = i;
                    break;
                }
            }
        }
    }
    else{
        if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            if(skill_window_list[if_draging_skill_window].if_drag){
                for(int i=0;i<9;i++){
                    if(skill_window_key[i].state && skill_window_key[i].if_equip == 0){
                        skill_window_key[i].if_equip=1;
                        skill_window_key[i].img = skill_window_list[if_draging_skill_window].img;
                        skill_window_key[i].skill_index = if_draging_skill_window;
                        skill_window_list[if_draging_skill_window].if_equip = 1;
                        break;
                    }
                }
                skill_window_list[if_draging_skill_window].if_drag = 0;
                skill_window_list[if_draging_skill_window].icon_show = 1;
            }
            if(skill_window_key[if_draging_skill_window].if_drag){
                for(int i=0;i<9;i++){
                    if(skill_window_key[i].state && skill_window_key[i].if_equip == 0){
                        skill_window_key[i].if_equip=1;
                        skill_window_key[i].img = skill_window_key[if_draging_skill_window].img;
                        skill_window_key[i].skill_index = skill_window_key[if_draging_skill_window].skill_index;
                        skill_window_list[skill_window_key[i].skill_index].if_equip = 1;
                        break;
                    }
                }
                skill_window_key[if_draging_skill_window].if_drag = 0;
            }
            if_draging_skill_window=-1;
        }
    }
}
void skill_upgrade(ALLEGRO_EVENT event){
    if(get_chara_skill_point()>0 && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
        for(int i=0;i<skill_num;i++){
            if(skill_window_list[i].upgrade_state && skill_window_list[i].skill_level<10){
                skill_window_list[i].skill_level++;
                set_chara_skill_point(get_chara_skill_point()-1);
                set_chara_skill(i,get_chara_skill(i)+1);
                break;
            }
        }
    }
}
void skill_window_detroy(){
    for(int i=0;i<9;i++){
        if(skill_window_key[i].if_equip){
            set_skill_key_if_equip(i,skill_window_key[i].if_equip);
            set_skill_key_skill_index(i,skill_window_key[i].skill_index);
        }
        else{
            set_skill_key_if_equip(i,skill_window_key[i].if_equip);
            set_skill_key_skill_index(i,-1);
        }
    }

    al_destroy_font(skill_point_font);
    for(int i=0;i<skill_num;i++)
        al_destroy_bitmap(skill_window_list[i].img);
    al_destroy_bitmap(skill_windows.img);
    al_destroy_bitmap(skill_window_keyboard.img);
    al_destroy_bitmap(skill_window_bg);
    al_destroy_bitmap(skill_window_list_bg);
    al_destroy_bitmap(skill_window_upgrade_img);
    al_destroy_bitmap(skill_window_equiping_img);
}
