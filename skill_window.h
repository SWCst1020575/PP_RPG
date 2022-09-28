#include "global.h"
#include "mouse.h"
#include "skill_key.h"
#include "character.h"
#include "atk_skill.h"


void skill_window_init();
void skill_window_process(ALLEGRO_EVENT event);
void skill_window_draw();
void skill_window_mouse_check();
void skill_window_wheel();
void skill_window_item_drag(ALLEGRO_EVENT event);
void skill_upgrade(ALLEGRO_EVENT event);
void skill_window_detroy();
