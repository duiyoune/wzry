//
//  gamescene.cpp
//  SimpleGame
//
//  Created by 陈子杰 on 2019/5/12.
//
#include <iostream>
#include "gamescene_houyi.hpp"
#include "scene1.h"
#include <math.h>
#include "attr_init.hpp"


Scene*scene::gamescene()
{
    auto scene=Scene::create();
    auto layer_game=gamescene_houyi::create();
    auto layer_equipment=equipmentscene::create();;
    scene->addChild(layer_game);
    scene->addChild(layer_equipment);
    return scene;
    
}


bool gamescene_houyi::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    a.init();
    b.init();
    flag_creep=false;
    std::cout<<a.hero1.HP<<std::endl;

    
    sprite=Sprite::create("houyi.png");
    sprite->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(sprite,0);
    
    auto listener= EventListenerMouse::create();
    listener->onMouseDown=CC_CALLBACK_1(gamescene_houyi::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
//    auto to=MoveTo::create(2, Vec2(500,visibleSize.height/2));
//    sprite->runAction(to);
    
    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("tower-0001-default.plist");
    
    auto frame_tower1=SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("tower1.jpg");
    Tower1=Sprite::createWithSpriteFrame(frame_tower1);
    Tower1->setPosition(1700,visibleSize.height/2);
    this->addChild(Tower1,1);
    
    auto frame_tower2=SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("tower2.jpg");
    Tower2=Sprite::createWithSpriteFrame(frame_tower2);
    Tower2->setPosition(2500,visibleSize.height/2);
    this->addChild(Tower2,1);

    
    auto frame_crystal1=SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("crystal1.jpg");
    Crystal1=Sprite::createWithSpriteFrame(frame_crystal1);
    Crystal1->setPosition(800,visibleSize.height/2);
    this->addChild(Crystal1,1);
    
    
    auto frame_crystal2=SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("crystal2.jpg");
    Crystal2=Sprite::createWithSpriteFrame(frame_crystal2);
    Crystal2->setPosition(3300,visibleSize.height/2);
    this->addChild(Crystal2,1);

 
    
    
    this->schedule(schedule_selector(gamescene_houyi::update_creep1),15);
//    this->schedule(schedule_selector(gamescene_houyi::update_creep2),30,-1,15);
//    this->schedule(schedule_selector(gamescene_houyi::update_creep3),30,-1,22.5);
//    this->schedule(schedule_selector(gamescene_houyi::update_creep4),30,-1,30);
    
    
    this->schedule(schedule_selector(gamescene_houyi::update_tower2_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_tower1_attack),1);
    
    
    return true;
}


bool equipmentscene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto test=Sprite::create("Peashooter1.tiff");
    test->setPosition(50,visibleSize.height/2);
    this->addChild(test,6);
    

    auto hongbaoshi=MenuItemImage::create("hongbaoshi.jpg","hongbaoshi.jpg","hongbaoshi.jpg");
    hongbaoshi->setTarget(this,menu_selector(equipmentscene::item_hongbaoshi));
    hongbaoshi->setPosition(0,0);
    
    auto menu=Menu::create(hongbaoshi,NULL);
    
    this->addChild(menu,1);
    
    
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        keys[keyCode] = true;
    };
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
        keys[keyCode] = false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->schedule(schedule_selector(equipmentscene::update_keyboard),0.1);
    
    return true;
}





void gamescene_houyi::update_creep1(float t)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    flag_creep=true;
    Melee_creep1=Sprite::create("小兵.jpg");
    Melee_creep1->setPosition(Crystal1->getPositionX()+50,visibleSize.height/2);
    this->addChild(Melee_creep1,2);
    
    Range_creep1=Sprite::create("小兵.jpg");
    Range_creep1->setPosition(Crystal1->getPositionX()-50,visibleSize.height/2);
    this->addChild(Range_creep1,2);
    
//    Catapult1=Sprite::create("小兵.jpg");
//    Catapult1->setPosition(crystal1->getPositionX()-100,visibleSize.height/2);
//    this->addChild(Catapult1,2);
//    HP_Catapult1=200;
//
    
    Melee_creep2=Sprite::create("小兵.jpg");
    Melee_creep2->setPosition(Crystal2->getPositionX()-50,visibleSize.height/2);
    this->addChild(Melee_creep2,2);
    
    Range_creep2=Sprite::create("小兵.jpg");
    Range_creep2->setPosition(Crystal2->getPositionX()+50,visibleSize.height/2);
    this->addChild(Range_creep2,2);
    
    a.init_creep();
    b.init_creep();
    
//    Catapult2=Sprite::create("小兵.jpg");
//    Catapult2->setPosition(crystal2->getPositionX()+100,visibleSize.height/2);
//    this->addChild(Catapult2,2);
//    HP_Catapult2=200;
    
    std::cout<<getCurrentlvl(experience_hero1)<<std::endl;
    

    this->schedule(schedule_selector(gamescene_houyi::update_Melee_creep1_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_Melee_creep2_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_Range_creep1_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_Range_creep2_attack),1);

}

