#include "createCharacter.h"

typedef struct createCharacter_img{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool state=0; // the state of character 0=normal 1=onmouse
    ALLEGRO_BITMAP *img = NULL;
    ALLEGRO_BITMAP *img_onmouse = NULL;
}CreateCharacter_img;
CreateCharacter_img CreateCharacter_bg;
CreateCharacter_img CreateCharacter_confirmbg;
CreateCharacter_img CreateCharacter_warrior;
CreateCharacter_img CreateCharacter_archer;
CreateCharacter_img CreateCharacter_wizard;
CreateCharacter_img CreateCharacter_cancel;
CreateCharacter_img CreateCharacter_confirmok;
CreateCharacter_img CreateCharacter_confirmcancel;

bool confirm_window = 0;
int create_career_type = 0;

void CreateCharacter_init(){
    CreateCharacter_bg.img = al_load_bitmap("./image/menu/CreateCharacter/CreateCharacterBg.png");
    CreateCharacter_confirmbg.img = al_load_bitmap("./image/menu/CreateCharacter/CreateCharacterConfirm.png");

    CreateCharacter_warrior.img = al_load_bitmap("./image/menu/CreateCharacter/CreateCharacterWarrior.png");
    CreateCharacter_warrior.img_onmouse = al_load_bitmap("./image/menu/CreateCharacter/CreateCharacterWarrioronmouse.png");
    CreateCharacter_archer.img = al_load_bitmap("./image/menu/CreateCharacter/CreateCharacterArcher.png");
    CreateCharacter_archer.img_onmouse = al_load_bitmap("./image/menu/CreateCharacter/CreateCharacterArcheronmouse.png");
    CreateCharacter_wizard.img = al_load_bitmap("./image/menu/CreateCharacter/CreateCharacterWizard.png");
    CreateCharacter_wizard.img_onmouse = al_load_bitmap("./image/menu/CreateCharacter/CreateCharacterWizardonmouse.png");
    CreateCharacter_cancel.img = al_load_bitmap("./image/menu/CreateCharacter/CreateCharacterCancel.png");
    CreateCharacter_cancel.img_onmouse = al_load_bitmap("./image/menu/CreateCharacter/CreateCharacterCancelonmouse.png");
    CreateCharacter_confirmok.img = al_load_bitmap("./image/menu/CreateCharacter/CreateCharacterConfirmok.png");
    CreateCharacter_confirmok.img_onmouse = al_load_bitmap("./image/menu/CreateCharacter/CreateCharacterConfirmokonmouse.png");
    CreateCharacter_confirmcancel.img = al_load_bitmap("./image/menu/CreateCharacter/CreateCharacterConfirmcancel.png");
    CreateCharacter_confirmcancel.img_onmouse = al_load_bitmap("./image/menu/CreateCharacter/CreateCharacterConfirmcancelonmouse.png");

    CreateCharacter_warrior.width = al_get_bitmap_width(CreateCharacter_warrior.img);
    CreateCharacter_warrior.height = al_get_bitmap_height(CreateCharacter_warrior.img);
    CreateCharacter_archer.width = al_get_bitmap_width(CreateCharacter_archer.img);
    CreateCharacter_archer.height = al_get_bitmap_height(CreateCharacter_archer.img);
    CreateCharacter_wizard.width = al_get_bitmap_width(CreateCharacter_wizard.img);
    CreateCharacter_wizard.height = al_get_bitmap_height(CreateCharacter_wizard.img);
    CreateCharacter_cancel.width = al_get_bitmap_width(CreateCharacter_cancel.img);
    CreateCharacter_cancel.height = al_get_bitmap_height(CreateCharacter_cancel.img);
    CreateCharacter_confirmok.width = al_get_bitmap_width(CreateCharacter_confirmok.img);
    CreateCharacter_confirmok.height = al_get_bitmap_height(CreateCharacter_confirmok.img);
    CreateCharacter_confirmcancel.width = al_get_bitmap_width(CreateCharacter_confirmcancel.img);
    CreateCharacter_confirmcancel.height = al_get_bitmap_height(CreateCharacter_confirmcancel.img);
}

