//
//  attr_init.hpp
//  SimpleGame
//
//  Created by 陈子杰 on 2019/6/1.
//

#ifndef attr_init_hpp
#define attr_init_hpp


class attr
{
public:
     struct attr_hero
    {
        int HP;
        int HP_max;
        int base_damage;
        int attack_dis;
    }hero1;
    struct attr_creep
    {
        int HP;
        int base_damage;
        int attack_dis;
    }melee,range,tower,catapult,crystal;
public:
    void init();
    void init_creep();
    int get_melee_HP(){return melee.HP;};
};

#endif /* attr_init_hpp */
