#include "save_load.h"

typedef struct SL_window{
    int x,y;
    int width,height;
    bool if_exist;
    bool state;
    int career;
    char date_year[5];
    char date_month[5];
    char date_date[5];
    char date_time[10];
    int lv;
}sl_window;
typedef struct SL_button{
    int x,y;
    int width,height;
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *img_onmouse;
    bool state;
}sl_button;
bool sl_type;//0=save 1=load
bool sl_origin_window;//0=menu 1=esc

int now_page;
sl_window sl_window_slot[100];
sl_button left_change_page;
sl_button right_change_page;
ALLEGRO_BITMAP *sl_window_bg;
ALLEGRO_BITMAP *slot_margin;
ALLEGRO_BITMAP *page_change;
ALLEGRO_BITMAP *page_change_onmouse;
ALLEGRO_BITMAP *sl_window_warrior;
ALLEGRO_BITMAP *sl_window_warrior_onmouse;
ALLEGRO_BITMAP *sl_window_archer;
ALLEGRO_BITMAP *sl_window_archer_onmouse;
ALLEGRO_BITMAP *sl_window_slot_empty_onmouse;//only on save;

ALLEGRO_FONT *num_of_data;
ALLEGRO_FONT *sl_window_lv_font;
ALLEGRO_FONT *sl_window_date_font;
ALLEGRO_CONFIG *file;
/*time_t now; // 變數宣告
time(&now); // 取得現在的日期時間
printf("%s\n",ctime(&now));

// 列印*/

void sl_init(){
    num_of_data = al_load_ttf_font("./font/pirulen.ttf",24,0);
    sl_window_lv_font = al_load_ttf_font("./font/pirulen.ttf",20,0);
    sl_window_date_font = al_load_ttf_font("./font/pirulen.ttf",22,0);

    sl_window_warrior = al_load_bitmap("./image/saveload/warrior_bg.png");
    sl_window_warrior_onmouse = al_load_bitmap("./image/saveload/warrior_bg_onmouse.png");
    sl_window_archer = al_load_bitmap("./image/saveload/archer_bg.png");
    sl_window_archer_onmouse = al_load_bitmap("./image/saveload/archer_bg_onmouse.png");
    sl_window_slot_empty_onmouse = al_load_bitmap("./image/saveload/slot_empty_onmouse.png");
    page_change = al_load_bitmap("./image/saveload/sl_window_page_change.png");
    now_page=0;
    if(sl_type){
        sl_window_bg = al_load_bitmap("./image/saveload/load_bg.png");
        slot_margin = al_load_bitmap("./image/saveload/load_margin.png");
        page_change_onmouse = al_load_bitmap("./image/saveload/sl_window_page_change_load.png");
    }
    else{
        sl_window_bg = al_load_bitmap("./image/saveload/save_bg.png");
        slot_margin = al_load_bitmap("./image/saveload/save_margin.png");
        page_change_onmouse = al_load_bitmap("./image/saveload/sl_window_page_change_save.png");
    }

    left_change_page.img = page_change;
    left_change_page.img_onmouse = page_change_onmouse;
    right_change_page.img = page_change;
    right_change_page.img_onmouse = page_change_onmouse;

    left_change_page.width = al_get_bitmap_width(left_change_page.img);
    left_change_page.height = al_get_bitmap_height(left_change_page.img);
    right_change_page.width = al_get_bitmap_width(right_change_page.img);
    right_change_page.height = al_get_bitmap_height(right_change_page.img);
    left_change_page.x = 15;
    left_change_page.y = 429;
    right_change_page.x = 1542;
    right_change_page.y = 429;
    for(int k=0;k<10;k++){
        for(int i=0;i<10;i++){
            if(i<5){
                sl_window_slot[10*k+i].x = 80+297*i;
                sl_window_slot[10*k+i].y = 180;
            }
            else{
                sl_window_slot[10*k+i].x = 80+297*(i-5);
                sl_window_slot[10*k+i].y = 530;
            }
            sl_window_slot[10*k+i].width = al_get_bitmap_width(slot_margin);
            sl_window_slot[10*k+i].height = al_get_bitmap_height(slot_margin);


            char temp[50];
            sprintf( temp, "./save/save%d.dat", 10*k+i+1);
            file = al_load_config_file(temp);
            if(file!=NULL){
                sl_window_slot[10*k+i].if_exist = 1;
                strcpy(sl_window_slot[10*k+i].date_year,al_get_config_value(file,"DATE","YEAR"));
                strcpy(sl_window_slot[10*k+i].date_month,al_get_config_value(file,"DATE","MONTH"));
                strcpy(sl_window_slot[10*k+i].date_date,al_get_config_value(file,"DATE","DATE"));
                strcpy(sl_window_slot[10*k+i].date_time,al_get_config_value(file,"DATE","TIME"));
                sl_window_slot[10*k+i].career = atoi(al_get_config_value(file,"CHARACTER_STATUS","CAREER"));
                sl_window_slot[10*k+i].lv = atoi(al_get_config_value(file,"CHARACTER_STATUS","LV"));
            }
            else
                sl_window_slot[10*k+i].if_exist = 0;

            al_destroy_config(file);
        }
    }
}
void sl_process(ALLEGRO_EVENT event){
    sl_data_save(event);
    sl_data_load(event);
    if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
        if(left_change_page.state && now_page>0)
            now_page--;
        if(right_change_page.state && now_page<9)
            now_page++;
    }
}

