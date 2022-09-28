#include "forge_window.h"

typedef struct Forge_window{
    int x,y;
    int height,width;
    int display_height,display_width;// for slide slot using
    int display_x,display_y;// for slide slot using
    bool state; // 0=mouse out of region 1=mouse in region
    ALLEGRO_BITMAP *img = NULL;
}forge_windows;
typedef struct Forge_button{
    int x,y;
    int height,width;
    bool state; // 0=mouse out of region 1=mouse in region
    ALLEGRO_BITMAP *img = NULL;
    ALLEGRO_BITMAP *img_onmouse = NULL;
}forge_button;
typedef struct Forge_item{
    bool show;
    ALLEGRO_BITMAP *img = NULL;
    bool type;// 0=equipment 1=item
    int index;// what item/equipment
    int no;
    int equipment_type;
    int num;// numbers of items
    int x,y;
    int width,height;
    int onmouse_time;
    bool if_equip;
    bool if_drag;
    bool state; //check mouse position
}forge_item;
typedef struct Forge_slot{
    bool show;
    ALLEGRO_BITMAP *img = NULL;
    int index;// what equipment
    int no;
    int x,y;
    int width,height;
    int money;
    bool state; //check mouse position
}forge_slot;
int if_draging_forge;
int mouse_z_forge;
bool forge_wheel_state;

forge_windows forge_window;
forge_windows forge_storage_slot;
forge_windows forge_storage_window;
forge_button forge_forge_button;
forge_item forge_storage_item[50];
forge_slot forge_slot_item;

ALLEGRO_BITMAP *forge_window_bg;
ALLEGRO_BITMAP *forge_item_equiping;
ALLEGRO_BITMAP *forge_money;
ALLEGRO_FONT *forge_storage_text = NULL;
ALLEGRO_FONT *forge_money_text = NULL;
ALLEGRO_FONT *forge_level_text = NULL;
double success_rate;
void forge_window_init(){ // 0=weapon 1=item
    forge_storage_text = al_load_ttf_font("./font/pirulen.ttf",20,0);
    forge_money_text = al_load_ttf_font("./font/pirulen.ttf",16,0);
    forge_level_text = al_load_ttf_font("./font/pirulen.ttf",40,0);
    forge_window.img = al_load_bitmap("./image/forging_window/forging_window.png");
    forge_storage_slot.img = al_load_bitmap("./image/item_window/item_storage_slot.png");
    forge_storage_window.img = al_load_bitmap("./image/item_window/item_storage_window.png");
    forge_window_bg = al_load_bitmap("./image/menu/esc/esc_bg.png");
    forge_item_equiping = al_load_bitmap("./image/item_window/item_equiping.png");
    forge_money = al_load_bitmap("./image/item_window/item_money.png");
    forge_forge_button.img = al_load_bitmap("./image/forging_window/forging_window_forging_button.png");
    forge_forge_button.img_onmouse = al_load_bitmap("./image/forging_window/forging_window_forging_button_onmouse.png");

    forge_window.width = al_get_bitmap_width(forge_window.img);
    forge_window.height = al_get_bitmap_height(forge_window.img);
    forge_forge_button.width = al_get_bitmap_width(forge_forge_button.img);
    forge_forge_button.height = al_get_bitmap_height(forge_forge_button.img);
    forge_storage_slot.width = al_get_bitmap_width(forge_storage_slot.img);
    forge_storage_slot.height = al_get_bitmap_height(forge_storage_slot.img);
    forge_storage_window.width = al_get_bitmap_width(forge_storage_window.img);
    forge_storage_window.height = al_get_bitmap_height(forge_storage_window.img);

    if_draging_forge = -1;
    mouse_z_forge=0;
    al_set_mouse_z(0);
    success_rate=1;
    forge_storage_window.x = 840;
    forge_storage_window.y = 97;
    forge_window.x = 153;
    forge_window.y = forge_storage_window.y + forge_storage_window.height/2 - forge_window.height/2;
    forge_forge_button.x = forge_window.x+forge_window.width/2-forge_forge_button.width/2;
    forge_forge_button.y = 605;
    forge_storage_slot.x = 862;
    forge_storage_slot.y = 177;
    forge_storage_slot.display_y=0;
    forge_storage_slot.display_height = 600;
    forge_storage_slot.display_width = forge_storage_window.width;
    forge_slot_item.x=400;
    forge_slot_item.y=430;
    forge_slot_item.width=97;
    forge_slot_item.height=97;
    forge_slot_item.show=0;

    for(int i=0;i<50;i++){
        if(get_storage_num(i) == 0 || get_storage_index(i) == 0){
            forge_storage_item[i].show = 0;
        }
        else{
            forge_storage_item[i].index = get_storage_index(i);
            forge_storage_item[i].type = get_storage_type(i);
            if(forge_storage_item[i].type == 0){
                forge_storage_item[i].equipment_type = get_storage_equipment_type(i);
                forge_storage_item[i].no = get_storage_no(i);
            }
            forge_storage_item[i].num = get_storage_num(i);
            forge_storage_item[i].show = 1;
            char temp[50];
            sprintf( temp, "./image/item/item_type%d_index%d.png", forge_storage_item[i].type, forge_storage_item[i].index);
            forge_storage_item[i].img = al_load_bitmap(temp);
        }

        forge_storage_item[i].x = 871 + 108*(i%5);
        forge_storage_item[i].y = 183 + 106*(int)(i/5);
        forge_storage_item[i].width = 97;
        forge_storage_item[i].height = 97;
        forge_storage_item[i].onmouse_time = 0;

        forge_storage_item[i].if_drag=0;
        forge_storage_item[i].if_equip=get_storage_ifequip(i);
    }

}
void forge_process(ALLEGRO_EVENT event){
    forge_item_drag(event);
    forge_click(event);
    if( event.timer.source == fps ){
        for(int i=0;i<50;i++){
            if(forge_storage_item[i].state && forge_storage_item[i].show)
                forge_storage_item[i].onmouse_time++;
            else
                forge_storage_item[i].onmouse_time=0;
        }

    }
}

