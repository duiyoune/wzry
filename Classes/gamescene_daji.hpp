//
//  gamescene.hpp
//  SimpleGame
//
//  Created by 陈子杰 on 2019/5/12.
//

#ifndef gamescene_daji_hpp
#define gamescene_daji_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "attr_init.hpp"
#include "../extensions/cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

class daji :public Scene
{
public:
	static Scene * gamescene_daji();
};

class gamescene_daji :public Layer
{
private:
	int kills = 0;
	int deaths = 0;
	int time;
	int time_tolive;
	bool flag_creep;
	bool flag_heroalive;
	bool flag_aialive;
	std::string str;

public:
	virtual bool init();
	CREATE_FUNC(gamescene_daji);

private:
	void update_creep1(float t);
	friend class equipmentscene;

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
	void boundingbox_update1(float t);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);

	void onMouseDown(Event * event);
	void onMouseMove(Event *event);//鼠标移动

	void getBloodbar(Sprite *guaisprite, float a);
	void getBloodbar1(Sprite *guaisprite, float a);
	void hero_Attack();

    //工具
	virtual void update(float delta);//帧定时器
	float Distance(Sprite * A, Sprite * B);//计算距离

	//技能

	void cds(float dt);
	void cdf(float dt);

	void forf(float dt);
	void fors(float dt);
	void xiaobingsitu(float dt);
	void xiaoshis(float dt);
	double ability4(); //技能4
private:

	//技能
	//技能4
	int LV_ability4 = 1;//技能4等级
	Sprite *huoyan, *dazhao;
	Vec2 posmelee[600];
	Vec2 posrange[600];
	Vec2 poscat[600];
	Vec2 aipos;

	bool bools = true;
	bool boolf = true;
	int s = 50000, f = 50000;
	
	Size visibleSize;

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
	Label * label_KD;
private:
	int attack_flag = 0;
	int experience_hero1 = 0;
	int experience_hero2 = 0;
	int creep_i = 0;
	int deltaX = 0;
	int melee1_j;
	int melee2_j;
	bool hero_attack = false;
	bool hero_attack_target = false;

private:
	int getCurrentlvl(Sprite *sprite);
private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	void onKeyPressed4(EventKeyboard::KeyCode keyCode, Event* event);
	void onMouseMove1(Event * event);
	bool InTheArea(float X, float Y, Sprite  * A);
};

class set_daji :public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(set_daji);
	Sprite * equipment;
	void onMouseDown(Event * event);
private:
	int equip_number = -1;
	int equipX[6] = { 655,712,764,655,712,764 };
	int equipY[6] = { 66,66,66,22,22,22 };

};



#endif /* gamescene_daji_hpp */
