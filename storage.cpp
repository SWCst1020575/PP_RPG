#include "storage.h"

typedef struct Storage{
    int index;
    bool type;
    int num;
    bool if_equip;
    int equip_pos;
    int equipment_type;//for equipment
    int no;//for equipment
}storage_item;
storage_item storage[50];
int storage_num;
void storage_init(){
    storage_num = 0;
    if(enter_game_type == 1){
        for(int i=0;i<50;i++){
            storage[i].index =0;
            storage[i].num =0;
            storage[i].if_equip =0;
        }
        get_item(1,5);
        get_item(2,5);
        get_item(3,5);
        get_item(4,5);
        get_item(5,5);
        get_item(6,99);
        get_equipment(1,1,0);
        get_equipment(2,1,1);
        get_equipment(3,1,2);
        get_equipment(4,1,3);
        if(get_chara_career()==1)
            get_equipment(5,1,4);
        else if(get_chara_career()==2)
            get_equipment(6,1,4);
        storage_sort();
    }

}
void get_item(int index,int num){
    for(int i=0;i<50;i++){
        if(storage[i].index == index && storage[i].type == 1){
            storage[i].num += num;
            break;
        }
        else if(storage[i].num == 0){
            storage[i].index = index;
            storage[i].type = 1;
            storage[i].num = num;
            storage_num++;
            break;
        }
    }
}
void get_equipment(int index,int num,int equipment_type){
    for(int i=0;i<50;i++){
        if(storage[i].num == 0){
            storage[i].index = index;
            storage[i].type = 0;
            storage[i].num = num;
            storage[i].equipment_type = equipment_type;
            for(int j=0;j<50;j++)
                if(get_equipment_status_ifexist(j)==0){
                    create_new_equipment(j,equipment_type);
                    storage[i].no = j;
                    break;
                }
            storage_num++;
            break;
        }
    }
}
void use_item(int index,int num,bool type){
    for(int i=0;i<50;i++){
        if(storage[i].index == index && storage[i].type == type && type == 1 && storage[i].num>0){
            storage[i].num--;
            item_effect(index);
            if(storage[i].num == 0){
                storage[i].index = 0;
                storage[i].if_equip = 0;
                set_item_using_ifempty(storage[i].equip_pos,1);
                set_item_using_index(storage[i].equip_pos,0);
                set_item_using_storage_pos(storage[i].equip_pos,0);
                storage_num--;
            }
            return;
        }
    }
}

void sell_equiment(int i){
    storage[i].index = 0;
    storage[i].type = 0;
    storage[i].num = 0;
    storage[i].equipment_type = 0;
    storage[i].if_equip = 0;
    storage[i].no=0;
    storage[i].equip_pos=0;
}



int get_storage_index(int i){return storage[i].index;}
bool get_storage_type(int i){return storage[i].type;}
int get_storage_num(int i){return storage[i].num;}
bool get_storage_ifequip(int i){return storage[i].if_equip;}
int get_storage_total_num(){return storage_num;}
int get_storage_equipment_type(int i){return storage[i].equipment_type;}
int get_storage_equip_pos(int i){return storage[i].equip_pos;}
int get_storage_no(int i){return storage[i].no;}
void set_storage_ifequip(int i,bool status){storage[i].if_equip = status;}
void set_storage_equip_pos(int i,int value){storage[i].equip_pos = value;}
void set_storage_index(int i,int value){storage[i].index=value;}
void set_storage_type(int i,int value){storage[i].type=value;}
void set_storage_num(int i,int value){storage[i].num=value;}
void set_storage_equipment_type(int i,int value){storage[i].equipment_type=value;}
void set_storage_no(int i,int value){storage[i].no=value;}

void storage_sort(){
    qsort(storage,storage_num,sizeof(storage_item),storage_compare);
}
int storage_compare(const void *savea,const void *saveb){
    storage_item a = *(storage_item*) savea;
    storage_item b = *(storage_item*) saveb;

    if(a.num == 0 || b.num == 0)
        return b.num-a.num;
    else if(a.type == b.type)
        return a.index-b.index;
    else
        return a.type-b.type;
}
