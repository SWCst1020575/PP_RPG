#include "status.h"


Character_status *create_new_status(){
    Character_status *_this = (Character_status *)calloc(1, sizeof(Character_status));
    return _this;
}
// --------------------initiate character status(new game)------------------------------
void else_career_init(Character_status *status){
    status->max_SP = 100;
    status->SP = status->max_SP;
}
void warrior_create_init(Character_status *status){
    status->career = 1;
    status->LV = 1;
    status->max_exp = 1000;
    status->exp = 0;
    status->money = 10000;
    status->max_HP = 750;
    status->HP = status->max_HP;
    status->max_MP = 300;
    status->MP = status->max_MP;
    status->max_SP = 100;
    status->SP = status->max_SP;
    status->atk = 100;
    status->def = 60;
    status->speed = 4;
    status->run_speed = 7;
    status->atkP = 20;
    status->skill_point = 1;
    for(int i=0;i<9;i++)
        status->skill[i]=0;
}
void archer_create_init(Character_status *status){
    status->career = 2;
    status->LV = 1;
    status->max_exp = 1000;
    status->exp = 0;
    status->money = 10000;
    status->max_HP = 550;
    status->HP = status->max_HP;
    status->max_MP = 350;
    status->MP = status->max_MP;
    status->max_SP = 100;
    status->SP = status->max_SP;
    status->atk = 130;
    status->def = 25;
    status->speed = 4;
    status->run_speed = 8;
    status->atkP = 40;
     status->skill_point=1;
    for(int i=0;i<9;i++)
        status->skill[i]=0;;
}
void wizard_create_init(Character_status *status){
    status->career = 3;
    status->LV = 1;
    status->max_exp = 1000;
    status->exp = 0;
    status->money = 10000;
    status->max_HP = 600;
    status->HP = status->max_HP;
    status->max_MP = 500;
    status->MP = status->max_MP;
    status->max_SP = 100;
    status->SP = status->max_SP;
    status->atk = 150;
    status->def = 30;
    status->speed = 4;
    status->run_speed = 7;
    status->atkP = 30;
    status->skill_point=1;
    for(int i=0;i<9;i++)
        status->skill[i]=0;
}
// --------------------lvup------------------------------
bool check_lv_up(Character_status *status){
    if(status->exp >= status->max_exp){
        status->exp -= status->max_exp;
        status->max_exp = 1000*(1+(float)(status->LV)*(float)(status->LV)/100);
        status->LV++;
        status->skill_point+=3;
        if(status->career == 1){
                status->max_HP += ceil((float)status->LV/10)*50;
                status->HP = status->max_HP;
                status->max_MP += ceil((float)status->LV/10)*10;
                status->MP = status->max_MP;
                status->SP = status->max_SP;
                status->atk += ceil((float)status->LV/10)*10;
                status->def += ceil((float)status->LV/10)*20;
                status->atkP += ceil((float)status->LV/10)*3;
        }
        else if(status->career == 2){
                status->max_HP += ceil((float)status->LV/10)*25;
                status->HP = status->max_HP;
                status->max_MP += ceil((float)status->LV/10)*15;
                status->MP = status->max_MP;
                status->SP = status->max_SP;
                status->atk += ceil((float)status->LV/10)*15;
                status->def += ceil((float)status->LV/10)*8;
                status->atkP += ceil((float)status->LV/10)*8;
        }
        else{
                status->max_HP += ceil((float)status->LV/10)*30;
                status->HP = status->max_HP;
                status->max_MP += ceil((float)status->LV/10)*25;
                status->MP = status->max_MP;
                status->SP = status->max_SP;
                status->atk += ceil((float)status->LV/10)*18;
                status->def += ceil((float)status->LV/10)*10;
                status->atkP += ceil((float)status->LV/10)*5;
        }
        return 1;
    }
    else
        return 0;
}
// --------------------get value------------------------------
int get_character_career(Character_status *status){
    return status->career;
}
int get_character_LV(Character_status *status){
    return status->LV;
}
int get_character_exp(Character_status *status){
    return status->exp;
}
int get_character_maxexp(Character_status *status){
    return status->max_exp;
}
int get_character_money(Character_status *status){
    return status->money;
}
int get_character_HP(Character_status *status){
    return status->HP;
}
int get_character_maxHP(Character_status *status){
    return status->max_HP;
}
int get_character_MP(Character_status *status){
    return status->MP;
}
int get_character_maxMP(Character_status *status){
    return status->max_MP;
}
int get_character_SP(Character_status *status){
    return status->SP;
}
int get_character_maxSP(Character_status *status){
    return status->max_SP;
}
int get_character_atk(Character_status *status){
    return status->atk;
}
int get_character_def(Character_status *status){
    return status->def;
}
int get_character_speed(Character_status *status){
    return status->speed;
}
int get_character_run_speed(Character_status *status){
    return status->run_speed;
}
int get_character_atkP(Character_status *status){
    return status->atkP;
}
int get_character_skill(Character_status *status,int skill){
    return status->skill[skill];
}
// --------------------set value------------------------------
void set_character_career(Character_status *status,int num){
    status->career = num;
}
void set_character_LV(Character_status *status,int num){
    status->LV = num;
}
void set_character_exp(Character_status *status,int num){
    status->exp = num;
}
void set_character_maxexp(Character_status *status,int num){
    status->max_exp = num;
}
void set_character_money(Character_status *status,int num){
    status->money = num;
}
void set_character_HP(Character_status *status,int num){
    status->HP = num;
}
void set_character_maxHP(Character_status *status,int num){
    status->max_HP = num;
}
void set_character_MP(Character_status *status,int num){
    status->MP = num;
}
void set_character_maxMP(Character_status *status,int num){
    status->max_MP = num;
}
void set_character_SP(Character_status *status,int num){
    status->SP = num;
}
void set_character_maxSP(Character_status *status,int num){
    status->max_SP = num;
}
void set_character_atk(Character_status *status,int num){
    status->atk = num;
}
void set_character_def(Character_status *status,int num){
    status->def = num;
}
void set_character_speed(Character_status *status,int num){
    status->speed = num;
}
void set_character_run_speed(Character_status *status,int num){
    status->run_speed = num;
}
void set_character_atkP(Character_status *status,int num){
    status->atkP = num;
}
void set_character_skill(Character_status *status,int num,int skill){
    status->skill[skill] = num;
}