void sl_draw(){
    if(sl_origin_window)
        esc_draw();
    else
        menu_draw();
    al_draw_bitmap(sl_window_bg,0,0,0);
    if(left_change_page.state)
        al_draw_bitmap(left_change_page.img_onmouse,left_change_page.x,left_change_page.y,ALLEGRO_FLIP_HORIZONTAL);
    else
        al_draw_bitmap(left_change_page.img,left_change_page.x,left_change_page.y,ALLEGRO_FLIP_HORIZONTAL);
    if(right_change_page.state)
        al_draw_bitmap(right_change_page.img_onmouse,right_change_page.x,right_change_page.y,0);
    else
        al_draw_bitmap(right_change_page.img,right_change_page.x,right_change_page.y,0);

    for(int i=0;i<10;i++){

        int display_num = now_page*10+i+1;
        char data_num_1[2];
        char data_num_2[2];
        char data_num_3[2];
        sprintf(data_num_1,"%d",display_num/100);
        sprintf(data_num_2,"%d",(display_num%100)/10);
        sprintf(data_num_3,"%d",display_num%10);
        if(sl_window_slot[10*now_page+i].if_exist){
            if(sl_window_slot[10*now_page+i].state){
                if(sl_window_slot[10*now_page+i].career == 1)
                    al_draw_bitmap(sl_window_warrior_onmouse,sl_window_slot[10*now_page+i].x + 13, sl_window_slot[10*now_page+i].y+50,0);
                else if(sl_window_slot[10*now_page+i].career == 2)
                    al_draw_bitmap(sl_window_archer_onmouse,sl_window_slot[10*now_page+i].x + 13, sl_window_slot[10*now_page+i].y+50,0);
            }
            else{
                if(sl_window_slot[10*now_page+i].career == 1)
                    al_draw_bitmap(sl_window_warrior,sl_window_slot[10*now_page+i].x + 13, sl_window_slot[10*now_page+i].y+50,0);
                else if(sl_window_slot[10*now_page+i].career == 2)
                    al_draw_bitmap(sl_window_archer,sl_window_slot[10*now_page+i].x + 13, sl_window_slot[10*now_page+i].y+50,0);
            }
            char level_text[10]="LV ";
            char level_text_2[10];
            itoa(sl_window_slot[10*now_page+i].lv,level_text_2,10);
            strcat(level_text,level_text_2);
            al_draw_text(sl_window_lv_font, al_map_rgb(255,255,255), sl_window_slot[10*now_page+i].x + sl_window_slot[10*now_page+i].width/2, sl_window_slot[10*now_page+i].y+99,ALLEGRO_ALIGN_CENTER , level_text);
            al_draw_text(sl_window_date_font, al_map_rgb(255,255,255), sl_window_slot[10*now_page+i].x + sl_window_slot[10*now_page+i].width/2 - 65, sl_window_slot[10*now_page+i].y+205,ALLEGRO_ALIGN_CENTER , sl_window_slot[10*now_page+i].date_month);
            al_draw_text(sl_window_date_font, al_map_rgb(255,255,255), sl_window_slot[10*now_page+i].x + sl_window_slot[10*now_page+i].width/2 - 5, sl_window_slot[10*now_page+i].y+205,ALLEGRO_ALIGN_CENTER , sl_window_slot[10*now_page+i].date_date);
            al_draw_text(sl_window_date_font, al_map_rgb(255,255,255), sl_window_slot[10*now_page+i].x + sl_window_slot[10*now_page+i].width/2 + 70, sl_window_slot[10*now_page+i].y+205,ALLEGRO_ALIGN_CENTER , sl_window_slot[10*now_page+i].date_year);
            al_draw_text(sl_window_date_font, al_map_rgb(255,255,255), sl_window_slot[10*now_page+i].x + sl_window_slot[10*now_page+i].width/2, sl_window_slot[10*now_page+i].y+235,ALLEGRO_ALIGN_CENTER , sl_window_slot[10*now_page+i].date_time);
        }
        else{
            al_draw_text(sl_window_lv_font, al_map_rgb(255,255,255), sl_window_slot[10*now_page+i].x + sl_window_slot[10*now_page+i].width/2, sl_window_slot[10*now_page+i].y+98,ALLEGRO_ALIGN_CENTER , "no data");
            if(sl_type == 0 && sl_window_slot[10*now_page+i].state)
                al_draw_bitmap(sl_window_slot_empty_onmouse,sl_window_slot[10*now_page+i].x + 13, sl_window_slot[10*now_page+i].y+50,0);
        }
        al_draw_bitmap(slot_margin,sl_window_slot[10*now_page+i].x,sl_window_slot[10*now_page+i].y,0);
        if(sl_type){
            al_draw_text(num_of_data, al_map_rgb(0,137,216), sl_window_slot[10*now_page+i].x + sl_window_slot[10*now_page+i].width/2 - 33, sl_window_slot[10*now_page+i].y,ALLEGRO_ALIGN_CENTER , data_num_1);
            al_draw_text(num_of_data, al_map_rgb(0,137,216), sl_window_slot[10*now_page+i].x + sl_window_slot[10*now_page+i].width/2 , sl_window_slot[10*now_page+i].y,ALLEGRO_ALIGN_CENTER , data_num_2);
            al_draw_text(num_of_data, al_map_rgb(0,137,216), sl_window_slot[10*now_page+i].x + sl_window_slot[10*now_page+i].width/2 + 33, sl_window_slot[10*now_page+i].y,ALLEGRO_ALIGN_CENTER , data_num_3);
        }
        else{
            al_draw_text(num_of_data, al_map_rgb(226,0,65), sl_window_slot[10*now_page+i].x + sl_window_slot[10*now_page+i].width/2 - 33, sl_window_slot[10*now_page+i].y,ALLEGRO_ALIGN_CENTER , data_num_1);
            al_draw_text(num_of_data, al_map_rgb(226,0,65), sl_window_slot[10*now_page+i].x + sl_window_slot[10*now_page+i].width/2 , sl_window_slot[10*now_page+i].y,ALLEGRO_ALIGN_CENTER , data_num_2);
            al_draw_text(num_of_data, al_map_rgb(226,0,65), sl_window_slot[10*now_page+i].x + sl_window_slot[10*now_page+i].width/2 + 33, sl_window_slot[10*now_page+i].y,ALLEGRO_ALIGN_CENTER , data_num_3);
        }
    }
}