void CreateCharacter_process(ALLEGRO_EVENT event){
    if(confirm_window == 0){
        create_career_type = choose_career(event);
        if(click_Cancel(event)){
            judge_next_window = true;
            target_window = 1;
        }
        if(create_career_type != 0)
            confirm_window = 1;
    }
    else{
        if(click_confirmCancel(event))
            confirm_window = 0;
        else if(click_confirmOk(event)){
            judge_next_window = true;
            target_window = 5;
        }
    }
}
void CreateCharacter_draw(){
    menu_draw();

    al_draw_bitmap(CreateCharacter_bg.img, 144, 50, 0);

    if(CreateCharacter_warrior.state == 0)
        al_draw_bitmap(CreateCharacter_warrior.img, 230, 135, 0);
    else
        al_draw_bitmap(CreateCharacter_warrior.img_onmouse, 230, 135, 0);
    if(CreateCharacter_archer.state == 0)
        al_draw_bitmap(CreateCharacter_archer.img, 620, 135, 0);
    else
        al_draw_bitmap(CreateCharacter_archer.img_onmouse, 620, 135, 0);
    if(CreateCharacter_wizard.state == 0)
        al_draw_bitmap(CreateCharacter_wizard.img, 1010, 135, 0);
    else
        al_draw_bitmap(CreateCharacter_wizard.img_onmouse, 1010, 135, 0);
    if(CreateCharacter_cancel.state == 0)
        al_draw_bitmap(CreateCharacter_cancel.img, 1370, 20, 0);
    else
        al_draw_bitmap(CreateCharacter_cancel.img_onmouse, 1370, 20, 0);


    if(confirm_window){
        al_draw_bitmap(CreateCharacter_confirmbg.img, 580, 360, 0);
        if(CreateCharacter_confirmok.state == 0)
            al_draw_bitmap(CreateCharacter_confirmok.img, 600, 410, 0);
        else
            al_draw_bitmap(CreateCharacter_confirmok.img_onmouse, 600, 410, 0);
        if(CreateCharacter_confirmcancel.state == 0)
            al_draw_bitmap(CreateCharacter_confirmcancel.img, 815, 410, 0);
        else
            al_draw_bitmap(CreateCharacter_confirmcancel.img_onmouse, 815, 410, 0);
    }
}
int choose_career(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
        if(CreateCharacter_warrior.state)
            return 1;
        if(CreateCharacter_archer.state)
            return 2;
        if(CreateCharacter_wizard.state)
            return 3;
    }
    return 0;
}
bool click_confirmCancel(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
        return CreateCharacter_confirmcancel.state;
    return 0;
}
bool click_confirmOk(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
        return CreateCharacter_confirmok.state;
    return 0;
}
bool click_Cancel(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
        return CreateCharacter_cancel.state;
    return 0;
}

void CreateCharacter_onmouse_check(){
    if(confirm_window == 0){
        CreateCharacter_warrior.state = img_onmouse(230,135,CreateCharacter_warrior.width,CreateCharacter_warrior.height);
        CreateCharacter_archer.state = img_onmouse(620,135,CreateCharacter_archer.width,CreateCharacter_archer.height);
        CreateCharacter_wizard.state = 0;//img_onmouse(1010,135,CreateCharacter_wizard.width,CreateCharacter_wizard.height);
        CreateCharacter_cancel.state = img_onmouse(1370,20,CreateCharacter_cancel.width,CreateCharacter_cancel.height);
    }
    else{
        CreateCharacter_confirmok.state = img_onmouse(600,410,CreateCharacter_confirmok.width,CreateCharacter_confirmok.height);
        CreateCharacter_confirmcancel.state = img_onmouse(815,410,CreateCharacter_confirmcancel.width,CreateCharacter_confirmcancel.height);
    }
}

void CreateCharacter_destroy(){
    confirm_window = 0;
    al_destroy_bitmap(CreateCharacter_bg.img);
    al_destroy_bitmap(CreateCharacter_confirmbg.img);

    al_destroy_bitmap(CreateCharacter_warrior.img);
    al_destroy_bitmap(CreateCharacter_warrior.img_onmouse);
    al_destroy_bitmap(CreateCharacter_archer.img);
    al_destroy_bitmap(CreateCharacter_archer.img_onmouse);
    al_destroy_bitmap(CreateCharacter_wizard.img);
    al_destroy_bitmap(CreateCharacter_wizard.img_onmouse);
    al_destroy_bitmap(CreateCharacter_cancel.img);
    al_destroy_bitmap(CreateCharacter_cancel.img_onmouse);
    al_destroy_bitmap(CreateCharacter_confirmok.img);
    al_destroy_bitmap(CreateCharacter_confirmok.img_onmouse);
    al_destroy_bitmap(CreateCharacter_confirmcancel.img);
    al_destroy_bitmap(CreateCharacter_confirmcancel.img_onmouse);
}
