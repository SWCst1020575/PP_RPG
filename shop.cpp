#include "shop.h"

typedef struct Shop_window{
    int x,y;
    int height,width;
    int display_height,display_width;// for slide slot using
    int display_x,display_y;// for slide slot using
    bool state; // 0=mouse out of region 1=mouse in region
    ALLEGRO_BITMAP *img = NULL;
}shop_windows;
typedef struct Shop_button{
    int x,y;
    int height,width;
    bool state; // 0=mouse out of region 1=mouse in region
    ALLEGRO_BITMAP *img = NULL;
    ALLEGRO_BITMAP *img_onmouse = NULL;
}shop_button;
typedef struct Shop_item{
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
}shop_item;
typedef struct Shop_merchandise{
    bool show;
    ALLEGRO_BITMAP *img = NULL;
    ALLEGRO_BITMAP *bg = NULL;
    bool type;// 0=equipment 1=item
    int index;// what item/equipment
    int num;// numbers of items
    int x,y;
    int icon_x,icon_y;
    int width,height;
    int money;
    bool if_first_click;
    int first_click_time;
    bool state; //check mouse position
}shop_merchandise;
int if_draging_shop;
int mouse_z_shop;
bool shop_wheel_state;

shop_windows shop_window;
shop_windows shop_storage_slot;
shop_windows shop_storage_window;
shop_button shop_sell_button;
shop_item storage_item[50];
shop_merchandise shop_list[5];

ALLEGRO_BITMAP *shop_window_bg;
ALLEGRO_BITMAP *shop_merchandise_bg;
ALLEGRO_BITMAP *shop_item_equiping;
ALLEGRO_BITMAP *shop_money;
ALLEGRO_FONT *shop_num_text = NULL;

