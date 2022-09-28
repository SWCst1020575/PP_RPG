#ifndef __ITEM_USING_H__
#define __ITEM_USING_H__
#include "global.h"
#include "storage.h"
#include "character.h"


void item_using_init();
bool get_item_using_ifempty(int);
int get_item_using_index(int);
int get_item_using_storage_pos(int);
void set_item_using_ifempty(int,bool);
void set_item_using_index(int,int);
void set_item_using_storage_pos(int,int);

void item_effect(int);

#endif
