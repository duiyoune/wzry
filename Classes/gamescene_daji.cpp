//
//  gamescene.cpp
//  SimpleGame
//
//  Created by 陈子杰 on 2019/5/12.
//
#include <iostream>
#include<string.h>
#include "gamescene_daji.hpp"
#include "scene1.h"
#include <math.h>
#include "attr_init.hpp"
#include "SimpleAudioEngine.h"
#include "win.h"
#include "lose.h"

using namespace CocosDenshion;
USING_NS_CC;
using namespace std;

Layer *layer_game_daji;
Layer *layer_set_daji;
Sprite * bug_daji;
Sprite * store_daji;
bool flag_tab_daji = false;
attr a_daji;
attr b_daji;
auto AbilitySoundEffect_daji = SimpleAudioEngine::getInstance();//音效


Scene* daji::gamescene_daji()
{
	auto scene = Scene::create();
	layer_game_daji = gamescene_daji::create();
	layer_set_daji = set_daji::create();
	scene->addChild(layer_game_daji);
	scene->addChild(layer_set_daji);
	return scene;

}

bool gamescene_daji::init()
{
	if (!Layer::init())
	{
		return false;
	}
	time = 0;



	visibleSize = Director::getInstance()->getVisibleSize();
	//背景音乐
	auto BGM = SimpleAudioEngine::getInstance();
	BGM->playBackgroundMusic("bgm.mp3", true);


	a_daji.init();
	b_daji.init();
	flag_creep = false;
	//地图
	auto map = Sprite::create("map.png");
	this->addChild(map, 0);
	map->setPosition(2100, visibleSize.height / 2);
	//英雄
	sprite = Sprite::create("daji1.png");
	sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(sprite, 4);
	flag_heroalive = true;
	//ai
	ai = Sprite::create("bm.png");
	ai->setPosition(3500, visibleSize.height / 2);
	ai->setScale(0.5);
	this->addChild(ai, 4);
	flag_aialive = true;
	//塔

	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("tower-0001-default.plist");

	Tower1 = Sprite::create("tower1.png");
	Tower1->setPosition(1700, visibleSize.height / 2);
	this->addChild(Tower1, 1);

	Tower2 = Sprite::create("tower2.png");
	Tower2->setPosition(2500, visibleSize.height / 2);
	this->addChild(Tower2, 1);
	//基地
	Crystal1 = Sprite::create("crystal1.png");
	Crystal1->setPosition(800, visibleSize.height / 2);
	this->addChild(Crystal1, 1);

	Crystal2 = Sprite::create("crystal2.png");
	Crystal2->setPosition(3300, visibleSize.height / 2);
	this->addChild(Crystal2, 1);
	//监听器	
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(gamescene_daji::onMouseDown, this);
	listener->onMouseMove = CC_CALLBACK_1(gamescene_daji::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto listener1 = EventListenerMouse::create();
	listener1->onMouseMove = CC_CALLBACK_1(gamescene_daji::onMouseMove1, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	auto listener3 = EventListenerKeyboard::create();
	listener3->onKeyPressed = CC_CALLBACK_2(gamescene_daji::onKeyPressed, this);
	listener3->onKeyReleased = CC_CALLBACK_2(gamescene_daji::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener3, this);

	auto listener4 = EventListenerKeyboard::create();
	listener4->onKeyPressed = CC_CALLBACK_2(gamescene_daji::onKeyPressed4, this);
	listener4->onKeyReleased = CC_CALLBACK_2(gamescene_daji::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener4, this);

	this->scheduleUpdate();
	this->schedule(schedule_selector(gamescene_daji::update_time), 1);
	//出兵
	this->schedule(schedule_selector(gamescene_daji::update_creep1), 15);
	this->schedule(schedule_selector(gamescene_daji::update_heroHP), 0.1f);
	//塔攻击

	this->schedule(schedule_selector(gamescene_daji::update_tower2_attack), 1);
	this->schedule(schedule_selector(gamescene_daji::update_tower1_attack), 1);

	return true;
}

bool set_daji::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	bug_daji = Sprite::create("equipment.png");
	bug_daji->setPosition(0, 0);
	this->addChild(bug_daji);
	bug_daji->setVisible(false);

	store_daji = Sprite::create("store.png");
	store_daji->setScale(2);
	store_daji->setPosition(128, visibleSize.height / 2);
	this->addChild(store_daji);
	store_daji->setVisible(false);

	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(set_daji::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void gamescene_daji::update(float delta)
{
	if (Crystal2 == nullptr)//胜利
	{
		auto scene = win::createScene();
		Director::getInstance()->replaceScene(scene);
	}
	if (Crystal1 == nullptr)//失败
	{
		auto scene = lose::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}

//出兵
void gamescene_daji::update_creep1(float t)
{
	flag_creep = true;
	if (Crystal1 != nullptr)
	{
		Melee_creep1[creep_i] = Sprite::create("melee1.png");
		Melee_creep1[creep_i]->setPosition(Crystal1->getPositionX() + 50, visibleSize.height / 2);
		this->addChild(Melee_creep1[creep_i], 2);
		auto *animation1 = Animation::create();
		for (int i = 1; i < 3; i++)
		{
			auto string = String::createWithFormat("melee%d.png", i);
			auto frame = SpriteFrame::create(string->getCString(), CCRectMake(0, 0, 43, 53));
			animation1->addSpriteFrame(frame);

		}
		animation1->setDelayPerUnit(0.3);
		animation1->setLoops(-1);
		auto animate1 = Animate::create(animation1);
		Melee_creep1[creep_i]->runAction(animate1);

		Range_creep1[creep_i] = Sprite::create("range1.png");
		Range_creep1[creep_i]->setPosition(Crystal1->getPositionX() - 50, visibleSize.height / 2);
		this->addChild(Range_creep1[creep_i], 2);
		auto *animation3 = Animation::create();
		for (int i = 1; i < 9; i++)
		{
			auto string = String::createWithFormat("range%d.png", i);
			auto frame = SpriteFrame::create(string->getCString(), CCRectMake(0, 0, 41, 56));
			animation3->addSpriteFrame(frame);

		}
		animation3->setDelayPerUnit(0.3);
		animation3->setLoops(-1);
		auto animate3 = Animate::create(animation3);
		Range_creep1[creep_i]->runAction(animate3);

		Catapult1[creep_i] = Sprite::create("catapult1.png");
		Catapult1[creep_i]->setPosition(Crystal1->getPositionX() - 100, visibleSize.height / 2);
		this->addChild(Catapult1[creep_i], 2);
	}

	if (Crystal2 != nullptr)
	{
		Melee_creep2[creep_i] = Sprite::create("melee3.png");
		Melee_creep2[creep_i]->setPosition(Crystal2->getPositionX() - 50, visibleSize.height / 2);
		this->addChild(Melee_creep2[creep_i], 2);
		auto *animation2 = Animation::create();
		for (int i = 3; i < 5; i++)
		{
			auto string = String::createWithFormat("melee%d.png", i);
			auto frame = SpriteFrame::create(string->getCString(), CCRectMake(0, 0, 57, 57));
			animation2->addSpriteFrame(frame);

		}
		animation2->setDelayPerUnit(0.3);
		animation2->setLoops(-1);
		auto animate2 = Animate::create(animation2);
		Melee_creep2[creep_i]->runAction(animate2);

		Range_creep2[creep_i] = Sprite::create("range9.png");
		Range_creep2[creep_i]->setPosition(Crystal2->getPositionX() + 50, visibleSize.height / 2);
		this->addChild(Range_creep2[creep_i], 2);
		auto *animation4 = Animation::create();
		for (int i = 9; i < 17; i++)
		{
			auto string = String::createWithFormat("range%d.png", i);
			auto frame = SpriteFrame::create(string->getCString(), CCRectMake(0, 0, 41, 56));
			animation4->addSpriteFrame(frame);

		}
		animation4->setDelayPerUnit(0.3);
		animation4->setLoops(-1);
		auto animate4 = Animate::create(animation4);
		Range_creep2[creep_i]->runAction(animate4);


		Catapult2[creep_i] = Sprite::create("catapult2.png");
		Catapult2[creep_i]->setPosition(Crystal2->getPositionX() + 100, visibleSize.height / 2);
		this->addChild(Catapult2[creep_i], 2);
	}

	a_daji.init_creep(creep_i);
	b_daji.init_creep(creep_i);

	creep_i++;

	this->schedule(schedule_selector(gamescene_daji::update_Melee_creep1_attack), 1);
	this->schedule(schedule_selector(gamescene_daji::update_Melee_creep2_attack), 1);
	this->schedule(schedule_selector(gamescene_daji::update_Range_creep1_attack), 1);
	this->schedule(schedule_selector(gamescene_daji::update_Range_creep2_attack), 1);
	this->schedule(schedule_selector(gamescene_daji::update_Catapult1_attack), 1);
	this->schedule(schedule_selector(gamescene_daji::update_Catapult2_attack), 1);

	this->schedule(schedule_selector(gamescene_daji::update_ai), 1);
	this->schedule(SEL_SCHEDULE(&gamescene_daji::xiaobingsitu), 0.1f, kRepeatForever, 0);
}
//鼠标按下
void gamescene_daji::onMouseDown(Event *event)
{
	//移动
	if (sprite != NULL && flag_tab_daji == false)
	{
		auto e = (EventMouse *)event;
		int X = e->getCursorX() - 512;
		int Y = e->getCursorY() - sprite->getPositionY();
		double dis = sqrt(X*X + Y * Y);
		auto by1 = MoveBy::create(dis / a_daji.hero1.MoveSpeed, Vec2(-X, 0));
		by1->setTag(7);
		layer_game_daji->stopActionByTag(7);
		layer_game_daji->resume();
		layer_game_daji->runAction(by1);

		auto by2 = MoveBy::create(dis / a_daji.hero1.MoveSpeed, Vec2(X, Y));
		by2->setTag(6);
		sprite->stopActionByTag(6);
		sprite->resume();
		sprite->runAction(by2);

		/*auto *animation = Animation::create();
		for (int i = 1; i < 5; i++)
		{
			auto string = String::createWithFormat("daji%d.png", i);
			auto frame = SpriteFrame::create(string->getCString(), CCRectMake(0, 0, 104, 104));
			animation->addSpriteFrame(frame);

		}
		animation->setDelayPerUnit(0.2);
		animation->setLoops(-1);
		auto animate = Animate::create(animation);
		animate->setTag(10);
		sprite->stopActionByTag(10);
		sprite->resume();
		sprite->runAction(animate);*/

		auto by3 = MoveBy::create(dis / a_daji.hero1.MoveSpeed, Vec2(X, Y));
		by3->setTag(5);
		bug_daji->stopActionByTag(5);
		bug_daji->resume();
		bug_daji->runAction(by3);

		clickCreep_enemy(e->getCursorX() + bug_daji->getPositionX(), e->getCursorY());
	}
	EventMouse* e = (EventMouse*)event;
	//获取鼠标点击位置
	float cursorX = e->getCursorX() + bug_daji->getPositionX();
	float cursorY = e->getCursorY();
}
//鼠标移动
void gamescene_daji::onMouseMove(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	//获取鼠标点击位置
	float cursorX = e->getCursorX() + bug_daji->getPositionX();
	float cursorY = e->getCursorY();
}

void gamescene_daji::onMouseMove1(Event *event)
{
	auto e = (EventMouse *)event;
	if (hero_attack == true && e != nullptr)
	{
		if (cursor != nullptr)
		{
			cursor->removeFromParent();
		}
		cursor = Sprite::create("cursor.png");
		cursor->setPosition(e->getCursorX() + bug_daji->getPositionX() - 60, e->getCursorY());
		this->addChild(cursor);
	}
}

void set_daji::onMouseDown(Event *event)
{
	auto e = (EventMouse *)event;
	if (flag_tab_daji == true)
	{
		if (equip_number < 5)
		{
			if (e->getCursorX() > 0 && e->getCursorX() < 80 && e->getCursorY() > 550 && e->getCursorY() < 620)
			{
				if (a_daji.hero1.gold > 200)
				{
					a_daji.hero1.gold -= 200;
					equip_number++;
					auto att20 = Sprite::create("20att.png");
					att20->setScale(2);
					att20->setPosition(equipX[equip_number], equipY[equip_number]);
					layer_set_daji->addChild(att20, 10);
					a_daji.hero1.base_damage += 20;
				}
			}
			if (e->getCursorX() > 0 && e->getCursorX() < 80 && e->getCursorY() > 450 && e->getCursorY() < 500)
			{
				if (a_daji.hero1.gold > 1000)
				{
					a_daji.hero1.gold -= 1000;
					equip_number++;
					auto att50 = Sprite::create("50att.png");
					att50->setScale(2);
					att50->setPosition(equipX[equip_number], equipY[equip_number]);
					layer_set_daji->addChild(att50, 10);
					a_daji.hero1.base_damage += 50;
				}
			}
			if (e->getCursorX() > 0 && e->getCursorX() < 80 && e->getCursorY() > 320 && e->getCursorY() < 380)
			{
				if (a_daji.hero1.gold > 2000)
				{
					a_daji.hero1.gold -= 2000;
					equip_number++;
					auto att100 = Sprite::create("100att.png");
					att100->setScale(2);
					att100->setPosition(equipX[equip_number], equipY[equip_number]);
					layer_set_daji->addChild(att100, 10);
					a_daji.hero1.base_damage += 100;
				}
			}
			if (e->getCursorX() > 100 && e->getCursorX() < 150 && e->getCursorY() > 550 && e->getCursorY() < 620)
			{
				if (a_daji.hero1.gold > 200)
				{
					a_daji.hero1.gold -= 200;
					equip_number++;
					auto hp300 = Sprite::create("300hp.png");
					hp300->setScale(2);
					hp300->setPosition(equipX[equip_number], equipY[equip_number]);
					layer_set_daji->addChild(hp300, 10);
					a_daji.hero1.HP_max += 300;
					a_daji.hero1.HP += 300;
				}
			}
			if (e->getCursorX() > 100 && e->getCursorX() < 150 && e->getCursorY() > 450 && e->getCursorY() < 500)
			{
				if (a_daji.hero1.gold > 1000)
				{
					a_daji.hero1.gold -= 1000;
					equip_number++;
					auto hp1000 = Sprite::create("1000hp.png");
					hp1000->setScale(2);
					hp1000->setPosition(equipX[equip_number], equipY[equip_number]);
					layer_set_daji->addChild(hp1000, 10);
					a_daji.hero1.HP_max += 1000;
					a_daji.hero1.HP += 1000;
				}
			}
			if (e->getCursorX() > 100 && e->getCursorX() < 150 && e->getCursorY() > 320 && e->getCursorY() < 380)
			{
				if (a_daji.hero1.gold > 2000)
				{
					a_daji.hero1.gold -= 2000;
					equip_number++;
					auto hp2000 = Sprite::create("2000hp.png");
					hp2000->setScale(2);
					hp2000->setPosition(equipX[equip_number], equipY[equip_number]);
					layer_set_daji->addChild(hp2000, 10);
					a_daji.hero1.HP_max += 2000;
					a_daji.hero1.HP += 2000;
				}
			}
			if (e->getCursorX() > 180 && e->getCursorX() < 250 && e->getCursorY() > 450 && e->getCursorY() < 500)
			{
				if (a_daji.hero1.gold > 3000)
				{
					a_daji.hero1.gold -= 3000;
					equip_number++;
					auto att300 = Sprite::create("300att.png");
					att300->setScale(2);
					att300->setPosition(equipX[equip_number], equipY[equip_number]);
					layer_set_daji->addChild(att300, 10);
					a_daji.hero1.base_damage += 300;

				}
			}
		}

	}

	std::cout << e->getCursorX() << " " << e->getCursorY() << std::endl;
}

void gamescene_daji::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		huoyan = Sprite::create("0.png");
		auto po = sprite->getPosition();
		int dis = sqrt((aipos.x - po.x)*(aipos.x - po.x) + (aipos.y - po.y)*(aipos.y - po.y));
		if (bools)
		{
			if (dis <= 300)
			{
				bools = false;
				CCSprite *mainsprite = CCSprite::create("0.png");
				CCAnimation *animation = CCAnimation::create();
				animation->addSpriteFrameWithFileName("0.png");
				animation->addSpriteFrameWithFileName("1.png");
				animation->addSpriteFrameWithFileName("2.png");
				animation->addSpriteFrameWithFileName("3.png");
				animation->setDelayPerUnit(0.1f);//设置动画的间隔时间  
				animation->setRestoreOriginalFrame(false);//是否返回第一帧  


				huoyan->setPosition(Vec2(po.x + 50, po.y));
				auto pohuoyan = huoyan->getPosition();
				double dx = aipos.x - pohuoyan.x;
				double dy = aipos.y - pohuoyan.y;
				double rad = atan(dy / dx);
				huoyan->setRotation(rad);
				this->addChild(huoyan);
				huoyan->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
				auto moveto = MoveTo::create(dis / 100, aipos);
				huoyan->runAction(moveto);
				this->schedule(SEL_SCHEDULE(&gamescene_daji::fors), 0.1f, 40, 0);
				this->schedule(SEL_SCHEDULE(&gamescene_daji::cds), 5.0f, 1, 0);
				this->schedule(SEL_SCHEDULE(&gamescene_daji::xiaoshis), 1.0f, 1, 0);
			}
			else
			{
				auto la = Label::createWithTTF("out of the range", "fonts/Marker Felt.ttf", 24);
				la->setPosition(Vec2(po.x, po.y + 100));
				this->addChild(la);
				auto fadeOut = FadeOut::create(2.0f);
				la->runAction(fadeOut);
			}
		}
		else
		{
			auto la = Label::createWithTTF("still in CD", "fonts/Marker Felt.ttf", 24);
			la->setPosition(Vec2(po.x, po.y + 100));
			this->addChild(la);
			auto fadeOut = FadeOut::create(2.0f);
			la->runAction(fadeOut);
		}

	}
	if (keyCode == EventKeyboard::KeyCode::KEY_F)
	{
		if (boolf)
		{
			auto po = sprite->getPosition();
			int dis = sqrt((aipos.x - po.x)*(aipos.x - po.x) + (aipos.y - po.y)*(aipos.y - po.y));
			if (dis <= 300)
			{
				boolf = false;

				dazhao = Sprite::create("00.png");
				dazhao->setPosition(Vec2(aipos.x, aipos.y + 50));
				this->addChild(dazhao);

				CCSprite *mainsprite = CCSprite::create("00.png");
				CCAnimation *animation = CCAnimation::create();
				animation->addSpriteFrameWithFileName("00.png");
				animation->addSpriteFrameWithFileName("01.png");
				animation->addSpriteFrameWithFileName("02.png");
				animation->addSpriteFrameWithFileName("03.png");
				animation->addSpriteFrameWithFileName("4.png");
				animation->addSpriteFrameWithFileName("5.png");
				animation->addSpriteFrameWithFileName("6.png");
				animation->addSpriteFrameWithFileName("7.png");
				animation->addSpriteFrameWithFileName("8.png");
				animation->addSpriteFrameWithFileName("9.png");
				animation->addSpriteFrameWithFileName("10.png");
				animation->addSpriteFrameWithFileName("11.png");
				animation->addSpriteFrameWithFileName("12.png");
				animation->addSpriteFrameWithFileName("13.png");
				animation->addSpriteFrameWithFileName("14.png");
				animation->addSpriteFrameWithFileName("15.png");
				animation->addSpriteFrameWithFileName("16.png");
				animation->addSpriteFrameWithFileName("17.png");
				animation->addSpriteFrameWithFileName("18.png");
				animation->addSpriteFrameWithFileName("19.png");
				animation->setDelayPerUnit(0.1f);//设置动画的间隔时间  
				animation->setRestoreOriginalFrame(false);//是否返回第一帧  
				dazhao->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
				auto fadeOut = FadeOut::create(2.5f);
				dazhao->runAction(fadeOut);

				this->schedule(SEL_SCHEDULE(&gamescene_daji::forf), 0.1f, 40, 0);
				this->schedule(SEL_SCHEDULE(&gamescene_daji::cdf), 30.0f, 1, 0);
			}
			else
			{
				auto la = Label::createWithTTF("out of the range", "fonts/Marker Felt.ttf", 24);
				la->setPosition(Vec2(po.x, po.y + 100));
				this->addChild(la);
				auto fadeOut = FadeOut::create(2.0f);
				la->runAction(fadeOut);
			}
		}
		else
		{
			auto la = Label::createWithTTF("still in CD", "fonts/Marker Felt.ttf", 24);
			auto po = sprite->getPosition();
			la->setPosition(Vec2(po.x, po.y + 100));
			this->addChild(la);
			auto fadeOut = FadeOut::create(2.0f);
			la->runAction(fadeOut);
		}
	}
}

void gamescene_daji::onKeyPressed4(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_TAB)
	{
		flag_tab_daji = 1 - flag_tab_daji;
		if (flag_tab_daji == true)
		{
			store_daji->setVisible(true);

		}
		else
			store_daji->setVisible(false);
	}
	
}

void gamescene_daji::getBloodbar(Sprite *guaisprite, float a)
{
	if (guaisprite != nullptr)
	{
		pBloodKongSp = Sprite::create("HPbar_full.png");
		pBloodKongSp->setPosition(Vec2(guaisprite->getContentSize().width / 2, guaisprite->getContentSize().height / 1.1));
		guaisprite->addChild(pBloodKongSp, 2);
		auto pBloodManSp = Sprite::create("HPbar_empty.png");

		auto pBloodProGress = CCProgressTimer::create(pBloodManSp);
		pBloodProGress->setType(kCCProgressTimerTypeBar);
		pBloodProGress->setBarChangeRate(Vec2(1, 0));
		pBloodProGress->setMidpoint(Vec2(1, 0));
		pBloodProGress->setPosition(Vec2(guaisprite->getContentSize().width / 2, guaisprite->getContentSize().height / 1.1));
		pBloodProGress->setPercentage(a);
		guaisprite->addChild(pBloodProGress, 2);
	}
}

void gamescene_daji::getBloodbar1(Sprite *guaisprite, float a)
{

	auto pBloodManSp = Sprite::create("HPbar_full.png");

	auto pBloodProGress = CCProgressTimer::create(pBloodManSp);
	pBloodProGress->setType(kCCProgressTimerTypeBar);
	pBloodProGress->setBarChangeRate(Vec2(1, 0));
	pBloodProGress->setMidpoint(Vec2(0, 0));
	pBloodProGress->setPosition(Vec2(guaisprite->getContentSize().width / 2, guaisprite->getContentSize().height / 1.1));
	pBloodProGress->setPercentage(1 - a);
	guaisprite->addChild(pBloodProGress, 2);
}

//技能

void gamescene_daji::xiaobingsitu(float dt)
{
	int i = 0;
	for (i = 0; i < 600; i++)
	{
		if (Melee_creep2[i])
			posmelee[i] = Melee_creep2[i]->getPosition();
		if (Range_creep2[i])
			posrange[i] = Range_creep2[i]->getPosition();
		if (Catapult2[i])
			poscat[i] = Catapult2[i]->getPosition();
	}
	if (ai)
		aipos = ai->getPosition();
}
//技能
void gamescene_daji::cds(float dt)
{
	bools = true;
}
void gamescene_daji::cdf(float dt)
{
	boolf = true;
}
void gamescene_daji::xiaoshis(float dt)
{
	this->removeChild(huoyan);
	huoyan = NULL;
}

void gamescene_daji::fors(float dt)
{
	int i = 0;
	if (huoyan)
	{
		for (i = 0; i < 600; i++)
		{
			if (Melee_creep2[i])
			{
				if (huoyan->boundingBox().intersectsRect(Melee_creep2[i]->boundingBox()))
				{
					b_daji.melee.HP[i] = b_daji.melee.HP[i] - s;

				}
			}
			if (Range_creep2[i])
			{
				if (huoyan->boundingBox().intersectsRect(Range_creep2[i]->boundingBox()))
				{
					b_daji.range.HP[i] = b_daji.range.HP[i] - s;
				}
			}
			if (Catapult2[i])
			{
				if (huoyan->boundingBox().intersectsRect(Catapult2[i]->boundingBox()))
				{
					b_daji.catapult.HP[i] = b_daji.catapult.HP[i] - s;
				}
			}
		}
		if (ai)
		{
			if (huoyan->boundingBox().intersectsRect(ai->boundingBox()))
			{
				b_daji.hero1.HP -= s;
			}
		}
	}
}
void gamescene_daji::forf(float dt)
{
	b_daji.hero1.HP -= f;
}

//技能4
double gamescene_daji::ability4()
{
	double CriticalDamage = 1;
	if (LV_ability4 != 0)
	{
		//技能4效果
		if (random(1, 100) <= 25)
		{
			switch (LV_ability4)
			{
			case 1:CriticalDamage = 2; break;
			case 2:CriticalDamage = 3; break;
			case 3:CriticalDamage = 4; break;
			case 4:CriticalDamage = 5; break;
			}
		}
	}
	return CriticalDamage;
}
int gamescene_daji::getCurrentlvl(Sprite *sprite)
{
	int lvlup_experience[14] = { 50,100,150,200,250,300,350,400,450,500,550,600,650,700 };
	int lvl = 1;
	if (a_daji.hero1.exp > lvlup_experience[lvl - 1])
	{
		a_daji.hero1.exp -= lvlup_experience[lvl - 1];
		lvl++;
		LV_ability4++;
		a_daji.hero1.base_damage += 10;
		a_daji.hero1.HP += 100;
		a_daji.hero1.HP_max += 100;
	}
	return lvl;
}

void gamescene_daji::update_time(float t)
{
	time += 1;
	a_daji.hero1.gold += 2;
	if (time < 60)
	{
		if (int(time) % 60 < 10)
			str = "00:0" + std::to_string(time);
		else
			str = "00:" + std::to_string(time);
	}
	else if (time < 600)
	{
		if (int(time) % 60 < 10)
			str = "0" + std::to_string(int(time / 60)) + ":0" + std::to_string(int(time) % 60);
		else
			str = "0" + std::to_string(int(time / 60)) + ":" + std::to_string(int(time) % 60);
	}
	else
	{
		if (int(time) % 60 < 10)
			str = std::to_string(int(time / 60)) + ":0" + std::to_string(int(time) % 60);
		else
			str = std::to_string(int(time / 60)) + ":" + std::to_string(int(time) % 60);
	}
	layer_set_daji->removeChild(label_time);
	label_time = Label::createWithSystemFont(str, "Arial", 24);
	label_time->setPosition(512, 600);
	layer_set_daji->addChild(label_time);

	std::string str_gold = std::to_string(a_daji.hero1.gold) + "g";
	layer_set_daji->removeChild(label_gold);
	label_gold = Label::createWithSystemFont(str_gold, "Arial", 24);
	label_gold->setPosition(300, 60);
	layer_set_daji->addChild(label_gold);

	std::string str_lvl = "lv:" + std::to_string(getCurrentlvl(sprite));
	layer_set_daji->removeChild(label_lvl);
	label_lvl = Label::createWithSystemFont(str_lvl, "Arial", 24);
	label_lvl->setPosition(300, 120);
	layer_set_daji->addChild(label_lvl);

	std::string str_damage = "damage:" + std::to_string(a_daji.hero1.base_damage);
	layer_set_daji->removeChild(label_damage);
	label_damage = Label::createWithSystemFont(str_damage, "Arial", 24);
	label_damage->setPosition(500, 120);
	layer_set_daji->addChild(label_damage);

	std::string str_hp = "hp:" + std::to_string(a_daji.hero1.HP) + "/" + std::to_string(a_daji.hero1.HP_max);
	layer_set_daji->removeChild(label_hp);
	label_hp = Label::createWithSystemFont(str_hp, "Arial", 24);
	label_hp->setPosition(500, 60);
	layer_set_daji->addChild(label_hp);
	//显示击杀死亡
	stringstream Kills; Kills << kills;
	stringstream Deaths; Deaths << deaths;
	string str1 = "Kills:";
	string str2 = Kills.str();
	string str3 = " Deaths:";
	string str4 = Deaths.str();
	string KillsDeaths = str1 + str2 + str3 + str4;
	layer_set_daji->removeChild(label_KD);
	label_KD = Label::createWithSystemFont(KillsDeaths, "Arial", 24);
	label_KD->setPosition(900,600);
	layer_set_daji->addChild(label_KD);

	if (flag_heroalive == false)
	{
		time_tolive = 25;
		flag_heroalive = true;
	}
	if (sprite == NULL)
	{
		time_tolive--;
		if (time_tolive <= 0)
		{
			a_daji.hero1.HP = a_daji.hero1.HP_max;
			sprite = Sprite::create("daji.png");
			sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
			auto by = MoveBy::create(0.1, Vec2(deltaX, 0));
			layer_game_daji->runAction(by);
			this->addChild(sprite, 4);
		}
	}
}

bool gamescene_daji::InTheArea(float X, float Y, Sprite  * A)
{
	if (A != nullptr)
	{
		float positionX = A->getPositionX();
		float positionY = A->getPositionY();
		float contentSizeX = 2 * A->getContentSize().width;
		float contentSizeY = 2 * A->getContentSize().height;
		float area_Xmin = positionX - 0.5*contentSizeX;
		float area_Xmax = positionX + 0.5*contentSizeX;
		float area_Ymin = positionY - 0.5*contentSizeY;
		float area_Ymax = positionY + 0.5*contentSizeY;
		if (X >= area_Xmin && X <= area_Xmax && Y >= area_Ymin && Y <= area_Ymax)
		{
			return true;
		}
		else return false;
	}
}

void gamescene_daji::clickCreep_enemy(float X, float Y)
{
	hero_attack_target = false;
	for (int i = 0; i < creep_i; i++)
	{
		if (b_daji.melee.HP[i] > 0 && hero_attack_target == false)
		{
			if (InTheArea(X, Y, Melee_creep2[i]) == true)
			{
				hero_attack_target = true;
				flag_sprite = Melee_creep2[i];
				hero_Attack();
				log("true");
			}
		}
		if (b_daji.range.HP[i] > 0 && hero_attack_target == false)
		{
			if (InTheArea(X, Y, Range_creep2[i]) == true)
			{
				hero_attack_target = true;
				flag_sprite = Range_creep2[i];
				hero_Attack();
				log("true");
			}
		}
		if (b_daji.catapult.HP[i] > 0 && hero_attack_target == false)
		{
			if (InTheArea(X, Y, Catapult2[i]) == true)
			{
				hero_attack_target = true;
				flag_sprite = Catapult2[i];
				hero_Attack();
				log("true");
			}
		}
	}
	if (b_daji.hero1.HP > 0 && hero_attack_target == false)
	{
		if (InTheArea(X, Y, ai) == true)
		{
			hero_attack_target = true;
			flag_sprite = ai;
			hero_Attack();
			log("true");
		}
	}
	if (b_daji.tower.HP > 0 && hero_attack_target == false)
	{
		if (InTheArea(X, Y, Tower2) == true)
		{
			hero_attack_target = true;
			flag_sprite = Tower2;
			hero_Attack();
			log("true");
		}
	}
	if (b_daji.crystal.HP > 0 && hero_attack_target == false)
	{
		if (InTheArea(X, Y, Crystal2) == true)
		{
			hero_attack_target = true;
			flag_sprite = Crystal2;
			hero_Attack();
			log("true");
		}
	}
	std::cout << flag_sprite << std::endl;
}

void gamescene_daji::update_Melee_creep1_attack(float t)
{
	for (int j = 0; j < creep_i; j++)
	{
		int X[9], Y[9], dis[9];
		for (int i = 0; i < 9; i++)
		{
			X[i] = 100000;
			Y[i] = 100000;
			dis[i] = 1000000000;
		}
		if (a_daji.melee.HP[j] > 0)
		{
			if (b_daji.melee.HP[j] > 0)
			{
				X[0] = -Melee_creep1[j]->getPositionX() + Melee_creep2[j]->getPositionX();
				Y[0] = -Melee_creep1[j]->getPositionY() + Melee_creep2[j]->getPositionY();
				dis[0] = X[0] * X[0] + Y[0] * Y[0];
			}
			if (b_daji.crystal.HP > 0)
			{
				X[1] = -Melee_creep1[j]->getPositionX() + Crystal2->getPositionX();
				Y[1] = -Melee_creep1[j]->getPositionY() + Crystal2->getPositionY();
				dis[1] = X[1] * X[1] + Y[1] * Y[1];

			}
			if (b_daji.tower.HP > 0)
			{
				X[2] = -Melee_creep1[j]->getPositionX() + Tower2->getPositionX();
				Y[2] = -Melee_creep1[j]->getPositionY() + Tower2->getPositionY();
				dis[2] = X[2] * X[2] + Y[2] * Y[2];
			}
			if (b_daji.range.HP[j] > 0)
			{
				X[3] = -Melee_creep1[j]->getPositionX() + Range_creep2[j]->getPositionX();
				Y[3] = -Melee_creep1[j]->getPositionY() + Range_creep2[j]->getPositionY();
				dis[3] = X[3] * X[3] + Y[3] * Y[3];
			}
			if (b_daji.catapult.HP[j] > 0)
			{
				X[4] = -Melee_creep1[j]->getPositionX() + Catapult2[j]->getPositionX();
				Y[4] = -Melee_creep1[j]->getPositionY() + Catapult2[j]->getPositionY();
				dis[4] = X[4] * X[4] + Y[4] * Y[4];
			}
			if (j != 0)
			{
				if (b_daji.melee.HP[j - 1] > 0)
				{
					X[5] = -Melee_creep1[j]->getPositionX() + Melee_creep2[j - 1]->getPositionX();
					Y[5] = -Melee_creep1[j]->getPositionY() + Melee_creep2[j - 1]->getPositionY();
					dis[5] = X[5] * X[5] + Y[5] * Y[5];
				}
				if (b_daji.range.HP[j - 1] > 0)
				{
					X[6] = -Melee_creep1[j]->getPositionX() + Range_creep2[j - 1]->getPositionX();
					Y[6] = -Melee_creep1[j]->getPositionY() + Range_creep2[j - 1]->getPositionY();
					dis[6] = X[6] * X[6] + Y[6] * Y[6];
				}
				if (b_daji.catapult.HP[j - 1] > 0)
				{
					X[7] = -Melee_creep1[j]->getPositionX() + Catapult2[j - 1]->getPositionX();
					Y[7] = -Melee_creep1[j]->getPositionY() + Catapult2[j - 1]->getPositionY();
					dis[7] = X[7] * X[7] + Y[7] * Y[7];
				}
			}
			if (b_daji.hero1.HP > 0)
			{
				X[8] = -Melee_creep1[j]->getPositionX() + ai->getPositionX();
				Y[8] = -Melee_creep1[j]->getPositionY() + ai->getPositionY();
				dis[8] = X[8] * X[8] + Y[8] * Y[8];
			}

			int min_dis = 1000000000;
			for (int i = 0; i < 9; i++)
			{
				if (dis[i] < min_dis)
					min_dis = dis[i];
			}
			double time = sqrt(min_dis) / 100;


			if (min_dis <= 2500)
			{
				if (min_dis == dis[0])
					b_daji.melee.HP[j] -= 20;
				else if (min_dis == dis[1])
					b_daji.crystal.HP -= 20;
				else if (min_dis == dis[2])
					b_daji.tower.HP -= 20;
				else if (min_dis == dis[3])
					b_daji.range.HP[j] -= 20;
				else if (min_dis == dis[4])
					b_daji.catapult.HP[j] -= 20;
				else if (min_dis == dis[5])
					b_daji.melee.HP[j - 1] -= 20;
				else if (min_dis == dis[6])
					b_daji.range.HP[j - 1] -= 20;
				else if (min_dis == dis[7])
					b_daji.catapult.HP[j - 1] -= 20;
				else if (min_dis == dis[8])
					b_daji.hero1.HP -= 20;

			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					if (min_dis == dis[i])
					{
						auto by = MoveBy::create(1, Vec2((abs(X[i]) - 50) / time, 0));
						Melee_creep1[j]->runAction(by);
						break;
					}
				}
			}
		}

		if (a_daji.melee.HP[j] > 0)
			this->getBloodbar(Melee_creep1[j], (200 - a_daji.melee.HP[j]) / 2);


		if (b_daji.melee.HP[j] <= 0 && Melee_creep2[j] != NULL)
		{
			this->removeChild(Melee_creep2[j]);
			Melee_creep2[j] = NULL;
			a_daji.hero1.gold += 20;
			a_daji.hero1.exp += 10;
		}
		if (b_daji.range.HP[j] <= 0 && Range_creep2[j] != NULL)
		{
			this->removeChild(Range_creep2[j]);
			Range_creep2[j] = NULL;
			a_daji.hero1.gold += 50;
			a_daji.hero1.exp += 15;
		}
		if (b_daji.catapult.HP[j] <= 0 && Catapult2[j] != NULL)
		{
			this->removeChild(Catapult2[j]);
			Catapult2[j] = NULL;
			a_daji.hero1.gold += 50;
			a_daji.hero1.exp += 20;
		}
	}
}

