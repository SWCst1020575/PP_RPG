#include "global.h"
#include "mouse.h"
#include "storage.h"
#include "character.h"
#include "item_using.h"


void item_window_init();
void item_window_process(ALLEGRO_EVENT event);
void item_window_draw();
void item_detail_draw(int);
void item_window_mouse_check();
void item_window_wheel();
void item_drag(ALLEGRO_EVENT event);
void item_window_destroy();
