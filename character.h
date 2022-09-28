#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "global.h"
#include "createCharacter.h"
#include "status.h"
#include "stage.h"
#include "normal_atk.h"
#include "damage.h"
#include "item_using.h"
#include "equipment.h"
#include "skill_key.h"


void character_init();
void character_process(ALLEGRO_EVENT event);
void character_update();
void character_draw(int,int);
void character_destory();

void character_set_sevolume();
void set_character_pos(int,int);
void character_reborn();
void character_nature_recovering();
void character_status_check();

int get_character_x();
int get_character_y();
int get_character_standing_y();
int get_character_width();
int get_character_heigth();
int get_character_damage_x();
int get_character_damage_width();

void set_chara_HP(int);
void set_chara_MP(int);
void set_chara_EXP(int);
void set_chara_money(int);
void set_chara_skill_point(int);
void set_chara_skill(int,int);
void set_chara_speed(int);
void set_chara_run_speed(int);
void set_chara_atk(int);
void set_chara_def(int);
void set_chara_atkP(int);
void set_chara_maxHP(int);
void set_chara_maxMP(int);
void set_chara_maxEXP(int);
void set_chara_career(int);
void set_chara_LV(int);
int get_chara_career();
int get_chara_lv();
int get_chara_hp();
int get_chara_maxhp();
int get_chara_mp();
int get_chara_maxmp();
int get_chara_sp();
int get_chara_exp();
int get_chara_maxexp();
int get_chara_atk();
int get_chara_def();
int get_chara_atkP();
int get_chara_money();
int get_chara_skill_point();
int get_chara_skill(int);
int get_chara_real_maxhp();
int get_chara_real_maxmp();
int get_chara_real_atk();
int get_chara_real_def();
int get_chara_real_atkP();
int get_chara_speed();
int get_chara_run_speed();
bool get_chara_dir();
void warrior_draw(int,int);
void archer_draw(int,int);

#endif // __CHARACTER_H__