void gamescene_daji::update_Melee_creep2_attack(float t)
{
	for (int j = 0; j < creep_i; j++)
	{
		int X[9], Y[9], dis[9];
		for (int i = 0; i < 9; i++)
		{
			X[i] = 100000;
			Y[i] = 100000;
			dis[i] = 1000000000;
		}
		if (b_daji.melee.HP[j] > 0)
		{
			if (a_daji.melee.HP[j] > 0)
			{
				X[0] = -Melee_creep1[j]->getPositionX() + Melee_creep2[j]->getPositionX();
				Y[0] = -Melee_creep1[j]->getPositionY() + Melee_creep2[j]->getPositionY();
				dis[0] = X[0] * X[0] + Y[0] * Y[0];
			}
			if (a_daji.crystal.HP > 0)
			{
				X[1] = -Melee_creep2[j]->getPositionX() + Crystal1->getPositionX();
				Y[1] = -Melee_creep2[j]->getPositionY() + Crystal1->getPositionY();
				dis[1] = X[1] * X[1] + Y[1] * Y[1];
			}
			if (a_daji.tower.HP > 0)
			{
				X[2] = -Melee_creep2[j]->getPositionX() + Tower1->getPositionX();
				Y[2] = -Melee_creep2[j]->getPositionY() + Tower1->getPositionY();
				dis[2] = X[2] * X[2] + Y[2] * Y[2];
			}
			if (a_daji.range.HP[j] > 0)
			{
				X[3] = -Melee_creep2[j]->getPositionX() + Range_creep1[j]->getPositionX();
				Y[3] = -Melee_creep2[j]->getPositionY() + Range_creep1[j]->getPositionY();
				dis[3] = X[3] * X[3] + Y[3] * Y[3];
			}
			if (a_daji.catapult.HP[j] > 0)
			{
				X[4] = -Melee_creep2[j]->getPositionX() + Catapult1[j]->getPositionX();
				Y[4] = -Melee_creep2[j]->getPositionY() + Catapult1[j]->getPositionY();
				dis[4] = X[4] * X[4] + Y[4] * Y[4];
			}
			if (j != 0)
			{
				if (a_daji.melee.HP[j - 1] > 0)
				{
					X[5] = -Melee_creep2[j]->getPositionX() + Melee_creep1[j - 1]->getPositionX();
					Y[5] = -Melee_creep2[j]->getPositionY() + Melee_creep1[j - 1]->getPositionY();
					dis[5] = X[5] * X[5] + Y[5] * Y[5];
				}
				if (a_daji.range.HP[j - 1] > 0)
				{
					X[6] = -Melee_creep2[j]->getPositionX() + Range_creep1[j - 1]->getPositionX();
					Y[6] = -Melee_creep2[j]->getPositionY() + Range_creep1[j - 1]->getPositionY();
					dis[6] = X[6] * X[6] + Y[6] * Y[6];
				}
				if (a_daji.catapult.HP[j - 1] > 0)
				{
					X[7] = -Melee_creep2[j]->getPositionX() + Catapult1[j - 1]->getPositionX();
					Y[7] = -Melee_creep2[j]->getPositionY() + Catapult1[j - 1]->getPositionY();
					dis[7] = X[7] * X[7] + Y[7] * Y[7];
				}
			}
			if (a_daji.hero1.HP > 0)
			{
				X[8] = -Melee_creep2[j]->getPositionX() + sprite->getPositionX();
				Y[8] = -Melee_creep2[j]->getPositionY() + sprite->getPositionY();
				dis[8] = X[8] * X[8] + Y[8] * Y[8];
			}
			int min_dis = 1000000000;
			for (int i = 0; i < 9; i++)
			{
				if (dis[i] < min_dis)
					min_dis = dis[i];
			}
			double time = sqrt(min_dis) / 100;


			if (min_dis <= 2500)
			{
				if (min_dis == dis[0])
					a_daji.melee.HP[j] -= 20;
				else if (min_dis == dis[1])
					a_daji.crystal.HP -= 20;
				else if (min_dis == dis[2])
					a_daji.tower.HP -= 20;
				else if (min_dis == dis[3])
					a_daji.range.HP[j] -= 20;
				else if (min_dis == dis[4])
					a_daji.catapult.HP[j] -= 20;
				else if (min_dis == dis[5])
					a_daji.melee.HP[j - 1] -= 20;
				else if (min_dis == dis[6])
					a_daji.range.HP[j - 1] -= 20;
				else if (min_dis == dis[7])
					a_daji.catapult.HP[j - 1] -= 20;
				else if (min_dis == dis[8])
					a_daji.hero1.HP -= 20;

			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					if (min_dis == dis[i])
					{
						auto by = MoveBy::create(1, Vec2(-(abs(X[i]) - 50) / time, 0));
						Melee_creep2[j]->runAction(by);
						break;
					}
				}
			}
		}
		if (b_daji.melee.HP[j] > 0)
			this->getBloodbar(Melee_creep2[j], (200 - a_daji.melee.HP[j]) / 2);

		if (a_daji.melee.HP[j] <= 0 && Melee_creep1[j] != NULL)
		{
			this->removeChild(Melee_creep1[j]);
			Melee_creep1[j] = NULL;
		}
		if (a_daji.range.HP[j] <= 0 && Range_creep1[j] != NULL)
		{
			this->removeChild(Range_creep1[j]);
			Range_creep1[j] = NULL;
		}
		if (a_daji.catapult.HP[j] <= 0 && Catapult1[j] != NULL)
		{
			this->removeChild(Catapult1[j]);
			Catapult1[j] = NULL;
		}
	}
}