void sl_window_onmouse_check(){
    left_change_page.state = img_onmouse(left_change_page.x,left_change_page.y,left_change_page.width,left_change_page.height);
    right_change_page.state = img_onmouse(right_change_page.x,right_change_page.y,right_change_page.width,right_change_page.height);
    for(int i=0;i<10;i++)
        sl_window_slot[10*now_page+i].state = img_onmouse(sl_window_slot[10*now_page+i].x,sl_window_slot[10*now_page+i].y,sl_window_slot[10*now_page+i].width,sl_window_slot[10*now_page+i].height);
}
void sl_window_reload(){
    for(int k=0;k<10;k++){
        for(int i=0;i<10;i++){

            char temp[50];
            sprintf( temp, "./save/save%d.dat", 10*k+i+1);
            file = al_load_config_file(temp);
            if(file!=NULL){
                sl_window_slot[10*k+i].if_exist = 1;
                strcpy(sl_window_slot[10*k+i].date_year,al_get_config_value(file,"DATE","YEAR"));
                strcpy(sl_window_slot[10*k+i].date_month,al_get_config_value(file,"DATE","MONTH"));
                strcpy(sl_window_slot[10*k+i].date_date,al_get_config_value(file,"DATE","DATE"));
                strcpy(sl_window_slot[10*k+i].date_time,al_get_config_value(file,"DATE","TIME"));
                sl_window_slot[10*k+i].career = atoi(al_get_config_value(file,"CHARACTER_STATUS","CAREER"));
                sl_window_slot[10*k+i].lv = atoi(al_get_config_value(file,"CHARACTER_STATUS","LV"));
            }
            else
                sl_window_slot[10*k+i].if_exist = 0;

            al_destroy_config(file);
        }
    }
}
void sl_data_save(ALLEGRO_EVENT event){
    if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && sl_type == 0){
        for(int i=0;i<10;i++){
            if(sl_window_slot[10*now_page+i].state){
                file = al_create_config();
                al_add_config_section(file,"DATE");
                al_add_config_section(file,"CHARACTER");
                al_add_config_section(file,"CHARACTER_STATUS");
                al_add_config_section(file,"POTION_KEY");
                al_add_config_section(file,"EQUIPMENT");
                al_add_config_section(file,"EQUIPMENT_STATUS");
                al_add_config_section(file,"STORAGE");
                al_add_config_section(file,"SKILL_KEY");
                char temp[50];
                //date save
                char *time_text;
                //Sun Jun 27 23:52:05 2021
                time_t now;
                time(&now);
                time_text = ctime(&now);
                char *time_text_save = strtok(time_text, " ");
                al_set_config_value(file,"DATE","DAY", time_text_save);
                time_text_save = strtok(NULL, " ");
                al_set_config_value(file,"DATE","MONTH", time_text_save);
                time_text_save = strtok(NULL, " ");
                al_set_config_value(file,"DATE","DATE", time_text_save);
                time_text_save = strtok(NULL, " ");
                al_set_config_value(file,"DATE","TIME", time_text_save);
                time_text_save = strtok(NULL, " ");
                al_set_config_value(file,"DATE","YEAR", time_text_save);

                //character save
                itoa(get_character_x(),temp,10);
                al_set_config_value(file,"CHARACTER","X", temp);
                itoa(get_character_y(),temp,10);
                al_set_config_value(file,"CHARACTER","y", temp);
                //character status save
                itoa(get_chara_career(),temp,10);
                al_set_config_value(file,"CHARACTER_STATUS","CAREER", temp);
                itoa(get_chara_lv(),temp,10);
                al_set_config_value(file,"CHARACTER_STATUS","LV", temp);
                itoa(get_chara_exp(),temp,10);
                al_set_config_value(file,"CHARACTER_STATUS","EXP", temp);
                itoa(get_chara_maxexp(),temp,10);
                al_set_config_value(file,"CHARACTER_STATUS","MAX_EXP", temp);
                itoa(get_chara_money(),temp,10);
                al_set_config_value(file,"CHARACTER_STATUS","MONEY", temp);
                itoa(get_chara_hp(),temp,10);
                al_set_config_value(file,"CHARACTER_STATUS","HP", temp);
                itoa(get_chara_real_maxhp(),temp,10);
                al_set_config_value(file,"CHARACTER_STATUS","MAX_HP", temp);
                itoa(get_chara_mp(),temp,10);
                al_set_config_value(file,"CHARACTER_STATUS","MP", temp);
                itoa(get_chara_real_maxmp(),temp,10);
                al_set_config_value(file,"CHARACTER_STATUS","MAX_MP", temp);
                itoa(get_chara_real_atk(),temp,10);
                al_set_config_value(file,"CHARACTER_STATUS","ATK", temp);
                itoa(get_chara_real_def(),temp,10);
                al_set_config_value(file,"CHARACTER_STATUS","DEF", temp);
                itoa(get_chara_real_atkP(),temp,10);
                al_set_config_value(file,"CHARACTER_STATUS","ATKP", temp);
                itoa(get_chara_speed(),temp,10);
                al_set_config_value(file,"CHARACTER_STATUS","SPEED", temp);
                itoa(get_chara_run_speed(),temp,10);
                al_set_config_value(file,"CHARACTER_STATUS","RUN_SPEED", temp);
                itoa(get_chara_skill_point(),temp,10);
                al_set_config_value(file,"CHARACTER_STATUS","SKILL_POINT", temp);
                for(int j=0;j<10;j++){
                    itoa(get_chara_skill(j),temp,10);
                    char text_save[20];
                    sprintf( text_save, "SKILL_LEVEL_%d", j);
                    al_set_config_value(file,"CHARACTER_STATUS",text_save, temp);
                }
                //potion key
                for(int j=0;j<9;j++){
                    char text_save[20];
                    itoa(get_item_using_ifempty(j),temp,10);
                    sprintf( text_save, "IFEMPTY_%d", j);
                    al_set_config_value(file,"POTION_KEY",text_save, temp);
                    itoa(get_item_using_index(j),temp,10);
                    sprintf( text_save, "INDEX_%d", j);
                    al_set_config_value(file,"POTION_KEY",text_save, temp);
                    itoa(get_item_using_storage_pos(j),temp,10);
                    sprintf( text_save, "STORAGE_POS_%d", j);
                    al_set_config_value(file,"POTION_KEY",text_save, temp);
                }
                //equipment
                for(int j=0;j<5;j++){
                    char text_save[20];
                    itoa(get_equipment_ifempty(j),temp,10);
                    sprintf( text_save, "IFEMPTY_%d", j);
                    al_set_config_value(file,"EQUIPMENT",text_save, temp);
                    itoa(get_equipment_index(j),temp,10);
                    sprintf( text_save, "INDEX_%d", j);
                    al_set_config_value(file,"EQUIPMENT",text_save, temp);
                    itoa(get_equipment_no(j),temp,10);
                    sprintf( text_save, "NO_%d", j);
                    al_set_config_value(file,"EQUIPMENT",text_save, temp);
                    itoa(get_equipment_storage_pos(j),temp,10);
                    sprintf( text_save, "STORAGE_POS_%d", j);
                    al_set_config_value(file,"EQUIPMENT",text_save, temp);
                    itoa(get_equipment_equipment_type(j),temp,10);
                    sprintf( text_save, "EQUIPMENT_TYPE_%d", j);
                    al_set_config_value(file,"EQUIPMENT",text_save, temp);
                }
                //equipment status
                for(int j=0;j<50;j++){
                    char text_save[20];
                    itoa(get_equipment_status_ifexist(j),temp,10);
                    sprintf( text_save, "IFEXIST_%d", j);
                    al_set_config_value(file,"EQUIPMENT_STATUS",text_save, temp);
                    itoa(get_equipment_status_lv(j),temp,10);
                    sprintf( text_save, "LV_%d", j);
                    al_set_config_value(file,"EQUIPMENT_STATUS",text_save, temp);
                    itoa(get_equipment_status_hp(j),temp,10);
                    sprintf( text_save, "HP_%d", j);
                    al_set_config_value(file,"EQUIPMENT_STATUS",text_save, temp);
                    itoa(get_equipment_status_mp(j),temp,10);
                    sprintf( text_save, "MP_%d", j);
                    al_set_config_value(file,"EQUIPMENT_STATUS",text_save, temp);
                    itoa(get_equipment_status_atk(j),temp,10);
                    sprintf( text_save, "ATK_%d", j);
                    al_set_config_value(file,"EQUIPMENT_STATUS",text_save, temp);
                    itoa(get_equipment_status_def(j),temp,10);
                    sprintf( text_save, "DEF_%d", j);
                    al_set_config_value(file,"EQUIPMENT_STATUS",text_save, temp);
                    itoa(get_equipment_status_atkP(j),temp,10);
                    sprintf( text_save, "ATKP_%d", j);
                    al_set_config_value(file,"EQUIPMENT_STATUS",text_save, temp);
                    itoa(get_equipment_status_money(j),temp,10);
                    sprintf( text_save, "MONEY_%d", j);
                    al_set_config_value(file,"EQUIPMENT_STATUS",text_save, temp);
                    itoa(get_equipment_status_enhancement_level(j),temp,10);
                    sprintf( text_save, "ENHANCEMENT_LEVEL_%d", j);
                    al_set_config_value(file,"EQUIPMENT_STATUS",text_save, temp);
                }
                //storage
                for(int j=0;j<50;j++){
                    char text_save[20];
                    itoa(get_storage_ifequip(j),temp,10);
                    sprintf( text_save, "IFEQUIP_%d", j);
                    al_set_config_value(file,"STORAGE",text_save, temp);
                    itoa(get_storage_index(j),temp,10);
                    sprintf( text_save, "INDEX_%d", j);
                    al_set_config_value(file,"STORAGE",text_save, temp);
                    itoa(get_storage_type(j),temp,10);
                    sprintf( text_save, "TYPE_%d", j);
                    al_set_config_value(file,"STORAGE",text_save, temp);
                    itoa(get_storage_num(j),temp,10);
                    sprintf( text_save, "NUM_%d", j);
                    al_set_config_value(file,"STORAGE",text_save, temp);
                    itoa(get_storage_no(j),temp,10);
                    sprintf( text_save, "NO_%d", j);
                    al_set_config_value(file,"STORAGE",text_save, temp);
                    itoa(get_storage_equip_pos(j),temp,10);
                    sprintf( text_save, "EQUIP_POS_%d", j);
                    al_set_config_value(file,"STORAGE",text_save, temp);
                    itoa(get_storage_equipment_type(j),temp,10);
                    sprintf( text_save, "EQUIPMENT_TYPE_%d", j);
                    al_set_config_value(file,"STORAGE",text_save, temp);
                }
                //SKILL_KEY
                for(int j=0;j<9;j++){
                    char text_save[20];
                    itoa(get_skill_key_skill_index(j),temp,10);
                    sprintf( text_save, "SKILL_INDEX_%d", j);
                    al_set_config_value(file,"SKILL_KEY",text_save, temp);
                    itoa(get_skill_key_if_equip(j),temp,10);
                    sprintf( text_save, "IFEQUIP_%d", j);
                    al_set_config_value(file,"SKILL_KEY",text_save, temp);
                }



                sprintf( temp, "./save/save%d.dat", 10*now_page+i+1);
                al_save_config_file(temp, file);
                al_destroy_config(file);
                sl_window_reload();
                break;
            }
        }
    }
}
void sl_data_load(ALLEGRO_EVENT event){
    if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && sl_type == 1){
        for(int i=0;i<10;i++){
            if(sl_window_slot[10*now_page+i].state && sl_window_slot[10*now_page+i].if_exist){
                char temp[50];
                sprintf( temp, "./save/save%d.dat", 10*now_page+i+1);
                file = al_load_config_file(temp);
                //character load
                set_character_pos(atoi(al_get_config_value(file,"CHARACTER","X")),atoi(al_get_config_value(file,"CHARACTER","y")));

                //character status save
                set_chara_career(atoi(al_get_config_value(file,"CHARACTER_STATUS","CAREER")));
                set_chara_LV(atoi(al_get_config_value(file,"CHARACTER_STATUS","LV")));
                set_chara_EXP(atoi(al_get_config_value(file,"CHARACTER_STATUS","EXP")));
                set_chara_maxEXP(atoi(al_get_config_value(file,"CHARACTER_STATUS","MAX_EXP")));
                set_chara_money(atoi(al_get_config_value(file,"CHARACTER_STATUS","MONEY")));
                set_chara_HP(atoi(al_get_config_value(file,"CHARACTER_STATUS","HP")));
                set_chara_maxHP(atoi(al_get_config_value(file,"CHARACTER_STATUS","MAX_HP")));
                set_chara_MP(atoi(al_get_config_value(file,"CHARACTER_STATUS","MP")));
                set_chara_maxMP(atoi(al_get_config_value(file,"CHARACTER_STATUS","MAX_MP")));
                set_chara_atk(atoi(al_get_config_value(file,"CHARACTER_STATUS","ATK")));
                set_chara_def(atoi(al_get_config_value(file,"CHARACTER_STATUS","DEF")));
                set_chara_atkP(atoi(al_get_config_value(file,"CHARACTER_STATUS","ATKP")));
                set_chara_speed(atoi(al_get_config_value(file,"CHARACTER_STATUS","SPEED")));
                set_chara_run_speed(atoi(al_get_config_value(file,"CHARACTER_STATUS","RUN_SPEED")));
                set_chara_skill_point(atoi(al_get_config_value(file,"CHARACTER_STATUS","SKILL_POINT")));
                for(int j=0;j<10;j++){
                    char text_save[20];
                    sprintf( text_save, "SKILL_LEVEL_%d", j);
                    set_chara_skill(j,atoi(al_get_config_value(file,"CHARACTER_STATUS",text_save)));
                }

                //potion key
                for(int j=0;j<9;j++){
                    char text_save[20];
                    sprintf( text_save, "IFEMPTY_%d", j);
                    set_item_using_ifempty(j,atoi(al_get_config_value(file,"POTION_KEY",text_save)));
                    sprintf( text_save, "INDEX_%d", j);
                    set_item_using_index(j,atoi(al_get_config_value(file,"POTION_KEY",text_save)));
                    sprintf( text_save, "STORAGE_POS_%d", j);
                    set_item_using_storage_pos(j,atoi(al_get_config_value(file,"POTION_KEY",text_save)));
                }
                //equipment
                for(int j=0;j<5;j++){
                    char text_save[20];
                    sprintf( text_save, "IFEMPTY_%d", j);
                    set_equipment_ifempty(j,atoi(al_get_config_value(file,"EQUIPMENT",text_save)));
                    sprintf( text_save, "INDEX_%d", j);
                    set_equipment_index(j,atoi(al_get_config_value(file,"EQUIPMENT",text_save)));
                    sprintf( text_save, "NO_%d", j);
                    set_equipment_no(j,atoi(al_get_config_value(file,"EQUIPMENT",text_save)));
                    sprintf( text_save, "STORAGE_POS_%d", j);
                    set_equipment_storage_pos(j,atoi(al_get_config_value(file,"EQUIPMENT",text_save)));
                    sprintf( text_save, "EQUIPMENT_TYPE_%d", j);
                    set_equipment_equipment_type(j,atoi(al_get_config_value(file,"EQUIPMENT",text_save)));
                }
                //equipment status
                for(int j=0;j<50;j++){
                    char text_save[20];
                    sprintf( text_save, "IFEXIST_%d", j);
                    set_equipment_status_ifexist(j,atoi(al_get_config_value(file,"EQUIPMENT_STATUS",text_save)));
                    sprintf( text_save, "LV_%d", j);
                    set_equipment_status_lv(j,atoi(al_get_config_value(file,"EQUIPMENT_STATUS",text_save)));
                    sprintf( text_save, "HP_%d", j);
                    set_equipment_status_hp(j,atoi(al_get_config_value(file,"EQUIPMENT_STATUS",text_save)));
                    sprintf( text_save, "MP_%d", j);
                    set_equipment_status_mp(j,atoi(al_get_config_value(file,"EQUIPMENT_STATUS",text_save)));
                    sprintf( text_save, "ATK_%d", j);
                    set_equipment_status_atk(j,atoi(al_get_config_value(file,"EQUIPMENT_STATUS",text_save)));
                    sprintf( text_save, "DEF_%d", j);
                    set_equipment_status_def(j,atoi(al_get_config_value(file,"EQUIPMENT_STATUS",text_save)));
                    sprintf( text_save, "ATKP_%d", j);
                    set_equipment_status_atkP(j,atoi(al_get_config_value(file,"EQUIPMENT_STATUS",text_save)));
                    sprintf( text_save, "MONEY_%d", j);
                    set_equipment_status_money(j,atoi(al_get_config_value(file,"EQUIPMENT_STATUS",text_save)));
                    sprintf( text_save, "ENHANCEMENT_LEVEL_%d", j);
                    set_equipment_status_enhancement_level(j,atoi(al_get_config_value(file,"EQUIPMENT_STATUS",text_save)));
                }
                //storage
                for(int j=0;j<50;j++){
                    char text_save[20];
                    sprintf( text_save, "IFEQUIP_%d", j);
                    set_storage_ifequip(j,atoi(al_get_config_value(file,"STORAGE",text_save)));
                    sprintf( text_save, "INDEX_%d", j);
                    set_storage_index(j,atoi(al_get_config_value(file,"STORAGE",text_save)));
                    sprintf( text_save, "TYPE_%d", j);
                    set_storage_type(j,atoi(al_get_config_value(file,"STORAGE",text_save)));
                    sprintf( text_save, "NUM_%d", j);
                    set_storage_num(j,atoi(al_get_config_value(file,"STORAGE",text_save)));
                    sprintf( text_save, "NO_%d", j);
                    set_storage_no(j,atoi(al_get_config_value(file,"STORAGE",text_save)));
                    sprintf( text_save, "EQUIP_POS_%d", j);
                    set_storage_equip_pos(j,atoi(al_get_config_value(file,"STORAGE",text_save)));
                    sprintf( text_save, "EQUIPMENT_TYPE_%d", j);
                    set_storage_equipment_type(j,atoi(al_get_config_value(file,"STORAGE",text_save)));
                }
                //SKILL_KEY
                for(int j=0;j<9;j++){
                    char text_save[20];
                    sprintf( text_save, "SKILL_INDEX_%d", j);
                    set_skill_key_skill_index(j,atoi(al_get_config_value(file,"SKILL_KEY",text_save)));
                    sprintf( text_save, "IFEQUIP_%d", j);
                    set_skill_key_if_equip(j,atoi(al_get_config_value(file,"SKILL_KEY",text_save)));
                }



                sprintf( temp, "./save/save%d.dat", 10*now_page+i+1);
                al_save_config_file(temp, file);
                al_destroy_config(file);

                judge_next_window = true;
                target_window = 5;
                break;
            }
        }
    }
}
void sl_destroy(){
    al_destroy_font(num_of_data);
    al_destroy_font(sl_window_lv_font);
    al_destroy_font(sl_window_date_font);
    al_destroy_bitmap(sl_window_bg);
    al_destroy_bitmap(slot_margin);
    al_destroy_bitmap(sl_window_slot_empty_onmouse);
    al_destroy_bitmap(sl_window_warrior);
    al_destroy_bitmap(sl_window_warrior_onmouse);
    al_destroy_bitmap(sl_window_archer);
    al_destroy_bitmap(sl_window_archer_onmouse);
    al_destroy_bitmap(page_change);
    al_destroy_bitmap(page_change_onmouse);
}
