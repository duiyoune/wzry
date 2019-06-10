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
#include "attack_logic.hpp"

Layer *layer_game;
Layer *layer_set;
Sprite * flag;
Sprite * store;

Scene*scene::gamescene()
{
    auto scene=Scene::create();
    layer_game=gamescene_houyi::create();
    layer_set=set::create();
    scene->addChild(layer_game);
    scene->addChild(layer_set);
    return scene;
    
}


bool gamescene_houyi::init()
{
    if(!Layer::init())
    {
        return false;
    }
    time=0;

    this->schedule(schedule_selector(gamescene_houyi::update_time),0.1);

    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    



    a.init();
    b.init();
    flag_creep=false;

    
    sprite=Sprite::create("houyi.png");
    sprite->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(sprite,4);
    flag_heroalive=true;
    
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

    


    

    
    
    
    auto listener1= EventListenerMouse::create();
    listener1->onMouseMove=CC_CALLBACK_1(gamescene_houyi::onMouseMove1,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
//    auto listener2 = EventListenerKeyboard::create();
//    listener2->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
//    {
//        keys[keyCode] = true;
//    };
//    listener2->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
//        keys[keyCode] = false;
//    };
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
    
    auto listener3 = EventListenerKeyboard::create();
    listener3->onKeyPressed = CC_CALLBACK_2(gamescene_houyi::onKeyPressed, this);
    listener3->onKeyReleased = CC_CALLBACK_2(gamescene_houyi::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener3, this);
    
    auto listener4 = EventListenerKeyboard::create();
    listener4->onKeyPressed = CC_CALLBACK_2(gamescene_houyi::onKeyPressed4, this);
    listener4->onKeyReleased = CC_CALLBACK_2(gamescene_houyi::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener4, this);

    
    
//    this->schedule(schedule_selector(gamescene_houyi::update_keyboard),0.1);
    
    


    this->schedule(schedule_selector(gamescene_houyi::update_time),1);
    
    
    this->schedule(schedule_selector(gamescene_houyi::update_creep1),15);
    this->schedule(schedule_selector(gamescene_houyi::update_heroHP), 0.1f);

    
    
    this->schedule(schedule_selector(gamescene_houyi::update_tower2_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_tower1_attack),1);
    
    
    return true;
}

bool set::init()
{
    if(!Layer::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    equipment=Sprite::create("equipment.png");
    equipment->setPosition(visibleSize.width/2+200,50);
    this->addChild(equipment);
    
    flag=Sprite::create("equipment.png");
    flag->setPosition(0,0);
    
    store=Sprite::create("store.png");
    store->setScale(2);
    store->setPosition(128,visibleSize.height/2);
    this->addChild(store);
    store->setVisible(false);

    
    return true;
}



void gamescene_houyi::update_creep1(float t)
{
    creep_i++;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    flag_creep=true;
    Melee_creep1[creep_i]=Sprite::create("小兵.jpg");
    Melee_creep1[creep_i]->setPosition(Crystal1->getPositionX()+50,visibleSize.height/2);
    this->addChild(Melee_creep1[creep_i],2);
    
    Range_creep1[creep_i]=Sprite::create("小兵.jpg");
    Range_creep1[creep_i]->setPosition(Crystal1->getPositionX()-50,visibleSize.height/2);
    this->addChild(Range_creep1[creep_i],2);
    
    Catapult1[creep_i]=Sprite::create("小兵.jpg");
    Catapult1[creep_i]->setPosition(Crystal1->getPositionX()-100,visibleSize.height/2);
    this->addChild(Catapult1[creep_i],2);

    
    Melee_creep2[creep_i]=Sprite::create("小兵.jpg");
    Melee_creep2[creep_i]->setPosition(Crystal2->getPositionX()-50,visibleSize.height/2);
    this->addChild(Melee_creep2[creep_i],2);
    
    Range_creep2[creep_i]=Sprite::create("小兵.jpg");
    Range_creep2[creep_i]->setPosition(Crystal2->getPositionX()+50,visibleSize.height/2);
    this->addChild(Range_creep2[creep_i],2);
    
    Catapult2[creep_i]=Sprite::create("小兵.jpg");
    Catapult2[creep_i]->setPosition(Crystal2->getPositionX()+100,visibleSize.height/2);
    this->addChild(Catapult2[creep_i],2);
    
    a.init_creep(creep_i);
    b.init_creep(creep_i);


    

    this->schedule(schedule_selector(gamescene_houyi::update_Melee_creep1_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_Melee_creep2_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_Range_creep1_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_Range_creep2_attack),1);

}







void gamescene_houyi::onMouseMove(Event *event)
{
    if(sprite!=NULL)
    {
        auto e=(EventMouse *)event;
        int X=e->getCursorX()-512;
        int Y=e->getCursorY()-sprite->getPositionY();
        double dis=sqrt(X*X+Y*Y);
        auto by1=MoveBy::create(dis/200,Vec2(-X,0));
        layer_game->stopActionByTag(tag_layer);
        layer_game->resume();
        layer_game->runAction(by1);
        by1->setTag(tag_layer);
        auto by2=MoveBy::create(dis/200,Vec2(X,Y));
        sprite->stopActionByTag(tag_hero);
        sprite->resume();
        sprite->runAction(by2);
        by2->setTag(tag_hero);
        auto by3=MoveBy::create(dis/200,Vec2(X,Y));
        flag->stopActionByTag(tag_flag);
        flag->resume();
        flag->runAction(by3);
        by3->setTag(tag_flag);
        
        clickCreep_enemy(e->getCursorX()+flag->getPositionX(),e->getCursorY());
        
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
            //cursor->setPosition(-1000,-1000);
        }
        cursor=Sprite::create("cursor.png");
        cursor->setPosition(e->getCursorX()+flag->getPositionX()-60,e->getCursorY());
        this->addChild(cursor);
    }
        
        
}

void gamescene_houyi::getBloodbar(Sprite *guaisprite ,float a)
{
    
    pBloodKongSp = Sprite::create("满血条.png");
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
    guaisprite->addChild(pBloodProGress,2);
}

void gamescene_houyi::getBloodbar1(Sprite *guaisprite ,float a)
{
    

    auto pBloodManSp = Sprite::create("满血条.png");
    
    auto pBloodProGress = CCProgressTimer::create(pBloodManSp);
    pBloodProGress->setType(kCCProgressTimerTypeBar);
    pBloodProGress->setBarChangeRate(Vec2(1, 0));
    pBloodProGress->setMidpoint(Vec2(0, 0));
    pBloodProGress->setScale(0.1,0.3);
    pBloodProGress->setPosition(Vec2(guaisprite->getContentSize().width / 2, guaisprite->getContentSize().height / 1.1));
    pBloodProGress->setPercentage(1-a);
    guaisprite->addChild(pBloodProGress,2);
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


//bool gamescene_houyi::onKeyPressed1(EventKeyboard::KeyCode keyCode)
//{
//    if(keyCode == EventKeyboard::KeyCode::KEY_TAB)
//        return (1-flag_tab);
//}



//void gamescene_houyi::update_keyboard(float t)
//{
//
//    if(onKeyPressed1(cocos2d::EventKeyboard::KeyCode::KEY_TAB))
//        store->setVisible(true);
//    else
//        store->setVisible(false);
//
//
//}


void gamescene_houyi::update_time(float t)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    time+=1;
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
    
    layer_set->removeChild(label);
    label=Label::createWithSystemFont(str, "Arial", 24);
    label->setPosition(512,600);
    layer_set->addChild(label);
    
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
            a.hero1.HP=a.hero1.HP_max;
            sprite=Sprite::create("houyi.png");
            sprite->setPosition(visibleSize.width/2,visibleSize.height/2);
            auto by=MoveBy::create(0.1,Vec2(deltaX,0));
            layer_game->runAction(by);  
            this->addChild(sprite,4);
        }
    }
}


