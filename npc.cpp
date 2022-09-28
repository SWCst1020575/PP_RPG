#include "npc.h"

ALLEGRO_FONT *npc_text = NULL;
typedef struct npc_img{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool state=0; // the state of character 0=normal 1=onmouse
    ALLEGRO_BITMAP *img = NULL;
    ALLEGRO_BITMAP *img_onmouse = NULL;
    ALLEGRO_BITMAP *text_img = NULL;
}NPC_img;
NPC_img weapon_shop;
NPC_img medicine_shop;
NPC_img forging_shop;
NPC_img bulletin_board;
NPC_img tp_gate;
ALLEGRO_BITMAP *tp_window = NULL;
NPC_img tp_stage2_text;
NPC_img tp_gate_cancel;

bool tp_window_display;

void npc_init(){
    npc_text = al_load_ttf_font("./font/pirulen.ttf",70,0);

    weapon_shop.img_onmouse = al_load_bitmap("./image/NPC/weapon_shop_onmouse.png");
    medicine_shop.img_onmouse = al_load_bitmap("./image/NPC/medicine_shop_onmouse.png");
    forging_shop.img_onmouse = al_load_bitmap("./image/NPC/forging_shop_onmouse.png");
    bulletin_board.img = al_load_bitmap("./image/NPC/bulletin_board.png");
    tp_gate.img = al_load_bitmap("./image/NPC/tp_gate.png");
    bulletin_board.img_onmouse = al_load_bitmap("./image/NPC/bulletin_board_onmouse.png");
    tp_gate.img_onmouse = al_load_bitmap("./image/NPC/tp_gate_onmouse.png");


    weapon_shop.text_img = al_load_bitmap("./image/NPC/weapon_shop_text.png");
    medicine_shop.text_img = al_load_bitmap("./image/NPC/medicine_shop_text.png");
    forging_shop.text_img = al_load_bitmap("./image/NPC/forging_shop_text.png");
    bulletin_board.text_img = al_load_bitmap("./image/NPC/bulletin_board_text.png");
    tp_gate.text_img = al_load_bitmap("./image/NPC/tp_gate_text.png");





    weapon_shop.x=4;
    weapon_shop.y=1108;
    medicine_shop.x=409;
    medicine_shop.y=1096;
    forging_shop.x=905;
    forging_shop.y=1097;
    bulletin_board.x=1431;
    bulletin_board.y=1073;
    tp_gate.x=2480;
    tp_gate.y=1160;
    tp_stage2_text.x=244;
    tp_stage2_text.y=103;
    tp_gate_cancel.x=1370;
    tp_gate_cancel.y=20;

    weapon_shop.width=al_get_bitmap_width(weapon_shop.img_onmouse);
    weapon_shop.height=al_get_bitmap_height(weapon_shop.img_onmouse);
    medicine_shop.width=al_get_bitmap_width(medicine_shop.img_onmouse);
    medicine_shop.height=al_get_bitmap_height(medicine_shop.img_onmouse);
    forging_shop.width=al_get_bitmap_width(forging_shop.img_onmouse);
    forging_shop.height=al_get_bitmap_height(forging_shop.img_onmouse);
    bulletin_board.width=al_get_bitmap_width(bulletin_board.img_onmouse);
    bulletin_board.height=al_get_bitmap_height(bulletin_board.img_onmouse);
    tp_gate.width=al_get_bitmap_width(tp_gate.img_onmouse);
    tp_gate.height=al_get_bitmap_height(tp_gate.img_onmouse);


    tp_window_display = 0;
}


void npc_draw(int camera_x,int camera_y){
    if(weapon_shop.state){
        al_draw_bitmap(weapon_shop.img_onmouse, weapon_shop.x - camera_x, weapon_shop.y - camera_y, 0);
        if(game_stop == 0)
            al_draw_bitmap(weapon_shop.text_img, get_mouse_x()+10, get_mouse_y()+15, 0);
    }
    if(medicine_shop.state){
        al_draw_bitmap(medicine_shop.img_onmouse, medicine_shop.x - camera_x, medicine_shop.y - camera_y, 0);
        if(game_stop == 0)
            al_draw_bitmap(medicine_shop.text_img, get_mouse_x()+10, get_mouse_y()+15, 0);
    }
    if(forging_shop.state){
        al_draw_bitmap(forging_shop.img_onmouse, forging_shop.x - camera_x, forging_shop.y - camera_y, 0);
        if(game_stop == 0)
            al_draw_bitmap(forging_shop.text_img, get_mouse_x()+10, get_mouse_y()+15, 0);
    }
    if(bulletin_board.state){
        al_draw_bitmap(bulletin_board.img_onmouse, bulletin_board.x - camera_x, bulletin_board.y - camera_y, 0);
        if(game_stop == 0)
            al_draw_bitmap(bulletin_board.text_img, get_mouse_x()+10, get_mouse_y()+15, 0);
    }
    else
        al_draw_bitmap(bulletin_board.img, bulletin_board.x - camera_x, bulletin_board.y - camera_y, 0);
    if(tp_gate.state){
        al_draw_bitmap(tp_gate.img_onmouse, tp_gate.x - camera_x, tp_gate.y - camera_y, 0);
        if(game_stop == 0)
            al_draw_bitmap(tp_gate.text_img, get_mouse_x()+10, get_mouse_y()+15, 0);
    }
    else
        al_draw_bitmap(tp_gate.img, tp_gate.x - camera_x, tp_gate.y - camera_y, 0);

}

