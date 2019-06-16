//
//  gamescene.cpp
//  SimpleGame
//
//  Created by 陈子杰 on 2019/5/12.
//
#include <iostream>
#include<string.h>
#include "gamescene_houyi.hpp"
#include "scene1.h"
#include <math.h>
#include "attr_init.hpp"
#include "SimpleAudioEngine.h"
#include "win.h"
#include "lose.h"

using namespace CocosDenshion;
USING_NS_CC;
using namespace std;

Layer *layer_game_houyi;
Layer *layer_set_houyi;
Sprite * bug_houyi;
Sprite * store_houyi;
bool flag_tab_houyi=false;
attr a_houyi;
attr b_houyi;
auto AbilitySoundEffect_houyi = SimpleAudioEngine::getInstance();//音效


Scene* houyi::gamescene_houyi()
{
    auto scene=Scene::create();
    layer_game_houyi=gamescene_houyi::create();
    layer_set_houyi=set_houyi::create();
    scene->addChild(layer_game_houyi);
    scene->addChild(layer_set_houyi);
    return scene;
    
}

bool gamescene_houyi::init()
{
    if(!Layer::init())
    {
        return false;
    }
    time=0;


    
    visibleSize = Director::getInstance()->getVisibleSize();
    //背景音乐
    auto BGM = SimpleAudioEngine::getInstance();
    BGM->playBackgroundMusic("bgm.mp3", true);


    a_houyi.init();
    b_houyi.init();
    flag_creep=false;
	//地图
	auto map = Sprite::create("map.png");
	this->addChild(map,0);
	map->setPosition(2100, visibleSize.height / 2);
    //英雄
    sprite=Sprite::create("bm_right.png");
    sprite->setPosition(visibleSize.width/2,visibleSize.height/2);
	sprite->setScale(0.5);
    this->addChild(sprite,4);
    flag_heroalive=true;
    //ai
    ai=Sprite::create("bm.png");
    ai->setPosition(3500,visibleSize.height/2);
    ai->setScale(0.5);
    this->addChild(ai,4);
    flag_aialive=true;
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
	listener->onMouseDown = CC_CALLBACK_1(gamescene_houyi::onMouseDown, this);
	listener->onMouseMove = CC_CALLBACK_1(gamescene_houyi::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto listener1= EventListenerMouse::create();
    listener1->onMouseMove=CC_CALLBACK_1(gamescene_houyi::onMouseMove1,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
 
    auto listener3 = EventListenerKeyboard::create();
    listener3->onKeyPressed = CC_CALLBACK_2(gamescene_houyi::onKeyPressed, this);
    listener3->onKeyReleased = CC_CALLBACK_2(gamescene_houyi::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener3, this);
    
    auto listener4 = EventListenerKeyboard::create();
    listener4->onKeyPressed = CC_CALLBACK_2(gamescene_houyi::onKeyPressed4, this);
    listener4->onKeyReleased = CC_CALLBACK_2(gamescene_houyi::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener4, this);

	this->scheduleUpdate();
    this->schedule(schedule_selector(gamescene_houyi::update_time),1);
    //出兵
    this->schedule(schedule_selector(gamescene_houyi::update_creep1),15);
    this->schedule(schedule_selector(gamescene_houyi::update_heroHP), 0.1f);
	//塔攻击

    this->schedule(schedule_selector(gamescene_houyi::update_tower2_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_tower1_attack),1);
    
    return true;
}

bool set_houyi::init()
{
    if(!Layer::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();

	bug_houyi =Sprite::create("equipment.png");
	bug_houyi->setPosition(0,0);
	this->addChild(bug_houyi);
	bug_houyi->setVisible(false);
    
    store_houyi=Sprite::create("store.png");
    store_houyi->setScale(2);
    store_houyi->setPosition(128,visibleSize.height/2);
    this->addChild(store_houyi);
    store_houyi->setVisible(false);
    
    auto listener= EventListenerMouse::create();
    listener->onMouseDown=CC_CALLBACK_1(set_houyi::onMouseDown,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void gamescene_houyi::update(float delta)
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
void gamescene_houyi::update_creep1(float t)
{
    flag_creep=true;
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
    
    a_houyi.init_creep(creep_i);
    b_houyi.init_creep(creep_i);

    creep_i++;
 
    this->schedule(schedule_selector(gamescene_houyi::update_Melee_creep1_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_Melee_creep2_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_Range_creep1_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_Range_creep2_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_Catapult1_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_Catapult2_attack),1);
    
    this->schedule(schedule_selector(gamescene_houyi::update_ai),1);

}
//鼠标按下
void gamescene_houyi::onMouseDown(Event *event)
{
	//移动
    if(sprite!=NULL && flag_tab_houyi==false)
    {
        auto e=(EventMouse *)event;
        int X=e->getCursorX()-512;
        int Y=e->getCursorY()-sprite->getPositionY();
        double dis=sqrt(X*X+Y*Y);
        auto by1=MoveBy::create(dis/ a_houyi.hero1.MoveSpeed,Vec2(-X,0));
        by1->setTag(7);
        layer_game_houyi->stopActionByTag(7);
        layer_game_houyi->resume();
        layer_game_houyi->runAction(by1);

        auto by2=MoveBy::create(dis/ a_houyi.hero1.MoveSpeed,Vec2(X,Y));
        by2->setTag(6);
        sprite->stopActionByTag(6);
        sprite->resume();
        sprite->runAction(by2);
     
        auto by3=MoveBy::create(dis/ a_houyi.hero1.MoveSpeed,Vec2(X,Y));
        by3->setTag(5);
		bug_houyi->stopActionByTag(5);
		bug_houyi->resume();
		bug_houyi->runAction(by3);

        clickCreep_enemy(e->getCursorX()+ bug_houyi->getPositionX(),e->getCursorY());        
    }
	EventMouse* e = (EventMouse*)event;
	//获取鼠标点击位置
	float cursorX = e->getCursorX() + bug_houyi->getPositionX() ;
	float cursorY = e->getCursorY();
	//获取技能3目标
	if (ability3Clicked == true || ability3MovingToMelee == true || ability3MovingToAI == true || ability3MovingToRange == true || ability3MovingToSiege == true)
	{
		//判断技能3是否作用于敌方单位
		ability3Hit(cursorX, cursorY);
		return;
	}
}
//鼠标移动
void gamescene_houyi::onMouseMove(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	//获取鼠标点击位置
	float cursorX = e->getCursorX() + bug_houyi->getPositionX();
	float cursorY = e->getCursorY();
	//技能3光标随鼠标移动
	if (ability3Clicked == true)
	{
		ability3Cursor(cursorX, cursorY);
	}
}

void gamescene_houyi::onMouseMove1(Event *event)
{
    auto e=(EventMouse *)event;
    if(hero_attack==true && e!=nullptr)
    {
        if (cursor!= nullptr)
        {
            cursor->removeFromParent();
        }
        cursor=Sprite::create("cursor.png");
        cursor->setPosition(e->getCursorX()+ bug_houyi->getPositionX()-60,e->getCursorY());
        this->addChild(cursor);
    }    
}

void set_houyi::onMouseDown(Event *event)
{
    auto e=(EventMouse *)event;
	if (flag_tab_houyi == true)
	{
		if (equip_number < 5)
		{
			if (e->getCursorX() > 0 && e->getCursorX() < 80 && e->getCursorY() > 550 && e->getCursorY() < 620)
			{
				if (a_houyi.hero1.gold > 200)
				{
					a_houyi.hero1.gold -= 200;
					equip_number++;
					auto att20 = Sprite::create("20att.png");
					att20->setScale(2);
					att20->setPosition(equipX[equip_number], equipY[equip_number]);
					layer_set_houyi->addChild(att20, 10);
					a_houyi.hero1.base_damage += 20;
				}
			}
			if (e->getCursorX() > 0 && e->getCursorX() < 80 && e->getCursorY() > 450 && e->getCursorY() < 500)
			{
				if (a_houyi.hero1.gold > 1000)
				{
					a_houyi.hero1.gold -= 1000;
					equip_number++;
					auto att50 = Sprite::create("50att.png");
					att50->setScale(2);
					att50->setPosition(equipX[equip_number], equipY[equip_number]);
					layer_set_houyi->addChild(att50, 10);
					a_houyi.hero1.base_damage += 50;
				}
			}
			if (e->getCursorX() > 0 && e->getCursorX() < 80 && e->getCursorY() > 320 && e->getCursorY() < 380)
			{
				if (a_houyi.hero1.gold > 2000)
				{
					a_houyi.hero1.gold -= 2000;
					equip_number++;
					auto att100 = Sprite::create("100att.png");
					att100->setScale(2);
					att100->setPosition(equipX[equip_number], equipY[equip_number]);
					layer_set_houyi->addChild(att100, 10);
					a_houyi.hero1.base_damage += 100;
				}
			}
			if (e->getCursorX() > 100 && e->getCursorX() < 150 && e->getCursorY() > 550 && e->getCursorY() < 620)
			{
				if (a_houyi.hero1.gold > 200)
				{
					a_houyi.hero1.gold -= 200;
					equip_number++;
					auto hp300 = Sprite::create("300hp.png");
					hp300->setScale(2);
					hp300->setPosition(equipX[equip_number], equipY[equip_number]);
					layer_set_houyi->addChild(hp300, 10);
					a_houyi.hero1.HP_max += 300;
					a_houyi.hero1.HP += 300;
				}
			}
			if (e->getCursorX() > 100 && e->getCursorX() < 150 && e->getCursorY() > 450 && e->getCursorY() < 500)
			{
				if (a_houyi.hero1.gold > 1000)
				{
					a_houyi.hero1.gold -= 1000;
					equip_number++;
					auto hp1000 = Sprite::create("1000hp.png");
					hp1000->setScale(2);
					hp1000->setPosition(equipX[equip_number], equipY[equip_number]);
					layer_set_houyi->addChild(hp1000, 10);
					a_houyi.hero1.HP_max += 1000;
					a_houyi.hero1.HP += 1000;
				}
			}
			if (e->getCursorX() > 100 && e->getCursorX() < 150 && e->getCursorY() > 320 && e->getCursorY() < 380)
			{
				if (a_houyi.hero1.gold > 2000)
				{
					a_houyi.hero1.gold -= 2000;
					equip_number++;
					auto hp2000 = Sprite::create("2000hp.png");
					hp2000->setScale(2);
					hp2000->setPosition(equipX[equip_number], equipY[equip_number]);
					layer_set_houyi->addChild(hp2000, 10);
					a_houyi.hero1.HP_max += 2000;
					a_houyi.hero1.HP += 2000;
				}
			}
			if (e->getCursorX() > 180 && e->getCursorX() < 250 && e->getCursorY() > 450 && e->getCursorY() < 500)
			{
				if (a_houyi.hero1.gold > 3000)
				{
					a_houyi.hero1.gold -= 3000;
					equip_number++;
					auto att300 = Sprite::create("300att.png");
					att300->setScale(2);
					att300->setPosition(equipX[equip_number], equipY[equip_number]);
					layer_set_houyi->addChild(att300, 10);
					a_houyi.hero1.base_damage += 300;

				}
			}
		}
        
    }
    
    std::cout<<e->getCursorX()<<" "<<e->getCursorY()<<std::endl;
}

void gamescene_houyi::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{	
	//技能1触发
	if (keyCode == EventKeyboard::KeyCode::KEY_R && sprite != nullptr)
	{
		if (cd_ability1 == false)
		{
			if (LV_ability1 != 0)
			{
				ability1();
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
	//技能2触发
	if (keyCode == EventKeyboard::KeyCode::KEY_T && sprite != nullptr)
	{
		if (cd_ability2 == false)
		{
			if (LV_ability2 != 0)
			{
				ability2();
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
	// 技能3触发
	if (keyCode == EventKeyboard::KeyCode::KEY_G && sprite != nullptr)
	{
		if (cd_ability3 == false)
		{
			if (LV_ability3 != 0)
			{
				//选取目标
				ability3Clicked = true;
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
	
	//取消释放技能3
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE && sprite != nullptr)
	{
		ability3Clicked = false;
		if (cursor != nullptr)
		{
			cursor->removeFromParent(); cursor = nullptr;
		}
	}
}

void gamescene_houyi::onKeyPressed4(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_TAB)
	{
		flag_tab_houyi = 1 - flag_tab_houyi;
		if (flag_tab_houyi == true)
		{
			store_houyi->setVisible(true);

		}
		else
			store_houyi->setVisible(false);
	}
}

//技能
//技能1
void gamescene_houyi::ability1()
{
	//技能1冷却、持续
	this->scheduleOnce(schedule_selector(gamescene_houyi::ability1DurationUpdate), Duration_ability1);
	this->scheduleOnce(schedule_selector(gamescene_houyi::ability1CDUpdate), CD_ability1);
	duration_ability1 = true;
	cd_ability1 = true;
	//技能1音效
	AbilitySoundEffect_houyi->playEffect("ability1.wav", false, 1, 0, 1);
	//技能1效果
	switch (LV_ability1)
	{
	case 1:a_houyi.hero1.MoveSpeed *= 1.5; a_houyi.hero1.AttackInterval *= 0.65; a_houyi.hero1.base_damage *= 1.5; break;
	case 2:a_houyi.hero1.MoveSpeed *= 1.65; a_houyi.hero1.AttackInterval *= 0.6; a_houyi.hero1.base_damage *= 1.65; break;
	case 3:a_houyi.hero1.MoveSpeed *= 1.8; a_houyi.hero1.AttackInterval *= 0.55; a_houyi.hero1.base_damage *= 1.8; break;
	case 4:a_houyi.hero1.MoveSpeed *= 2; a_houyi.hero1.AttackInterval *= 0.5; a_houyi.hero1.base_damage *= 2; break;
	}
}
//技能1持续时间
void gamescene_houyi::ability1DurationUpdate(float delta)
{
	switch (LV_ability1)
	{
	case 1:a_houyi.hero1.MoveSpeed /= 1.5; a_houyi.hero1.AttackInterval /= 0.65; a_houyi.hero1.base_damage /= 1.5; break;
	case 2:a_houyi.hero1.MoveSpeed /= 1.65; a_houyi.hero1.AttackInterval /= 0.6; a_houyi.hero1.base_damage /= 1.65; break;
	case 3:a_houyi.hero1.MoveSpeed /= 1.8; a_houyi.hero1.AttackInterval /= 0.55; a_houyi.hero1.base_damage /= 1.8; break;
	case 4:a_houyi.hero1.MoveSpeed /= 2; a_houyi.hero1.AttackInterval /= 0.5; a_houyi.hero1.base_damage /= 2; break;
	}
	duration_ability1 = false;
}
//技能1冷却时间
void gamescene_houyi::ability1CDUpdate(float delta)
{
	cd_ability1 = false;
}
//技能2
void gamescene_houyi::ability2()
{
	//技能2冷却
	this->scheduleOnce(schedule_selector(gamescene_houyi::ability2CDUpdate), CD_ability2);
	cd_ability2 = true;
	//技能2音效
	AbilitySoundEffect_houyi->playEffect("ability2.wav", false, 1, 0, 1);
	//技能2动画
	auto blade = Sprite::create("blade array.png");
	float positionX = sprite->getPositionX() + 30;
	float positionY = sprite->getPositionY() - 60;
	blade->setPosition(Vec2(positionX, positionY));
	this->addChild(blade, 1);
	auto FadeOut = FadeOut::create(2);
	blade->runAction(FadeOut);
	//技能2效果
	if (Distance(sprite, ai) <= 400)
	{
		switch (LV_ability2)
		{
		case 1:b_houyi.hero1.HP -= 200; break;
		case 2:b_houyi.hero1.HP -= 400; break;
		case 3:b_houyi.hero1.HP -= 600; break;
		case 4:b_houyi.hero1.HP -= 800; break;
		}
	}
	for (int i = 0; i < 600; i++)
	{
		//近战
		if (Distance(sprite, Melee_creep2[i]) <= 400)
		{
			switch (LV_ability2)
			{
			case 1:b_houyi.melee.HP[i] -= 200;
			case 2:b_houyi.melee.HP[i] -= 400;
			case 3:b_houyi.melee.HP[i] -= 600;
			case 4:b_houyi.melee.HP[i] -= 800;
			}
		}
		//远程
		if (Distance(sprite, Range_creep2[i]) <= 400)
		{
			switch (LV_ability2)
			{
			case 1:b_houyi.range.HP[i] -= 200; break;
			case 2:b_houyi.range.HP[i] -= 400; break;
			case 3:b_houyi.range.HP[i] -= 600; break;
			case 4:b_houyi.range.HP[i] -= 800; break;
			}
		}
		//攻城
		if (Distance(sprite, Catapult2[i]) <= 400)
		{
			switch (LV_ability2)
			{
			case 1:b_houyi.catapult.HP[i] -= 200; break;
			case 2:b_houyi.catapult.HP[i] -= 400; break;
			case 3:b_houyi.catapult.HP[i] -= 600; break;
			case 4:b_houyi.catapult.HP[i] -= 800; break;
			}
		}
	}
}
//技能2冷却时间
void gamescene_houyi::ability2CDUpdate(float delta)
{
	cd_ability2 = false;
}
//技能3效果
void gamescene_houyi::ability3Effect()
{
	//技能3冷却
	this->scheduleOnce(schedule_selector(gamescene_houyi::ability3CDUpdate), CD_ability3);
	cd_ability3 = true;
	//技能3音效
	AbilitySoundEffect_houyi->playEffect("ability3.wav", false, 1, 0, 1);
	//技能3动画
	auto blade = Sprite::create("blade.png");
	float positionX;
	float positionY;
	//ai
	if (ability3_targetAI == true)
	{
		positionX = ai->getPositionX();
		positionY = ai->getPositionY();
	}
	//近战
	if (ability3_targetMelee == true)
	{
		positionX = Melee_creep2[ability3_target]->getPositionX();
		positionY = Melee_creep2[ability3_target]->getPositionY();
	}
	//远程
	if (ability3_targetRange == true)
	{
		positionX = Range_creep2[ability3_target]->getPositionX();
		positionY = Range_creep2[ability3_target]->getPositionY();
	}
	//攻城
	if (ability3_targetSiege == true)
	{
		positionX = Catapult2[ability3_target]->getPositionX();
		positionY = Catapult2[ability3_target]->getPositionY();
	}
	blade->setPosition(Vec2(positionX, positionY + 50));
	this->addChild(blade, 1);
	auto MoveTo = MoveTo::create(2, Vec2(positionX, positionY));
	blade->runAction(MoveTo);
	auto FadeOut = FadeOut::create(2);
	blade->runAction(FadeOut);
	//技能3效果
	//ai
	if (ability3_targetAI == true)
	{
		ability3_targetAI = false;
		switch (LV_ability3)
		{
		case 1:b_houyi.hero1.HP -= 500; break;
		case 2:b_houyi.hero1.HP -= 1000; break;
		case 3:b_houyi.hero1.HP -= 1500; break;
		case 4:b_houyi.hero1.HP -= 2000; break;
		}
		return;
	}
	//近战
	if (ability3_targetMelee = true)
	{
		ability3_targetMelee = false;
		switch (LV_ability3)
		{
		case 1:b_houyi.melee.HP[ability3_target] -= 500; break;
		case 2:b_houyi.melee.HP[ability3_target] -= 1000; break;
		case 3:b_houyi.melee.HP[ability3_target] -= 1500; break;
		case 4:b_houyi.melee.HP[ability3_target] -= 2000; break;
		}
		return;
	}
	//远程
	if (ability3_targetRange = true)
	{
		ability3_targetRange = false;
		switch (LV_ability3)
		{
		case 1:b_houyi.range.HP[ability3_target] -= 500; break;
		case 2:b_houyi.range.HP[ability3_target] -= 1000; break;
		case 3:b_houyi.range.HP[ability3_target] -= 1500; break;
		case 4:b_houyi.range.HP[ability3_target] -= 2000; break;
		}
		return;
	}
	//攻城
	if (ability3_targetSiege = true)
	{
		ability3_targetSiege = false;
		switch (LV_ability3)
		{
		case 1:b_houyi.catapult.HP[ability3_target] -= 500; break;
		case 2:b_houyi.catapult.HP[ability3_target] -= 1000; break;
		case 3:b_houyi.catapult.HP[ability3_target] -= 1500; break;
		case 4:b_houyi.catapult.HP[ability3_target] -= 2000; break;
		}
		return;
	}
}
//判断技能3是否作用于敌方单位
void gamescene_houyi::ability3Hit(float X, float Y)
{
	//ai
	if (InTheArea(X, Y, ai) == true)
	{
		ability3Clicked = false;
		ability3_targetAI = true;
		if (cursor != nullptr)
		{
			cursor->removeFromParent(); cursor = nullptr;
		}
		//判断敌人是否进入技能3施法范围
		if (Distance(sprite, ai) > CastRange_ability3)
		{
			//移动至施法范围内
			ability3MovingToAI = true;
			float time = Distance(sprite, ai) / a_houyi.hero1.MoveSpeed;
			float positionX = ai->getPositionX();
			float positionY = ai->getPositionY();
			auto moveTo = MoveTo::create(time, Vec2(positionX, positionY));
			sprite->runAction(moveTo);
			moveTo->setTag(1);
		}
		if (Distance(sprite, ai) <= CastRange_ability3)
		{
			//技能3效果
			ability3Effect();
		}
		return;
	}
	//小兵
	for (int i = 0; i < 600; i++)
	{
		//近战
		if (Melee_creep2[i] != nullptr)
		{
			if (InTheArea(X, Y, Melee_creep2[i]) == true)
			{
				ability3_target = i;
				ability3Clicked = false;
				ability3_targetMelee = true;
				cursor->removeFromParent(); cursor = nullptr;
				//判断敌人是否进入技能3施法范围
				if (Distance(sprite, Melee_creep2[ability3_target]) > CastRange_ability3)
				{
					//移动至施法范围内
					ability3MovingToMelee = true;
					float time = Distance(sprite, Melee_creep2[ability3_target]) / a_houyi.hero1.MoveSpeed;
					float positionX = Melee_creep2[ability3_target]->getPositionX();
					float positionY = Melee_creep2[ability3_target]->getPositionY();
					auto moveTo = MoveTo::create(time, Vec2(positionX, positionY));
					sprite->runAction(moveTo);
					moveTo->setTag(1);
				}
				if (Distance(sprite, Melee_creep2[ability3_target]) <= CastRange_ability3)
				{
					//技能3效果
					ability3Effect();
					break;
				}
			}
		}
		//远程
		if (Range_creep2[i] != nullptr)
		{
			if (InTheArea(X, Y, Range_creep2[i]) == true)
			{
				ability3_target = i;
				ability3Clicked = false;
				ability3_targetRange = true;
				cursor->removeFromParent(); cursor = nullptr;
				//判断敌人是否进入技能3施法范围
				if (Distance(sprite, Range_creep2[ability3_target]) > CastRange_ability3)
				{
					//移动至施法范围内
					ability3MovingToRange = true;
					float time = Distance(sprite, Range_creep2[ability3_target]) / a_houyi.hero1.MoveSpeed;
					float positionX = Range_creep2[ability3_target]->getPositionX();
					float positionY = Range_creep2[ability3_target]->getPositionY();
					auto moveTo = MoveTo::create(time, Vec2(positionX, positionY));
					sprite->runAction(moveTo);
					moveTo->setTag(1);
				}
				if (Distance(sprite, Range_creep2[ability3_target]) <= CastRange_ability3)
				{
					//技能3效果
					ability3Effect();
					break;
				}
			}
		}
		//攻城
		if (Catapult2[i] != nullptr)
		{
			if (InTheArea(X, Y, Catapult2[i]) == true)
			{
				ability3_target = i;
				ability3Clicked = false;
				ability3_targetSiege = true;
				cursor->removeFromParent(); cursor = nullptr;
				//判断敌人是否进入技能3施法范围
				if (Distance(sprite, Catapult2[ability3_target]) > CastRange_ability3)
				{
					//移动至施法范围内
					ability3MovingToSiege = true;
					float time = Distance(sprite, Catapult2[ability3_target]) / a_houyi.hero1.MoveSpeed;
					float positionX = Catapult2[ability3_target]->getPositionX();
					float positionY = Catapult2[ability3_target]->getPositionY();
					auto moveTo = MoveTo::create(time, Vec2(positionX, positionY));
					sprite->runAction(moveTo);
					moveTo->setTag(1);
				}
				if (Distance(sprite, Catapult2[ability3_target]) <= CastRange_ability3)
				{
					//技能3效果
					ability3Effect();
					break;
				}
			}
		}
	}
}
//技能3冷却时间
void gamescene_houyi::ability3CDUpdate(float delta)
{
	cd_ability3 = false;
}
//技能3光标随鼠标移动
void gamescene_houyi::ability3Cursor(float X, float Y)
{
	if (cursor != nullptr)
	{
		cursor->removeFromParent();
	}
	cursor = Sprite::create("cursor.png");
	this->addChild(cursor, 100);
	cursor->setPosition(X, Y);
}


void gamescene_houyi::getBloodbar(Sprite *guaisprite ,float a)
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

void gamescene_houyi::getBloodbar1(Sprite *guaisprite ,float a)
{
    

    auto pBloodManSp = Sprite::create("HPbar_full.png");
    
    auto pBloodProGress = CCProgressTimer::create(pBloodManSp);
    pBloodProGress->setType(kCCProgressTimerTypeBar);
    pBloodProGress->setBarChangeRate(Vec2(1, 0));
    pBloodProGress->setMidpoint(Vec2(0, 0));
    pBloodProGress->setPosition(Vec2(guaisprite->getContentSize().width / 2, guaisprite->getContentSize().height / 1.1));
    pBloodProGress->setPercentage(1-a);
    guaisprite->addChild(pBloodProGress,2);
}

int gamescene_houyi::getCurrentlvl(Sprite *sprite)
{
    int lvlup_experience[14]={50,100,150,200,250,300,350,400,450,500,550,600,650,700};
    int lvl=1;
    if(a_houyi.hero1.exp>lvlup_experience[lvl-1])
    {
        a_houyi.hero1.exp-=lvlup_experience[lvl-1];
        lvl++;
		LV_ability1++;
		LV_ability2++;
		LV_ability3++;
		a_houyi.hero1.base_damage += 10;
		a_houyi.hero1.HP += 100;
		a_houyi.hero1.HP_max += 100;
    }
    return lvl;
}

void gamescene_houyi::update_time(float t)
{
    time+=1;
    a_houyi.hero1.gold+=2;
    if(time<60)
    {
        if(int(time)%60<10)
            str="00:0"+std::to_string(time);
        else
            str="00:"+std::to_string(time);
    }
    else if(time<600)
    {
        if(int(time)%60<10)
            str="0"+std::to_string(int(time/60))+":0"+std::to_string(int(time)%60);
        else
            str="0"+std::to_string(int(time/60))+":"+std::to_string(int(time)%60);
    }
    else
    {
        if(int(time)%60<10)
            str=std::to_string(int(time/60))+":0"+std::to_string(int(time)%60);
        else
            str=std::to_string(int(time/60))+":"+std::to_string(int(time)%60);
    }
    layer_set_houyi->removeChild(label_time);
    label_time=Label::createWithSystemFont(str, "Arial", 24);
    label_time->setPosition(512,600);
    layer_set_houyi->addChild(label_time);
    
    std::string str_gold=std::to_string(a_houyi.hero1.gold)+"g";
    layer_set_houyi->removeChild(label_gold);
    label_gold=Label::createWithSystemFont(str_gold, "Arial", 24);
    label_gold->setPosition(300,60);
    layer_set_houyi->addChild(label_gold);
    
    std::string str_lvl="lv:"+std::to_string(getCurrentlvl(sprite));
    layer_set_houyi->removeChild(label_lvl);
    label_lvl=Label::createWithSystemFont(str_lvl, "Arial", 24);
    label_lvl->setPosition(300,120);
    layer_set_houyi->addChild(label_lvl);
    
    std::string str_damage="damage:"+std::to_string(a_houyi.hero1.base_damage);
    layer_set_houyi->removeChild(label_damage);
    label_damage=Label::createWithSystemFont(str_damage, "Arial", 24);
    label_damage->setPosition(500,120);
    layer_set_houyi->addChild(label_damage);
    
    std::string str_hp="hp:"+std::to_string(a_houyi.hero1.HP)+"/"+std::to_string(a_houyi.hero1.HP_max);
    layer_set_houyi->removeChild(label_hp);
    label_hp=Label::createWithSystemFont(str_hp, "Arial", 24);
    label_hp->setPosition(500,60);
    layer_set_houyi->addChild(label_hp);

	//显示击杀死亡
	stringstream Kills; Kills << kills;
	stringstream Deaths; Deaths << deaths;
	string str1 = "Kills:";
	string str2 = Kills.str();
	string str3 = " Deaths:";
	string str4 = Deaths.str();
	string KillsDeaths = str1 + str2 + str3 + str4;
	layer_set_houyi->removeChild(label_KD);
	label_KD = Label::createWithSystemFont(KillsDeaths, "Arial", 24);
	label_KD->setPosition(900, 600);
	layer_set_houyi->addChild(label_KD);
    
    if(flag_heroalive==false)
    {
        time_tolive=25;
        flag_heroalive=true;
    }
    if(sprite==NULL)
    {
        time_tolive--;
        if(time_tolive<=0)
        {
            a_houyi.hero1.HP=a_houyi.hero1.HP_max;
            sprite=Sprite::create("houyi.png");
            sprite->setPosition(visibleSize.width/2,visibleSize.height/2);
            auto by=MoveBy::create(0.1,Vec2(deltaX,0));
            layer_game_houyi->runAction(by);  
            this->addChild(sprite,4);
        }
    }
}

bool gamescene_houyi::InTheArea(float X, float Y,Sprite  * A)
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

void gamescene_houyi::clickCreep_enemy(float X, float Y)
{
    hero_attack_target=false;
    for (int i=0;i<creep_i;i++)
    {
        if (b_houyi.melee.HP[i]>0&& hero_attack_target==false)
        {
            if (InTheArea(X,Y,Melee_creep2[i])==true)
            {
                hero_attack_target=true;
                flag_sprite=Melee_creep2[i];
                hero_Attack();
                log("true");
            }
        }
        if (b_houyi.range.HP[i]>0&& hero_attack_target==false)
        {
            if (InTheArea(X,Y,Range_creep2[i])==true)
            {
                hero_attack_target=true;
                flag_sprite=Range_creep2[i];
                hero_Attack();
                log("true");
            }
        }
        if (b_houyi.catapult.HP[i]>0 && hero_attack_target==false)
        {
            if (InTheArea(X,Y,Catapult2[i])==true)
            {
                hero_attack_target=true;
                flag_sprite=Catapult2[i];
                hero_Attack();
                log("true");
            }
        }
    }
    if(b_houyi.hero1.HP>0&& hero_attack_target==false)
    {
        if (InTheArea(X,Y,ai)==true)
        {
            hero_attack_target=true;
            flag_sprite=ai;
            hero_Attack();
            log("true");
        }
    }
    if (b_houyi.tower.HP>0 && hero_attack_target==false)
    {
        if (InTheArea(X,Y,Tower2)==true)
        {
            hero_attack_target=true;
            flag_sprite=Tower2;
            hero_Attack();
            log("true");
        }
    }
    if (b_houyi.crystal.HP>0 && hero_attack_target==false)
    {
        if (InTheArea(X,Y,Crystal2)==true)
        {
            hero_attack_target=true;
            flag_sprite=Crystal2;
            hero_Attack();
            log("true");
        }
    }
    std::cout<<flag_sprite<<std::endl;
}

void gamescene_houyi::update_Melee_creep1_attack(float t)
{
    for(int j=0;j<creep_i;j++)
    {
        int X[9],Y[9],dis[9];
        for(int i=0;i<9;i++)
        {
            X[i]=100000;
            Y[i]=100000;
            dis[i]=1000000000;
        }
        if(a_houyi.melee.HP[j]>0)
        {
            if(b_houyi.melee.HP[j]>0)
            {
                X[0]=-Melee_creep1[j]->getPositionX()+Melee_creep2[j]->getPositionX();
                Y[0]=-Melee_creep1[j]->getPositionY()+Melee_creep2[j]->getPositionY();
                dis[0]=X[0]*X[0]+Y[0]*Y[0];
            }
            if(b_houyi.crystal.HP>0)
            {
                X[1]=-Melee_creep1[j]->getPositionX()+Crystal2->getPositionX();
                Y[1]=-Melee_creep1[j]->getPositionY()+Crystal2->getPositionY();
                dis[1]=X[1]*X[1]+Y[1]*Y[1];
                
            }
            if(b_houyi.tower.HP>0)
            {
                X[2]=-Melee_creep1[j]->getPositionX()+Tower2->getPositionX();
                Y[2]=-Melee_creep1[j]->getPositionY()+Tower2->getPositionY();
                dis[2]=X[2]*X[2]+Y[2]*Y[2];
            }
            if(b_houyi.range.HP[j]>0)
            {
                X[3]=-Melee_creep1[j]->getPositionX()+Range_creep2[j]->getPositionX();
                Y[3]=-Melee_creep1[j]->getPositionY()+Range_creep2[j]->getPositionY();
                dis[3]=X[3]*X[3]+Y[3]*Y[3];
            }
            if(b_houyi.catapult.HP[j]>0)
            {
                X[4]=-Melee_creep1[j]->getPositionX()+Catapult2[j]->getPositionX();
                Y[4]=-Melee_creep1[j]->getPositionY()+Catapult2[j]->getPositionY();
                dis[4]=X[4]*X[4]+Y[4]*Y[4];
            }
            if(j!=0)
            {
                if(b_houyi.melee.HP[j-1]>0)
                {
                    X[5]=-Melee_creep1[j]->getPositionX()+Melee_creep2[j-1]->getPositionX();
                    Y[5]=-Melee_creep1[j]->getPositionY()+Melee_creep2[j-1]->getPositionY();
                    dis[5]=X[5]*X[5]+Y[5]*Y[5];
                }
                if(b_houyi.range.HP[j-1]>0)
                {
                    X[6]=-Melee_creep1[j]->getPositionX()+Range_creep2[j-1]->getPositionX();
                    Y[6]=-Melee_creep1[j]->getPositionY()+Range_creep2[j-1]->getPositionY();
                    dis[6]=X[6]*X[6]+Y[6]*Y[6];
                }
                if(b_houyi.catapult.HP[j-1]>0)
                {
                    X[7]=-Melee_creep1[j]->getPositionX()+Catapult2[j-1]->getPositionX();
                    Y[7]=-Melee_creep1[j]->getPositionY()+Catapult2[j-1]->getPositionY();
                    dis[7]=X[7]*X[7]+Y[7]*Y[7];
                }
            }
            if(b_houyi.hero1.HP>0)
            {
                X[8]=-Melee_creep1[j]->getPositionX()+ai->getPositionX();
                Y[8]=-Melee_creep1[j]->getPositionY()+ai->getPositionY();
                dis[8]=X[8]*X[8]+Y[8]*Y[8];
            }
            
            int min_dis=1000000000;
            for(int i=0;i<9;i++)
            {
                if(dis[i]<min_dis)
                    min_dis=dis[i];
            }
            double time=sqrt(min_dis)/100;
            
            
            if(min_dis<=2500)
            {
                if(min_dis==dis[0])
                    b_houyi.melee.HP[j]-=20;
                else if(min_dis==dis[1])
                    b_houyi.crystal.HP-=20;
                else if(min_dis==dis[2])
                    b_houyi.tower.HP-=20;
                else if(min_dis==dis[3])
                    b_houyi.range.HP[j]-=20;
                else if(min_dis==dis[4])
                    b_houyi.catapult.HP[j]-=20;
                else if(min_dis==dis[5])
                    b_houyi.melee.HP[j-1]-=20;
                else if(min_dis==dis[6])
                    b_houyi.range.HP[j-1]-=20;
                else if(min_dis==dis[7])
                    b_houyi.catapult.HP[j-1]-=20;
                else if(min_dis==dis[8])
                    b_houyi.hero1.HP-=20;
                
            }
            else
            {
                for(int i=0;i<10;i++)
                {
                    if(min_dis==dis[i])
                    {
                        auto by=MoveBy::create(1, Vec2((abs(X[i])-50)/time,0));
                        Melee_creep1[j]->runAction(by);
                        break;
                    }
                }
            }
        }
        
        if(a_houyi.melee.HP[j]>0)
            this->getBloodbar(Melee_creep1[j],(200-a_houyi.melee.HP[j])/2);
        
        
        if(b_houyi.melee.HP[j]<=0&&Melee_creep2[j]!=NULL)
        {
            this->removeChild(Melee_creep2[j]);
            Melee_creep2[j]=NULL;
            a_houyi.hero1.gold+=20;
            a_houyi.hero1.exp+=10;
        }
        if(b_houyi.range.HP[j]<=0&&Range_creep2[j]!=NULL)
        {
            this->removeChild(Range_creep2[j]);
            Range_creep2[j]=NULL;
            a_houyi.hero1.gold+=50;
            a_houyi.hero1.exp+=15;
        }
        if(b_houyi.catapult.HP[j]<=0&&Catapult2[j]!=NULL)
        {
            this->removeChild(Catapult2[j]);
            Catapult2[j]=NULL;
            a_houyi.hero1.gold+=50;
            a_houyi.hero1.exp+=20;
        }
    }
}

void gamescene_houyi::update_Melee_creep2_attack(float t)
{
    for(int j=0;j<creep_i;j++)
    {
        int X[9],Y[9],dis[9];
        for(int i=0;i<9;i++)
        {
            X[i]=100000;
            Y[i]=100000;
            dis[i]=1000000000;
        }
        if(b_houyi.melee.HP[j]>0)
        {
            if(a_houyi.melee.HP[j]>0)
            {
                X[0]=-Melee_creep1[j]->getPositionX()+Melee_creep2[j]->getPositionX();
                Y[0]=-Melee_creep1[j]->getPositionY()+Melee_creep2[j]->getPositionY();
                dis[0]=X[0]*X[0]+Y[0]*Y[0];
            }
            if(a_houyi.crystal.HP>0)
            {
                X[1]=-Melee_creep2[j]->getPositionX()+Crystal1->getPositionX();
                Y[1]=-Melee_creep2[j]->getPositionY()+Crystal1->getPositionY();
                dis[1]=X[1]*X[1]+Y[1]*Y[1];
            }
            if(a_houyi.tower.HP>0)
            {
                X[2]=-Melee_creep2[j]->getPositionX()+Tower1->getPositionX();
                Y[2]=-Melee_creep2[j]->getPositionY()+Tower1->getPositionY();
                dis[2]=X[2]*X[2]+Y[2]*Y[2];
            }
            if(a_houyi.range.HP[j]>0)
            {
                X[3]=-Melee_creep2[j]->getPositionX()+Range_creep1[j]->getPositionX();
                Y[3]=-Melee_creep2[j]->getPositionY()+Range_creep1[j]->getPositionY();
                dis[3]=X[3]*X[3]+Y[3]*Y[3];
            }
            if(a_houyi.catapult.HP[j]>0)
            {
                X[4]=-Melee_creep2[j]->getPositionX()+Catapult1[j]->getPositionX();
                Y[4]=-Melee_creep2[j]->getPositionY()+Catapult1[j]->getPositionY();
                dis[4]=X[4]*X[4]+Y[4]*Y[4];
            }
            if(j!=0)
            {
                if(a_houyi.melee.HP[j-1]>0)
                {
                    X[5]=-Melee_creep2[j]->getPositionX()+Melee_creep1[j-1]->getPositionX();
                    Y[5]=-Melee_creep2[j]->getPositionY()+Melee_creep1[j-1]->getPositionY();
                    dis[5]=X[5]*X[5]+Y[5]*Y[5];
                }
                if(a_houyi.range.HP[j-1]>0)
                {
                    X[6]=-Melee_creep2[j]->getPositionX()+Range_creep1[j-1]->getPositionX();
                    Y[6]=-Melee_creep2[j]->getPositionY()+Range_creep1[j-1]->getPositionY();
                    dis[6]=X[6]*X[6]+Y[6]*Y[6];
                }
                if(a_houyi.catapult.HP[j-1]>0)
                {
                    X[7]=-Melee_creep2[j]->getPositionX()+Catapult1[j-1]->getPositionX();
                    Y[7]=-Melee_creep2[j]->getPositionY()+Catapult1[j-1]->getPositionY();
                    dis[7]=X[7]*X[7]+Y[7]*Y[7];
                }
            }
            if(a_houyi.hero1.HP>0)
            {
                X[8]=-Melee_creep2[j]->getPositionX()+sprite->getPositionX();
                Y[8]=-Melee_creep2[j]->getPositionY()+sprite->getPositionY();
                dis[8]=X[8]*X[8]+Y[8]*Y[8];
            }
            int min_dis=1000000000;
            for(int i=0;i<9;i++)
            {
                if(dis[i]<min_dis)
                    min_dis=dis[i];
            }
            double time=sqrt(min_dis)/100;
            
            
            if(min_dis<=2500)
            {
                if(min_dis==dis[0])
                    a_houyi.melee.HP[j]-=20;
                else if(min_dis==dis[1])
                    a_houyi.crystal.HP-=20;
                else if(min_dis==dis[2])
                    a_houyi.tower.HP-=20;
                else if(min_dis==dis[3])
                    a_houyi.range.HP[j]-=20;
                else if(min_dis==dis[4])
                    a_houyi.catapult.HP[j]-=20;
                else if(min_dis==dis[5])
                    a_houyi.melee.HP[j-1]-=20;
                else if(min_dis==dis[6])
                    a_houyi.range.HP[j-1]-=20;
                else if(min_dis==dis[7])
                    a_houyi.catapult.HP[j-1]-=20;
                else if(min_dis==dis[8])
                    a_houyi.hero1.HP-=20;
                
            }
            else
            {
                for(int i=0;i<10;i++)
                {
                    if(min_dis==dis[i])
                    {
                        auto by=MoveBy::create(1, Vec2(-(abs(X[i])-50)/time,0));
                        Melee_creep2[j]->runAction(by);
                        break;
                    }
                }
            }
        }
        if(b_houyi.melee.HP[j]>0)
            this->getBloodbar(Melee_creep2[j],(200-a_houyi.melee.HP[j])/2);
        
        if(a_houyi.melee.HP[j]<=0&&Melee_creep1[j]!=NULL)
        {
            this->removeChild(Melee_creep1[j]);
            Melee_creep1[j]=NULL;
        }
        if(a_houyi.range.HP[j]<=0&&Range_creep1[j]!=NULL)
        {
            this->removeChild(Range_creep1[j]);
            Range_creep1[j]=NULL;
        }
        if(a_houyi.catapult.HP[j]<=0&&Catapult1[j]!=NULL)
        {
            this->removeChild(Catapult1[j]);
            Catapult1[j]=NULL;
        }
    }
}

void gamescene_houyi::update_Range_creep1_attack(float t)
{
    for(int j=0;j<creep_i;j++)
    {
        int X[9],Y[9],dis[9];
        for(int i=0;i<9;i++)
        {
            X[i]=100000;
            Y[i]=100000;
            dis[i]=1000000000;
        }
        if(a_houyi.range.HP[j]>0)
        {
            if(b_houyi.melee.HP[j]>0)
            {
                X[0]=-Range_creep1[j]->getPositionX()+Melee_creep2[j]->getPositionX();
                Y[0]=-Range_creep1[j]->getPositionY()+Melee_creep2[j]->getPositionY();
                dis[0]=X[0]*X[0]+Y[0]*Y[0];
            }
            if(b_houyi.crystal.HP>0)
            {
                X[1]=-Range_creep1[j]->getPositionX()+Crystal2->getPositionX();
                Y[1]=-Range_creep1[j]->getPositionY()+Crystal2->getPositionY();
                dis[1]=X[1]*X[1]+Y[1]*Y[1];
            }
            if(b_houyi.tower.HP>0)
            {
                X[2]=-Range_creep1[j]->getPositionX()+Tower2->getPositionX();
                Y[2]=-Range_creep1[j]->getPositionY()+Tower2->getPositionY();
                dis[2]=X[2]*X[2]+Y[2]*Y[2];
            }
            if(b_houyi.range.HP[j]>0)
            {
                X[3]=-Range_creep1[j]->getPositionX()+Range_creep2[j]->getPositionX();
                Y[3]=-Range_creep1[j]->getPositionY()+Range_creep2[j]->getPositionY();
                dis[3]=X[3]*X[3]+Y[3]*Y[3];
            }
            if(b_houyi.catapult.HP[j]>0)
            {
                X[4]=-Range_creep1[j]->getPositionX()+Catapult2[j]->getPositionX();
                Y[4]=-Range_creep1[j]->getPositionY()+Catapult2[j]->getPositionY();
                dis[4]=X[4]*X[4]+Y[4]*Y[4];
            }
            if(j!=0)
            {
                if(b_houyi.melee.HP[j-1]>0)
                {
                    X[5]=-Range_creep1[j]->getPositionX()+Melee_creep2[j-1]->getPositionX();
                    Y[5]=-Range_creep1[j]->getPositionY()+Melee_creep2[j-1]->getPositionY();
                    dis[5]=X[5]*X[5]+Y[5]*Y[5];
                }
                if(b_houyi.range.HP[j-1]>0)
                {
                    X[6]=-Range_creep1[j]->getPositionX()+Range_creep2[j-1]->getPositionX();
                    Y[6]=-Range_creep1[j]->getPositionY()+Range_creep2[j-1]->getPositionY();
                    dis[6]=X[6]*X[6]+Y[6]*Y[6];
                }
                if(b_houyi.catapult.HP[j-1]>0)
                {
                    X[7]=-Range_creep1[j]->getPositionX()+Catapult2[j-1]->getPositionX();
                    Y[7]=-Range_creep1[j]->getPositionY()+Catapult2[j-1]->getPositionY();
                    dis[7]=X[7]*X[7]+Y[7]*Y[7];
                }
            }
            if(b_houyi.hero1.HP>0)
            {
                X[8]=-Range_creep1[j]->getPositionX()+ai->getPositionX();
                Y[8]=-Range_creep1[j]->getPositionY()+ai->getPositionY();
                dis[8]=X[8]*X[8]+Y[8]*Y[8];
            }
            
            int min_dis=1000000000;
            for(int i=0;i<9;i++)
            {
                if(dis[i]<min_dis)
                    min_dis=dis[i];
            }
            double time=sqrt(min_dis)/100;
            
            
            if(min_dis<=90000)
            {
                if(min_dis==dis[0])
                    b_houyi.melee.HP[j]-=30;
                else if(min_dis==dis[1])
                    b_houyi.crystal.HP-=30;
                else if(min_dis==dis[2])
                    b_houyi.tower.HP-=30;
                else if(min_dis==dis[3])
                    b_houyi.range.HP[j]-=30;
                else if(min_dis==dis[4])
                    b_houyi.catapult.HP[j]-=30;
                else if(min_dis==dis[5])
                    b_houyi.melee.HP[j-1]-=30;
                else if(min_dis==dis[6])
                    b_houyi.range.HP[j-1]-=30;
                else if(min_dis==dis[7])
                    b_houyi.catapult.HP[j-1]-=30;
                else if(min_dis==dis[8])
                    b_houyi.hero1.HP-=30;
            }
            else
            {
                for(int i=0;i<10;i++)
                {
                    if(min_dis==dis[i])
                    {
                        auto by=MoveBy::create(1, Vec2((abs(X[i])-50)/time,0));
                        Range_creep1[j]->runAction(by);
                        break;
                    }
                }
            }
        }
        
        if(a_houyi.range.HP[j]>0)
            this->getBloodbar(Range_creep1[j],100-a_houyi.range.HP[j]);
        
        if(b_houyi.melee.HP[j]<=0 && Melee_creep2[j]!=NULL)
        {
            this->removeChild(Melee_creep2[j]);
            Melee_creep2[j]=NULL;
            a_houyi.hero1.gold+=20;
            a_houyi.hero1.exp+=10;
        }
        if(b_houyi.range.HP[j]<=0 && Range_creep2[j]!=NULL)
        {
            this->removeChild(Range_creep2[j]);
            Range_creep2[j]=NULL;
            a_houyi.hero1.gold+=50;
            a_houyi.hero1.exp+=15;
        }
        if(b_houyi.catapult.HP[j]<=0 && Catapult2[j]!=NULL)
        {
            this->removeChild(Catapult2[j]);
            Catapult2[j]=NULL;
            a_houyi.hero1.gold+=50;
            a_houyi.hero1.exp+=15;
        }
    }
}

void gamescene_houyi::update_Range_creep2_attack(float t)
{
    for(int j=0;j<creep_i;j++)
    {
        int X[9],Y[9],dis[9];
        for(int i=0;i<9;i++)
        {
            X[i]=100000;
            Y[i]=100000;
            dis[i]=1000000000;
        }
        if(b_houyi.range.HP[j]>0)
        {
            if(a_houyi.melee.HP[j]>0)
            {
                X[0]=-Melee_creep1[j]->getPositionX()+Range_creep2[j]->getPositionX();
                Y[0]=-Melee_creep1[j]->getPositionY()+Range_creep2[j]->getPositionY();
                dis[0]=X[0]*X[0]+Y[0]*Y[0];
            }
            if(a_houyi.crystal.HP>0)
            {
                X[1]=-Range_creep2[j]->getPositionX()+Crystal1->getPositionX();
                Y[1]=-Range_creep2[j]->getPositionY()+Crystal1->getPositionY();
                dis[1]=X[1]*X[1]+Y[1]*Y[1];
            }
            if(a_houyi.tower.HP>0)
            {
                X[2]=-Range_creep2[j]->getPositionX()+Tower1->getPositionX();
                Y[2]=-Range_creep2[j]->getPositionY()+Tower1->getPositionY();
                dis[2]=X[2]*X[2]+Y[2]*Y[2];
            }
            if(a_houyi.range.HP[j]>0)
            {
                X[3]=-Range_creep2[j]->getPositionX()+Range_creep1[j]->getPositionX();
                Y[3]=-Range_creep2[j]->getPositionY()+Range_creep1[j]->getPositionY();
                dis[3]=X[3]*X[3]+Y[3]*Y[3];
            }
            if(a_houyi.catapult.HP[j]>0)
            {
                X[4]=-Range_creep2[j]->getPositionX()+Catapult1[j]->getPositionX();
                Y[4]=-Range_creep2[j]->getPositionY()+Catapult1[j]->getPositionY();
                dis[4]=X[4]*X[4]+Y[4]*Y[4];
            }
            if(j!=0)
            {
                if(a_houyi.melee.HP[j-1]>0)
                {
                    X[5]=-Range_creep2[j]->getPositionX()+Melee_creep1[j-1]->getPositionX();
                    Y[5]=-Range_creep2[j]->getPositionY()+Melee_creep1[j-1]->getPositionY();
                    dis[5]=X[5]*X[5]+Y[5]*Y[5];
                }
                if(a_houyi.range.HP[j-1]>0)
                {
                    X[6]=-Range_creep2[j]->getPositionX()+Range_creep1[j-1]->getPositionX();
                    Y[6]=-Range_creep2[j]->getPositionY()+Range_creep1[j-1]->getPositionY();
                    dis[6]=X[6]*X[6]+Y[6]*Y[6];
                }
                if(a_houyi.catapult.HP[j-1]>0)
                {
                    X[7]=-Range_creep2[j]->getPositionX()+Catapult1[j-1]->getPositionX();
                    Y[7]=-Range_creep2[j]->getPositionY()+Catapult1[j-1]->getPositionY();
                    dis[7]=X[7]*X[7]+Y[7]*Y[7];
                }
            }
            if(a_houyi.hero1.HP > 0)
            {
                X[8]=-Range_creep2[j]->getPositionX()+sprite->getPositionX();
                Y[8]=-Range_creep2[j]->getPositionY()+sprite->getPositionY();
                dis[8]=X[8]*X[8]+Y[8]*Y[8];
            }
            
            int min_dis=1000000000;
            for(int i=0;i<5;i++)
            {
                if(dis[i]<min_dis)
                    min_dis=dis[i];
            }
            double time=sqrt(min_dis)/100;
            
            
            if(min_dis<=90000)
            {
                if(min_dis==dis[0])
                    a_houyi.melee.HP[j]-=30;
                else if(min_dis==dis[1])
                    a_houyi.crystal.HP-=30;
                else if(min_dis==dis[2])
                    a_houyi.tower.HP-=30;
                else if(min_dis==dis[3])
                    a_houyi.range.HP[j]-=30;
                else if(min_dis==dis[4])
                    a_houyi.catapult.HP[j]-=30;
                else if(min_dis==dis[5])
                    a_houyi.melee.HP[j-1]-=30;
                else if(min_dis==dis[6])
                    a_houyi.range.HP[j-1]-=30;
                else if(min_dis==dis[7])
                    a_houyi.catapult.HP[j-1]-=30;
                else if(min_dis==dis[8])
                    a_houyi.hero1.HP-=30;
            }
            else
            {
                for(int i=0;i<10;i++)
                {
                    if(min_dis==dis[i])
                    {
                        auto by=MoveBy::create(1, Vec2(-(abs(X[i])-50)/time,0));
                        Range_creep2[j]->runAction(by);
                        break;
                    }
                }

            }
        }
        
        if(b_houyi.range.HP[j]>0)
            this->getBloodbar(Range_creep2[j],100-b_houyi.range.HP[j]);
        
        if(a_houyi.melee.HP[j]<=0 && Melee_creep1[j]!=NULL)
        {
            this->removeChild(Melee_creep1[j]);
            Melee_creep1[j]=NULL;
        }
        
        if(a_houyi.range.HP[j]<=0 && Range_creep1[j]!=NULL)
        {
            this->removeChild(Range_creep1[j]);
            Range_creep1[j]=NULL;
        }
        if(a_houyi.catapult.HP[j]<=0 && Catapult1[j]!=NULL)
        {
            this->removeChild(Catapult1[j]);
            Catapult1[j]=NULL;
        }
    }
}

void gamescene_houyi::update_Catapult1_attack(float t)
{
    for(int j=0;j<creep_i;j++)
    {
        int X[9],Y[9],dis[9];
        for(int i=0;i<9;i++)
        {
            X[i]=100000;
            Y[i]=100000;
            dis[i]=1000000000;
        }
        if(a_houyi.catapult.HP[j]>0)
        {
            if(b_houyi.melee.HP[j]>0)
            {
                X[0]=-Catapult1[j]->getPositionX()+Melee_creep2[j]->getPositionX();
                Y[0]=-Catapult1[j]->getPositionY()+Melee_creep2[j]->getPositionY();
                dis[0]=X[0]*X[0]+Y[0]*Y[0];
            }
            if(b_houyi.crystal.HP>0)
            {
                X[1]=-Catapult1[j]->getPositionX()+Crystal2->getPositionX();
                Y[1]=-Catapult1[j]->getPositionY()+Crystal2->getPositionY();
                dis[1]=X[1]*X[1]+Y[1]*Y[1];
            }
            if(b_houyi.tower.HP>0)
            {
                X[2]=-Catapult1[j]->getPositionX()+Tower2->getPositionX();
                Y[2]=-Catapult1[j]->getPositionY()+Tower2->getPositionY();
                dis[2]=X[2]*X[2]+Y[2]*Y[2];
            }
            if(b_houyi.range.HP[j]>0)
            {
                X[3]=-Catapult1[j]->getPositionX()+Range_creep2[j]->getPositionX();
                Y[3]=-Catapult1[j]->getPositionY()+Range_creep2[j]->getPositionY();
                dis[3]=X[3]*X[3]+Y[3]*Y[3];
            }
            if(b_houyi.catapult.HP[j]>0)
            {
                X[4]=-Catapult1[j]->getPositionX()+Catapult2[j]->getPositionX();
                Y[4]=-Catapult1[j]->getPositionY()+Catapult2[j]->getPositionY();
                dis[4]=X[4]*X[4]+Y[4]*Y[4];
            }
            if(j!=0)
            {
                if(b_houyi.melee.HP[j-1]>0)
                {
                    X[5]=-Catapult1[j]->getPositionX()+Melee_creep2[j-1]->getPositionX();
                    Y[5]=-Catapult1[j]->getPositionY()+Melee_creep2[j-1]->getPositionY();
                    dis[5]=X[5]*X[5]+Y[5]*Y[5];
                }
                if(b_houyi.range.HP[j-1]>0)
                {
                    X[6]=-Catapult1[j]->getPositionX()+Range_creep2[j-1]->getPositionX();
                    Y[6]=-Catapult1[j]->getPositionY()+Range_creep2[j-1]->getPositionY();
                    dis[6]=X[6]*X[6]+Y[6]*Y[6];
                }
                if(b_houyi.catapult.HP[j-1]>0)
                {
                    X[7]=-Catapult1[j]->getPositionX()+Catapult2[j-1]->getPositionX();
                    Y[7]=-Catapult1[j]->getPositionY()+Catapult2[j-1]->getPositionY();
                    dis[7]=X[7]*X[7]+Y[7]*Y[7];
                }
            }
            if(b_houyi.hero1.HP > 0)
            {
                X[8]=-Catapult1[j]->getPositionX()+ai->getPositionX();
                Y[8]=-Catapult1[j]->getPositionY()+ai->getPositionY();
                dis[8]=X[8]*X[8]+Y[8]*Y[8];
            }
            int min_dis=1000000000;
            for(int i=0;i<9;i++)
            {
                if(dis[i]<min_dis)
                    min_dis=dis[i];
            }
            double time=sqrt(min_dis)/100;
            
            
            if(min_dis<=160000)
            {
                if(min_dis==dis[0])
                    b_houyi.melee.HP[j]-=20;
                else if(min_dis==dis[1])
                    b_houyi.crystal.HP-=50;
                else if(min_dis==dis[2])
                    b_houyi.tower.HP-=50;
                else if(min_dis==dis[3])
                    b_houyi.range.HP[j]-=20;
                else if(min_dis==dis[4])
                    b_houyi.catapult.HP[j]-=20;
                else if(min_dis==dis[5])
                    b_houyi.melee.HP[j-1]-=20;
                else if(min_dis==dis[6])
                    b_houyi.range.HP[j-1]-=20;
                else if(min_dis==dis[7])
                    b_houyi.catapult.HP[j-1]-=20;
                else if(min_dis==dis[8])
                    b_houyi.hero1.HP-=20;
            }
            else
            {
                for(int i=0;i<10;i++)
                {
                    if(min_dis==dis[i])
                    {
                        auto by=MoveBy::create(1, Vec2((abs(X[i])-50)/time,0));
                        Catapult1[j]->runAction(by);
                        break;
                    }
                }
            }
        }
        
        if(a_houyi.catapult.HP[j]>0)
            this->getBloodbar(Catapult1[j],(150-a_houyi.catapult.HP[j])/1.5);
            
        if(b_houyi.melee.HP[j]<=0 && Melee_creep2[j]!=NULL)
        {
            this->removeChild(Melee_creep2[j]);
            Melee_creep2[j]=NULL;
            a_houyi.hero1.gold+=20;
            a_houyi.hero1.exp+=10;
        }
        if(b_houyi.range.HP[j]<=0 && Range_creep2[j]!=NULL)
        {
            this->removeChild(Range_creep2[j]);
            Range_creep2[j]=NULL;
            a_houyi.hero1.gold+=50;
            a_houyi.hero1.exp+=15;
        }
        if(b_houyi.catapult.HP[j]<=0 && Catapult2[j]!=NULL)
        {
            this->removeChild(Catapult2[j]);
            Catapult2[j]=NULL;
            a_houyi.hero1.gold+=50;
            a_houyi.hero1.exp+=15;
        }
    }
}

void gamescene_houyi::update_Catapult2_attack(float t)
{
    for(int j=0;j<creep_i;j++)
    {
        int X[9],Y[9],dis[9];
        for(int i=0;i<9;i++)
        {
            X[i]=100000;
            Y[i]=100000;
            dis[i]=1000000000;
        }
        if(b_houyi.catapult.HP[j]>0)
        {
            if(a_houyi.melee.HP[j]>0)
            {
                X[0]=-Melee_creep1[j]->getPositionX()+Catapult2[j]->getPositionX();
                Y[0]=-Melee_creep1[j]->getPositionY()+Catapult2[j]->getPositionY();
                dis[0]=X[0]*X[0]+Y[0]*Y[0];
            }
            if(a_houyi.crystal.HP>0)
            {
                X[1]=-Catapult2[j]->getPositionX()+Crystal1->getPositionX();
                Y[1]=-Catapult2[j]->getPositionY()+Crystal1->getPositionY();
                dis[1]=X[1]*X[1]+Y[1]*Y[1];
            }
            if(a_houyi.tower.HP>0)
            {
                X[2]=-Catapult2[j]->getPositionX()+Tower1->getPositionX();
                Y[2]=-Catapult2[j]->getPositionY()+Tower1->getPositionY();
                dis[2]=X[2]*X[2]+Y[2]*Y[2];
            }
            if(a_houyi.range.HP[j]>0)
            {
                X[3]=-Catapult2[j]->getPositionX()+Range_creep1[j]->getPositionX();
                Y[3]=-Catapult2[j]->getPositionY()+Range_creep1[j]->getPositionY();
                dis[3]=X[3]*X[3]+Y[3]*Y[3];
            }
            if(a_houyi.catapult.HP[j]>0)
            {
                X[4]=-Catapult2[j]->getPositionX()+Catapult1[j]->getPositionX();
                Y[4]=-Catapult2[j]->getPositionY()+Catapult1[j]->getPositionY();
                dis[4]=X[4]*X[4]+Y[4]*Y[4];
            }
            if(j!=0)
            {
                if(a_houyi.melee.HP[j-1]>0)
                {
                    X[5]=-Catapult2[j]->getPositionX()+Melee_creep1[j-1]->getPositionX();
                    Y[5]=-Catapult2[j]->getPositionY()+Melee_creep1[j-1]->getPositionY();
                    dis[5]=X[5]*X[5]+Y[5]*Y[5];
                }
                if(a_houyi.range.HP[j-1]>0)
                {
                    X[6]=-Catapult2[j]->getPositionX()+Range_creep1[j-1]->getPositionX();
                    Y[6]=-Catapult2[j]->getPositionY()+Range_creep1[j-1]->getPositionY();
                    dis[6]=X[6]*X[6]+Y[6]*Y[6];
                }
                if(a_houyi.catapult.HP[j-1]>0)
                {
                    X[7]=-Catapult2[j]->getPositionX()+Catapult1[j-1]->getPositionX();
                    Y[7]=-Catapult2[j]->getPositionY()+Catapult1[j-1]->getPositionY();
                    dis[7]=X[7]*X[7]+Y[7]*Y[7];
                }
            }
            if(a_houyi.hero1.HP > 0)
            {
                X[8]=-Catapult2[j]->getPositionX()+sprite->getPositionX();
                Y[8]=-Catapult2[j]->getPositionY()+sprite->getPositionY();
                dis[8]=X[8]*X[8]+Y[8]*Y[8];
            }
            
            int min_dis=1000000000;
            for(int i=0;i<5;i++)
            {
                if(dis[i]<min_dis)
                    min_dis=dis[i];
            }
            double time=sqrt(min_dis)/100;
            
            
            if(min_dis<=160000)
            {
                if(min_dis==dis[0])
                    a_houyi.melee.HP[j]-=20;
                else if(min_dis==dis[1])
                    a_houyi.crystal.HP-=50;
                else if(min_dis==dis[2])
                    a_houyi.tower.HP-=50;
                else if(min_dis==dis[3])
                    a_houyi.range.HP[j]-=20;
                else if(min_dis==dis[4])
                    a_houyi.catapult.HP[j]-=20;
                else if(min_dis==dis[5])
                    a_houyi.melee.HP[j-1]-=20;
                else if(min_dis==dis[6])
                    a_houyi.range.HP[j-1]-=20;
                else if(min_dis==dis[7])
                    a_houyi.catapult.HP[j-1]-=20;
                else if(min_dis==dis[8])
                    a_houyi.hero1.HP-=20;
            }
            else
            {
                for(int i=0;i<10;i++)
                {
                    if(min_dis==dis[i])
                    {
                        auto by=MoveBy::create(1, Vec2(-(abs(X[i])-50)/time,0));
                        Catapult2[j]->runAction(by);
                        break;
                    }
                }
                
            }
        }
        
        if(b_houyi.catapult.HP[j]>0)
            this->getBloodbar(Catapult2[j],(150-b_houyi.catapult.HP[j])/1.5);
        
        if(a_houyi.melee.HP[j]<=0 && Melee_creep1[j]!=NULL)
        {
            this->removeChild(Melee_creep1[j]);
            Melee_creep1[j]=NULL;
        }
        
        if(a_houyi.range.HP[j]<=0 && Range_creep1[j]!=NULL)
        {
            this->removeChild(Range_creep1[j]);
            Range_creep1[j]=NULL;
        }
        if(a_houyi.catapult.HP[j]<=0 && Catapult1[j]!=NULL)
        {
            this->removeChild(Catapult1[j]);
            Catapult1[j]=NULL;
        }
    }
}

void gamescene_houyi::update_tower1_attack(float t)
{
    bool attack_flag=false;
    int dis_ai=1000000;
    if(a_houyi.tower.HP>0)
    {
        for(int j=0;j<creep_i;j++)
        {
            int dis_Melee_creep=1000000,dis_hero=1000000;
            if(flag_creep==true)
            {
                if(b_houyi.melee.HP[j]>0&&attack_flag==false)
                {
                    dis_Melee_creep=abs(Tower1->getPositionX()-Melee_creep2[j]->getPositionX());
                    
                    if(dis_Melee_creep<300)
                    {
                        attack_flag=true;
                        pb=Sprite::create("PB01.png");
                        pb->setPosition(Tower1->getPositionX(),Tower1->getPositionY()+50);
                        this->addChild(pb);
                        auto to=MoveTo::create(0.2,Vec2(Melee_creep2[j]->getPositionX(),Melee_creep2[j]->getPositionY()));
                        auto hide=Hide::create();
                        pb->runAction(CCSequence::create(to,hide,NULL));
                        b_houyi.melee.HP[j]-=a_houyi.tower.base_damage;
                        
                    }
                }
                if(b_houyi.range.HP[j]>0&&attack_flag==false)
                {
                    dis_Melee_creep=abs(Tower1->getPositionX()-Range_creep2[j]->getPositionX());
                    if(dis_Melee_creep<300)
                    {
                        attack_flag=true;
                        pb=Sprite::create("PB01.png");
                        pb->setPosition(Tower1->getPositionX(),Tower1->getPositionY()+50);
                        this->addChild(pb);
                        auto to=MoveTo::create(0.2,Vec2(Range_creep2[j]->getPositionX(),Range_creep2[j]->getPositionY()));
                        auto hide=Hide::create();
                        pb->runAction(CCSequence::create(to,hide,NULL));
                        b_houyi.range.HP[j]-=a_houyi.tower.base_damage;
                        
                    }
                }
                if(b_houyi.catapult.HP[j]>0&&attack_flag==false)
                {
                    dis_Melee_creep=abs(Tower1->getPositionX() -Catapult2[j]->getPositionX());
                    if(dis_Melee_creep<300)
                    {
                        attack_flag=true;
                        pb=Sprite::create("PB01.png");
                        pb->setPosition(Tower1->getPositionX(),Tower1->getPositionY()+50);
                        this->addChild(pb);
                        auto to=MoveTo::create(0.2,Vec2(Catapult2[j]->getPositionX(),Catapult2[j]->getPositionY()));
                        auto hide=Hide::create();
                        pb->runAction(CCSequence::create(to,hide,NULL));
                        b_houyi.catapult.HP[j]-=a_houyi.tower.base_damage;
                        
                    }
                }
                if(b_houyi.hero1.HP>0&&attack_flag==false)
                {
                    dis_Melee_creep=abs(Tower1->getPositionX()-ai->getPositionX());
                    if(dis_Melee_creep<300)
                    {
                        attack_flag=true;
                        pb=Sprite::create("PB01.png");
                        pb->setPosition(Tower1->getPositionX(),Tower1->getPositionY()+50);
                        this->addChild(pb);
                        auto to=MoveTo::create(0.2,Vec2(ai->getPositionX(),ai->getPositionY()));
                        auto hide=Hide::create();
                        pb->runAction(CCSequence::create(to,hide,NULL));
                        b_houyi.hero1.HP-=a_houyi.tower.base_damage;
                    }
                }
                
            }
        
        
            if(b_houyi.melee.HP[j]<=0 && Melee_creep2[j]!=NULL)
            {
                this->removeChild(Melee_creep2[j]);
                Melee_creep2[j]=NULL;
                a_houyi.hero1.gold+=20;
                a_houyi.hero1.exp+=10;
            }
            if(b_houyi.range.HP[j]<=0 && Range_creep2[j]!=NULL)
            {
                this->removeChild(Range_creep2[j]);
                Range_creep2[j]=NULL;
                a_houyi.hero1.gold+=50;
                a_houyi.hero1.exp+=15;
            }
            if(b_houyi.catapult.HP[j]<=0 && Catapult2[j]!=NULL)
            {
                this->removeChild(Catapult2[j]);
                Catapult2[j]=NULL;
                a_houyi.hero1.gold+=50;
                a_houyi.hero1.exp+=20;
            }
        }
    }
}

void gamescene_houyi::update_tower2_attack(float t)
{
	bool attack_flag = false;
	int dis_hero = 1000000;
	if (b_houyi.tower.HP > 0)
	{
		for (int j = 0; j < creep_i; j++)
		{

			int dis_Melee_creep = 1000000, dis_Range_creep = 1000000, dis_Catapult = 1000000;

			if (flag_creep == true)
			{
				if (a_houyi.melee.HP[j] > 0 && attack_flag == false)
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
						a_houyi.melee.HP[j] -= b_houyi.tower.base_damage;

					}
				}
				if (a_houyi.range.HP[j] > 0 && attack_flag == false)
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
						a_houyi.range.HP[j] -= b_houyi.tower.base_damage;

					}
				}
				if (a_houyi.catapult.HP[j] > 0 && attack_flag == false)
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
						a_houyi.catapult.HP[j] -= b_houyi.tower.base_damage;

					}
				}
				if (a_houyi.hero1.HP > 0 && attack_flag == false)
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
						a_houyi.hero1.HP -= b_houyi.tower.base_damage;
					}
				}
			}
		}
		if (a_houyi.hero1.HP > 0 && attack_flag == false)
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
				a_houyi.hero1.HP -= b_houyi.tower.base_damage;
			}
		}
	}
}

void gamescene_houyi::update_ai(float t)
{
    if(b_houyi.hero1.HP>b_houyi.hero1.HP_max/2)
    {
        int dis[15];
        int min_dis=100000;
        int flag=std::min(4,creep_i);
        Sprite *target;
        for(int i=0;i<15;i++)
            dis[i]=10000;
        for(int i=0;i<flag;i++)
        {
            if(Melee_creep1[creep_i-i-1]!=NULL)
            {
                dis[i]=abs(ai->getPositionX()-Melee_creep1[creep_i-i-1]->getPositionX());
            }
            if(Range_creep1[creep_i-i-1]!=NULL)
                dis[i+4]=abs(ai->getPositionX()-Range_creep1[creep_i-i-1]->getPositionX());
            if(Catapult1[creep_i-i-1]!=NULL)
                dis[i+8]=abs(ai->getPositionX()-Catapult1[creep_i-i-1]->getPositionX());
            if(dis[i]<min_dis)
            {
                min_dis=dis[i];
                target=Melee_creep1[creep_i-i-1];
            }
            if(dis[i+4]<min_dis)
            {
                min_dis=dis[i];
                target=Range_creep1[creep_i-i-1];
            }
            if(dis[i+8]<min_dis)
            {
                min_dis=dis[i];
                target=Catapult1[creep_i-i-1];
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
        if(min_dis<=100)
        {
            if(target==sprite)
                a_houyi.hero1.HP-=b_houyi.hero1.base_damage;
            else if(target==Tower1)
                a_houyi.tower.HP-=b_houyi.hero1.base_damage;
            else if(target==Crystal1)
                a_houyi.crystal.HP-=b_houyi.hero1.base_damage;
            else
            {
                for(int i=0;i<4;i++)
                {
                    if(target==Melee_creep1[creep_i-i-1])
                        a_houyi.melee.HP[creep_i-i-1]-=b_houyi.hero1.base_damage;
                    else if(target==Range_creep1[creep_i-i-1])
                        a_houyi.range.HP[creep_i-i-1]-=b_houyi.hero1.base_damage;
                    else if(target==Catapult1[creep_i-i-1])
                        a_houyi.catapult.HP[creep_i-i-1]-=b_houyi.hero1.base_damage;
                }
            }
        }
        else
        {
            auto by=MoveBy::create(1,Vec2(-100,0));
            ai->runAction(by);
        }
    }
    else if(b_houyi.hero1.HP>0)
    {
        int x=Crystal2->getPositionX()+500-ai->getPositionX();
        int X=std::min(x,100);
        auto by=MoveBy::create(1,Vec2(X,0));
        ai->runAction(by);
    }
    else
    {
        this->removeChild(ai);
        ai=NULL;
    }
}

void gamescene_houyi::update_heroHP(float t)
{
    if(b_houyi.tower.HP>0)
        this->getBloodbar(Tower2,(1000-b_houyi.tower.HP)/10);
    else if(Tower2!=NULL)
    {
        this->removeChild(Tower2);
        Tower2=NULL;
        a_houyi.hero1.gold+=200;
    }
    if(a_houyi.tower.HP>0)
        this->getBloodbar(Tower1,(1000-a_houyi.tower.HP)/10);
    else if(Tower1!=NULL)
    {
        this->removeChild(Tower1);
        Tower1=NULL;
    }
    if(a_houyi.hero1.HP>0)
        this->getBloodbar(sprite,(a_houyi.hero1.HP_max-a_houyi.hero1.HP)/(a_houyi.hero1.HP_max/100));
    else if(sprite!=NULL)
    {
        this->removeChild(sprite);
        sprite=NULL;
        flag_heroalive=false;
    }
    if(b_houyi.hero1.HP>0)
        this->getBloodbar(ai,(b_houyi.hero1.HP_max-b_houyi.hero1.HP)/(b_houyi.hero1.HP_max/100));
    else if(ai!=NULL)
    {
        this->removeChild(ai);
        ai=NULL;
    }
    if(a_houyi.crystal.HP>0)
        this->getBloodbar(Crystal1, (3000-a_houyi.crystal.HP)/30);
	else if (Crystal1 != nullptr)
	{
		this->removeChild(Crystal1);
		Crystal1 = nullptr;
	}
    if(b_houyi.crystal.HP>0)
        this->getBloodbar(Crystal2, (3000-b_houyi.crystal.HP)/30);
    else if(Crystal2!=nullptr)
    {
        this->removeChild(Crystal2);
        Crystal2=nullptr;
    }
    if(sprite!=NULL&&Crystal1 != nullptr)
    {
        if(sprite->getPositionX()<Crystal1->getPositionX()-300)
        {
            if(a_houyi.hero1.HP<a_houyi.hero1.HP_max)
                a_houyi.hero1.HP+=a_houyi.hero1.HP_max/50;
            else if(a_houyi.hero1.HP>a_houyi.hero1.HP_max)
                a_houyi.hero1.HP=a_houyi.hero1.HP_max;
            this->getBloodbar1(sprite, (a_houyi.hero1.HP_max-a_houyi.hero1.HP)/(a_houyi.hero1.HP_max/100));
        }
    }
    if(ai!=NULL&&Crystal2 != nullptr)
    {
        if(ai->getPositionX()>Crystal2->getPositionX()+300)
        {
            if(b_houyi.hero1.HP<b_houyi.hero1.HP_max)
                b_houyi.hero1.HP+=b_houyi.hero1.HP_max/50;
            else if(b_houyi.hero1.HP>b_houyi.hero1.HP_max)
                b_houyi.hero1.HP=b_houyi.hero1.HP_max;
            this->getBloodbar1(ai, (b_houyi.hero1.HP_max-b_houyi.hero1.HP)/(b_houyi.hero1.HP_max/100));
        }
    }
}

void gamescene_houyi::hero_Attack()
{
    this->unschedule(schedule_selector(gamescene_houyi::boundingbox_update1));
    this->schedule(schedule_selector(gamescene_houyi::boundingbox_update1),0.1);
}

void gamescene_houyi::boundingbox_update1(float t)
{
    if(sprite!= nullptr && flag_sprite!= nullptr && cd_ability3==false)
    {
        if(sprite->boundingBox().intersectsRect(flag_sprite->boundingBox()))
        {
            attack_flag++;
            if(attack_flag%10==0)
            {
                for(int i=0;i<creep_i;i++)
                {
                    if(flag_sprite==Melee_creep2[i])
                    {
						b_houyi.melee.HP[i] -= a_houyi.hero1.base_damage;
                        if(b_houyi.melee.HP[i]<=0)
                            flag_sprite=NULL;
                    }
                    else if(flag_sprite==Range_creep2[i])
                    {
                        b_houyi.range.HP[i]-=a_houyi.hero1.base_damage;
                        if(b_houyi.range.HP[i]<=0)
                            flag_sprite=NULL;
                    }
                    else if(flag_sprite==Catapult2[i])
                    {
                        b_houyi.catapult.HP[i]-=a_houyi.hero1.base_damage;
                        if(b_houyi.catapult.HP[i]<=0)
                            flag_sprite=NULL;
                    }
                }
                if(flag_sprite==ai)
                {
                    b_houyi.hero1.HP-=a_houyi.hero1.base_damage ;
                    if(b_houyi.hero1.HP<0)
                        flag_sprite=NULL;
                }
                if(flag_sprite==Tower2)
                {
                    b_houyi.tower.HP-=a_houyi.hero1.base_damage;
                    if(b_houyi.tower.HP<=0)
                        flag_sprite=NULL;
                }
                else if(flag_sprite==Crystal2)
                {
                    b_houyi.crystal.HP-=a_houyi.hero1.base_damage;
                    if(b_houyi.crystal.HP<=0)
                        flag_sprite=NULL;
                }
            }
        }
    }
    if(flag_sprite==NULL)
        hero_attack_target=false;
}

//计算两者距离
float gamescene_houyi::Distance(Sprite * A, Sprite * B)
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