void gamescene_daji::update_Range_creep1_attack(float t)
{
	for (int j = 0; j < creep_i; j++)
	{
		int X[9], Y[9], dis[9];
		for (int i = 0; i < 9; i++)
		{
			X[i] = 100000;
			Y[i] = 100000;
			dis[i] = 1000000000;
		}
		if (a_daji.range.HP[j] > 0)
		{
			if (b_daji.melee.HP[j] > 0)
			{
				X[0] = -Range_creep1[j]->getPositionX() + Melee_creep2[j]->getPositionX();
				Y[0] = -Range_creep1[j]->getPositionY() + Melee_creep2[j]->getPositionY();
				dis[0] = X[0] * X[0] + Y[0] * Y[0];
			}
			if (b_daji.crystal.HP > 0)
			{
				X[1] = -Range_creep1[j]->getPositionX() + Crystal2->getPositionX();
				Y[1] = -Range_creep1[j]->getPositionY() + Crystal2->getPositionY();
				dis[1] = X[1] * X[1] + Y[1] * Y[1];
			}
			if (b_daji.tower.HP > 0)
			{
				X[2] = -Range_creep1[j]->getPositionX() + Tower2->getPositionX();
				Y[2] = -Range_creep1[j]->getPositionY() + Tower2->getPositionY();
				dis[2] = X[2] * X[2] + Y[2] * Y[2];
			}
			if (b_daji.range.HP[j] > 0)
			{
				X[3] = -Range_creep1[j]->getPositionX() + Range_creep2[j]->getPositionX();
				Y[3] = -Range_creep1[j]->getPositionY() + Range_creep2[j]->getPositionY();
				dis[3] = X[3] * X[3] + Y[3] * Y[3];
			}
			if (b_daji.catapult.HP[j] > 0)
			{
				X[4] = -Range_creep1[j]->getPositionX() + Catapult2[j]->getPositionX();
				Y[4] = -Range_creep1[j]->getPositionY() + Catapult2[j]->getPositionY();
				dis[4] = X[4] * X[4] + Y[4] * Y[4];
			}
			if (j != 0)
			{
				if (b_daji.melee.HP[j - 1] > 0)
				{
					X[5] = -Range_creep1[j]->getPositionX() + Melee_creep2[j - 1]->getPositionX();
					Y[5] = -Range_creep1[j]->getPositionY() + Melee_creep2[j - 1]->getPositionY();
					dis[5] = X[5] * X[5] + Y[5] * Y[5];
				}
				if (b_daji.range.HP[j - 1] > 0)
				{
					X[6] = -Range_creep1[j]->getPositionX() + Range_creep2[j - 1]->getPositionX();
					Y[6] = -Range_creep1[j]->getPositionY() + Range_creep2[j - 1]->getPositionY();
					dis[6] = X[6] * X[6] + Y[6] * Y[6];
				}
				if (b_daji.catapult.HP[j - 1] > 0)
				{
					X[7] = -Range_creep1[j]->getPositionX() + Catapult2[j - 1]->getPositionX();
					Y[7] = -Range_creep1[j]->getPositionY() + Catapult2[j - 1]->getPositionY();
					dis[7] = X[7] * X[7] + Y[7] * Y[7];
				}
			}
			if (b_daji.hero1.HP > 0)
			{
				X[8] = -Range_creep1[j]->getPositionX() + ai->getPositionX();
				Y[8] = -Range_creep1[j]->getPositionY() + ai->getPositionY();
				dis[8] = X[8] * X[8] + Y[8] * Y[8];
			}

			int min_dis = 1000000000;
			for (int i = 0; i < 9; i++)
			{
				if (dis[i] < min_dis)
					min_dis = dis[i];
			}
			double time = sqrt(min_dis) / 100;


			if (min_dis <= 90000)
			{
				if (min_dis == dis[0])
					b_daji.melee.HP[j] -= 30;
				else if (min_dis == dis[1])
					b_daji.crystal.HP -= 30;
				else if (min_dis == dis[2])
					b_daji.tower.HP -= 30;
				else if (min_dis == dis[3])
					b_daji.range.HP[j] -= 30;
				else if (min_dis == dis[4])
					b_daji.catapult.HP[j] -= 30;
				else if (min_dis == dis[5])
					b_daji.melee.HP[j - 1] -= 30;
				else if (min_dis == dis[6])
					b_daji.range.HP[j - 1] -= 30;
				else if (min_dis == dis[7])
					b_daji.catapult.HP[j - 1] -= 30;
				else if (min_dis == dis[8])
					b_daji.hero1.HP -= 30;
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					if (min_dis == dis[i])
					{
						auto by = MoveBy::create(1, Vec2((abs(X[i]) - 50) / time, 0));
						Range_creep1[j]->runAction(by);
						break;
					}
				}
			}
		}

		if (a_daji.range.HP[j] > 0)
			this->getBloodbar(Range_creep1[j], 100 - a_daji.range.HP[j]);

		if (b_daji.melee.HP[j] <= 0 && Melee_creep2[j] != NULL)
		{
			this->removeChild(Melee_creep2[j]);
			Melee_creep2[j] = NULL;
			a_daji.hero1.gold += 20;
			a_daji.hero1.exp += 10;
		}
		if (b_daji.range.HP[j] <= 0 && Range_creep2[j] != NULL)
		{
			this->removeChild(Range_creep2[j]);
			Range_creep2[j] = NULL;
			a_daji.hero1.gold += 50;
			a_daji.hero1.exp += 15;
		}
		if (b_daji.catapult.HP[j] <= 0 && Catapult2[j] != NULL)
		{
			this->removeChild(Catapult2[j]);
			Catapult2[j] = NULL;
			a_daji.hero1.gold += 50;
			a_daji.hero1.exp += 15;
		}
	}
}

