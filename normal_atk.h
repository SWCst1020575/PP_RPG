#ifndef __NORMAL_ATK_H__
#define __NORMAL_ATK_H__

#include "global.h"
#include "damage.h"
#include "character.h"

void remote_atk_init(int);
void remote_atk_process(ALLEGRO_EVENT event);
void remote_atk_update();
void remote_atk_draw(int,int);
void remote_atk_damage(int);
void remote_atk_call(int,int,int,bool);
void remote_atk_destroy();

#endif // __NORMAL_ATK_H__
