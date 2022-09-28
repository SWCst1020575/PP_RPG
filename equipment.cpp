#include "equipment.h"

typedef struct Equipment_equip{
    bool if_item_empty;
    int no;// unique
    int index;
    int storage_pos;
    int equipment_type;
}equipment_equip;
typedef struct Equipment_status{
    bool if_exist;
    int lv;
    int hp;
    int mp;
    int atk;
    int def;
    int atkP;
    int money;
    int enhancement_level;
}equipment_status;
equipment_equip equipment[5];
equipment_status equipment_ability[50];

void equipment_init(){
    if(enter_game_type == 1){
        for(int i=0;i<5;i++)
            equipment[i].if_item_empty=1;
        for(int i=0;i<50;i++)
            equipment_ability[i].if_exist=0;
    }

}

void create_new_equipment(int no,int equipment_type){
    equipment_ability[no].if_exist = 1;
    equipment_ability[no].lv = get_chara_lv();
    equipment_ability[no].money = equipment_ability[no].lv*get_rand(800,1200);
    equipment_ability[no].hp = 0;
    equipment_ability[no].mp = 0;
    equipment_ability[no].atk = 0;
    equipment_ability[no].def = 0;
    equipment_ability[no].atkP = 0;
    equipment_ability[no].enhancement_level = 0;
    if(equipment_type == 0){
        equipment_ability[no].def = equipment_ability[no].lv*get_rand(9,11);
        equipment_ability[no].hp = equipment_ability[no].lv*get_rand(45,55);
    }
    else if(equipment_type == 1){
        equipment_ability[no].hp = equipment_ability[no].lv*get_rand(90,110);
        equipment_ability[no].def = equipment_ability[no].lv*get_rand(9,11);
    }
    else if(equipment_type == 2){
        equipment_ability[no].hp = equipment_ability[no].lv*get_rand(27,33);
    }
    else if(equipment_type == 3){
        equipment_ability[no].hp = equipment_ability[no].lv*get_rand(27,33);
    }
    else{
        equipment_ability[no].atk = equipment_ability[no].lv*get_rand(72,88);
        equipment_ability[no].atkP = equipment_ability[no].lv*get_rand(9,11);
    }
}

bool get_equipment_ifempty(int i){return equipment[i].if_item_empty;}
int get_equipment_no(int i){return equipment[i].no;}
int get_equipment_index(int i){return equipment[i].index;}
int get_equipment_storage_pos(int i){return equipment[i].storage_pos;}
int get_equipment_equipment_type(int i){return equipment[i].equipment_type;}
void set_equipment_ifempty(int i,bool value){equipment[i].if_item_empty = value;}
void set_equipment_no(int i,int value){equipment[i].no = value;}
void set_equipment_index(int i,int value){equipment[i].index = value;}
void set_equipment_storage_pos(int i,int value){equipment[i].storage_pos = value;}
void set_equipment_equipment_type(int i,int value){equipment[i].equipment_type = value;}

bool get_equipment_status_ifexist(int i){return equipment_ability[i].if_exist;}
int get_equipment_status_lv(int i){return equipment_ability[i].lv;}
int get_equipment_status_hp(int i){return equipment_ability[i].hp;}
int get_equipment_status_mp(int i){return equipment_ability[i].mp;}
int get_equipment_status_atk(int i){return equipment_ability[i].atk;}
int get_equipment_status_def(int i){return equipment_ability[i].def;}
int get_equipment_status_atkP(int i){return equipment_ability[i].atkP;}
int get_equipment_status_money(int i){return equipment_ability[i].money;}
int get_equipment_status_enhancement_level(int i){return equipment_ability[i].enhancement_level;}
void set_equipment_status_ifexist(int i,bool value){equipment_ability[i].if_exist = value;}
void set_equipment_status_lv(int i,int value){equipment_ability[i].lv = value;}
void set_equipment_status_hp(int i,int value){equipment_ability[i].hp = value;}
void set_equipment_status_mp(int i,int value){equipment_ability[i].mp = value;}
void set_equipment_status_atk(int i,int value){equipment_ability[i].atk = value;}
void set_equipment_status_def(int i,int value){equipment_ability[i].def = value;}
void set_equipment_status_atkP(int i,int value){equipment_ability[i].atkP = value;}
void set_equipment_status_money(int i,int value){equipment_ability[i].money = value;}
void set_equipment_status_enhancement_level(int i,int value){equipment_ability[i].enhancement_level = value;}

int get_equipment_total_hp(){
    int sum=0;
    for(int i=0;i<5;i++)
        if(!equipment[i].if_item_empty)
            sum+=equipment_ability[equipment[i].no].hp;
    return sum;
}
int get_equipment_total_mp(){
    int sum=0;
    for(int i=0;i<5;i++)
        if(!equipment[i].if_item_empty)
            sum+=equipment_ability[equipment[i].no].mp;
    return sum;
}
int get_equipment_total_atk(){
    int sum=0;
    for(int i=0;i<5;i++)
        if(!equipment[i].if_item_empty)
            sum+=equipment_ability[equipment[i].no].atk;
    return sum;
}
int get_equipment_total_def(){
    int sum=0;
    for(int i=0;i<5;i++)
        if(!equipment[i].if_item_empty)
            sum+=equipment_ability[equipment[i].no].def;
    return sum;
}
int get_equipment_total_atkP(){
    int sum=0;
    for(int i=0;i<5;i++)
        if(!equipment[i].if_item_empty)
            sum+=equipment_ability[equipment[i].no].atkP;
    return sum;
}