bool gamescene_houyi::InTheArea(float X, float Y,Sprite  * A)
{
    float positionX = A->getPositionX();
    float positionY = A->getPositionY();
    float contentSizeX = 2*A->getContentSize().width;
    float contentSizeY = 2*A->getContentSize().height;
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


void gamescene_houyi::clickCreep_enemy(float X, float Y)
{
    hero_attack_target=false;
    for (int i=0;i<creep_i;i++)
    {
        if (Melee_creep2[i]!=NULL && hero_attack_target==false)
        {
            if (InTheArea(X,Y,Melee_creep2[i])==true)
            {
                hero_attack_target=true;
                flag_sprite=Melee_creep2[i];
                hero_Attack();
                log("true");
            }
        }
        if (Range_creep2[i]!=NULL && hero_attack_target==false)
        {
            if (InTheArea(X,Y,Range_creep2[i])==true)
            {
                hero_attack_target=true;
                flag_sprite=Range_creep2[i];
                hero_Attack();
                log("true");
            }
        }
        if (Catapult2[i]!=NULL && hero_attack_target==false)
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
    if (Tower2!=NULL && hero_attack_target==false)
    {
        if (InTheArea(X,Y,Tower2)==true)
        {
            hero_attack_target=true;
            flag_sprite=Tower2;
            hero_Attack();
            log("true");
        }
    }
    if (Crystal2!=NULL && hero_attack_target==false)
    {
        if (InTheArea(X,Y,Crystal2)==true)
        {
            hero_attack_target=true;
            flag_sprite=Crystal2;
            hero_Attack();
            log("true");
        }
    }
    
}


void gamescene_houyi::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_A && sprite!=NULL)
    {
        hero_attack=true;
    }
}

void gamescene_houyi::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    
}

