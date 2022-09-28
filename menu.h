#include "global.h"
#include "mouse.h"


void menu_init();
void menu_process(ALLEGRO_EVENT event);
void menu_draw();
void menu_destroy();
void menu_text_onmouse_check();

bool click_newgame(ALLEGRO_EVENT event);
bool click_loadgame(ALLEGRO_EVENT event);
bool click_setting(ALLEGRO_EVENT event);
bool click_exitgame(ALLEGRO_EVENT event);