//void gamescene_houyi::update_creep2(float t)
//{
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    
//    Melee_creep1=Sprite::create("小兵.jpg");
//    Melee_creep1->setPosition(crystal1->getPositionX()+50,visibleSize.height/2);
//    this->addChild(Melee_creep1,2);
//    HP_Melee_creep1=100;
//    
//    Range_creep1=Sprite::create("小兵.jpg");
//    Range_creep1->setPosition(crystal1->getPositionX()-50,visibleSize.height/2);
//    this->addChild(Range_creep1,2);
//    HP_Range_creep1=50;
//    
//    //    Catapult1=Sprite::create("小兵.jpg");
//    //    Catapult1->setPosition(crystal1->getPositionX()-100,visibleSize.height/2);
//    //    this->addChild(Catapult1,2);
//    //    HP_Catapult1=200;
//    //
//    
//    Melee_creep2=Sprite::create("小兵.jpg");
//    Melee_creep2->setPosition(crystal2->getPositionX()-50,visibleSize.height/2);
//    this->addChild(Melee_creep2,2);
//    HP_Melee_creep2=100;
//    
//    Range_creep2=Sprite::create("小兵.jpg");
//    Range_creep2->setPosition(crystal2->getPositionX()+50,visibleSize.height/2);
//    this->addChild(Range_creep2,2);
//    HP_Range_creep2=50;
//    
//    //    Catapult2=Sprite::create("小兵.jpg");
//    //    Catapult2->setPosition(crystal2->getPositionX()+100,visibleSize.height/2);
//    //    this->addChild(Catapult2,2);
//    //    HP_Catapult2=200;
//    
//    std::cout<<getCurrentlvl(experience_hero1)<<std::endl;
//    
//    
//    this->schedule(schedule_selector(gamescene_houyi::update_Melee_creep1_attack),1);
//    this->schedule(schedule_selector(gamescene_houyi::update_Melee_creep2_attack),1);
//    this->schedule(schedule_selector(gamescene_houyi::update_Range_creep1_attack),1);
//    this->schedule(schedule_selector(gamescene_houyi::update_Range_creep2_attack),1);
//    
//}
//
//void gamescene_houyi::update_creep3(float t)
//{
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    
//    Melee_creep1=Sprite::create("小兵.jpg");
//    Melee_creep1->setPosition(crystal1->getPositionX()+50,visibleSize.height/2);
//    this->addChild(Melee_creep1,2);
//    HP_Melee_creep1=100;
//    
//    Range_creep1=Sprite::create("小兵.jpg");
//    Range_creep1->setPosition(crystal1->getPositionX()-50,visibleSize.height/2);
//    this->addChild(Range_creep1,2);
//    HP_Range_creep1=50;
//    
//    //    Catapult1=Sprite::create("小兵.jpg");
//    //    Catapult1->setPosition(crystal1->getPositionX()-100,visibleSize.height/2);
//    //    this->addChild(Catapult1,2);
//    //    HP_Catapult1=200;
//    //
//    
//    Melee_creep2=Sprite::create("小兵.jpg");
//    Melee_creep2->setPosition(crystal2->getPositionX()-50,visibleSize.height/2);
//    this->addChild(Melee_creep2,2);
//    HP_Melee_creep2=100;
//    
//    Range_creep2=Sprite::create("小兵.jpg");
//    Range_creep2->setPosition(crystal2->getPositionX()+50,visibleSize.height/2);
//    this->addChild(Range_creep2,2);
//    HP_Range_creep2=50;
//    
//    //    Catapult2=Sprite::create("小兵.jpg");
//    //    Catapult2->setPosition(crystal2->getPositionX()+100,visibleSize.height/2);
//    //    this->addChild(Catapult2,2);
//    //    HP_Catapult2=200;
//    
//    std::cout<<getCurrentlvl(experience_hero1)<<std::endl;
//    
//    
//    this->schedule(schedule_selector(gamescene_houyi::update_Melee_creep1_attack),1);
//    this->schedule(schedule_selector(gamescene_houyi::update_Melee_creep2_attack),1);
//    this->schedule(schedule_selector(gamescene_houyi::update_Range_creep1_attack),1);
//    this->schedule(schedule_selector(gamescene_houyi::update_Range_creep2_attack),1);
//    
//}
//
//void gamescene_houyi::update_creep4(float t)
//{
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    
//    Melee_creep1=Sprite::create("小兵.jpg");
//    Melee_creep1->setPosition(crystal1->getPositionX()+50,visibleSize.height/2);
//    this->addChild(Melee_creep1,2);
//    HP_Melee_creep1=100;
//    
//    Range_creep1=Sprite::create("小兵.jpg");
//    Range_creep1->setPosition(crystal1->getPositionX()-50,visibleSize.height/2);
//    this->addChild(Range_creep1,2);
//    HP_Range_creep1=50;
//    
//    //    Catapult1=Sprite::create("小兵.jpg");
//    //    Catapult1->setPosition(crystal1->getPositionX()-100,visibleSize.height/2);
//    //    this->addChild(Catapult1,2);
//    //    HP_Catapult1=200;
//    //
//    
//    Melee_creep2=Sprite::create("小兵.jpg");
//    Melee_creep2->setPosition(crystal2->getPositionX()-50,visibleSize.height/2);
//    this->addChild(Melee_creep2,2);
//    HP_Melee_creep2=100;
//    
//    Range_creep2=Sprite::create("小兵.jpg");
//    Range_creep2->setPosition(crystal2->getPositionX()+50,visibleSize.height/2);
//    this->addChild(Range_creep2,2);
//    HP_Range_creep2=50;
//    
//    //    Catapult2=Sprite::create("小兵.jpg");
//    //    Catapult2->setPosition(crystal2->getPositionX()+100,visibleSize.height/2);
//    //    this->addChild(Catapult2,2);
//    //    HP_Catapult2=200;
//    
//    std::cout<<getCurrentlvl(experience_hero1)<<std::endl;
//    
//    
//    this->schedule(schedule_selector(gamescene_houyi::update_Melee_creep1_attack),1);
//    this->schedule(schedule_selector(gamescene_houyi::update_Melee_creep2_attack),1);
//    this->schedule(schedule_selector(gamescene_houyi::update_Range_creep1_attack),1);
//    this->schedule(schedule_selector(gamescene_houyi::update_Range_creep2_attack),1);
//    
//}