void gamescene_houyi::onKeyPressed4(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_TAB)
    {
        flag_tab=1-flag_tab;
        if(flag_tab==true)
            store->setVisible(true);
        else
            store->setVisible(false);
    }
}



void gamescene_houyi::update_tower2_attack(float t)
{
    bool attack_flag=false;
    int dis_hero=1000000;
    if(Tower2!=NULL)
    {
        for(int j=0;j<creep_i;j++)
        {

            int dis_Melee_creep=1000000,dis_Range_creep=1000000,dis_Catapult=1000000;
            
            if(flag_creep==true)
            {
                if(a.melee.HP[j]>0 && attack_flag==false)
                {
                    
                    dis_Melee_creep=abs(Melee_creep1[j]->getPositionX()-Tower2->getPositionX());
                    if(dis_Melee_creep<500)
                    {
                        attack_flag=true;
                        pb=Sprite::create("PB01.png");
                        pb->setPosition(Tower2->getPositionX(),Tower2->getPositionY()+50);
                        this->addChild(pb);
                        auto to=MoveTo::create(0.2,Vec2(Melee_creep1[j]->getPositionX(),Melee_creep1[j]->getPositionY()));
                        auto hide=Hide::create();
                        pb->runAction(CCSequence::create(to,hide,NULL));
                        a.melee.HP[j]-=b.tower.base_damage;
                        
                    }
                }
                if(a.range.HP[j]>0 && attack_flag==false)
                {
                    dis_Range_creep=abs(Range_creep1[j]->getPositionX()-Tower2->getPositionX());
                    if(dis_Range_creep<500)
                    {
                        attack_flag=true;
                        pb=Sprite::create("PB01.png");
                        pb->setPosition(Tower2->getPositionX(),Tower2->getPositionY()+50);
                        this->addChild(pb);
                        auto to=MoveTo::create(0.2,Vec2(Range_creep1[j]->getPositionX(),Range_creep1[j]->getPositionY()));
                        auto hide=Hide::create();
                        pb->runAction(CCSequence::create(to,hide,NULL));
                        a.range.HP[j]-=b.tower.base_damage;
                        
                    }
                }
                if(a.catapult.HP[j]>0 && attack_flag==false)
                {
                    dis_Catapult=abs(Tower2->getPositionX()-Catapult1[j]->getPositionX());
                    if(dis_Catapult<500)
                    {
                        attack_flag=true;
                        pb=Sprite::create("PB01.png");
                        pb->setPosition(Tower2->getPositionX(),Tower2->getPositionY()+50);
                        this->addChild(pb);
                        auto to=MoveTo::create(0.2,Vec2(Catapult1[j]->getPositionX(),Catapult1[j]->getPositionY()));
                        auto hide=Hide::create();
                        pb->runAction(CCSequence::create(to,hide,NULL));
                        a.catapult.HP[j]-=b.tower.base_damage;
                        
                    }
                }
                if(a.hero1.HP>0 && attack_flag==false)
                {
                    dis_hero=abs(Tower2->getPositionX()-sprite->getPositionX());
                    if(dis_hero<500)
                    {
                        attack_flag=true;
                        pb=Sprite::create("PB01.png");
                        pb->setPosition(Tower2->getPositionX(),Tower2->getPositionY()+50);
                        this->addChild(pb);
                        auto to=MoveTo::create(0.2,Vec2(sprite->getPositionX(),sprite->getPositionY()));
                        auto hide=Hide::create();
                        pb->runAction(CCSequence::create(to,hide,NULL));
                        a.hero1.HP-=b.tower.base_damage;
                    }
                }
            }
        }
    }
       
        
    for(int j=0;j<creep_i;j++)
    {

        if(a.melee.HP[j]<=0 && Melee_creep1!=NULL)
        {
            this->removeChild(Melee_creep1[j]);
            Melee_creep1[j]=NULL;
        }
        if(a.range.HP[j]<=0 && Range_creep1!=NULL)
        {
            this->removeChild(Range_creep1[j]);
            Range_creep1[j]=NULL;
        }
        if(a.catapult.HP[j]<=0 && Catapult1!=NULL)
        {
            this->removeChild(Catapult1[creep_i]);
            Catapult1[j]=NULL;
        }

    }
    if(a.hero1.HP>0 && attack_flag==false)
    {
        dis_hero=abs(Tower2->getPositionX()-sprite->getPositionX());
        if(dis_hero<500)
        {
            attack_flag=true;
            pb=Sprite::create("PB01.png");
            pb->setPosition(Tower2->getPositionX(),Tower2->getPositionY()+50);
            this->addChild(pb);
            auto to=MoveTo::create(0.2,Vec2(sprite->getPositionX(),sprite->getPositionY()));
            auto hide=Hide::create();
            pb->runAction(CCSequence::create(to,hide,NULL));
            a.hero1.HP-=b.tower.base_damage;
        }
    }

}