void gamescene_daji::update_Range_creep2_attack(float t)
{
	for (int j = 0; j < creep_i; j++)
	{
		int X[9], Y[9], dis[9];
		for (int i = 0; i < 9; i++)
		{
			X[i] = 100000;
			Y[i] = 100000;
			dis[i] = 1000000000;
		}
		if (b_daji.range.HP[j] > 0)
		{
			if (a_daji.melee.HP[j] > 0)
			{
				X[0] = -Melee_creep1[j]->getPositionX() + Range_creep2[j]->getPositionX();
				Y[0] = -Melee_creep1[j]->getPositionY() + Range_creep2[j]->getPositionY();
				dis[0] = X[0] * X[0] + Y[0] * Y[0];
			}
			if (a_daji.crystal.HP > 0)
			{
				X[1] = -Range_creep2[j]->getPositionX() + Crystal1->getPositionX();
				Y[1] = -Range_creep2[j]->getPositionY() + Crystal1->getPositionY();
				dis[1] = X[1] * X[1] + Y[1] * Y[1];
			}
			if (a_daji.tower.HP > 0)
			{
				X[2] = -Range_creep2[j]->getPositionX() + Tower1->getPositionX();
				Y[2] = -Range_creep2[j]->getPositionY() + Tower1->getPositionY();
				dis[2] = X[2] * X[2] + Y[2] * Y[2];
			}
			if (a_daji.range.HP[j] > 0)
			{
				X[3] = -Range_creep2[j]->getPositionX() + Range_creep1[j]->getPositionX();
				Y[3] = -Range_creep2[j]->getPositionY() + Range_creep1[j]->getPositionY();
				dis[3] = X[3] * X[3] + Y[3] * Y[3];
			}
			if (a_daji.catapult.HP[j] > 0)
			{
				X[4] = -Range_creep2[j]->getPositionX() + Catapult1[j]->getPositionX();
				Y[4] = -Range_creep2[j]->getPositionY() + Catapult1[j]->getPositionY();
				dis[4] = X[4] * X[4] + Y[4] * Y[4];
			}
			if (j != 0)
			{
				if (a_daji.melee.HP[j - 1] > 0)
				{
					X[5] = -Range_creep2[j]->getPositionX() + Melee_creep1[j - 1]->getPositionX();
					Y[5] = -Range_creep2[j]->getPositionY() + Melee_creep1[j - 1]->getPositionY();
					dis[5] = X[5] * X[5] + Y[5] * Y[5];
				}
				if (a_daji.range.HP[j - 1] > 0)
				{
					X[6] = -Range_creep2[j]->getPositionX() + Range_creep1[j - 1]->getPositionX();
					Y[6] = -Range_creep2[j]->getPositionY() + Range_creep1[j - 1]->getPositionY();
					dis[6] = X[6] * X[6] + Y[6] * Y[6];
				}
				if (a_daji.catapult.HP[j - 1] > 0)
				{
					X[7] = -Range_creep2[j]->getPositionX() + Catapult1[j - 1]->getPositionX();
					Y[7] = -Range_creep2[j]->getPositionY() + Catapult1[j - 1]->getPositionY();
					dis[7] = X[7] * X[7] + Y[7] * Y[7];
				}
			}
			if (a_daji.hero1.HP > 0)
			{
				X[8] = -Range_creep2[j]->getPositionX() + sprite->getPositionX();
				Y[8] = -Range_creep2[j]->getPositionY() + sprite->getPositionY();
				dis[8] = X[8] * X[8] + Y[8] * Y[8];
			}

			int min_dis = 1000000000;
			for (int i = 0; i < 5; i++)
			{
				if (dis[i] < min_dis)
					min_dis = dis[i];
			}
			double time = sqrt(min_dis) / 100;


			if (min_dis <= 90000)
			{
				if (min_dis == dis[0])
					a_daji.melee.HP[j] -= 30;
				else if (min_dis == dis[1])
					a_daji.crystal.HP -= 30;
				else if (min_dis == dis[2])
					a_daji.tower.HP -= 30;
				else if (min_dis == dis[3])
					a_daji.range.HP[j] -= 30;
				else if (min_dis == dis[4])
					a_daji.catapult.HP[j] -= 30;
				else if (min_dis == dis[5])
					a_daji.melee.HP[j - 1] -= 30;
				else if (min_dis == dis[6])
					a_daji.range.HP[j - 1] -= 30;
				else if (min_dis == dis[7])
					a_daji.catapult.HP[j - 1] -= 30;
				else if (min_dis == dis[8])
					a_daji.hero1.HP -= 30;
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					if (min_dis == dis[i])
					{
						auto by = MoveBy::create(1, Vec2(-(abs(X[i]) - 50) / time, 0));
						Range_creep2[j]->runAction(by);
						break;
					}
				}

			}
		}

		if (b_daji.range.HP[j] > 0)
			this->getBloodbar(Range_creep2[j], 100 - b_daji.range.HP[j]);

		if (a_daji.melee.HP[j] <= 0 && Melee_creep1[j] != NULL)
		{
			this->removeChild(Melee_creep1[j]);
			Melee_creep1[j] = NULL;
		}

		if (a_daji.range.HP[j] <= 0 && Range_creep1[j] != NULL)
		{
			this->removeChild(Range_creep1[j]);
			Range_creep1[j] = NULL;
		}
		if (a_daji.catapult.HP[j] <= 0 && Catapult1[j] != NULL)
		{
			this->removeChild(Catapult1[j]);
			Catapult1[j] = NULL;
		}
	}
}

