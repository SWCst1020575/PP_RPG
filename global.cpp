#include "global.h"

// variables for global usage
const float FPS = 60.0;
const int WIDTH = 1600;
const int HEIGHT = 900;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;

bool key_state[ALLEGRO_KEY_MAX] = {false};
bool judge_next_window = false;
int target_window = 1;
int enter_game_type = 0;
bool exit_game = false;
bool if_stage_change = 0;

int object_count = 0;

int get_rand(int a,int b){

    return (rand()%(b-a+1)) + a;
}
