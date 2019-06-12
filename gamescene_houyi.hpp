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
    int time;
    int time_tolive;
    bool flag_creep;
    bool flag_heroalive;
    bool flag_aialive;

    std::string str;
public:
    virtual bool init();
    CREATE_FUNC(gamescene_houyi);
   
private:
    void onMenuItem(Ref * obj);
    void update_creep1(float t);
    friend class equipmentscene;
    void update_creep2(float t);
    void update_creep3(float t);
    void update_creep4(float t);

    void update_Melee_creep1_attack(float t);
    void update_Range_creep1_attack(float t);
    void update_Catapult1_attack(float t);
    void update_tower1_attack(float t);
    void update_heroHP(float t);
    void update_time(float t);
    void update_ai(float t);
    void clickCreep_enemy(float X, float Y);
    void update_Melee_creep2_attack(float t);
    void update_Range_creep2_attack(float t);
    void update_Catapult2_attack(float t);
    void update_tower2_attack(float t);
    void boundingbox_update(float t);
    void boundingbox_update1(float t);
    void boundingbox_update2(float t);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);
    int getDistance(Sprite *target1 ,Sprite *target2);

    void onMouseMove(Event * event);

    void getBloodbar(Sprite *guaisprite ,float a);
    void getBloodbar1(Sprite *guaisprite ,float a);
    void hero_Attack();

    
private:
    Sprite * sprite;
    Sprite * ai;
    Sprite * Melee_creep1[600];
    Sprite * Melee_creep2[600];
    Sprite * Crystal1;
    Sprite * Crystal2;
    Sprite * Tower1;
    Sprite * Tower2;
    Sprite * pb;
    Sprite * Range_creep1[600];
    Sprite * Range_creep2[600];
    Sprite * Catapult1[600];
    Sprite * Catapult2[600];
    Sprite * pBloodKongSp;
    Sprite * cursor;
    Sprite * flag_sprite;
    Sprite * melee1_target[4];
    Sprite * melee2_target[4];
    Sprite * range1_target[4];
    Sprite * range2_target[4];
    Label * label_time;
    Label * label_gold;
    Label * label_lvl;

public:
    int attack_flag=0;
    int tag_flag=5;
    int tag_hero=6;
    int tag_layer=7;
    int experience_hero1=0;
    int experience_hero2=0;
    int creep_i=0;
    int deltaX=0;
    int melee1_j;
    int melee2_j;
    bool hero_attack=false;
    bool flag_tab=false;
    bool hero_attack_target=false;
private:
     int getCurrentlvl(Sprite *sprite);
private:
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
//    void update_keyboard(float t);
//    bool onKeyPressed1(EventKeyboard::KeyCode keyCode);
    void onKeyPressed4(EventKeyboard::KeyCode keyCode,Event* event);
    void onMouseMove1(Event * event);
    bool InTheArea(float X, float Y,Sprite  * A);
};

class set:public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(set);
    Sprite * equipment;
    void onMouseDown(Event * event);
public:
    int equip_number=-1;
    int equipX[6]={655,712,764,655,712,764};
    int equipY[6]={66,66,66,22,22,22};

};



#endif /* gamescene_houyi_hpp */