void gamescene_daji::update_Catapult1_attack(float t)
{
	for (int j = 0; j < creep_i; j++)
	{
		int X[9], Y[9], dis[9];
		for (int i = 0; i < 9; i++)
		{
			X[i] = 100000;
			Y[i] = 100000;
			dis[i] = 1000000000;
		}
		if (a_daji.catapult.HP[j] > 0)
		{
			if (b_daji.melee.HP[j] > 0)
			{
				X[0] = -Catapult1[j]->getPositionX() + Melee_creep2[j]->getPositionX();
				Y[0] = -Catapult1[j]->getPositionY() + Melee_creep2[j]->getPositionY();
				dis[0] = X[0] * X[0] + Y[0] * Y[0];
			}
			if (b_daji.crystal.HP > 0)
			{
				X[1] = -Catapult1[j]->getPositionX() + Crystal2->getPositionX();
				Y[1] = -Catapult1[j]->getPositionY() + Crystal2->getPositionY();
				dis[1] = X[1] * X[1] + Y[1] * Y[1];
			}
			if (b_daji.tower.HP > 0)
			{
				X[2] = -Catapult1[j]->getPositionX() + Tower2->getPositionX();
				Y[2] = -Catapult1[j]->getPositionY() + Tower2->getPositionY();
				dis[2] = X[2] * X[2] + Y[2] * Y[2];
			}
			if (b_daji.range.HP[j] > 0)
			{
				X[3] = -Catapult1[j]->getPositionX() + Range_creep2[j]->getPositionX();
				Y[3] = -Catapult1[j]->getPositionY() + Range_creep2[j]->getPositionY();
				dis[3] = X[3] * X[3] + Y[3] * Y[3];
			}
			if (b_daji.catapult.HP[j] > 0)
			{
				X[4] = -Catapult1[j]->getPositionX() + Catapult2[j]->getPositionX();
				Y[4] = -Catapult1[j]->getPositionY() + Catapult2[j]->getPositionY();
				dis[4] = X[4] * X[4] + Y[4] * Y[4];
			}
			if (j != 0)
			{
				if (b_daji.melee.HP[j - 1] > 0)
				{
					X[5] = -Catapult1[j]->getPositionX() + Melee_creep2[j - 1]->getPositionX();
					Y[5] = -Catapult1[j]->getPositionY() + Melee_creep2[j - 1]->getPositionY();
					dis[5] = X[5] * X[5] + Y[5] * Y[5];
				}
				if (b_daji.range.HP[j - 1] > 0)
				{
					X[6] = -Catapult1[j]->getPositionX() + Range_creep2[j - 1]->getPositionX();
					Y[6] = -Catapult1[j]->getPositionY() + Range_creep2[j - 1]->getPositionY();
					dis[6] = X[6] * X[6] + Y[6] * Y[6];
				}
				if (b_daji.catapult.HP[j - 1] > 0)
				{
					X[7] = -Catapult1[j]->getPositionX() + Catapult2[j - 1]->getPositionX();
					Y[7] = -Catapult1[j]->getPositionY() + Catapult2[j - 1]->getPositionY();
					dis[7] = X[7] * X[7] + Y[7] * Y[7];
				}
			}
			if (b_daji.hero1.HP > 0)
			{
				X[8] = -Catapult1[j]->getPositionX() + ai->getPositionX();
				Y[8] = -Catapult1[j]->getPositionY() + ai->getPositionY();
				dis[8] = X[8] * X[8] + Y[8] * Y[8];
			}
			int min_dis = 1000000000;
			for (int i = 0; i < 9; i++)
			{
				if (dis[i] < min_dis)
					min_dis = dis[i];
			}
			double time = sqrt(min_dis) / 100;


			if (min_dis <= 160000)
			{
				if (min_dis == dis[0])
					b_daji.melee.HP[j] -= 20;
				else if (min_dis == dis[1])
					b_daji.crystal.HP -= 50;
				else if (min_dis == dis[2])
					b_daji.tower.HP -= 50;
				else if (min_dis == dis[3])
					b_daji.range.HP[j] -= 20;
				else if (min_dis == dis[4])
					b_daji.catapult.HP[j] -= 20;
				else if (min_dis == dis[5])
					b_daji.melee.HP[j - 1] -= 20;
				else if (min_dis == dis[6])
					b_daji.range.HP[j - 1] -= 20;
				else if (min_dis == dis[7])
					b_daji.catapult.HP[j - 1] -= 20;
				else if (min_dis == dis[8])
					b_daji.hero1.HP -= 20;
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					if (min_dis == dis[i])
					{
						auto by = MoveBy::create(1, Vec2((abs(X[i]) - 50) / time, 0));
						Catapult1[j]->runAction(by);
						break;
					}
				}
			}
		}

		if (a_daji.catapult.HP[j] > 0)
			this->getBloodbar(Catapult1[j], (150 - a_daji.catapult.HP[j]) / 1.5);

		if (b_daji.melee.HP[j] <= 0 && Melee_creep2[j] != NULL)
		{
			this->removeChild(Melee_creep2[j]);
			Melee_creep2[j] = NULL;
			a_daji.hero1.gold += 20;
			a_daji.hero1.exp += 10;
		}
		if (b_daji.range.HP[j] <= 0 && Range_creep2[j] != NULL)
		{
			this->removeChild(Range_creep2[j]);
			Range_creep2[j] = NULL;
			a_daji.hero1.gold += 50;
			a_daji.hero1.exp += 15;
		}
		if (b_daji.catapult.HP[j] <= 0 && Catapult2[j] != NULL)
		{
			this->removeChild(Catapult2[j]);
			Catapult2[j] = NULL;
			a_daji.hero1.gold += 50;
			a_daji.hero1.exp += 15;
		}
	}
}

