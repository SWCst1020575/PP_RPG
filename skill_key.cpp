#include "skill_key.h"

typedef struct Skill_key{
    int skill_index;
    bool if_equip;
}skill_key;

skill_key key[9];

void skill_key_init(){
    if(enter_game_type == 1){
        for(int i=0;i<9;i++){
            key[i].skill_index=-1;
            key[i].if_equip=0;
        }
    }
}

void skill_key_call(int i){
    if(key[i].if_equip)
        skill_call(get_character_x(),get_character_y(),get_character_standing_y(),get_chara_dir(),key[i].skill_index);
}

int get_skill_key_skill_index(int i){return key[i].skill_index;}
bool get_skill_key_if_equip(int i){return key[i].if_equip;}
void set_skill_key_skill_index(int i,int value){key[i].skill_index = value;}
void set_skill_key_if_equip(int i,bool value){key[i].if_equip = value;}
