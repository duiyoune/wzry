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
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
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
	attr a;
	attr b;

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
    void update_Melee_creep2_attack(float t);
    void update_Range_creep2_attack(float t);
    void update_Catapult2_attack(float t);
    
    void update_tower1_attack(float t);
    void update_heroHP(float t);
    void update_time(float t);
    void update_ai(float t);
    void clickCreep_enemy(float X, float Y);

    void update_tower2_attack(float t);
    void boundingbox_update(float t);
    void boundingbox_update1(float t);
    void boundingbox_update2(float t);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);
    int getDistance(Sprite *target1 ,Sprite *target2);

    void onMouseDown(Event * event);
	void onMouseMove(Event *event);//鼠标移动

    void getBloodbar(Sprite *guaisprite ,float a);
    void getBloodbar1(Sprite *guaisprite ,float a);
    void hero_Attack();

	//技能
	void ability1();//技能1
	void ability1DurationUpdate(float delta);//技能1持续时间
	void ability1CDUpdate(float delta);//技能1冷却时间
	void ability2();//技能2
	void ability2CDUpdate(float delta);//技能2冷却时间
	void ability3Effect();//技能3效果
	void ability3CDUpdate(float delta);//技能3冷却时间
	void ability3Hit(float X, float Y);//判断技能3是否作用于敌方单位
	void ability3Cursor(float X, float Y);//技能3光标随鼠标移动
	double ability4(); //技能4
	//工具
	float Distance(Sprite * A, Sprite * B);//计算距离
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
    Label * label_damage;
    Label * label_hp;

public:
    int attack_flag=0;
    int experience_hero1=0;
    int experience_hero2=0;
    int creep_i=0;
    int deltaX=0;
    int melee1_j;
    int melee2_j;
    bool hero_attack=false;
    bool hero_attack_target=false;
	//技能
	//技能1
	int LV_ability1 = 4;//技能1等级
	bool duration_ability1 = false;//技能1是否处于持续期间
	bool cd_ability1 = false;//技能1是否处于冷却期间
	//技能1属性
	int CD_ability1 = 30;//技能1冷却时间
	int Duration_ability1 = 15;//技能1持续时间
	//技能2
	int LV_ability2 = 4;//技能2等级
	bool cd_ability2 = false;//技能2是否处于冷却期间
	//技能2属性
	int CD_ability2 = 10;//技能2冷却时间
	//技能3
	int LV_ability3 = 4;//技能3等级
	bool cd_ability3 = false;//技能3是否处于冷却期间
	bool ability3Clicked = false;//技能3是否被按下
	int ability3_target = -1;//技能3所作用的小兵
	bool ability3_targetAI = false;//技能3是否作用于ai
	bool ability3_targetMelee = false;//技能3是否作用于近战
	bool ability3_targetRange = false;//技能3是否作用于远程
	bool ability3_targetSiege = false;//技能3是否作用于攻城
	bool ability3MovingToAI = false;//英雄是否为释放技能3向ai移动
	bool ability3MovingToMelee = false;//英雄是否为释放技能3向近战移动
	bool ability3MovingToRange = false;//英雄是否为释放技能3向远程移动
	bool ability3MovingToSiege = false;//英雄是否为释放技能3向攻城移动
	//技能3属性
	double CastRange_ability3 = 500;//技能3施法范围
	int CD_ability3 = 10;//技能3冷却时间
	//技能4
	int LV_ability4 = 4;//技能4等级

private:
     int getCurrentlvl(Sprite *sprite);
private:
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
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
