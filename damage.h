#ifndef __DAMAGE_H__
#define __DAMAGE_H__

#include "global.h"
#include "character.h"
#include "monster.h"


void damage_text_init();
void creat_new_damage(bool,int,int,int);
void damage_text_process(ALLEGRO_EVENT event);
void damage_text_update();
void damage_text_draw(int,int);


bool damage_to_monster1(int,int,int,int,int,int);
void damage_monster1_to_character(int,int,int,int,int);

int compare_distance(const void *,const void *);
void damage_text_destroy();

#endif
