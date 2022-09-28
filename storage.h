#include "global.h"
#include "item_using.h"
#include "equipment.h"

void storage_init();
void get_item(int,int);
void get_equipment(int,int,int);
void use_item(int,int,bool);
void sell_equiment(int);

int get_storage_index(int);
bool get_storage_type(int);
int get_storage_num(int);
bool get_storage_ifequip(int);
int get_storage_total_num();
int get_storage_equipment_type(int);
int get_storage_no(int);
int get_storage_equip_pos(int i);
void set_storage_ifequip(int,bool);
void set_storage_equip_pos(int,int);
void set_storage_index(int,int);
void set_storage_type(int,int);
void set_storage_num(int,int);
void set_storage_equipment_type(int,int);
void set_storage_no(int,int);

void storage_sort();
int storage_compare(const void*,const void*);
