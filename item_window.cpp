#include "item_window.h"

typedef struct Item_window{
    int x,y;
    int height,width;
    int display_height,display_width;// for slide slot using
    int display_x,display_y;// for slide slot using
    bool state; // 0=mouse in region 1=mouse in region
    ALLEGRO_BITMAP *img = NULL;
}item_windows;

typedef struct Item{
    bool show;
    ALLEGRO_BITMAP *img = NULL;
    bool type;// 0=equipment 1=item
    int equipment_type;//0=hat 1=clothe 2=gloves 3=shoes 4=weapon
    int no;//for equipment(link to the status of equipment)
    int index;// what item/equipment
    int num;// numbers of items
    int storage_pos;
    int x,y;
    int width,height;
    int onmouse_time;
    bool if_equip;
    bool if_drag;
    bool state; //check mouse positon
}item;
item Storage[50];
item Equipment[5];
item Item_slot[9];

item_windows equipment_window;
item_windows item_slot;
item_windows item_window;
item_windows storage_slot;
item_windows storage_window;
ALLEGRO_BITMAP *item_window_bg;
ALLEGRO_BITMAP *item_equiping;
ALLEGRO_BITMAP *item_money;
ALLEGRO_FONT *item_num_text = NULL;
int if_draging;
int mouse_z;


void item_window_init(){
    item_num_text = al_load_ttf_font("./font/pirulen.ttf",20,0);
    equipment_window.img = al_load_bitmap("./image/item_window/item_equipment_window.png");
    item_slot.img = al_load_bitmap("./image/item_window/item_item_slot.png");
    item_window.img = al_load_bitmap("./image/item_window/item_item_window.png");
    storage_slot.img = al_load_bitmap("./image/item_window/item_storage_slot.png");
    storage_window.img = al_load_bitmap("./image/item_window/item_storage_window.png");
    item_window_bg = al_load_bitmap("./image/menu/esc/esc_bg.png");
    item_equiping = al_load_bitmap("./image/item_window/item_equiping.png");
    item_money = al_load_bitmap("./image/item_window/item_money.png");

    equipment_window.width = al_get_bitmap_width(equipment_window.img);
    equipment_window.height = al_get_bitmap_height(equipment_window.img);
    item_slot.width = al_get_bitmap_width(item_slot.img);
    item_slot.height = al_get_bitmap_height(item_slot.img);
    item_window.width = al_get_bitmap_width(item_window.img);
    item_window.height = al_get_bitmap_height(item_window.img);
    storage_slot.width = al_get_bitmap_width(storage_slot.img);
    storage_slot.height = al_get_bitmap_height(storage_slot.img);
    storage_window.width = al_get_bitmap_width(storage_window.img);
    storage_window.height = al_get_bitmap_height(storage_window.img);

    if_draging = -1;
    mouse_z=0;
    al_set_mouse_z(0);

    equipment_window.x = 69;
    equipment_window.y = 254;
    item_window.x = 69;
    item_window.y = 481;
    item_slot.x = 73;
    item_slot.y = 510;
    item_slot.display_x = 0;
    item_slot.display_width = 646;
    item_slot.display_height = item_slot.height;
    storage_window.x = 830;
    storage_window.y = 97;
    storage_slot.x = 852;
    storage_slot.y = 177;
    storage_slot.display_y=0;
    storage_slot.display_height = 600;
    storage_slot.display_width = storage_window.width;


    for(int i=0;i<50;i++){
        if(get_storage_num(i) == 0 || get_storage_index(i) == 0){
            Storage[i].show = 0;
        }
        else{
            Storage[i].index = get_storage_index(i);
            Storage[i].type = get_storage_type(i);
            if(Storage[i].type == 0){
                Storage[i].equipment_type = get_storage_equipment_type(i);
                Storage[i].no = get_storage_no(i);
            }
            Storage[i].num = get_storage_num(i);
            Storage[i].show = 1;
            char temp[50];
            sprintf( temp, "./image/item/item_type%d_index%d.png", Storage[i].type, Storage[i].index);
            Storage[i].img = al_load_bitmap(temp);
        }

        Storage[i].x = 861 + 108*(i%5);
        Storage[i].y = 183 + 106*(int)(i/5);
        Storage[i].width = 97;
        Storage[i].height = 97;
        Storage[i].onmouse_time = 0;

        Storage[i].if_drag=0;
        Storage[i].if_equip=get_storage_ifequip(i);
    }
    for(int i=0;i<9;i++){
        Item_slot[i].show = !(get_item_using_ifempty(i));
        if(Item_slot[i].show){
            Item_slot[i].storage_pos = get_item_using_storage_pos(i);
            Item_slot[i].num = Storage[Item_slot[i].storage_pos].num;
            Item_slot[i].type = 1;
            Item_slot[i].index = get_item_using_index(i);
        }
        else{
            Item_slot[i].show = 0;
            Item_slot[i].storage_pos = 0;
            Item_slot[i].num = 0;
            Item_slot[i].type = 1;
            Item_slot[i].index = 0;
        }
        Item_slot[i].onmouse_time = 0;
        Item_slot[i].width = Storage[0].width;
        Item_slot[i].height = Storage[0].height;
        Item_slot[i].x = 81+108*i;
        Item_slot[i].y = 516;
        Item_slot[i].if_drag =0;
    }
    for(int i=0;i<5;i++){
        Equipment[i].show = !get_equipment_ifempty(i);
        if(Equipment[i].show){
            Equipment[i].storage_pos = get_equipment_storage_pos(i);
            Equipment[i].num = 1;
            Equipment[i].type = 0;
            Equipment[i].index = get_equipment_index(i);
            Equipment[i].no = get_equipment_no(i);
            Equipment[i].equipment_type = get_equipment_equipment_type(i);
        }
        else{
            Equipment[i].show = 0;
            Equipment[i].storage_pos = 0;
            Equipment[i].num = 0;
            Equipment[i].type = 0;
            Equipment[i].index = 0;
            Equipment[i].no=0;
        }
        Equipment[i].onmouse_time = 0;
        Equipment[i].width = Storage[0].width;
        Equipment[i].height = Storage[0].height;
        if(i==4)
            Equipment[i].x = 617;
        else
            Equipment[i].x = 83+108*i;
        Equipment[i].y = 288;
        Equipment[i].if_drag =0;
    }
}

