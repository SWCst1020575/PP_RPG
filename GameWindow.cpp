#include "GameWindow.h"

bool draw = false;
int window = 1; // 1=menu 2=setting 3=createCharacter 4=saveloadGame 5=stage 6=esc 7=item 8=shop 9=skill window
int screenmode = 1; // 0=fullscreen 1=window
int bgmvolume = 100;
int sevolume = 100;
bool game_stop = 0;
bool if_battle = 0;
bool shop_type = 0;
int now_stage = 0;
int if_update = 0;

const char *title = "Final Project 109020021";
ALLEGRO_FILE *settingfile = NULL;
// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_SAMPLE *song=NULL;
ALLEGRO_SAMPLE_INSTANCE *sample_instance;
ALLEGRO_DISPLAY_MODE mode;


int Game_establish() {
    int msg = 0;

    game_init();
    game_begin();

    while ( msg != GAME_TERMINATE ) {
        msg = game_run();
        if ( msg == GAME_TERMINATE )

            ( "Game Over\n" );
    }

    game_destroy();
    return 0;
}

void game_init() {
    printf( "Game Initializing...\n" );

    al_init();
    // init audio
    al_install_audio();
    al_init_acodec_addon();
    // Create display

    //read settingdat
    ALLEGRO_CONFIG *setting_config = al_load_config_file("./save/setting.dat");


    screenmode = atoi(al_get_config_value(setting_config,"SCREEN_MODE","MODE"));
    bgmvolume = atoi(al_get_config_value(setting_config,"BGM_VOLUME","VOLUME"));
    sevolume = atoi(al_get_config_value(setting_config,"SE_VOLUME","VOLUME"));

    al_destroy_config(setting_config);



    if(screenmode==0){
        al_get_display_mode(al_get_num_display_modes() , &mode);
        mode.height=HEIGHT;
        mode.width=WIDTH;
        al_set_new_display_flags(ALLEGRO_FULLSCREEN);
        display = al_create_display(mode.width, mode.height);
    }
    else{
        al_get_display_mode(al_get_num_display_modes() , &mode);
        mode.height=HEIGHT;
        mode.width=WIDTH;
        al_set_new_display_flags(ALLEGRO_WINDOWED);
        display = al_create_display(mode.width, mode.height);
    }

    // create event queue
    event_queue = al_create_event_queue();
    // Initialize Allegro settings
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, title);
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event
    // Register event
    al_register_event_source(event_queue, al_get_display_event_source( display ));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    fps  = al_create_timer( 1.0 / FPS );
    al_register_event_source(event_queue, al_get_timer_event_source( fps )) ;
    // initialize the icon on the display
    ALLEGRO_BITMAP *icon = al_load_bitmap("./image/icon.jpg");
    al_set_display_icon(display, icon);
}

void game_begin() {
    //Load sound
    song = al_load_sample("./sound/hello.wav");
    al_reserve_samples(20);
    sample_instance = al_create_sample_instance(song);
    //Loop the song until the display closes
    al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(sample_instance, (float)bgmvolume/100);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_play_sample_instance(sample_instance);
    al_start_timer(fps);
    // initialize the menu before entering the loop
    menu_init();

}

