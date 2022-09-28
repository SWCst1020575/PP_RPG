#ifndef __SKILL_KEY_H__
#define __SKILL_KEY_H__

#include "global.h"
#include "character.h"
#include "atk_skill.h"



void skill_key_init();
void skill_key_call(int);

int get_skill_key_skill_index(int);
bool get_skill_key_if_equip(int);
void set_skill_key_skill_index(int,int);
void set_skill_key_if_equip(int,bool);


#endif // __SKILL_KEY_H__
