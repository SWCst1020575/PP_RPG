#include "global.h"
#include "mouse.h"
#include "createCharacter.h"
#include "statusPrivate.h"

Character_status *create_new_status();

void else_career_init(Character_status *status);
void warrior_create_init(Character_status *status);
void archer_create_init(Character_status *status);
void wizard_create_init(Character_status *status);

bool check_lv_up(Character_status *status);

int get_character_career(Character_status *status);
int get_character_LV(Character_status *status);
int get_character_exp(Character_status *status);
int get_character_maxexp(Character_status *status);
int get_character_money(Character_status *status);
int get_character_HP(Character_status *status);
int get_character_maxHP(Character_status *status);
int get_character_MP(Character_status *status);
int get_character_maxMP(Character_status *status);
int get_character_SP(Character_status *status);
int get_character_maxSP(Character_status *status);
int get_character_atk(Character_status *status);
int get_character_def(Character_status *status);
int get_character_speed(Character_status *status);
int get_character_run_speed(Character_status *status);
int get_character_atkP(Character_status *status);
int get_character_skill(Character_status *status,int);

void set_character_career(Character_status *status,int);
void set_character_LV(Character_status *status,int);
void set_character_exp(Character_status *status,int);
void set_character_maxexp(Character_status *status,int);
void set_character_money(Character_status *status,int);
void set_character_HP(Character_status *status,int);
void set_character_maxHP(Character_status *status,int);
void set_character_MP(Character_status *status,int);
void set_character_maxMP(Character_status *status,int);
void set_character_SP(Character_status *status,int);
void set_character_maxSP(Character_status *status,int);
void set_character_atk(Character_status *status,int);
void set_character_def(Character_status *status,int);
void set_character_speed(Character_status *status,int);
void set_character_run_speed(Character_status *status,int);
void set_character_atkP(Character_status *status,int);
void set_character_skill(Character_status *status,int,int);

