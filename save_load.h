#ifndef __SAVE_LOAD_H__
#define __SAVE_LOAD_H__
#include "global.h"
#include "character.h"
#include "storage.h"
#include "item_using.h"
#include "skill_key.h"
#include "mouse.h"
#include "menu.h"
#include "esc.h"

extern bool sl_type;
extern bool sl_origin_window;

void sl_init();
void sl_process(ALLEGRO_EVENT event);
void sl_draw();
void sl_window_onmouse_check();
void sl_window_reload();
void sl_data_save(ALLEGRO_EVENT event);
void sl_data_load(ALLEGRO_EVENT event);
void sl_destroy();

#endif // __SAVE_LOAD_H__