void shop_window_init(){ // 0=weapon 1=item
    shop_num_text = al_load_ttf_font("./font/pirulen.ttf",20,0);
    shop_window.img = al_load_bitmap("./image/shop/shop_window.png");
    shop_merchandise_bg = al_load_bitmap("./image/shop/shop_merchandise.png");
    shop_storage_slot.img = al_load_bitmap("./image/item_window/item_storage_slot.png");
    shop_storage_window.img = al_load_bitmap("./image/item_window/item_storage_window.png");
    shop_window_bg = al_load_bitmap("./image/menu/esc/esc_bg.png");
    shop_item_equiping = al_load_bitmap("./image/item_window/item_equiping.png");
    shop_money = al_load_bitmap("./image/item_window/item_money.png");
    shop_sell_button.img = al_load_bitmap("./image/shop/shop_sell_button.png");
    shop_sell_button.img_onmouse = al_load_bitmap("./image/shop/shop_sell_button_onmouse.png");

    shop_window.width = al_get_bitmap_width(shop_window.img);
    shop_window.height = al_get_bitmap_height(shop_window.img);
    shop_sell_button.width = al_get_bitmap_width(shop_sell_button.img);
    shop_sell_button.height = al_get_bitmap_height(shop_sell_button.img);
    shop_storage_slot.width = al_get_bitmap_width(shop_storage_slot.img);
    shop_storage_slot.height = al_get_bitmap_height(shop_storage_slot.img);
    shop_storage_window.width = al_get_bitmap_width(shop_storage_window.img);
    shop_storage_window.height = al_get_bitmap_height(shop_storage_window.img);

    if_draging_shop = -1;
    mouse_z_shop=0;
    al_set_mouse_z(0);

    shop_window.x = 153;
    shop_window.y = 97;
    shop_sell_button.x = shop_window.x+shop_window.width/2-shop_sell_button.width/2;
    shop_sell_button.y = 745;
    shop_storage_window.x = 840;
    shop_storage_window.y = 97;
    shop_storage_slot.x = 862;
    shop_storage_slot.y = 177;
    shop_storage_slot.display_y=0;
    shop_storage_slot.display_height = 600;
    shop_storage_slot.display_width = shop_storage_window.width;
    for(int i=0;i<5;i++){
        shop_list[i].bg = shop_merchandise_bg;
        shop_list[i].width = al_get_bitmap_width(shop_list[i].bg);
        shop_list[i].height = al_get_bitmap_height(shop_list[i].bg);
        shop_list[i].show = 1;
        shop_list[i].x = shop_window.x+shop_window.width/2-shop_list[i].width/2;
        shop_list[i].y = 190+135*i;
        if(shop_type == 0){
            if(i==4){
                if(get_chara_career() == 1){
                    char temp[50];
                    sprintf( temp, "./image/item/item_type0_index5.png");
                    shop_list[i].img = al_load_bitmap(temp);
                }
                else if(get_chara_career() == 2){
                    char temp[50];
                    sprintf( temp, "./image/item/item_type0_index6.png");
                    shop_list[i].img = al_load_bitmap(temp);
                }
            }
            else{
                char temp[50];
                sprintf( temp, "./image/item/item_type0_index%d.png",i+1);
                shop_list[i].img = al_load_bitmap(temp);
            }
            shop_list[i].money = get_chara_lv()*get_rand(9000,11000);
        }
        else{
            char temp[50];
            sprintf( temp, "./image/item/item_type1_index%d.png",i+1);
            shop_list[i].img = al_load_bitmap(temp);
            if(i==0 || i==1)
                shop_list[i].money = (get_chara_lv()*300+500)*5;
            else if(i==2 || i==3)
                shop_list[i].money = (get_chara_lv()*600+1000)*5;
            else if(i==4)
                shop_list[i].money = (get_chara_lv()*1500+3000)*5;
        }
        shop_list[i].icon_x=shop_list[i].x+13;
        shop_list[i].icon_y=shop_list[i].y+13;
        shop_list[i].if_first_click=0;
        shop_list[i].first_click_time=0;

    }
    shop_window.display_y=0;
    shop_window.display_height = 545;
    shop_window.display_width = shop_list[0].width;


    for(int i=0;i<50;i++){
        if(get_storage_num(i) == 0 || get_storage_index(i) == 0){
            storage_item[i].show = 0;
        }
        else{
            storage_item[i].index = get_storage_index(i);
            storage_item[i].type = get_storage_type(i);
            if(storage_item[i].type == 0){
                storage_item[i].equipment_type = get_storage_equipment_type(i);
                storage_item[i].no = get_storage_no(i);
            }
            storage_item[i].num = get_storage_num(i);
            storage_item[i].show = 1;
            char temp[50];
            sprintf( temp, "./image/item/item_type%d_index%d.png", storage_item[i].type, storage_item[i].index);
            storage_item[i].img = al_load_bitmap(temp);
        }

        storage_item[i].x = 871 + 108*(i%5);
        storage_item[i].y = 183 + 106*(int)(i/5);
        storage_item[i].width = 97;
        storage_item[i].height = 97;
        storage_item[i].onmouse_time = 0;

        storage_item[i].if_drag=0;
        storage_item[i].if_equip=get_storage_ifequip(i);
    }
}
void shop_process(ALLEGRO_EVENT event){
    shop_item_drag(event);
    shop_buy(event);
    if( event.timer.source == fps ){
        for(int i=0;i<50;i++){
            if(storage_item[i].state && storage_item[i].show)
                storage_item[i].onmouse_time++;
            else
                storage_item[i].onmouse_time=0;
        }
        for(int i=0;i<5;i++)
            if(shop_list[i].if_first_click)
                shop_list[i].first_click_time++;
    }
}