void game_update(){
    if( judge_next_window ){
        if( window == 1 && target_window == 3){
            CreateCharacter_init();
            judge_next_window = false;
            window = 3;
        }
        if( window == 1 && target_window == 2){
            setting_init();
            setting_origin_window = 0;
            judge_next_window = false;
            window = 2;
        }
        if( window == 1 && target_window == 4){
            sl_type = 1;
            sl_origin_window = 0;
            sl_init();
            judge_next_window = false;
            window = 4;
        }
        if( window == 2 && target_window == 1){
            setting_destroy();
            judge_next_window = false;
            window = 1;
        }
        if( window == 2 && target_window == 6){
            setting_destroy();
            judge_next_window = false;
            window = 6;
        }
        if( window == 3 && target_window == 5){
            CreateCharacter_destroy();
            menu_destroy();
            enter_game_type = 1;
            now_stage = 1;
            game_scene_init();
            judge_next_window = false;
            window = 5;
        }
        if( window == 3 && target_window == 1){
            CreateCharacter_destroy();
            judge_next_window = false;
            window = 1;
        }
        if( window == 4 && target_window == 1){
            sl_destroy();
            judge_next_window = false;
            window = 1;
        }
        if( window == 4 && target_window == 5){
            sl_destroy();
            if(sl_origin_window){
                esc_destroy();
                game_scene_destroy();
            }
            else
                menu_destroy();
            game_stop = 0;
            now_stage = 1;
            enter_game_type = 0;
            game_scene_init();
            judge_next_window = false;
            window = 5;
        }
        if( window == 4 && target_window == 6){
            sl_destroy();
            judge_next_window = false;
            window = 6;
        }
        if(window == 5 && target_window == 6){
            judge_next_window = false;
            esc_init();
            for(int i=0;i<ALLEGRO_KEY_MAX;i++)
                key_state[i] = false;
            window = 6;
        }
        if(window == 5 && target_window == 8){
            judge_next_window = false;
            shop_window_init();
            for(int i=0;i<ALLEGRO_KEY_MAX;i++)
                key_state[i] = false;
            window = 8;
        }
        if(window == 5 && target_window == 10){
            judge_next_window = false;
            forge_window_init();
            for(int i=0;i<ALLEGRO_KEY_MAX;i++)
                key_state[i] = false;
            window = 10;
        }
        if(window == 6 && target_window == 5){
            esc_destroy();
            judge_next_window = false;
            for(int i=0;i<ALLEGRO_KEY_MAX;i++)
                key_state[i] = false;
            window = 5;
        }
        if(window == 6 && target_window == 2){
            setting_origin_window = 1;
            setting_init();
            judge_next_window = false;
            window = 2;
        }
        if(window == 6 && target_window == 4){
            sl_origin_window = 1;
            sl_init();
            judge_next_window = false;
            window = 4;
        }
        if(window == 6 && target_window == 1){
            esc_destroy();
            game_scene_destroy();
            now_stage = 0;
            enter_game_type = 0;
            menu_init();
            judge_next_window = false;
            window = 1;
        }
        if(window == 6 && target_window == 7){
            judge_next_window = false;
            item_window_init();
            window = 7;
        }
        if(window == 6 && target_window == 9){
            judge_next_window = false;
            skill_window_init();
            window = 9;
        }
        if(window == 7 && target_window == 6){
            judge_next_window = false;
            item_window_destroy();
            window = 6;
        }
        if(window == 8 && target_window == 5){
            judge_next_window = false;
            shop_destory();
            window = 5;
        }
        if(window == 9 && target_window == 6){
            judge_next_window = false;
            skill_window_detroy();
            window = 6;
        }
        if(window == 10 && target_window == 5){
            judge_next_window = false;
            forge_destory();
            window = 5;
        }
    }
    else if(window == 2){
        al_set_sample_instance_gain(sample_instance, (float)bgmvolume/100);
        if(now_stage!=0)
            character_set_sevolume();
        if(now_stage !=0 && now_stage != 1)
            set_monster_volume();
    }
    else if( window == 5 ){
        game_scene_update();

    }
    else if(window == 7){
        item_window_mouse_check();
        item_window_wheel();
    }
    else if(window == 8){
        shop_window_mouse_check();
        shop_window_wheel();
    }
    else if(window == 9){
        skill_window_mouse_check();
        skill_window_wheel();
    }
    else if(window == 10){
        forge_window_mouse_check();
        forge_window_wheel();
    }
}
int process_event(){
    // Request the event
    mouse_update();
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    // process the event of other component


    if( window == 1 ){
        menu_process(event);
        if(exit_game)
            return GAME_TERMINATE;

    }
    else if( window == 2 ){

        if(screenmode == 0 && click_windowmode(event))
            switch_window();
        if(screenmode == 1 && click_fullscreenmode(event))
            switch_fullscreen();

        if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
            key_state[event.keyboard.keycode] = true;
            if( key_state[ALLEGRO_KEY_ESCAPE]){
                save_setting();
                if(setting_origin_window)
                    target_window = 6;
                else
                    target_window = 1;
                judge_next_window = true;
            }
            key_state[event.keyboard.keycode] = false;
        }

        setting_process(event);
    }
    else if( window == 3 ){
        if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
            key_state[event.keyboard.keycode] = true;
            if( key_state[ALLEGRO_KEY_ESCAPE]){
                target_window = 1;
                judge_next_window = true;
            }
            key_state[event.keyboard.keycode] = false;
        }
        CreateCharacter_process(event);
    }
    else if( window == 4 ){
        if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
            key_state[event.keyboard.keycode] = true;
            if( key_state[ALLEGRO_KEY_ESCAPE]){
                if(sl_origin_window)
                    target_window = 6;
                else
                    target_window = 1;
                judge_next_window = true;
            }
            key_state[event.keyboard.keycode] = false;
        }
        sl_process(event);
    }
    else if( window == 5 ){

        if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
            key_state[event.keyboard.keycode] = true;
            if(key_state[ALLEGRO_KEY_ESCAPE]){
                game_stop = 1;
                target_window = 6;
                judge_next_window = true;
            }
            key_state[event.keyboard.keycode] = false;
        }
        game_scene_process(event);
    }
    else if(window == 6){
        if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
            key_state[event.keyboard.keycode] = true;
            if( key_state[ALLEGRO_KEY_ESCAPE]){
                game_stop = 0;
                target_window = 5;
                judge_next_window = true;
            }
            key_state[event.keyboard.keycode] = false;
        }
        else
            esc_process(event);
    }
    else if(window == 7){
        if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
            key_state[event.keyboard.keycode] = true;
            if( key_state[ALLEGRO_KEY_ESCAPE]){
                target_window = 6;
                judge_next_window = true;
            }
            key_state[event.keyboard.keycode] = false;
        }
        item_window_process(event);
    }
    else if(window == 8){
        if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
            key_state[event.keyboard.keycode] = true;
            if( key_state[ALLEGRO_KEY_ESCAPE]){
                game_stop = 0;
                target_window = 5;
                judge_next_window = true;
            }
            key_state[event.keyboard.keycode] = false;
        }
        else
            shop_process(event);
    }
    else if(window == 9){
        if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
            key_state[event.keyboard.keycode] = true;
            if( key_state[ALLEGRO_KEY_ESCAPE]){
                target_window = 6;
                judge_next_window = true;
            }
            key_state[event.keyboard.keycode] = false;
        }
        skill_window_process(event);
    }
    else if(window == 10){
        if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
            key_state[event.keyboard.keycode] = true;
            if( key_state[ALLEGRO_KEY_ESCAPE]){
                game_stop = 0;
                target_window = 5;
                judge_next_window = true;
            }
            key_state[event.keyboard.keycode] = false;
        }
        else
            forge_process(event);
    }
    // Shutdown our program
    //if(judge_next_window)
        //game_update();
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return GAME_TERMINATE;
    else if(event.type == ALLEGRO_EVENT_TIMER)
        if(event.timer.source == fps){
            draw = true;
            if_update = 0;
        }
    if(if_update == 0){
        game_update();
        if_update = 1;
    }
    return 0;
}
void game_draw(){

    if( window == 1 ){
        menu_text_onmouse_check();
        menu_draw();
    }
    else if( window == 2 ){
        setting_text_onmouse_check();
        setting_draw();
    }
    else if( window == 3 ){
        CreateCharacter_onmouse_check();
        CreateCharacter_draw();
    }
    else if( window == 4 ){
        sl_window_onmouse_check();
        sl_draw();
    }
    else if( window == 5 ){
        if(now_stage == 1)
            npc_onmouse_check(get_camera_x(),get_camera_y());
        game_scene_draw();
    }
    else if( window == 6 ){
        esc_draw();
        esc_text_onmouse_check();
    }
    else if(window == 7){
        esc_draw();
        item_window_draw();
    }
    else if(window == 8){
        game_scene_draw();
        shop_draw();
    }
    else if(window == 9){
        esc_draw();
        skill_window_draw();
    }
    else if(window == 10){
        game_scene_draw();
        forge_draw();
    }
    al_flip_display();
}
int game_run() {
    int error = 0;
    if( draw ){
        game_draw();
        draw = false;
    }
    if ( !al_is_event_queue_empty(event_queue) ) {
        error = process_event();
    }
    return error;
}

void game_destroy() {

    // Make sure you destroy all things
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    game_scene_destroy();
}

void switch_fullscreen(){
    al_destroy_display(display);
    al_get_display_mode(al_get_num_display_modes() , &mode);
    mode.height=HEIGHT;
    mode.width=WIDTH;
    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    display = al_create_display(mode.width, mode.height);
    screenmode = 0;
}
void switch_window(){
    al_destroy_display(display);
    al_get_display_mode(al_get_num_display_modes() , &mode);
    mode.height=HEIGHT;
    mode.width=WIDTH;
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(mode.width, mode.height);
    screenmode = 1;
}