void gamescene_daji::update_Catapult2_attack(float t)
{
	for (int j = 0; j < creep_i; j++)
	{
		int X[9], Y[9], dis[9];
		for (int i = 0; i < 9; i++)
		{
			X[i] = 100000;
			Y[i] = 100000;
			dis[i] = 1000000000;
		}
		if (b_daji.catapult.HP[j] > 0)
		{
			if (a_daji.melee.HP[j] > 0)
			{
				X[0] = -Melee_creep1[j]->getPositionX() + Catapult2[j]->getPositionX();
				Y[0] = -Melee_creep1[j]->getPositionY() + Catapult2[j]->getPositionY();
				dis[0] = X[0] * X[0] + Y[0] * Y[0];
			}
			if (a_daji.crystal.HP > 0)
			{
				X[1] = -Catapult2[j]->getPositionX() + Crystal1->getPositionX();
				Y[1] = -Catapult2[j]->getPositionY() + Crystal1->getPositionY();
				dis[1] = X[1] * X[1] + Y[1] * Y[1];
			}
			if (a_daji.tower.HP > 0)
			{
				X[2] = -Catapult2[j]->getPositionX() + Tower1->getPositionX();
				Y[2] = -Catapult2[j]->getPositionY() + Tower1->getPositionY();
				dis[2] = X[2] * X[2] + Y[2] * Y[2];
			}
			if (a_daji.range.HP[j] > 0)
			{
				X[3] = -Catapult2[j]->getPositionX() + Range_creep1[j]->getPositionX();
				Y[3] = -Catapult2[j]->getPositionY() + Range_creep1[j]->getPositionY();
				dis[3] = X[3] * X[3] + Y[3] * Y[3];
			}
			if (a_daji.catapult.HP[j] > 0)
			{
				X[4] = -Catapult2[j]->getPositionX() + Catapult1[j]->getPositionX();
				Y[4] = -Catapult2[j]->getPositionY() + Catapult1[j]->getPositionY();
				dis[4] = X[4] * X[4] + Y[4] * Y[4];
			}
			if (j != 0)
			{
				if (a_daji.melee.HP[j - 1] > 0)
				{
					X[5] = -Catapult2[j]->getPositionX() + Melee_creep1[j - 1]->getPositionX();
					Y[5] = -Catapult2[j]->getPositionY() + Melee_creep1[j - 1]->getPositionY();
					dis[5] = X[5] * X[5] + Y[5] * Y[5];
				}
				if (a_daji.range.HP[j - 1] > 0)
				{
					X[6] = -Catapult2[j]->getPositionX() + Range_creep1[j - 1]->getPositionX();
					Y[6] = -Catapult2[j]->getPositionY() + Range_creep1[j - 1]->getPositionY();
					dis[6] = X[6] * X[6] + Y[6] * Y[6];
				}
				if (a_daji.catapult.HP[j - 1] > 0)
				{
					X[7] = -Catapult2[j]->getPositionX() + Catapult1[j - 1]->getPositionX();
					Y[7] = -Catapult2[j]->getPositionY() + Catapult1[j - 1]->getPositionY();
					dis[7] = X[7] * X[7] + Y[7] * Y[7];
				}
			}
			if (a_daji.hero1.HP > 0)
			{
				X[8] = -Catapult2[j]->getPositionX() + sprite->getPositionX();
				Y[8] = -Catapult2[j]->getPositionY() + sprite->getPositionY();
				dis[8] = X[8] * X[8] + Y[8] * Y[8];
			}

			int min_dis = 1000000000;
			for (int i = 0; i < 5; i++)
			{
				if (dis[i] < min_dis)
					min_dis = dis[i];
			}
			double time = sqrt(min_dis) / 100;


			if (min_dis <= 160000)
			{
				if (min_dis == dis[0])
					a_daji.melee.HP[j] -= 20;
				else if (min_dis == dis[1])
					a_daji.crystal.HP -= 50;
				else if (min_dis == dis[2])
					a_daji.tower.HP -= 50;
				else if (min_dis == dis[3])
					a_daji.range.HP[j] -= 20;
				else if (min_dis == dis[4])
					a_daji.catapult.HP[j] -= 20;
				else if (min_dis == dis[5])
					a_daji.melee.HP[j - 1] -= 20;
				else if (min_dis == dis[6])
					a_daji.range.HP[j - 1] -= 20;
				else if (min_dis == dis[7])
					a_daji.catapult.HP[j - 1] -= 20;
				else if (min_dis == dis[8])
					a_daji.hero1.HP -= 20;
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					if (min_dis == dis[i])
					{
						auto by = MoveBy::create(1, Vec2(-(abs(X[i]) - 50) / time, 0));
						Catapult2[j]->runAction(by);
						break;
					}
				}

			}
		}

		if (b_daji.catapult.HP[j] > 0)
			this->getBloodbar(Catapult2[j], (150 - b_daji.catapult.HP[j]) / 1.5);

		if (a_daji.melee.HP[j] <= 0 && Melee_creep1[j] != NULL)
		{
			this->removeChild(Melee_creep1[j]);
			Melee_creep1[j] = NULL;
		}

		if (a_daji.range.HP[j] <= 0 && Range_creep1[j] != NULL)
		{
			this->removeChild(Range_creep1[j]);
			Range_creep1[j] = NULL;
		}
		if (a_daji.catapult.HP[j] <= 0 && Catapult1[j] != NULL)
		{
			this->removeChild(Catapult1[j]);
			Catapult1[j] = NULL;
		}
	}
}