void item_window_process(ALLEGRO_EVENT event){
    item_drag(event);
    if( event.timer.source == fps ){
        for(int i=0;i<50;i++){
            if(Storage[i].state && Storage[i].show)
                Storage[i].onmouse_time++;
            else
                Storage[i].onmouse_time=0;
        }
        for(int i=0;i<9;i++){
            if(Item_slot[i].state && Item_slot[i].show)
                Item_slot[i].onmouse_time++;
            else
                Item_slot[i].onmouse_time=0;
        }
        for(int i=0;i<5;i++){
            if(Equipment[i].state && Equipment[i].show)
                Equipment[i].onmouse_time++;
            else
                Equipment[i].onmouse_time=0;
        }
    }
}

void item_window_draw(){

    al_draw_bitmap(item_window_bg, 0, 0, 0);
    al_draw_filled_rounded_rectangle(storage_window.x, storage_window.y - 40, storage_window.x + storage_window.width/2, storage_window.y+100, 8, 8, al_map_rgb(45,47,59));
    char text_money[10];
    sprintf(text_money,"%d",get_chara_money());
    al_draw_text(item_num_text, al_map_rgb(253,214,3), storage_window.x + storage_window.width/2-5, storage_window.y - 35,ALLEGRO_ALIGN_RIGHT ,text_money);
    al_draw_bitmap(item_money, storage_window.x+5, storage_window.y-35, 0);
    al_draw_bitmap(equipment_window.img, equipment_window.x, equipment_window.y, 0);
    al_draw_bitmap(item_window.img, item_window.x, item_window.y, 0);
    al_draw_bitmap(storage_window.img, storage_window.x, storage_window.y, 0);

    al_draw_bitmap_region(item_slot.img, item_slot.display_x, 0, item_slot.display_width, item_slot.display_height,item_slot.x,item_slot.y,0);
    al_draw_bitmap_region(storage_slot.img, 0, storage_slot.display_y, storage_slot.display_width, storage_slot.display_height,storage_slot.x,storage_slot.y,0);

    for(int i=0;i<50;i++){
        if(Storage[i].show){
            al_draw_bitmap_region(Storage[i].img, -Storage[i].x+storage_slot.x, -Storage[i].y+storage_slot.y+storage_slot.display_y, storage_slot.display_width, storage_slot.display_height,storage_slot.x,storage_slot.y,0);
            if(Storage[i].type && Storage[i].y-storage_slot.display_y+Storage[i].height>=storage_slot.y && Storage[i].y-storage_slot.display_y+Storage[i].height< storage_slot.y+storage_slot.display_height){
                char text[10];
                sprintf(text,"%d",Storage[i].num);
                al_draw_text(item_num_text, al_map_rgb(255,255,255), Storage[i].x+94, Storage[i].y-storage_slot.display_y+70,ALLEGRO_ALIGN_RIGHT ,text);
            }
            if(Storage[i].if_equip)
                al_draw_bitmap_region(item_equiping, -Storage[i].x+storage_slot.x, -Storage[i].y+storage_slot.y+storage_slot.display_y, storage_slot.display_width, storage_slot.display_height,storage_slot.x,storage_slot.y,0);
        }
    }
    for(int i=0;i<9;i++){
        if(Item_slot[i].show){
            al_draw_bitmap_region(Storage[Item_slot[i].storage_pos].img, -Item_slot[i].x+item_slot.x+item_slot.display_x, -Item_slot[i].y+item_slot.y, item_slot.display_width, item_slot.display_height,item_slot.x,item_slot.y,0);
            if(Item_slot[i].x-item_slot.display_x+Item_slot[i].width>=item_slot.x && Item_slot[i].x-item_slot.display_x+Item_slot[i].width< item_slot.x+item_slot.display_width){
                char text[10];
                sprintf(text,"%d",Item_slot[i].num);
                al_draw_text(item_num_text, al_map_rgb(255,255,255), Item_slot[i].x-item_slot.display_x+94, Item_slot[i].y+70,ALLEGRO_ALIGN_RIGHT ,text);
            }
        }
    }
    for(int i=0;i<5;i++)
        if(Equipment[i].show)
            al_draw_bitmap(Storage[Equipment[i].storage_pos].img, Equipment[i].x, Equipment[i].y,0);


    for(int i=0;i<50;i++)
        if(Storage[i].if_drag)
            al_draw_bitmap(Storage[i].img, get_mouse_x()-Storage[i].width/2, get_mouse_y()-Storage[i].height/2,0);
    for(int i=0;i<9;i++)
        if(Item_slot[i].if_drag)
            al_draw_bitmap(Storage[Item_slot[i].storage_pos].img, get_mouse_x()-Item_slot[i].width/2, get_mouse_y()-Item_slot[i].height/2,0);
    for(int i=0;i<5;i++)
        if(Equipment[i].if_drag)
            al_draw_bitmap(Storage[Equipment[i].storage_pos].img, get_mouse_x()-Equipment[i].width/2, get_mouse_y()-Equipment[i].height/2,0);


    if(if_draging == -1){
        for(int i=0;i<50;i++)
            if(Storage[i].onmouse_time>=30){
                item_detail_draw(i);
                break;
            }
        for(int i=0;i<9;i++)
            if(Item_slot[i].onmouse_time>=30){
                item_detail_draw(i);
                break;
            }
        for(int i=0;i<5;i++)
            if(Equipment[i].onmouse_time>=30){
                item_detail_draw(i);
                break;
            }
    }

}
void item_window_mouse_check(){
    item_slot.state = img_onmouse(item_slot.x,item_slot.y,item_slot.display_width,item_slot.display_height);
    storage_slot.state = img_onmouse(storage_slot.x,storage_slot.y,storage_slot.display_width,storage_slot.display_height);
    for(int i=0;i<50;i++){
        if(Storage[i].y-storage_slot.display_y+Storage[i].height<storage_slot.y)
            Storage[i].state = 0;
        else if(Storage[i].y-storage_slot.display_y<=storage_slot.y && Storage[i].y-storage_slot.display_y+Storage[i].height>storage_slot.y)
            Storage[i].state = img_onmouse(Storage[i].x,storage_slot.y,Storage[i].width, Storage[i].y-storage_slot.display_y+Storage[i].height - storage_slot.y );
        else if(Storage[i].y-storage_slot.display_y>=storage_slot.y && Storage[i].y-storage_slot.display_y+Storage[i].height<storage_slot.y+storage_slot.display_height)
            Storage[i].state = img_onmouse(Storage[i].x, Storage[i].y-storage_slot.display_y, Storage[i].width,  Storage[i].height);
        else if(Storage[i].y-storage_slot.display_y+Storage[i].height>=storage_slot.y+storage_slot.display_height && Storage[i].y-storage_slot.display_y<storage_slot.y+storage_slot.display_height)
            Storage[i].state = img_onmouse(Storage[i].x, Storage[i].y-storage_slot.display_y, Storage[i].width, storage_slot.y+storage_slot.display_height-(Storage[i].y-storage_slot.display_y));
        else
            Storage[i].state = 0;
    }
    for(int i=0;i<9;i++){
        if(Item_slot[i].x-item_slot.display_x+Item_slot[i].width<item_slot.x)
            Item_slot[i].state = 0;
        else if(Item_slot[i].x-item_slot.display_x<=item_slot.x && Item_slot[i].x-item_slot.display_x+Item_slot[i].width>item_slot.x)
            Item_slot[i].state = img_onmouse(item_slot.x, Item_slot[i].y, Item_slot[i].x-item_slot.display_x+Item_slot[i].width-item_slot.x, Item_slot[i].height);
        else if(Item_slot[i].x-item_slot.display_x>=item_slot.x && Item_slot[i].x-item_slot.display_x+Item_slot[i].width<item_slot.x+item_slot.display_width)
            Item_slot[i].state = img_onmouse(Item_slot[i].x-item_slot.display_x, Item_slot[i].y, Item_slot[i].width,  Item_slot[i].height);
        else if(Item_slot[i].x-item_slot.display_x+Item_slot[i].width>=item_slot.x+item_slot.display_width && Item_slot[i].x-item_slot.display_x<item_slot.x+item_slot.display_width)
            Item_slot[i].state = img_onmouse(Item_slot[i].x-item_slot.display_x, Item_slot[i].y, item_slot.x+item_slot.display_width-(Item_slot[i].x-item_slot.display_x), Item_slot[i].height);
        else
            Item_slot[i].state = 0;
    }
    for(int i=0;i<5;i++)
        Equipment[i].state = img_onmouse(Equipment[i].x,Equipment[i].y,Equipment[i].width,Equipment[i].height);
}
void item_window_wheel(){
    if(item_slot.state && mouse_z!=get_mouse_z()){
        item_slot.display_x += -(get_mouse_z()-mouse_z)*40;
        if(item_slot.display_x<0)
            item_slot.display_x=0;
        else if(item_slot.display_x+item_slot.display_width>item_slot.width)
            item_slot.display_x = item_slot.width-item_slot.display_width;
    }
    if(storage_slot.state && mouse_z!=get_mouse_z()){
        storage_slot.display_y += -(get_mouse_z()-mouse_z)*40;
        if(storage_slot.display_y<0)
            storage_slot.display_y=0;
        else if(storage_slot.display_y+storage_slot.display_height>storage_slot.height)
            storage_slot.display_y = storage_slot.height-storage_slot.display_height;
    }
    mouse_z=get_mouse_z();
}

