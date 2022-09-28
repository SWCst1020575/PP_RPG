#include "global.h"
#include "stage.h"
#include "damage.h"
#include "character.h"

void monster_init(int);
void monster_process(ALLEGRO_EVENT event);
void monster_spawn();
void monster_die();
void monster_update(int,int,int);
void monster_draw(int,int,int,int);
void monster_hp_draw(int,int,int);
void monster_destory();

int get_monster1_hp(int);
int get_monster1_def(int);
int get_monster1_x(int);
int get_monster1_y(int);
int get_monster1_standing_y(int);
int get_monster1_width();
int get_monster1_heigth();
bool get_monster1_show(int);
bool get_monster1_if_die(int);
void set_monster1_hp(int,int);

void set_monster_volume();

int monster_compare(const void *,const void *);
void draw_stage2_monster1(int,int,int);
void monster_atk_on_character_draw(int,int);