void gamescene_daji::update_tower1_attack(float t)
{
	bool attack_flag = false;
	int dis_ai = 1000000;
	if (a_daji.tower.HP > 0)
	{
		for (int j = 0; j < creep_i; j++)
		{
			int dis_Melee_creep = 1000000, dis_hero = 1000000;
			if (flag_creep == true)
			{
				if (b_daji.melee.HP[j] > 0 && attack_flag == false)
				{
					dis_Melee_creep = abs(Tower1->getPositionX() - Melee_creep2[j]->getPositionX());

					if (dis_Melee_creep < 300)
					{
						attack_flag = true;
						pb = Sprite::create("PB01.png");
						pb->setPosition(Tower1->getPositionX(), Tower1->getPositionY() + 50);
						this->addChild(pb);
						auto to = MoveTo::create(0.2, Vec2(Melee_creep2[j]->getPositionX(), Melee_creep2[j]->getPositionY()));
						auto hide = Hide::create();
						pb->runAction(CCSequence::create(to, hide, NULL));
						b_daji.melee.HP[j] -= a_daji.tower.base_damage;

					}
				}
				if (b_daji.range.HP[j] > 0 && attack_flag == false)
				{
					dis_Melee_creep = abs(Tower1->getPositionX() - Range_creep2[j]->getPositionX());
					if (dis_Melee_creep < 300)
					{
						attack_flag = true;
						pb = Sprite::create("PB01.png");
						pb->setPosition(Tower1->getPositionX(), Tower1->getPositionY() + 50);
						this->addChild(pb);
						auto to = MoveTo::create(0.2, Vec2(Range_creep2[j]->getPositionX(), Range_creep2[j]->getPositionY()));
						auto hide = Hide::create();
						pb->runAction(CCSequence::create(to, hide, NULL));
						b_daji.range.HP[j] -= a_daji.tower.base_damage;

					}
				}
				if (b_daji.catapult.HP[j] > 0 && attack_flag == false)
				{
					dis_Melee_creep = abs(Tower1->getPositionX() - Catapult2[j]->getPositionX());
					if (dis_Melee_creep < 300)
					{
						attack_flag = true;
						pb = Sprite::create("PB01.png");
						pb->setPosition(Tower1->getPositionX(), Tower1->getPositionY() + 50);
						this->addChild(pb);
						auto to = MoveTo::create(0.2, Vec2(Catapult2[j]->getPositionX(), Catapult2[j]->getPositionY()));
						auto hide = Hide::create();
						pb->runAction(CCSequence::create(to, hide, NULL));
						b_daji.catapult.HP[j] -= a_daji.tower.base_damage;

					}
				}
				if (b_daji.hero1.HP > 0 && attack_flag == false)
				{
					dis_Melee_creep = abs(Tower1->getPositionX() - ai->getPositionX());
					if (dis_Melee_creep < 300)
					{
						attack_flag = true;
						pb = Sprite::create("PB01.png");
						pb->setPosition(Tower1->getPositionX(), Tower1->getPositionY() + 50);
						this->addChild(pb);
						auto to = MoveTo::create(0.2, Vec2(ai->getPositionX(), ai->getPositionY()));
						auto hide = Hide::create();
						pb->runAction(CCSequence::create(to, hide, NULL));
						b_daji.hero1.HP -= a_daji.tower.base_damage;
					}
				}

			}


			if (b_daji.melee.HP[j] <= 0 && Melee_creep2[j] != NULL)
			{
				this->removeChild(Melee_creep2[j]);
				Melee_creep2[j] = NULL;
				a_daji.hero1.gold += 20;
				a_daji.hero1.exp += 10;
			}
			if (b_daji.range.HP[j] <= 0 && Range_creep2[j] != NULL)
			{
				this->removeChild(Range_creep2[j]);
				Range_creep2[j] = NULL;
				a_daji.hero1.gold += 50;
				a_daji.hero1.exp += 15;
			}
			if (b_daji.catapult.HP[j] <= 0 && Catapult2[j] != NULL)
			{
				this->removeChild(Catapult2[j]);
				Catapult2[j] = NULL;
				a_daji.hero1.gold += 50;
				a_daji.hero1.exp += 20;
			}
		}
	}
}

void gamescene_daji::update_tower2_attack(float t)
{
	bool attack_flag = false;
	int dis_hero = 1000000;
	if (b_daji.tower.HP > 0)
	{
		for (int j = 0; j < creep_i; j++)
		{

			int dis_Melee_creep = 1000000, dis_Range_creep = 1000000, dis_Catapult = 1000000;

			if (flag_creep == true)
			{
				if (a_daji.melee.HP[j] > 0 && attack_flag == false)
				{

					dis_Melee_creep = abs(Melee_creep1[j]->getPositionX() - Tower2->getPositionX());
					if (dis_Melee_creep < 300)
					{
						attack_flag = true;
						pb = Sprite::create("PB01.png");
						pb->setPosition(Tower2->getPositionX(), Tower2->getPositionY() + 50);
						this->addChild(pb);
						auto to = MoveTo::create(0.2, Vec2(Melee_creep1[j]->getPositionX(), Melee_creep1[j]->getPositionY()));
						auto hide = Hide::create();
						pb->runAction(CCSequence::create(to, hide, NULL));
						a_daji.melee.HP[j] -= b_daji.tower.base_damage;

					}
				}
				if (a_daji.range.HP[j] > 0 && attack_flag == false)
				{
					dis_Range_creep = abs(Range_creep1[j]->getPositionX() - Tower2->getPositionX());
					if (dis_Range_creep < 300)
					{
						attack_flag = true;
						pb = Sprite::create("PB01.png");
						pb->setPosition(Tower2->getPositionX(), Tower2->getPositionY() + 50);
						this->addChild(pb);
						auto to = MoveTo::create(0.2, Vec2(Range_creep1[j]->getPositionX(), Range_creep1[j]->getPositionY()));
						auto hide = Hide::create();
						pb->runAction(CCSequence::create(to, hide, NULL));
						a_daji.range.HP[j] -= b_daji.tower.base_damage;

					}
				}
				if (a_daji.catapult.HP[j] > 0 && attack_flag == false)
				{
					dis_Catapult = abs(Tower2->getPositionX() - Catapult1[j]->getPositionX());
					if (dis_Catapult < 300)
					{
						attack_flag = true;
						pb = Sprite::create("PB01.png");
						pb->setPosition(Tower2->getPositionX(), Tower2->getPositionY() + 50);
						this->addChild(pb);
						auto to = MoveTo::create(0.2, Vec2(Catapult1[j]->getPositionX(), Catapult1[j]->getPositionY()));
						auto hide = Hide::create();
						pb->runAction(CCSequence::create(to, hide, NULL));
						a_daji.catapult.HP[j] -= b_daji.tower.base_damage;

					}
				}
				if (a_daji.hero1.HP > 0 && attack_flag == false)
				{
					dis_hero = abs(Tower2->getPositionX() - sprite->getPositionX());
					if (dis_hero < 300)
					{
						attack_flag = true;
						pb = Sprite::create("PB01.png");
						pb->setPosition(Tower2->getPositionX(), Tower2->getPositionY() + 50);
						this->addChild(pb);
						auto to = MoveTo::create(0.2, Vec2(sprite->getPositionX(), sprite->getPositionY()));
						auto hide = Hide::create();
						pb->runAction(CCSequence::create(to, hide, NULL));
						a_daji.hero1.HP -= b_daji.tower.base_damage;
					}
				}
			}
		}
		if (a_daji.hero1.HP > 0 && attack_flag == false)
		{
			dis_hero = abs(Tower2->getPositionX() - sprite->getPositionX());
			if (dis_hero < 300)
			{
				attack_flag = true;
				pb = Sprite::create("PB01.png");
				pb->setPosition(Tower2->getPositionX(), Tower2->getPositionY() + 50);
				this->addChild(pb);
				auto to = MoveTo::create(0.2, Vec2(sprite->getPositionX(), sprite->getPositionY()));
				auto hide = Hide::create();
				pb->runAction(CCSequence::create(to, hide, NULL));
				a_daji.hero1.HP -= b_daji.tower.base_damage;
			}
		}
	}
}