void item_detail_draw(int i){
    bool type = Storage[i].type;
    int index = Storage[i].index;
    if(type == 0){
        int detail_num=0;
        int no = Storage[i].no;
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
                al_draw_text(item_num_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10+detail_num*30,ALLEGRO_ALIGN_CENTER,text);
                detail_num++;
            }
        }
    }
    else if(type == 1){
        if(index == 1){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+40,5, 5, al_map_rgba(10,10,25,180));
            char text[10]="HP +25%";
            al_draw_text(item_num_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text);
        }
        else if(index == 2){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+40,5, 5, al_map_rgba(10,10,25,180));
            char text[10]="MP +25%";
            al_draw_text(item_num_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text);
        }
        else if(index == 3){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+40,5, 5, al_map_rgba(10,10,25,180));
            char text[10]="HP +50%";
            al_draw_text(item_num_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text);
        }
        else if(index == 4){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+40,5, 5, al_map_rgba(10,10,25,180));
            char text[10]="MP +50%";
            al_draw_text(item_num_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text);
        }
        else if(index == 5){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+70,5, 5, al_map_rgba(10,10,25,180));
            char text1[10]="HP +100%";
            al_draw_text(item_num_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text1);
            char text2[10]="HP +100%";
            al_draw_text(item_num_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+40,ALLEGRO_ALIGN_CENTER,text2);
        }
        else if(index == 6){
            al_draw_filled_rounded_rectangle(get_mouse_x()+10, get_mouse_y()+10, get_mouse_x()+210, get_mouse_y()+40,5, 5, al_map_rgba(10,10,25,180));
            char text[10]="Level Up";
            al_draw_text(item_num_text,al_map_rgb(255,255,255),get_mouse_x()+110,get_mouse_y()+10,ALLEGRO_ALIGN_CENTER,text);
        }
    }
}

