#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#define GAME_TERMINATE -1
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// note that you can't assign initial value here!
extern int screenmode;
extern int bgmvolume;
extern int sevolume;
extern int enter_game_type;//0=menu 1=newgame 2=loadgame
extern int target_window;
extern int if_update;
extern int now_stage; //0=not in game 1~=game stage
extern int object_count;

extern bool key_state[ALLEGRO_KEY_MAX];
extern bool judge_next_window;
extern bool exit_game;
extern bool game_stop;
extern bool shop_type;
extern bool if_battle;// 0=in town 1=in dungeon
extern bool if_stage_change;// 0=in town 1=in dungeon

extern const float FPS;
extern const int WIDTH;
extern const int HEIGHT;

extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *fps;

int get_rand(int,int);
#endif