void npc_onmouse_check(int camera_x,int camera_y){
    if(tp_window_display){
        tp_stage2_text.state = img_onmouse(tp_stage2_text.x,tp_stage2_text.y,tp_stage2_text.width,tp_stage2_text.height);
        tp_gate_cancel.state = img_onmouse(tp_gate_cancel.x,tp_gate_cancel.y,tp_gate_cancel.width,tp_gate_cancel.height);
    }
    else{
        weapon_shop.state = img_onmouse(weapon_shop.x - camera_x,weapon_shop.y - camera_y,weapon_shop.width,weapon_shop.height);
        medicine_shop.state = img_onmouse(medicine_shop.x - camera_x,medicine_shop.y - camera_y,medicine_shop.width,medicine_shop.height);
        forging_shop.state = img_onmouse(forging_shop.x - camera_x,forging_shop.y - camera_y,forging_shop.width,forging_shop.height);
        bulletin_board.state = img_onmouse(bulletin_board.x - camera_x,bulletin_board.y - camera_y,bulletin_board.width,bulletin_board.height);
        tp_gate.state = img_onmouse(tp_gate.x - camera_x,tp_gate.y - camera_y,tp_gate.width,tp_gate.height);
    }
}

void tp_draw(){

    al_draw_bitmap(tp_window, 145, 50, 0);
    if(tp_gate_cancel.state)
        al_draw_bitmap(tp_gate_cancel.img_onmouse, tp_gate_cancel.x, tp_gate_cancel.y, 0);
    else
        al_draw_bitmap(tp_gate_cancel.img, tp_gate_cancel.x, tp_gate_cancel.y, 0);
    if(tp_stage2_text.state)
        al_draw_bitmap(tp_stage2_text.img_onmouse, tp_stage2_text.x, tp_stage2_text.y, 0);
    else
        al_draw_bitmap(tp_stage2_text.img, tp_stage2_text.x, tp_stage2_text.y, 0);
}

void npc_process(ALLEGRO_EVENT event){
    if(click_weapon_shop(event)){
        game_stop = 1;
        judge_next_window = true;
        shop_type =0;
        target_window = 8;
    }
    if(click_potion_shop(event)){
        game_stop = 1;
        judge_next_window = true;
        shop_type =1;
        target_window = 8;
    }
    if(click_forging_shop(event)){
        game_stop = 1;
        judge_next_window = true;
        target_window = 10;
    }
    if(click_tpgate(event) && tp_window_display == 0){
        tp_window = al_load_bitmap("./image/NPC/tp_window.png");
        tp_stage2_text.img_onmouse = al_load_bitmap("./image/NPC/stage2_text_onmouse.png");
        tp_gate_cancel.img_onmouse = al_load_bitmap("./image/menu/CreateCharacter/CreateCharacterCancelonmouse.png");
        tp_stage2_text.img = al_load_bitmap("./image/NPC/stage2_text.png");
        tp_gate_cancel.img = al_load_bitmap("./image/menu/CreateCharacter/CreateCharacterCancel.png");
        tp_stage2_text.width=al_get_bitmap_width(tp_stage2_text.img);
        tp_stage2_text.height=al_get_bitmap_height(tp_stage2_text.img);
        tp_gate_cancel.width=al_get_bitmap_width(tp_gate_cancel.img);
        tp_gate_cancel.height=al_get_bitmap_height(tp_gate_cancel.img);
        game_stop = 1;
        tp_window_display = 1;
    }
    if(tp_window_display && click_tpgate_cancel(event)){
        game_stop = 0;
        tp_window_display = 0;
        al_destroy_bitmap(tp_window);
        al_destroy_bitmap(tp_gate_cancel.img);
        al_destroy_bitmap(tp_gate_cancel.img_onmouse);
        al_destroy_bitmap(tp_stage2_text.img);
        al_destroy_bitmap(tp_stage2_text.img_onmouse);
        tp_gate_cancel.state=0;
    }
    if(tp_window_display && click_stage2_text(event)){
        game_stop = 0;
        tp_window_display = 0;
        al_destroy_bitmap(tp_window);
        al_destroy_bitmap(tp_gate_cancel.img);
        al_destroy_bitmap(tp_gate_cancel.img_onmouse);
        al_destroy_bitmap(tp_stage2_text.img);
        al_destroy_bitmap(tp_stage2_text.img_onmouse);
        now_stage = 2;
        if_battle = 1;
        if_stage_change = 1;
        tp_stage2_text.state=0;
        npc_destroy();
    }
}

bool click_weapon_shop(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            return  weapon_shop.state;
    }
    return 0;
}
bool click_potion_shop(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            return  medicine_shop.state;
    }
    return 0;
}
bool click_forging_shop(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            return  forging_shop.state;
    }
    return 0;
}
bool click_tpgate(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            return  tp_gate.state;
    }
    return 0;
}
bool click_tpgate_cancel(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            return  tp_gate_cancel.state;
    }
    return 0;
}
bool click_stage2_text(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            return  tp_stage2_text.state;
    }
    return 0;
}

void npc_destroy(){
    al_destroy_bitmap(weapon_shop.img_onmouse);
    al_destroy_bitmap(medicine_shop.img_onmouse);
    al_destroy_bitmap(forging_shop.img_onmouse);
    al_destroy_bitmap(bulletin_board.img);
    al_destroy_bitmap(tp_gate.img);
    al_destroy_bitmap(bulletin_board.img_onmouse);
    al_destroy_bitmap(tp_gate.img_onmouse);
    al_destroy_bitmap(weapon_shop.text_img);
    al_destroy_bitmap(medicine_shop.text_img);
    al_destroy_bitmap(forging_shop.text_img);
    al_destroy_bitmap(bulletin_board.text_img);
    al_destroy_bitmap(tp_gate.text_img);
}