void item_drag(ALLEGRO_EVENT event){
    if(if_draging == -1 ){
        if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
            for(int i=0;i<50;i++){
                if(Storage[i].show && Storage[i].state && Storage[i].if_equip ==0){
                    Storage[i].if_drag = 1;
                    Storage[i].show = 0;
                    if_draging=i;
                    break;
                }
            }
            for(int i=0;i<9;i++){
                if(Item_slot[i].show && Item_slot[i].state){
                    Item_slot[i].if_drag = 1;
                    Item_slot[i].show = 0;
                    if_draging=i;
                    break;
                }
            }
            for(int i=0;i<5;i++){
                if(Equipment[i].show && Equipment[i].state){
                    Equipment[i].if_drag = 1;
                    Equipment[i].show = 0;
                    if_draging=i;
                    break;
                }
            }
        }
    }
    else{
        if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ){
            if(Storage[if_draging].if_drag){
                bool check_add_item=0;
                for(int i=0;i<5;i++){
                    if(Equipment[i].state && i==Storage[if_draging].equipment_type && Storage[if_draging].type == 0 && Equipment[i].show==0){
                        Equipment[i].index=Storage[if_draging].index;
                        Equipment[i].type=Storage[if_draging].type;
                        Equipment[i].show=1;
                        Equipment[i].storage_pos=if_draging;
                        Equipment[i].num=Storage[if_draging].num;
                        Equipment[i].no=Storage[if_draging].no;
                        Equipment[i].equipment_type=Storage[if_draging].equipment_type;
                        Storage[if_draging].if_equip=1;
                        check_add_item=1;
                        break;
                    }
                    else if(Equipment[i].state && i==Storage[if_draging].equipment_type && Storage[if_draging].type == 0 && Equipment[i].show){
                        Storage[Equipment[i].storage_pos].if_equip=0;
                        Storage[if_draging].if_equip=1;
                        Equipment[i].index=Storage[if_draging].index;
                        Equipment[i].type=Storage[if_draging].type;
                        Equipment[i].storage_pos=if_draging;
                        Equipment[i].num=Storage[if_draging].num;
                        Equipment[i].no=Storage[if_draging].no;
                        Equipment[i].equipment_type=Storage[if_draging].equipment_type;
                        check_add_item=1;
                        break;
                    }
                }
                for(int i=0;i<9;i++){
                    if(Item_slot[i].state && Storage[if_draging].type == 1 && Item_slot[i].show==0){
                        Item_slot[i].index=Storage[if_draging].index;
                        Item_slot[i].type=Storage[if_draging].type;
                        Item_slot[i].show=1;
                        Item_slot[i].storage_pos=if_draging;
                        Item_slot[i].num=Storage[if_draging].num;
                        Storage[if_draging].if_equip=1;
                        check_add_item=1;
                        break;
                    }
                    else if(Item_slot[i].state && Storage[if_draging].type == 1 && Item_slot[i].show){
                        Storage[Item_slot[i].storage_pos].if_equip=0;
                        Item_slot[i].index=Storage[if_draging].index;
                        Item_slot[i].type=Storage[if_draging].type;
                        Item_slot[i].storage_pos=if_draging;
                        Item_slot[i].num=Storage[if_draging].num;
                        Storage[if_draging].if_equip=1;
                        check_add_item=1;
                        break;
                    }
                }
                for(int i=0;i<50;i++){
                    if(Storage[i].state && Storage[i].show == 0){
                        if(Storage[if_draging].if_equip){
                            Storage[if_draging].show = 0;
                            Storage[i].show = 1;
                            if(Storage[if_draging].type==1)
                                for(int j=0;j<9;j++)
                                    if(Item_slot[j].storage_pos==if_draging)
                                        Item_slot[j].storage_pos = i;
                            else
                                for(int j=0;j<5;j++)
                                    if(Equipment[j].storage_pos==if_draging)
                                        Equipment[j].storage_pos = i;
                            Storage[i].index = Storage[if_draging].index;
                            Storage[i].if_equip = 1;
                            Storage[i].type = Storage[if_draging].type;
                            Storage[i].num = Storage[if_draging].num;
                            Storage[i].no = Storage[if_draging].no;
                            Storage[i].equipment_type= Storage[if_draging].equipment_type;
                            Storage[i].img = al_clone_bitmap(Storage[if_draging].img);
                            al_destroy_bitmap(Storage[if_draging].img);
                            Storage[if_draging].if_equip=0;
                            break;
                        }
                        else{
                            Storage[if_draging].show = 0;
                            Storage[i].show = 1;
                            Storage[i].index = Storage[if_draging].index;
                            Storage[i].type = Storage[if_draging].type;
                            Storage[i].num = Storage[if_draging].num;
                            Storage[i].no = Storage[if_draging].no;
                            Storage[i].equipment_type= Storage[if_draging].equipment_type;
                            Storage[i].img = al_clone_bitmap(Storage[if_draging].img);
                            if(i!=if_draging)
                                al_destroy_bitmap(Storage[if_draging].img);
                            break;
                        }
                    }
                    else
                        Storage[if_draging].show = 1;
                }

                Storage[if_draging].if_drag = 0;
                if(check_add_item)
                    Storage[if_draging].show = 1;
            }
            else if(Item_slot[if_draging].if_drag){
                bool check_in_slot= 0;
                for(int i=0;i<9;i++){
                    if(Item_slot[i].state && i!=if_draging){
                        //Storage[Item_slot[i].storage_pos].if_equip=0;
                        Item_slot[i].index=Item_slot[if_draging].index;
                        Item_slot[i].type=Item_slot[if_draging].type;
                        Item_slot[i].show=1;
                        Item_slot[i].storage_pos=Item_slot[if_draging].storage_pos;
                        Item_slot[i].num=Item_slot[if_draging].num;

                        Item_slot[if_draging].index=0;
                        Item_slot[if_draging].type=0;
                        Item_slot[if_draging].show=0;
                        Item_slot[if_draging].if_drag = 0;
                        Item_slot[if_draging].storage_pos=0;
                        Item_slot[if_draging].num=0;
                        check_in_slot=1;
                        break;
                    }
                    else if(Item_slot[i].state && i==if_draging){
                        Item_slot[if_draging].show=1;
                        Item_slot[if_draging].if_drag = 0;
                        check_in_slot=1;
                        break;
                    }
                }
                if(check_in_slot == 0){
                    Storage[Item_slot[if_draging].storage_pos].if_equip=0;
                    Item_slot[if_draging].index=0;
                    Item_slot[if_draging].type=0;
                    Item_slot[if_draging].show=0;
                    Item_slot[if_draging].if_drag = 0;
                    Item_slot[if_draging].storage_pos=0;
                    Item_slot[if_draging].num=0;
                }

            }
            else if(Equipment[if_draging].if_drag){
                if(Equipment[if_draging].state){
                    Equipment[if_draging].show=1;
                    Equipment[if_draging].if_drag = 0;
                }
                else{
                    Storage[Equipment[if_draging].storage_pos].if_equip=0;
                    Equipment[if_draging].index=0;
                    Equipment[if_draging].type=0;
                    Equipment[if_draging].show=0;
                    Equipment[if_draging].if_drag = 0;
                    Equipment[if_draging].storage_pos=0;
                    Equipment[if_draging].num=0;
                }
            }
            if_draging=-1;
        }
    }
}

