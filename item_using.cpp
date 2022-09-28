#include "item_using.h"

typedef struct Item_using{
    bool if_item_empty;
    int index;
    int storage_pos;
}item_using;
item_using character_item_using[9];

void item_using_init(){
    if(enter_game_type == 1)
        for(int i=0;i<9;i++)
            character_item_using[i].if_item_empty=1;

}

bool get_item_using_ifempty(int i){return character_item_using[i].if_item_empty;}
int get_item_using_index(int i){return character_item_using[i].index;}
int get_item_using_storage_pos(int i){return character_item_using[i].storage_pos;}
void set_item_using_ifempty(int i,bool value){character_item_using[i].if_item_empty=value;}
void set_item_using_index(int i,int value){character_item_using[i].index=value;}
void set_item_using_storage_pos(int i,int value){character_item_using[i].storage_pos=value;}

void item_effect(int index){
    if(index == 1)//hp potion +25%hp
        set_chara_HP(get_chara_hp()+get_chara_maxhp()/4);
    else if(index == 2)//mp potion +25%mp
        set_chara_MP(get_chara_mp()+get_chara_maxmp()/4);
    else if(index == 3)//hp potion +50%hp
        set_chara_HP(get_chara_hp()+get_chara_maxhp()/2);
    else if(index == 4)//mp potion +50%mp
        set_chara_MP(get_chara_mp()+get_chara_maxmp()/2);
    else if(index == 5){//completed potion set hp/mp full
        set_chara_HP(get_chara_maxhp());
        set_chara_MP(get_chara_maxmp());
    }
    else if(index == 6)//level up potion (for bug test)
        set_chara_EXP(get_chara_maxexp());
}
