//
//  gamescene.hpp
//  SimpleGame
//
//  Created by 陈子杰 on 2019/5/12.
//

#ifndef gamescene_houyi_hpp
#define gamescene_houyi_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "attr_init.hpp"
#include "../extensions/cocos-ext.h"
USING_NS_CC;




class scene:public Scene
{
public:
    static Scene * gamescene();

};



class gamescene_houyi:public Layer
{
public:
    attr a;
    attr b;
    bool flag_creep;
public:
    virtual bool init();
    CREATE_FUNC(gamescene_houyi);
private:
    void onMenuItem(Ref * obj);
    void update_creep1(float t);
//    void update_creep2(float t);
//    void update_creep3(float t);
//    void update_creep4(float t);
    void update_Melee_creep1_attack(float t);
    void update_Range_creep1_attack(float t);
    void update_Catapult1_attack(float t);
    void update_tower1_attack(float t);
    void update_heroHP(float t);
    
    void update_Melee_creep2_attack(float t);
    void update_Range_creep2_attack(float t);
    void update_Catapult2_attack(float t);
    void update_tower2_attack(float t);
    void boundingbox_update(float t);

    void onMouseMove(Event * event);
    void getBloodbar(Sprite *guaisprite ,float a);
    int getDistance(Sprite *target1 ,Sprite *target2);
public:
    Sprite * sprite;
    Sprite * Melee_creep1;
    Sprite * Melee_creep2;
    Sprite * Crystal1;
    Sprite * Crystal2;
    Sprite * Tower1;
    Sprite * Tower2;
    Sprite * pb;
    Sprite * Range_creep1;
    Sprite * Range_creep2;
    Sprite * Catapult1;
    Sprite * Catapult2;
    
    int experience_hero1=0;
    int experience_hero2=0;
private:
     int getCurrentlvl(int experience_hero);
};


class equipmentscene:public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(equipmentscene);
private:
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
    void update_keyboard(float t);
    bool isKeyPressed(EventKeyboard::KeyCode keyCode);
    
    void  item_hongbaoshi(Ref * obj);
};



#endif /* gamescene_houyi_hpp */
