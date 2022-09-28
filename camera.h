#include "global.h"
#include "stage.h"
#include "character.h"

void stage_camera_init(int);
void camera_process(ALLEGRO_EVENT event);
void camera_update();
void trace_character(int);

int get_camera_x();
int get_camera_y();
