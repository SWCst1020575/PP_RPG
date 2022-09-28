#ifndef __EQUIPMENT_H__
#define __EQUIPMENT_H__

#include "global.h"
#include "storage.h"
#include "character.h"

void equipment_init();
void create_new_equipment(int,int);


bool get_equipment_ifempty(int);
int get_equipment_no(int);
int get_equipment_index(int);
int get_equipment_storage_pos(int);
int get_equipment_equipment_type(int);
void set_equipment_ifempty(int,bool);
void set_equipment_no(int,int);
void set_equipment_index(int,int);
void set_equipment_storage_pos(int,int);
void set_equipment_equipment_type(int,int);

bool get_equipment_status_ifexist(int);
int get_equipment_status_lv(int);
int get_equipment_status_hp(int);
int get_equipment_status_mp(int);
int get_equipment_status_atk(int);
int get_equipment_status_def(int);
int get_equipment_status_atkP(int);
int get_equipment_status_money(int);
int get_equipment_status_enhancement_level(int);
void set_equipment_status_ifexist(int,bool);
void set_equipment_status_lv(int,int);
void set_equipment_status_hp(int,int);
void set_equipment_status_mp(int,int);
void set_equipment_status_atk(int,int);
void set_equipment_status_def(int,int);
void set_equipment_status_atkP(int,int);
void set_equipment_status_money(int,int);
void set_equipment_status_enhancement_level(int,int);

int get_equipment_total_hp();
int get_equipment_total_mp();
int get_equipment_total_atk();
int get_equipment_total_def();
int get_equipment_total_atkP();

#endif // __EQUIPMENT_H__
