//
//  attr_init.cpp
//  SimpleGame
//
//  Created by 陈子杰 on 2019/6/1.
//

#include "attr_init.hpp"

void attr::init()
{
    hero1.HP=1000;
    hero1.attack_dis=500;
    hero1.base_damage=30;
    
    melee.attack_dis=100;
    melee.HP=200;
    melee.base_damage=20;
    
    range.attack_dis=400;
    range.HP=100;
    range.base_damage=30;
    
    tower.attack_dis=450;
    tower.HP=1000;
    tower.base_damage=50;
    
    crystal.attack_dis=500;
    crystal.HP=3000;
    crystal.base_damage=60;
}

void attr::init_creep()
{
    melee.HP=200;
    range.HP=100;
}



