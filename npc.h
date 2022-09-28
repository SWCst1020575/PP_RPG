#include "global.h"
#include "mouse.h"

extern bool tp_window_display;

void npc_init();
void npc_draw(int,int);
void npc_onmouse_check(int,int);
void npc_destroy();


void tp_draw();
void npc_process(ALLEGRO_EVENT event);
bool click_weapon_shop(ALLEGRO_EVENT event);
bool click_potion_shop(ALLEGRO_EVENT event);
bool click_forging_shop(ALLEGRO_EVENT event);
bool click_tpgate(ALLEGRO_EVENT event);
bool click_tpgate_cancel(ALLEGRO_EVENT event);
bool click_stage2_text(ALLEGRO_EVENT event);
