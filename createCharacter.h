#include "global.h"
#include "mouse.h"
#include "menu.h"


extern bool confirm_window;
extern int create_career_type; //1=warrior 2=archer 3=wizard

void CreateCharacter_init();
void CreateCharacter_process(ALLEGRO_EVENT event);
void CreateCharacter_draw();
void CreateCharacter_onmouse_check();
int choose_career(ALLEGRO_EVENT event);
bool click_confirmCancel(ALLEGRO_EVENT event);
bool click_confirmOk(ALLEGRO_EVENT event);
bool click_Cancel(ALLEGRO_EVENT event);
void CreateCharacter_destroy();