void gamescene_houyi::onMouseMove(Event *event)
{
    auto e=(EventMouse *)event;
    int X=e->getCursorX()-sprite->getPositionX();
    int Y=e->getCursorY()-sprite->getPositionY();
    double dis=sqrt(X*X+Y*Y);
    auto by1=MoveBy::create(dis/200,Vec2(-X,0));
    Tower1->runAction(by1);
    auto by2=MoveBy::create(dis/200,Vec2(-X,0));
    Tower2->runAction(by2);
    auto by3=MoveBy::create(dis/200,Vec2(-X,0));
    Crystal1->runAction(by3);
    auto by4=MoveBy::create(dis/200,Vec2(-X,0));
    Crystal2->runAction(by4);
    auto by=MoveBy::create(dis/200,Vec2(0,Y));
    sprite->runAction(by);
    if(flag_creep==true)
    {
        if(a.melee.HP>0)
        {
            auto by5=MoveBy::create(dis/200,Vec2(-X,0));
            Melee_creep1->runAction(by5);
        }
        if(a.range.HP>0)
        {
            auto by6=MoveBy::create(dis/200,Vec2(-X,0));
            Range_creep1->runAction(by6);
        }
        if(b.melee.HP>0)
        {
            auto by7=MoveBy::create(dis/200,Vec2(-X,0));
            Melee_creep2->runAction(by7);
        }
        if(b.range.HP>0)
        {
            auto by8=MoveBy::create(dis/200,Vec2(-X,0));
            Range_creep2->runAction(by8);
        }
    }
    
    

}



void gamescene_houyi::getBloodbar(Sprite *guaisprite ,float a)
{

        auto pBloodKongSp = Sprite::create("满血条.png");
        pBloodKongSp->setScale(0.1,0.3);
        pBloodKongSp->setPosition(Vec2(guaisprite->getContentSize().width / 2, guaisprite->getContentSize().height / 1.1));
        guaisprite->addChild(pBloodKongSp,2);
        auto pBloodManSp = Sprite::create("空血条.png");
       
        auto pBloodProGress = CCProgressTimer::create(pBloodManSp);
        pBloodProGress->setType(kCCProgressTimerTypeBar);
        pBloodProGress->setBarChangeRate(Vec2(1, 0));
        pBloodProGress->setMidpoint(Vec2(1, 0));
        pBloodProGress->setScale(0.06,0.15);
        pBloodProGress->setPosition(Vec2(guaisprite->getContentSize().width / 2, guaisprite->getContentSize().height / 1.1));
        pBloodProGress->setPercentage(a);
        guaisprite->addChild(pBloodProGress,3);
}







int gamescene_houyi::getCurrentlvl(int experience_hero)
{
    int lvlup_experience[15]={50,100,150,200,250,300,350,400,450,500,550,600,650,700};
    int lvl=1;
    for(int i=0;i<15;i++)
    {
        if(experience_hero>lvlup_experience[i])
        {
            lvl++;
            experience_hero-=lvlup_experience[i];
        }
        else
            break;
    }
    return lvl;
}


bool equipmentscene::isKeyPressed(EventKeyboard::KeyCode keyCode) {
    if(keys[keyCode])
        return true;
    else
        return false;
}



void equipmentscene::update_keyboard(float t)
{

    if(isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_TAB))
    {
        this->setVisible(true);
    }
    else
        this->setVisible(false);
        
}

void equipmentscene::item_hongbaoshi(Ref *obj)
{
    auto hongbaoshi1=Sprite::create("hongbaoshi.jpg");
    hongbaoshi1->setPosition(800,30);
    this->addChild(hongbaoshi1);
}

void gamescene_houyi::update_heroHP(float t)
{
    
}




