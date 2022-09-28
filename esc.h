#include "global.h"
#include "mouse.h"
#include "scene.h"
#include "save_load.h"

void esc_init();
void esc_process(ALLEGRO_EVENT event);
void esc_draw();
void esc_text_onmouse_check();
void esc_destroy();

bool esc_click_savegame(ALLEGRO_EVENT event);
bool esc_click_loadgame(ALLEGRO_EVENT event);
bool esc_click_backtomenu(ALLEGRO_EVENT event);
bool esc_click_setting(ALLEGRO_EVENT event);
bool esc_click_skill(ALLEGRO_EVENT event);
bool esc_click_cancel(ALLEGRO_EVENT event);
bool esc_click_item(ALLEGRO_EVENT event);
