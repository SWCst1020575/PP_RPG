#include "global.h"
#include "character.h"

void interface_init();
void interface_draw(int,int,int,int,int,int,int,int);
void wait_for_respawn();
void interface_destroy();
void interface_process(ALLEGRO_EVENT event);

void battle_count_init();
void battle_count_draw();
void battle_end();
void battle_count_destroy();

void crop_bmp(ALLEGRO_BITMAP ** bmp, int, int, int, int);
