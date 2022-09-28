#ifndef __SHOP_H__
#define __SHOP_H__

#include "global.h"
#include "character.h"
#include "storage.h"


void shop_window_init();
void shop_process(ALLEGRO_EVENT event);
void shop_draw();
void shop_window_mouse_check();
void shop_window_wheel();
void shop_buy(ALLEGRO_EVENT event);
void shop_item_drag(ALLEGRO_EVENT event);
void shop_item_detail_draw(int);
void storage_reload();
void shop_destory();

#endif // __SHOP_H__