void gamescene_daji::update_ai(float t)
{
	if (b_daji.hero1.HP > b_daji.hero1.HP_max / 2)
	{
		int dis[15];
		int min_dis = 100000;
		int flag = std::min(4, creep_i);
		Sprite *target;
		for (int i = 0; i < 15; i++)
			dis[i] = 10000;
		for (int i = 0; i < flag; i++)
		{
			if (Melee_creep1[creep_i - i - 1] != NULL)
			{
				dis[i] = abs(ai->getPositionX() - Melee_creep1[creep_i - i - 1]->getPositionX());
			}
			if (Range_creep1[creep_i - i - 1] != NULL)
				dis[i + 4] = abs(ai->getPositionX() - Range_creep1[creep_i - i - 1]->getPositionX());
			if (Catapult1[creep_i - i - 1] != NULL)
				dis[i + 8] = abs(ai->getPositionX() - Catapult1[creep_i - i - 1]->getPositionX());
			if (dis[i] < min_dis)
			{
				min_dis = dis[i];
				target = Melee_creep1[creep_i - i - 1];
			}
			if (dis[i + 4] < min_dis)
			{
				min_dis = dis[i];
				target = Range_creep1[creep_i - i - 1];
			}
			if (dis[i + 8] < min_dis)
			{
				min_dis = dis[i];
				target = Catapult1[creep_i - i - 1];
			}
		}
		if (sprite != nullptr)
		{
			dis[12] = abs(ai->getPositionX() - sprite->getPositionX());
			if (dis[12] < min_dis)
			{
				min_dis = dis[12];
				target = sprite;
			}
		}
		if (Tower1 != nullptr)
		{
			dis[13] = abs(ai->getPositionX() - Tower1->getPositionX());
			if (dis[13] < min_dis)
			{
				min_dis = dis[13];
				target = Tower1;
			}
		}
		if (Crystal1 != nullptr)
		{
			dis[14] = abs(ai->getPositionX() - Crystal1->getPositionX());
			if (dis[14] < min_dis)
			{
				min_dis = dis[14];
				target = Crystal1;
			}
		}
		if (min_dis <= 100)
		{
			if (target == sprite)
				a_daji.hero1.HP -= b_daji.hero1.base_damage;
			else if (target == Tower1)
				a_daji.tower.HP -= b_daji.hero1.base_damage;
			else if (target == Crystal1)
				a_daji.crystal.HP -= b_daji.hero1.base_damage;
			else
			{
				for (int i = 0; i < 4; i++)
				{
					if (target == Melee_creep1[creep_i - i - 1])
						a_daji.melee.HP[creep_i - i - 1] -= b_daji.hero1.base_damage;
					else if (target == Range_creep1[creep_i - i - 1])
						a_daji.range.HP[creep_i - i - 1] -= b_daji.hero1.base_damage;
					else if (target == Catapult1[creep_i - i - 1])
						a_daji.catapult.HP[creep_i - i - 1] -= b_daji.hero1.base_damage;
				}
			}
		}
		else
		{
			auto by = MoveBy::create(1, Vec2(-100, 0));
			ai->runAction(by);
		}
	}
	else if (b_daji.hero1.HP > 0)
	{
		int x = Crystal2->getPositionX() + 500 - ai->getPositionX();
		int X = std::min(x, 100);
		auto by = MoveBy::create(1, Vec2(X, 0));
		ai->runAction(by);
	}
	else
	{
		this->removeChild(ai);
		ai = NULL;
		
	}
}

void gamescene_daji::update_heroHP(float t)
{
	if (b_daji.tower.HP > 0)
		this->getBloodbar(Tower2, (1000 - b_daji.tower.HP) / 10);
	else if (Tower2 != NULL)
	{
		this->removeChild(Tower2);
		Tower2 = NULL;
		a_daji.hero1.gold += 200;
	}
	if (a_daji.tower.HP > 0)
		this->getBloodbar(Tower1, (1000 - a_daji.tower.HP) / 10);
	else if (Tower1 != NULL)
	{
		this->removeChild(Tower1);
		Tower1 = NULL;
	}
	if (a_daji.hero1.HP > 0)
		this->getBloodbar(sprite, (a_daji.hero1.HP_max - a_daji.hero1.HP) / (a_daji.hero1.HP_max / 100));
	else if (sprite != NULL)
	{
		this->removeChild(sprite);
		sprite = NULL;
		flag_heroalive = false;
		deaths += 1;
	}
	if (b_daji.hero1.HP > 0)
		this->getBloodbar(ai, (b_daji.hero1.HP_max - b_daji.hero1.HP) / (b_daji.hero1.HP_max / 100));
	else if (ai != NULL)
	{
		this->removeChild(ai);
		ai = NULL;
		kills += 1;
	}
	if (a_daji.crystal.HP > 0)
		this->getBloodbar(Crystal1, (3000 - a_daji.crystal.HP) / 30);
	else if (Crystal1 != nullptr)
	{
		this->removeChild(Crystal1);
		Crystal1 = nullptr;
	}
	if (b_daji.crystal.HP > 0)
		this->getBloodbar(Crystal2, (3000 - b_daji.crystal.HP) / 30);
	else if (Crystal2 != nullptr)
	{
		this->removeChild(Crystal2);
		Crystal2 = nullptr;
	}
	if (sprite != NULL && Crystal1 != nullptr)
	{
		if (sprite->getPositionX() < Crystal1->getPositionX() - 300)
		{
			if (a_daji.hero1.HP < a_daji.hero1.HP_max)
				a_daji.hero1.HP += a_daji.hero1.HP_max / 50;
			else if (a_daji.hero1.HP > a_daji.hero1.HP_max)
				a_daji.hero1.HP = a_daji.hero1.HP_max;
			this->getBloodbar1(sprite, (a_daji.hero1.HP_max - a_daji.hero1.HP) / (a_daji.hero1.HP_max / 100));
		}
	}
	if (ai != NULL && Crystal2 != nullptr)
	{
		if (ai->getPositionX() > Crystal2->getPositionX() + 300)
		{
			if (b_daji.hero1.HP < b_daji.hero1.HP_max)
				b_daji.hero1.HP += b_daji.hero1.HP_max / 50;
			else if (b_daji.hero1.HP > b_daji.hero1.HP_max)
				b_daji.hero1.HP = b_daji.hero1.HP_max;
			this->getBloodbar1(ai, (b_daji.hero1.HP_max - b_daji.hero1.HP) / (b_daji.hero1.HP_max / 100));
		}
	}
}

void gamescene_daji::hero_Attack()
{
	this->unschedule(schedule_selector(gamescene_daji::boundingbox_update1));
	this->schedule(schedule_selector(gamescene_daji::boundingbox_update1), 0.1);
}

void gamescene_daji::boundingbox_update1(float t)
{
	if (sprite != nullptr && flag_sprite != nullptr )
	{
		if (sprite->boundingBox().intersectsRect(flag_sprite->boundingBox()))
		{
			attack_flag++;
			if (attack_flag % 10 == 0)
			{
				for (int i = 0; i < creep_i; i++)
				{
					if (flag_sprite == Melee_creep2[i])
					{
						b_daji.melee.HP[i] -= a_daji.hero1.base_damage * ability4();
						if (b_daji.melee.HP[i] <= 0)
							flag_sprite = NULL;
					}
					else if (flag_sprite == Range_creep2[i])
					{
						b_daji.range.HP[i] -= a_daji.hero1.base_damage * ability4();
						if (b_daji.range.HP[i] <= 0)
							flag_sprite = NULL;
					}
					else if (flag_sprite == Catapult2[i])
					{
						b_daji.catapult.HP[i] -= a_daji.hero1.base_damage * ability4();
						if (b_daji.catapult.HP[i] <= 0)
							flag_sprite = NULL;
					}
				}
				if (flag_sprite == ai)
				{
					b_daji.hero1.HP -= a_daji.hero1.base_damage * ability4();
					if (b_daji.hero1.HP <= 0)
					{
						flag_sprite = NULL;
					}		
				}
				if (flag_sprite == Tower2)
				{
					b_daji.tower.HP -= a_daji.hero1.base_damage;
					if (b_daji.tower.HP <= 0)
						flag_sprite = NULL;
				}
				else if (flag_sprite == Crystal2)
				{
					b_daji.crystal.HP -= a_daji.hero1.base_damage;
					if (b_daji.crystal.HP <= 0)
						flag_sprite = NULL;
				}
			}
		}
	}
	if (flag_sprite == NULL)
		hero_attack_target = false;
}

//计算两者距离
float gamescene_daji::Distance(Sprite * A, Sprite * B)
{
	if (A != nullptr&&B != nullptr)
	{
		float positionX_A = A->getPositionX();
		float positionY_A = A->getPositionY();
		float positionX_B = B->getPositionX();
		float positionY_B = B->getPositionY();
		float distance = sqrt(pow(positionX_A - positionX_B, 2) + pow(positionY_A - positionY_B, 2));
		return distance;
	}
}