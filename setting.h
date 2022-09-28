#include "global.h"
#include "mouse.h"
#include "menu.h"
#include "esc.h"

void setting_init();
void setting_process(ALLEGRO_EVENT event);
void setting_draw();
void setting_text_onmouse_check();
void save_setting();
void setting_destroy();

extern bool setting_origin_window; //0=menu 1=esc

bool set_volume(ALLEGRO_EVENT event);
bool click_windowmode(ALLEGRO_EVENT event);
bool click_fullscreenmode(ALLEGRO_EVENT event);
bool click_backtomenu(ALLEGRO_EVENT event);
