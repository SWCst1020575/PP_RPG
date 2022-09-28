#include "scene.h"



// function of game_scene
void game_scene_init(){
    stage_init(now_stage);
    character_init();

    stage_camera_init(now_stage);
    interface_init();
    equipment_init();
    item_using_init();
    storage_init();
    skill_key_init();
    atk_skill_init();
    if(now_stage == 1)
        npc_init();
    if(get_chara_career() == 2 || get_chara_career() == 3)
        remote_atk_init(get_chara_career());
    // reset to normal pos

}
void game_scene_process(ALLEGRO_EVENT event){
    character_process(event);
    camera_process(event);
    remote_atk_process(event);
    interface_process(event);
    atk_skill_process(event);
    if(now_stage == 1)
        npc_process(event);
    else if(now_stage == 2){
        monster_process(event);
        damage_text_process(event);
    }
}
void game_scene_update(){
    object_count = 0;
    character_update();
    wait_for_respawn();
    camera_update();
    remote_atk_update();
    atk_skill_update();
    monster_update(get_character_damage_x(),get_character_damage_width(),get_character_standing_y());
    battle_end();
    if(if_stage_change){
        if_stage_change = 0;
        stage_destroy();
        stage_init(now_stage);
        stage_camera_init(now_stage);
        if(now_stage == 1){
            set_character_pos(get_stage_avail_lefttop_x()+50,get_stage_avail_lefttop_y()+get_stage_avail_heigth()/2-get_character_heigth());
            monster_destory();
            character_reborn();
            battle_count_destroy();
            damage_text_destroy();
            npc_init();
        }
        else if(now_stage == 2){
            set_character_pos(get_stage_avail_lefttop_x()+50,get_stage_avail_lefttop_y()+get_stage_avail_heigth()/2-get_character_heigth());
            monster_init(get_chara_lv());
            damage_text_init();
            battle_count_init();
        }
    }
    damage_text_update();

}
void game_scene_draw(){
    stage_draw(get_camera_x(),get_camera_y());

    if(now_stage == 1)
        npc_draw(get_camera_x(),get_camera_y());


    monster_draw(0,object_count,get_camera_x(),get_camera_y());
    character_draw(get_camera_x(),get_camera_y());
    remote_atk_draw(get_camera_x(),get_camera_y());
    monster_draw(object_count,10,get_camera_x(),get_camera_y());
    if(now_stage == 2)
        monster_atk_on_character_draw(get_camera_x(),get_camera_y());
    atk_skill_draw(get_camera_x(),get_camera_y());
    damage_text_draw(get_camera_x(),get_camera_y());
    if(now_stage == 2)
        battle_count_draw();
    interface_draw(get_chara_lv(),get_chara_hp(),get_chara_maxhp(),get_chara_mp(),get_chara_maxmp(),get_chara_sp(),get_chara_exp(),get_chara_maxexp());
    if(tp_window_display)
        tp_draw();
}
void game_scene_destroy(){
    character_destory();
    stage_destroy();
    if(now_stage!=1){
        monster_destory();
        damage_text_destroy();
    }
    interface_destroy();
    remote_atk_destroy();
    if(now_stage == 1)
        npc_destroy();
    for(int i=0;i<ALLEGRO_KEY_MAX;i++)
        key_state[i] = false;
    atk_skill_destroy();
}