void forge_click(ALLEGRO_EVENT event){
    success_rate=(double)1/pow(1.05,get_equipment_status_enhancement_level(forge_slot_item.no));
    forge_slot_item.money = ((get_equipment_status_lv(forge_slot_item.no)/10+1)*1000)*(1+get_equipment_status_enhancement_level(forge_slot_item.no));
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
        if(forge_forge_button.state && forge_slot_item.show && get_equipment_status_enhancement_level(forge_slot_item.no)<99 && get_chara_money()-forge_slot_item.money>=0){
            if(get_rand( 1, round((double)1/success_rate*(double)1000))<=1000){
                int now_lv = get_equipment_status_enhancement_level(forge_slot_item.no);
                set_equipment_status_enhancement_level(forge_slot_item.no,now_lv+1);
                set_equipment_status_hp(forge_slot_item.no,ceil((double)get_equipment_status_hp(forge_slot_item.no)*1.05));
                set_equipment_status_mp(forge_slot_item.no,ceil((double)get_equipment_status_mp(forge_slot_item.no)*1.05));
                set_equipment_status_atk(forge_slot_item.no,ceil((double)get_equipment_status_atk(forge_slot_item.no)*1.05));
                set_equipment_status_def(forge_slot_item.no,ceil((double)get_equipment_status_def(forge_slot_item.no)*1.05));
                set_equipment_status_atkP(forge_slot_item.no,ceil((double)get_equipment_status_atkP(forge_slot_item.no)*1.05));
                set_chara_money(get_chara_money()-forge_slot_item.money);
            }

        }
    }
}
void forge_draw(){

    al_draw_bitmap(forge_window_bg, 0, 0, 0);
    al_draw_filled_rounded_rectangle(forge_storage_window.x, forge_storage_window.y - 40, forge_storage_window.x + forge_storage_window.width/2, forge_storage_window.y+100, 8, 8, al_map_rgb(45,47,59));
    char text_money[10];
    sprintf(text_money,"%d",get_chara_money());
    al_draw_text(forge_storage_text, al_map_rgb(253,214,3), forge_storage_window.x + forge_storage_window.width/2-5, forge_storage_window.y - 35,ALLEGRO_ALIGN_RIGHT ,text_money);
    al_draw_bitmap(forge_money, forge_storage_window.x+5, forge_storage_window.y-35, 0);
    al_draw_bitmap(forge_window.img, forge_window.x, forge_window.y, 0);
    al_draw_bitmap(forge_storage_window.img, forge_storage_window.x, forge_storage_window.y, 0);
    if(forge_forge_button.state)
        al_draw_bitmap(forge_forge_button.img_onmouse, forge_forge_button.x, forge_forge_button.y, 0);
    else
        al_draw_bitmap(forge_forge_button.img, forge_forge_button.x, forge_forge_button.y, 0);

    al_draw_bitmap_region(forge_storage_slot.img, 0, forge_storage_slot.display_y, forge_storage_slot.display_width, forge_storage_slot.display_height,forge_storage_slot.x,forge_storage_slot.y,0);

    for(int i=0;i<50;i++){
        if(forge_storage_item[i].show){
            al_draw_bitmap_region(forge_storage_item[i].img, -forge_storage_item[i].x+forge_storage_slot.x, -forge_storage_item[i].y+forge_storage_slot.y+forge_storage_slot.display_y, forge_storage_slot.display_width, forge_storage_slot.display_height,forge_storage_slot.x,forge_storage_slot.y,0);
            if(forge_storage_item[i].type && forge_storage_item[i].y-forge_storage_slot.display_y+forge_storage_item[i].height>=forge_storage_slot.y && forge_storage_item[i].y-forge_storage_slot.display_y+forge_storage_item[i].height< forge_storage_slot.y+forge_storage_slot.display_height){
                char text[10];
                sprintf(text,"%d",forge_storage_item[i].num);
                al_draw_text(forge_storage_text, al_map_rgb(255,255,255), forge_storage_item[i].x+94, forge_storage_item[i].y-forge_storage_slot.display_y+70,ALLEGRO_ALIGN_RIGHT ,text);
            }
            if(forge_storage_item[i].if_equip)
                al_draw_bitmap_region(forge_item_equiping, -forge_storage_item[i].x+forge_storage_slot.x, -forge_storage_item[i].y+forge_storage_slot.y+forge_storage_slot.display_y, forge_storage_slot.display_width, forge_storage_slot.display_height,forge_storage_slot.x,forge_storage_slot.y,0);
        }
    }
    if(forge_slot_item.show){
        al_draw_bitmap(forge_slot_item.img,forge_slot_item.x,forge_slot_item.y,0);
        sprintf(text_money,"%d",forge_slot_item.money);
        al_draw_text(forge_money_text, al_map_rgb(253,214,3), forge_window.x + forge_window.width/2+85, forge_window.y +363,ALLEGRO_ALIGN_RIGHT ,text_money);
        sprintf(text_money,"%d",get_equipment_status_enhancement_level(forge_slot_item.no));
        al_draw_text(forge_level_text, al_map_rgb(255,255,255), forge_window.x + forge_window.width/2, forge_window.y +135,ALLEGRO_ALIGN_CENTER ,text_money);
        sprintf(text_money,"%.1f",success_rate*(double)100);
        char rate_text[20]="Success rate: ";
        strcat(rate_text,text_money);
        strcat(rate_text,"%");
        al_draw_text(forge_storage_text, al_map_rgb(255,255,255), forge_window.x+30, forge_window.y +470,ALLEGRO_ALIGN_LEFT ,rate_text);
    }

    for(int i=0;i<50;i++)
        if(forge_storage_item[i].if_drag)
            al_draw_bitmap(forge_storage_item[i].img, get_mouse_x()-forge_storage_item[i].width/2, get_mouse_y()-forge_storage_item[i].height/2,0);
    if(if_draging_forge == -1){
        for(int i=0;i<50;i++)
            if(forge_storage_item[i].onmouse_time>=30){
                forge_item_detail_draw(i);
                break;
            }
    }
}
void forge_window_mouse_check(){
    forge_forge_button.state = img_onmouse(forge_forge_button.x,forge_forge_button.y,forge_forge_button.width,forge_forge_button.height);
    forge_storage_slot.state = img_onmouse(forge_storage_slot.x,forge_storage_slot.y,forge_storage_slot.display_width,forge_storage_slot.display_height);
    forge_slot_item.state = img_onmouse(forge_slot_item.x,forge_slot_item.y,forge_slot_item.width,forge_slot_item.height);
    for(int i=0;i<50;i++){
        if(forge_storage_item[i].y-forge_storage_slot.display_y+forge_storage_item[i].height<forge_storage_slot.y)
            forge_storage_item[i].state = 0;
        else if(forge_storage_item[i].y-forge_storage_slot.display_y<=forge_storage_slot.y && forge_storage_item[i].y-forge_storage_slot.display_y+forge_storage_item[i].height>forge_storage_slot.y)
            forge_storage_item[i].state = img_onmouse(forge_storage_item[i].x,forge_storage_slot.y,forge_storage_item[i].width, forge_storage_item[i].y-forge_storage_slot.display_y+forge_storage_item[i].height - forge_storage_slot.y );
        else if(forge_storage_item[i].y-forge_storage_slot.display_y>=forge_storage_slot.y && forge_storage_item[i].y-forge_storage_slot.display_y+forge_storage_item[i].height<forge_storage_slot.y+forge_storage_slot.display_height)
            forge_storage_item[i].state = img_onmouse(forge_storage_item[i].x, forge_storage_item[i].y-forge_storage_slot.display_y, forge_storage_item[i].width,  forge_storage_item[i].height);
        else if(forge_storage_item[i].y-forge_storage_slot.display_y+forge_storage_item[i].height>=forge_storage_slot.y+forge_storage_slot.display_height && forge_storage_item[i].y-forge_storage_slot.display_y<forge_storage_slot.y+forge_storage_slot.display_height)
            forge_storage_item[i].state = img_onmouse(forge_storage_item[i].x, forge_storage_item[i].y-forge_storage_slot.display_y, forge_storage_item[i].width, forge_storage_slot.y+forge_storage_slot.display_height-(forge_storage_item[i].y-forge_storage_slot.display_y));
        else
            forge_storage_item[i].state = 0;
    }

}
void forge_window_wheel(){


    if(forge_storage_slot.state && mouse_z_forge!=get_mouse_z()){
        forge_storage_slot.display_y += -(get_mouse_z()-mouse_z_forge)*40;
        if(forge_storage_slot.display_y<0)
            forge_storage_slot.display_y=0;
        else if(forge_storage_slot.display_y+forge_storage_slot.display_height>forge_storage_slot.height)
            forge_storage_slot.display_y = forge_storage_slot.height-forge_storage_slot.display_height;
    }

    mouse_z_forge=get_mouse_z();
}
void forge_item_drag(ALLEGRO_EVENT event){

    if(if_draging_forge == -1 ){
        if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
            for(int i=0;i<50;i++){
                if(forge_storage_item[i].show && forge_storage_item[i].state && forge_storage_item[i].if_equip ==0){
                    forge_storage_item[i].if_drag = 1;
                    forge_storage_item[i].show = 0;
                    if_draging_forge=i;
                    break;
                }
            }
        }
    }
    else{
        if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            if(forge_storage_item[if_draging_forge].if_drag){
                if(forge_slot_item.state && forge_storage_item[if_draging_forge].type==0){
                    forge_slot_item.show = 1;
                    forge_slot_item.no = forge_storage_item[if_draging_forge].no;
                    forge_slot_item.index = forge_storage_item[if_draging_forge].index;
                    forge_slot_item.img = forge_storage_item[if_draging_forge].img;
                    forge_slot_item.money = (get_equipment_status_lv(forge_slot_item.no)*1000)*(1+(float)get_equipment_status_enhancement_level(forge_slot_item.no)/5);
                }
                forge_storage_item[if_draging_forge].show = 1;
                forge_storage_item[if_draging_forge].if_drag = 0;
            }
            if_draging_forge=-1;
        }
    }
}
void forge_item_detail_draw(int i){
    bool type = forge_storage_item[i].type;
    int index = forge_storage_item[i].index;
    if(type == 0){
        int detail_num=0;
        int no = forge_storage_item[i].no;
        int status[7];
        status[0]=get_equipment_status_lv(no);
        status[1]=get_equipment_status_hp(no);
        status[2]=get_equipment_status_mp(no);
        status[3]=get_equipment_status_atk(no);
        status[4]=get_equipment_status_def(no);
        status[5]=get_equipment_status_atkP(no);
        status[6]=get_equipment_status_money(no);
        for(int i=0;i<7;i++)
            if(status[i]>0)
                detail_num++;
        al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+10+30*detail_num,5, 5, al_map_rgba(10,10,25,180));
        detail_num=0;
        for(int i=0;i<7;i++){
            if(status[i]>0){
                char text[20];
                if(i==0)
                    strcpy(text,"LV:");
                else if(i==1)
                    strcpy(text,"HP:");
                else if(i==2)
                    strcpy(text,"MP:");
                else if(i==3)
                    strcpy(text,"ATK:");
                else if(i==4)
                    strcpy(text,"DEF:");
                else if(i==5)
                    strcpy(text,"ATKP:");
                else if(i==6)
                    strcpy(text,"MONEY:");
                char num_text[10];
                sprintf(num_text,"%d",status[i]);
                strcat(text,num_text);
                al_draw_text(forge_storage_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10+detail_num*30,ALLEGRO_ALIGN_CENTER,text);
                detail_num++;
            }
        }
    }
    else if(type == 1){
        if(index == 1){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+40,5, 5, al_map_rgba(10,10,25,180));
            char text[10]="HP +25%";
            al_draw_text(forge_storage_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text);
        }
        else if(index == 2){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+40,5, 5, al_map_rgba(10,10,25,180));
            char text[10]="MP +25%";
            al_draw_text(forge_storage_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text);
        }
        else if(index == 3){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+40,5, 5, al_map_rgba(10,10,25,180));
            char text[10]="HP +50%";
            al_draw_text(forge_storage_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text);
        }
        else if(index == 4){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+40,5, 5, al_map_rgba(10,10,25,180));
            char text[10]="MP +50%";
            al_draw_text(forge_storage_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text);
        }
        else if(index == 5){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+70,5, 5, al_map_rgba(10,10,25,180));
            char text1[10]="HP +100%";
            al_draw_text(forge_storage_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text1);
            char text2[10]="HP +100%";
            al_draw_text(forge_storage_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+40,ALLEGRO_ALIGN_CENTER,text2);
        }
        else if(index == 6){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+40,5, 5, al_map_rgba(10,10,25,180));
            char text[10]="Level Up";
            al_draw_text(forge_storage_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text);
        }
    }
}
void forge_storage_reload(){
    for(int i=0;i<50;i++){
        al_destroy_bitmap(forge_storage_item[i].img);
        if(get_storage_num(i) == 0 || get_storage_index(i) == 0){
            forge_storage_item[i].show = 0;
        }
        else{
            forge_storage_item[i].index = get_storage_index(i);
            forge_storage_item[i].type = get_storage_type(i);
            if(forge_storage_item[i].type == 0){
                forge_storage_item[i].equipment_type = get_storage_equipment_type(i);
                forge_storage_item[i].no = get_storage_no(i);
            }
            forge_storage_item[i].num = get_storage_num(i);
            forge_storage_item[i].show = 1;
            char temp[50];
            sprintf( temp, "./image/item/item_type%d_index%d.png", forge_storage_item[i].type, forge_storage_item[i].index);
            forge_storage_item[i].img = al_load_bitmap(temp);
        }
        forge_storage_item[i].onmouse_time = 0;
        forge_storage_item[i].if_drag=0;
        forge_storage_item[i].if_equip=get_storage_ifequip(i);
    }
}
void forge_destory(){
    al_destroy_bitmap(forge_window.img);
    al_destroy_bitmap(forge_storage_slot.img);
    al_destroy_bitmap(forge_storage_window.img);
    al_destroy_bitmap(forge_forge_button.img);
    al_destroy_bitmap(forge_forge_button.img_onmouse);
    for(int i=0;i<50;i++)
        if(forge_storage_item[i].show)
            al_destroy_bitmap(forge_storage_item[i].img);
    al_destroy_bitmap(forge_window_bg);
    al_destroy_bitmap(forge_item_equiping);
    al_destroy_bitmap(forge_money);
    al_destroy_font(forge_storage_text);
}
