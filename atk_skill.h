#include "global.h"
#include "damage.h"
#include "character.h"

void atk_skill_init();
void atk_skill_process(ALLEGRO_EVENT event);
void skill_call(int,int,int,bool,int);
void atk_skill_update();
void atk_skill_damage(int);
void atk_skill_draw(int,int);
void atk_skill_destroy();
