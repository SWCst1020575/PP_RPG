#ifndef __FORGE_WINDOW_H__
#define __FORGE_WINDOW_H__

#include "global.h"
#include "character.h"
#include "storage.h"
#include "equipment.h"

void forge_window_init();
void forge_process(ALLEGRO_EVENT event);
void forge_click(ALLEGRO_EVENT event);
void forge_draw();
void forge_window_mouse_check();
void forge_window_wheel();
void forge_item_drag(ALLEGRO_EVENT event);
void forge_item_detail_draw(int);
void forge_storage_reload();
void forge_destory();

#endif // __FORGE_WINDOW_H__
