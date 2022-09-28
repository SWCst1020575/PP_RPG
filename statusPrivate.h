#ifndef __STATUSPRIVATE_H__
#define __STATUSPRIVATE_H__


typedef struct Character_status{
    int career;//1=warrior 2=archer 3=wizard
    int LV;
    int exp;
    int max_exp;
    int money;
    int HP;
    int max_HP;
    int MP;
    int max_MP;
    int SP;
    int max_SP;
    int atk;
    int def;
    int speed;
    int run_speed;
    int atkP; //penetrate
    int skill_point;
    int skill[10]; //10 skills  value=skill level
};

#endif
