#include "global.h"
#include "character.h"
#include "scene.h"
#include "mouse.h"
#include "menu.h"
#include "setting.h"
#include "esc.h"
#include "createCharacter.h"
#include "item_window.h"
#include "shop.h"
#include "skill_window.h"
#include "forge_window.h"
#include "save_load.h"



int Game_establish();
void game_init();
void game_begin();
void game_update();
int process_event();
void game_draw();
int game_run();
void game_destroy();
void switch_fullscreen();
void switch_window();