void shop_buy(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
        for(int i=0;i<5;i++){
            if(shop_list[i].if_first_click == 0 && shop_list[i].state)
                shop_list[i].if_first_click =1;
        }
    }
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
        for(int i=0;i<5;i++){
            if(shop_list[i].if_first_click && shop_list[i].first_click_time<=10 && shop_list[i].state){
                if(get_storage_total_num()<=50 && get_chara_money()>=shop_list[i].money){
                    if(shop_type==0){
                        if(i==4){
                            if(get_chara_career()==1)
                                get_equipment(5,1,i);
                        }
                        else
                            get_equipment(i+1,1,i);
                    }
                    else
                        get_item(i+1,5);
                    storage_reload();
                    set_chara_money(get_chara_money()-shop_list[i].money);
                }
            }
            else
                shop_list[i].first_click_time =0;
            shop_list[i].if_first_click =0;
        }
    }
}
void shop_draw(){
    al_draw_bitmap(shop_window_bg, 0, 0, 0);
    al_draw_filled_rounded_rectangle(shop_storage_window.x, shop_storage_window.y - 40, shop_storage_window.x + shop_storage_window.width/2, shop_storage_window.y+100, 8, 8, al_map_rgb(45,47,59));
    char text_money[10];
    sprintf(text_money,"%d",get_chara_money());
    al_draw_text(shop_num_text, al_map_rgb(253,214,3), shop_storage_window.x + shop_storage_window.width/2-5, shop_storage_window.y - 35,ALLEGRO_ALIGN_RIGHT ,text_money);
    al_draw_bitmap(shop_money, shop_storage_window.x+5, shop_storage_window.y-35, 0);
    al_draw_bitmap(shop_window.img, shop_window.x, shop_window.y, 0);
    al_draw_bitmap(shop_storage_window.img, shop_storage_window.x, shop_storage_window.y, 0);
    if(shop_sell_button.state)
        al_draw_bitmap(shop_sell_button.img_onmouse, shop_sell_button.x, shop_sell_button.y, 0);
    else
        al_draw_bitmap(shop_sell_button.img, shop_sell_button.x, shop_sell_button.y, 0);

    al_draw_bitmap_region(shop_storage_slot.img, 0, shop_storage_slot.display_y, shop_storage_slot.display_width, shop_storage_slot.display_height,shop_storage_slot.x,shop_storage_slot.y,0);

    for(int i=0;i<50;i++){
        if(storage_item[i].show){
            al_draw_bitmap_region(storage_item[i].img, -storage_item[i].x+shop_storage_slot.x, -storage_item[i].y+shop_storage_slot.y+shop_storage_slot.display_y, shop_storage_slot.display_width, shop_storage_slot.display_height,shop_storage_slot.x,shop_storage_slot.y,0);
            if(storage_item[i].type && storage_item[i].y-shop_storage_slot.display_y+storage_item[i].height>=shop_storage_slot.y && storage_item[i].y-shop_storage_slot.display_y+storage_item[i].height< shop_storage_slot.y+shop_storage_slot.display_height){
                char text[10];
                sprintf(text,"%d",storage_item[i].num);
                al_draw_text(shop_num_text, al_map_rgb(255,255,255), storage_item[i].x+94, storage_item[i].y-shop_storage_slot.display_y+70,ALLEGRO_ALIGN_RIGHT ,text);
            }
            if(storage_item[i].if_equip)
                al_draw_bitmap_region(shop_item_equiping, -storage_item[i].x+shop_storage_slot.x, -storage_item[i].y+shop_storage_slot.y+shop_storage_slot.display_y, shop_storage_slot.display_width, shop_storage_slot.display_height,shop_storage_slot.x,shop_storage_slot.y,0);
        }
    }
    for(int i=0;i<5;i++){
        if(shop_list[i].y-shop_window.display_y+shop_list[i].height>=shop_list[0].y)
            al_draw_bitmap_region(shop_list[i].bg, 0, -shop_list[i].y+shop_list[0].y+shop_window.display_y, shop_window.display_width, shop_window.display_height,shop_list[0].x,shop_list[0].y,0);
        al_draw_bitmap_region(shop_list[i].img, 0, -shop_list[i].icon_y+shop_list[0].y+shop_window.display_y, shop_window.display_width, shop_window.display_height,shop_list[0].icon_x,shop_list[0].y,0);
        if(shop_list[i].y-shop_window.display_y+80>=shop_list[0].y && shop_list[i].y-shop_window.display_y+80<=shop_list[0].y+shop_window.display_height){
            char text[10];
            sprintf(text,"%d",shop_list[i].money);
            al_draw_text(shop_num_text, al_map_rgb(253,214,3), shop_list[i].x+shop_list[i].width-15, shop_list[i].y-shop_window.display_y+78,ALLEGRO_ALIGN_RIGHT ,text);
        }
        if(shop_list[i].y-shop_window.display_y+84>=shop_list[0].y && shop_list[i].y-shop_window.display_y+88<=shop_list[0].y+shop_window.display_height && shop_type == 1){
            char text_merchandise_num[5]="x5";
            al_draw_text(shop_num_text, al_map_rgb(255,255,255), shop_list[i].x+108, shop_list[i].y-shop_window.display_y+82,ALLEGRO_ALIGN_RIGHT ,text_merchandise_num);
        }
    }

    for(int i=0;i<50;i++)
        if(storage_item[i].if_drag)
            al_draw_bitmap(storage_item[i].img, get_mouse_x()-storage_item[i].width/2, get_mouse_y()-storage_item[i].height/2,0);
    if(if_draging_shop == -1){
        for(int i=0;i<50;i++)
            if(storage_item[i].onmouse_time>=30){
                shop_item_detail_draw(i);
                break;
            }
    }
}
void shop_window_mouse_check(){
    shop_sell_button.state = img_onmouse(shop_sell_button.x,shop_sell_button.y,shop_sell_button.width,shop_sell_button.height);
    shop_storage_slot.state = img_onmouse(shop_storage_slot.x,shop_storage_slot.y,shop_storage_slot.display_width,shop_storage_slot.display_height);
    shop_wheel_state = img_onmouse(shop_list[0].x-5,shop_list[0].y-5,shop_window.display_width+10,shop_window.display_height+10);
    for(int i=0;i<50;i++){
        if(storage_item[i].y-shop_storage_slot.display_y+storage_item[i].height<shop_storage_slot.y)
            storage_item[i].state = 0;
        else if(storage_item[i].y-shop_storage_slot.display_y<=shop_storage_slot.y && storage_item[i].y-shop_storage_slot.display_y+storage_item[i].height>shop_storage_slot.y)
            storage_item[i].state = img_onmouse(storage_item[i].x,shop_storage_slot.y,storage_item[i].width, storage_item[i].y-shop_storage_slot.display_y+storage_item[i].height - shop_storage_slot.y );
        else if(storage_item[i].y-shop_storage_slot.display_y>=shop_storage_slot.y && storage_item[i].y-shop_storage_slot.display_y+storage_item[i].height<shop_storage_slot.y+shop_storage_slot.display_height)
            storage_item[i].state = img_onmouse(storage_item[i].x, storage_item[i].y-shop_storage_slot.display_y, storage_item[i].width,  storage_item[i].height);
        else if(storage_item[i].y-shop_storage_slot.display_y+storage_item[i].height>=shop_storage_slot.y+shop_storage_slot.display_height && storage_item[i].y-shop_storage_slot.display_y<shop_storage_slot.y+shop_storage_slot.display_height)
            storage_item[i].state = img_onmouse(storage_item[i].x, storage_item[i].y-shop_storage_slot.display_y, storage_item[i].width, shop_storage_slot.y+shop_storage_slot.display_height-(storage_item[i].y-shop_storage_slot.display_y));
        else
            storage_item[i].state = 0;
    }
    for(int i=0;i<5;i++){
        if(shop_list[i].y-shop_window.display_y+shop_list[i].height<shop_list[0].y)
            shop_list[i].state = 0;
        else if(shop_list[i].y-shop_window.display_y+shop_list[i].height>=shop_list[0].y && shop_list[i].y-shop_window.display_y<shop_list[0].y)
            shop_list[i].state = img_onmouse(shop_list[i].x,shop_list[0].y,shop_list[i].width, shop_list[i].y-shop_window.display_y+shop_list[i].height - shop_list[0].y );
        else if(shop_list[i].y-shop_window.display_y>=shop_list[0].y && shop_list[i].y-shop_window.display_y+shop_list[i].height<=shop_list[0].y+shop_window.display_height)
            shop_list[i].state = img_onmouse(shop_list[i].x,shop_list[i].y-shop_window.display_y,shop_list[i].width,shop_list[i].height);
        else if(shop_list[i].y-shop_window.display_y+shop_list[i].height>shop_list[0].y+shop_window.display_height && shop_list[i].y-shop_window.display_y<=shop_list[0].y+shop_window.display_height)
            shop_list[i].state = img_onmouse(shop_list[i].x,shop_list[i].y-shop_window.display_y,shop_list[i].width, shop_list[0].y+shop_window.display_height-shop_list[i].y+shop_window.display_y );
        else
            shop_list[i].state = 0;
    }
}
void shop_window_wheel(){


    if(shop_storage_slot.state && mouse_z_shop!=get_mouse_z()){
        shop_storage_slot.display_y += -(get_mouse_z()-mouse_z_shop)*40;
        if(shop_storage_slot.display_y<0)
            shop_storage_slot.display_y=0;
        else if(shop_storage_slot.display_y+shop_storage_slot.display_height>shop_storage_slot.height)
            shop_storage_slot.display_y = shop_storage_slot.height-shop_storage_slot.display_height;
    }
    if(shop_wheel_state && mouse_z_shop!=get_mouse_z()){
        shop_window.display_y += -(get_mouse_z()-mouse_z_shop)*40;
        if(shop_window.display_y<0)
            shop_window.display_y=0;
        else if(shop_window.display_y+shop_window.display_height>shop_list[4].y-shop_list[0].y+shop_list[4].height+10)
            shop_window.display_y = shop_list[4].y-shop_list[0].y+shop_list[4].height+10-shop_window.display_height;
    }

    mouse_z_shop=get_mouse_z();
}
void shop_item_drag(ALLEGRO_EVENT event){

    if(if_draging_shop == -1 ){
        if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
            for(int i=0;i<50;i++){
                if(storage_item[i].show && storage_item[i].state && storage_item[i].if_equip ==0){
                    storage_item[i].if_drag = 1;
                    storage_item[i].show = 0;
                    if_draging_shop=i;
                    break;
                }
            }
        }
    }
    else{
        if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            if(storage_item[if_draging_shop].if_drag){
                if(shop_sell_button.state && storage_item[if_draging_shop].type == 0){
                    set_chara_money(get_chara_money()+get_equipment_status_money(storage_item[if_draging_shop].no));
                    sell_equiment(if_draging_shop);
                }
                else
                    storage_item[if_draging_shop].show = 1;
                storage_item[if_draging_shop].if_drag = 0;
            }
            if_draging_shop=-1;
        }
    }
}
void shop_item_detail_draw(int i){
    bool type = storage_item[i].type;
    int index = storage_item[i].index;
    if(type == 0){
        int detail_num=0;
        int no = storage_item[i].no;
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
                al_draw_text(shop_num_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10+detail_num*30,ALLEGRO_ALIGN_CENTER,text);
                detail_num++;
            }
        }
    }
    else if(type == 1){
        if(index == 1){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+40,5, 5, al_map_rgba(10,10,25,180));
            char text[10]="HP +25%";
            al_draw_text(shop_num_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text);
        }
        else if(index == 2){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+40,5, 5, al_map_rgba(10,10,25,180));
            char text[10]="MP +25%";
            al_draw_text(shop_num_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text);
        }
        else if(index == 3){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+40,5, 5, al_map_rgba(10,10,25,180));
            char text[10]="HP +50%";
            al_draw_text(shop_num_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text);
        }
        else if(index == 4){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+40,5, 5, al_map_rgba(10,10,25,180));
            char text[10]="MP +50%";
            al_draw_text(shop_num_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text);
        }
        else if(index == 5){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+70,5, 5, al_map_rgba(10,10,25,180));
            char text1[10]="HP +100%";
            al_draw_text(shop_num_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text1);
            char text2[10]="HP +100%";
            al_draw_text(shop_num_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+40,ALLEGRO_ALIGN_CENTER,text2);
        }
        else if(index == 6){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+40,5, 5, al_map_rgba(10,10,25,180));
            char text[10]="Level Up";
            al_draw_text(shop_num_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text);
        }
    }
}
void storage_reload(){
    for(int i=0;i<50;i++){
        al_destroy_bitmap(storage_item[i].img);
        if(get_storage_num(i) == 0 || get_storage_index(i) == 0){
            storage_item[i].show = 0;
        }
        else{
            storage_item[i].index = get_storage_index(i);
            storage_item[i].type = get_storage_type(i);
            if(storage_item[i].type == 0){
                storage_item[i].equipment_type = get_storage_equipment_type(i);
                storage_item[i].no = get_storage_no(i);
            }
            storage_item[i].num = get_storage_num(i);
            storage_item[i].show = 1;
            char temp[50];
            sprintf( temp, "./image/item/item_type%d_index%d.png", storage_item[i].type, storage_item[i].index);
            storage_item[i].img = al_load_bitmap(temp);
        }
        storage_item[i].onmouse_time = 0;
        storage_item[i].if_drag=0;
        storage_item[i].if_equip=get_storage_ifequip(i);
    }
}
void shop_destory(){
    al_destroy_bitmap(shop_window.img);
    al_destroy_bitmap(shop_storage_slot.img);
    al_destroy_bitmap(shop_storage_window.img);
    al_destroy_bitmap(shop_sell_button.img);
    al_destroy_bitmap(shop_sell_button.img_onmouse);
    for(int i=0;i<50;i++)
        if(storage_item[i].show)
            al_destroy_bitmap(storage_item[i].img);
    for(int i=0;i<5;i++)
        al_destroy_bitmap(shop_list[i].img);
    al_destroy_bitmap(shop_window_bg);
    al_destroy_bitmap(shop_merchandise_bg);
    al_destroy_bitmap(shop_item_equiping);
    al_destroy_bitmap(shop_money);
    al_destroy_font(shop_num_text);
}
