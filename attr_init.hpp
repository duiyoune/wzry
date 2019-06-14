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
		double MoveSpeed;
		double AttackInterval;
        int attack_dis;
        int gold;
        int exp;
    }hero1;
    struct attr_creep
    {
        double HP[600];
        double base_damage;
        int attack_dis;
    }melee,range,catapult;
    struct attr_tower
    {
        int HP;
        int base_damage;
        int attack_dis;
    }tower,crystal;
public:
    void init();
    void init_creep(int i);
};

#endif /* attr_init_hpp */
