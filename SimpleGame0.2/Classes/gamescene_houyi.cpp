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

static int HP1,HP2,HP_tower1,HP_tower2,HP_hero1,HP_hero2,HP_crystal1,HP_crystal2;

Scene*gamescene_houyi::scene()
{
    auto scene=Scene::create();
    auto layer=gamescene_houyi::create();
    scene->addChild(layer);
    return scene;
    
}

bool gamescene_houyi::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    

    
    sprite=Sprite::create("houyi.png");
    sprite->setPosition(50,visibleSize.height/2);
    this->addChild(sprite,0);
    HP_hero1=2000;
    
    auto listener= EventListenerMouse::create();
    listener->onMouseDown=CC_CALLBACK_1(gamescene_houyi::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
//    auto to=MoveTo::create(2, Vec2(500,visibleSize.height/2));
//    sprite->runAction(to);
    
    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("tower-0001-default.plist");
    
    auto frame_tower1=SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("tower1.jpg");
    tower1=Sprite::createWithSpriteFrame(frame_tower1);
    tower1->setPosition(100,visibleSize.height/2);
    this->addChild(tower1,1);
    HP_tower1=1000;
    
    
    auto frame_tower2=SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("tower2.jpg");
    tower2=Sprite::createWithSpriteFrame(frame_tower2);
    tower2->setPosition(1024-100,visibleSize.height/2);
    this->addChild(tower2,1);
    HP_tower2=1000;

    
    auto frame_crystal1=SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("crystal1.jpg");
    crystal1=Sprite::createWithSpriteFrame(frame_crystal1);
    crystal1->setPosition(-500,visibleSize.height/2);
    this->addChild(crystal1,1);
    HP_crystal1=3000;
    
    
    auto frame_crystal2=SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("crystal2.jpg");
    crystal2=Sprite::createWithSpriteFrame(frame_crystal2);
    crystal2->setPosition(1024+500,visibleSize.height/2);
    this->addChild(crystal2,1);
    HP_crystal2=3000;

 
    
    
    this->schedule(schedule_selector(gamescene_houyi::update_xiaobing),15);
    
    this->schedule(schedule_selector(gamescene_houyi::update_tower2_attack),1);
    
    
    return true;
}



void gamescene_houyi::update_xiaobing (float t)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    xiaobing1=Sprite::create("小兵.jpg");
    xiaobing1->setPosition(100,visibleSize.height/2);
    this->addChild(xiaobing1,2);
    HP1=100;
    
    
    xiaobing2=Sprite::create("小兵.jpg");
    xiaobing2->setPosition(1024-100,visibleSize.height/2);
    this->addChild(xiaobing2,2);
    HP2=100;
    

    this->schedule(schedule_selector(gamescene_houyi::update_xiaobing1_attack),1);
    
    
}

void gamescene_houyi::update_xiaobing1_attack(float t)
{
    int X1=100000,Y1=100000,X2=100000,Y2=100000,X3=1000000,Y3=100000;
    int dis1=1000000000,dis2=1000000000,dis3=1000000000;
    if(HP1)
    {
        if(HP2>0)
        {
            X1=-xiaobing1->getPositionX()+xiaobing2->getPositionX();
            Y1=-xiaobing1->getPositionY()+xiaobing2->getPositionY();
            dis1=X1*X1+Y1*Y1;
        }
        if(HP_crystal2>0)
        {
            X2=-xiaobing1->getPositionX()+crystal2->getPositionX();
            Y2=-xiaobing1->getPositionY()+crystal2->getPositionY();
            dis2=X2*X2+Y2*Y2;
        }
        if(HP_tower2>0)
        {
            X3=-xiaobing1->getPositionX()+tower2->getPositionX();
            Y3=-xiaobing1->getPositionY()+tower2->getPositionY();
            dis3=X3*X3+Y3*Y3;
        }
        
        int min_dis=std::min(std::min(dis1,dis2),dis3);
        int time=sqrt(min_dis)/300;
        
        
        if(min_dis<10000)
        {
            if(min_dis==dis1)
                HP2-=20;
            else if(min_dis==dis2)
                HP_crystal2-=20;
            else
                HP_tower2-=20;
        }
        else
        {
            if(min_dis==dis1)
            {
                auto by=MoveBy::create(1, Vec2((X1-30)/time,Y1/time));
                xiaobing1->runAction(by);
                
            }
            else if(min_dis==dis2)
            {
                auto by=MoveBy::create(1, Vec2((X2-30)/time,Y2/time));
                xiaobing1->runAction(by);
            }
            else
            {
                auto by=MoveBy::create(1, Vec2((X3-30)/time,Y3/time));
                xiaobing1->runAction(by);
            }
        }
    }
    float a=(1000-HP_tower2)/10;
    this->getBloodbar(tower2,a);
    float b=(2000-HP_hero1)/20;
    this->getBloodbar(sprite,b);
    
    if(HP2<=0)
        this->removeChild(xiaobing2);
    if(HP_tower2<=0)
        this->removeChild(tower2);
    if(HP_crystal2<=0)
        this->removeChild(crystal2);
}


void gamescene_houyi::onMouseMove(Event *event)
{
    auto e=(EventMouse *)event;
    auto to=MoveTo::create(3,Vec2(e->getCursorX(),e->getCursorY()));
    sprite->runAction(to);
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


void gamescene_houyi::update_tower2_attack(float t)
{
    int dis_xiaobing=1000000,dis_hero=1000000;
    if(HP1>0)
    {
        dis_xiaobing=sqrt((tower2->getPositionX()-xiaobing1->getPositionX())*(tower2->getPositionX()-xiaobing1->getPositionX())+(tower2->getPositionY()-xiaobing1->getPositionY())*(tower2->getPositionY()-xiaobing1->getPositionY()));
        std::cout<<dis_xiaobing<<std::endl;
        if(dis_xiaobing<200)
            HP1-=20;
    }
    if(HP_hero1>0)
    {
        dis_hero=sqrt((tower2->getPositionX()-sprite->getPositionX())*(tower2->getPositionX()-sprite->getPositionX())+(tower2->getPositionY()-sprite->getPositionY())*(tower2->getPositionY()-sprite->getPositionY()));
        if(dis_hero<200)
            HP_hero1-=20;
    }
    if(HP1<=0)
        this->removeChild(xiaobing1);
    
}

//
//int getDistance(Sprite *target1 ,Sprite *target2)
//{
//    int X=target1->getPositionX()-target2->getPositionX();
//    int Y=target1->getPositionY()-target2->getPositionY();
//    return sqrt(X*X+Y*Y);
//}