void item_window_destroy(){
    if(if_draging !=-1){
        Storage[if_draging].if_drag = 0;
        Storage[if_draging].show = 1;
        if_draging = -1;
    }
    for(int i=0;i<5;i++){
        if(Equipment[i].show){
            set_storage_ifequip(Equipment[i].storage_pos,1);
            set_equipment_index(i,Equipment[i].index);
            set_storage_equip_pos(Equipment[i].storage_pos,i);
            set_equipment_ifempty(i,0);
            set_equipment_storage_pos(i,Equipment[i].storage_pos);
            set_equipment_equipment_type(i,Equipment[i].equipment_type);
            set_equipment_no(i,Equipment[i].no);
        }
        else{
            set_equipment_ifempty(i,1);
            set_equipment_index(i,0);
            set_equipment_no(i,0);
        }
    }
    for(int i=0;i<9;i++){
        if(Item_slot[i].show){
            set_storage_ifequip(Item_slot[i].storage_pos,1);
            set_item_using_ifempty(i,0);
            set_item_using_index(i,Item_slot[i].index);
            set_item_using_storage_pos(i,Item_slot[i].storage_pos);
            set_storage_equip_pos(Item_slot[i].storage_pos,i);
        }
        else{
            set_item_using_ifempty(i,1);
            set_item_using_index(i,0);
        }
    }
    for(int i=0;i<50;i++){
        if(Storage[i].show){
            set_storage_ifequip(i,Storage[i].if_equip);
            set_storage_index(i,Storage[i].index);
            set_storage_num(i,Storage[i].num);
            set_storage_type(i,Storage[i].type);
            if(Storage[i].type == 0){
                set_storage_equipment_type(i,Storage[i].equipment_type);
                set_storage_no(i,Storage[i].no);
            }
        }
        else{
            set_storage_index(i,0);
            set_storage_num(i,0);
            set_storage_ifequip(i,0);
        }
    }
    al_destroy_font(item_num_text);
    al_destroy_bitmap(equipment_window.img);
    al_destroy_bitmap(item_slot.img);
    al_destroy_bitmap(item_window.img);
    al_destroy_bitmap(storage_slot.img);
    al_destroy_bitmap(storage_window.img);
    al_destroy_bitmap(item_window_bg);
    al_destroy_bitmap(item_money);
    al_destroy_bitmap(item_equiping);
    for(int i=0;i<50;i++)
        if(Storage[i].show)
            al_destroy_bitmap(Storage[i].img);
    for(int i=0;i<9;i++)
        if(Item_slot[i].show)
            al_destroy_bitmap(Item_slot[i].img);
    for(int i=0;i<5;i++)
        if(Equipment[i].show)
            al_destroy_bitmap(Equipment[i].img);

}
