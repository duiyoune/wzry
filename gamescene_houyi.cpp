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
attr a;
attr b;

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


    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    for(int i=0;i<600;i++)
    {
        Melee_creep1[i]=NULL;
        Melee_creep2[i]=NULL;
        Range_creep1[i]=NULL;
        Range_creep2[i]=NULL;
        Catapult1[i]=NULL;
        Catapult2[i]=NULL;
    }


    a.init();
    b.init();
    flag_creep=false;


    
    
    sprite=Sprite::create("npc1_553-1.png");
    sprite->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(sprite,4);
    flag_heroalive=true;

    
    ai=Sprite::create("HelloWorld.png");
    ai->setPosition(3500,visibleSize.height/2);
    ai->setScale(0.5);
    this->addChild(ai,4);
    flag_aialive=true;
    
    
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
//    equipment=Sprite::create("equipment.png");
//    equipment->setPosition(visibleSize.width/2+200,50);
//    this->addChild(equipment);
//
    flag=Sprite::create("equipment.png");
    flag->setPosition(0,0);
    
    store=Sprite::create("store.png");
    store->setScale(2);
    store->setPosition(128,visibleSize.height/2);
    this->addChild(store);
    store->setVisible(false);
    
    auto listener= EventListenerMouse::create();
    listener->onMouseDown=CC_CALLBACK_1(set::onMouseDown,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}



void gamescene_houyi::update_creep1(float t)
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    flag_creep=true;
    
    
    Melee_creep1[creep_i]=Sprite::create("melee1.png");
    Melee_creep1[creep_i]->setPosition(Crystal1->getPositionX()+50,visibleSize.height/2);
    this->addChild(Melee_creep1[creep_i],2);
    auto *animation1=Animation::create();
    for(int i = 1; i<3; i++)
    {
        auto string=String::createWithFormat("melee%d.png",i);
        auto frame=SpriteFrame::create(string->getCString(),CCRectMake(0, 0, 43, 53));
        animation1->addSpriteFrame(frame);
        
    }
    animation1->setDelayPerUnit(0.3);
    animation1->setLoops(-1);
    auto animate1=Animate::create(animation1);
    Melee_creep1[creep_i]->runAction(animate1);
    
    
    Melee_creep2[creep_i]=Sprite::create("melee3.png");
    Melee_creep2[creep_i]->setPosition(Crystal2->getPositionX()-50,visibleSize.height/2);
    this->addChild(Melee_creep2[creep_i],2);
    auto *animation2=Animation::create();
    for(int i = 3; i<5; i++)
    {
        auto string=String::createWithFormat("melee%d.png",i);
        auto frame=SpriteFrame::create(string->getCString(),CCRectMake(0, 0, 57, 57));
        animation2->addSpriteFrame(frame);
        
    }
    animation2->setDelayPerUnit(0.3);
    animation2->setLoops(-1);
    auto animate2=Animate::create(animation2);
    Melee_creep2[creep_i]->runAction(animate2);
    
    
    Range_creep1[creep_i]=Sprite::create("range1.png");
    Range_creep1[creep_i]->setPosition(Crystal1->getPositionX()-50,visibleSize.height/2);
    this->addChild(Range_creep1[creep_i],2);
    auto *animation3=Animation::create();
    for(int i = 1; i<9; i++)
    {
        auto string=String::createWithFormat("range%d.png",i);
        auto frame=SpriteFrame::create(string->getCString(),CCRectMake(0, 0, 41, 56));
        animation3->addSpriteFrame(frame);
        
    }
    animation3->setDelayPerUnit(0.3);
    animation3->setLoops(-1);
    auto animate3=Animate::create(animation3);
    Range_creep1[creep_i]->runAction(animate3);
    
    
    
    
    
    Catapult1[creep_i]=Sprite::create("小兵.jpg");
    Catapult1[creep_i]->setPosition(Crystal1->getPositionX()-100,visibleSize.height/2);
    this->addChild(Catapult1[creep_i],2);

    

    
    Range_creep2[creep_i]=Sprite::create("小兵.jpg");
    Range_creep2[creep_i]->setPosition(Crystal2->getPositionX()+50,visibleSize.height/2);
    this->addChild(Range_creep2[creep_i],2);
    
    Catapult2[creep_i]=Sprite::create("小兵.jpg");
    Catapult2[creep_i]->setPosition(Crystal2->getPositionX()+100,visibleSize.height/2);
    this->addChild(Catapult2[creep_i],2);
    
    a.init_creep(creep_i);
    b.init_creep(creep_i);

    creep_i++;
    

    this->schedule(schedule_selector(gamescene_houyi::update_Melee_creep1_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_Melee_creep2_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_Range_creep1_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_Range_creep2_attack),1);
    this->schedule(schedule_selector(gamescene_houyi::update_ai),1);

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
        by1->setTag(tag_layer);
        layer_game->stopActionByTag(tag_layer);
        layer_game->resume();
        layer_game->runAction(by1);

        auto by2=MoveBy::create(dis/200,Vec2(X,Y));
        by2->setTag(tag_hero);
        sprite->stopActionByTag(tag_hero);
        sprite->resume();
        sprite->runAction(by2);
        
        auto *animation=Animation::create();
        for(int i = 1; i<8; i++)
        {
            auto string=String::createWithFormat("npc1_553-%d.png",i);
            auto frame=SpriteFrame::create(string->getCString(),CCRectMake(0, 0, 104, 104));
            animation->addSpriteFrame(frame);
            
        }
        animation->setDelayPerUnit(0.2);
        animation->setLoops(-1);
        auto animate=Animate::create(animation);
        animate->setTag(10);
        sprite->stopActionByTag(10);
        sprite->resume();
        sprite->runAction(animate);

        auto by3=MoveBy::create(dis/200,Vec2(X,Y));
        by3->setTag(tag_flag);
        flag->stopActionByTag(tag_flag);
        flag->resume();
        flag->runAction(by3);

        
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

void set::onMouseDown(Event *event)
{
    auto e=(EventMouse *)event;
    if(equip_number<5)
    {
        if(e->getCursorX()>0&&e->getCursorX()<80&&e->getCursorY()>550&&e->getCursorY()<620)
        {
            if(a.hero1.gold>200)
            {
                a.hero1.gold-=200;
                equip_number++;
                auto att20=Sprite::create("20att.png");
                att20->setScale(2);
                att20->setPosition(equipX[equip_number],equipY[equip_number]);
                layer_set->addChild(att20,10);
                a.hero1.base_damage+=20;
            }
        }
        if(e->getCursorX()>0&&e->getCursorX()<80&&e->getCursorY()>450&&e->getCursorY()<500)
        {
            if(a.hero1.gold>1000)
            {
                a.hero1.gold-=1000;
                equip_number++;
                auto att50=Sprite::create("50att.png");
                att50->setScale(2);
                att50->setPosition(equipX[equip_number],equipY[equip_number]);
                layer_set->addChild(att50,10);
                a.hero1.base_damage+=50;
            }
        }
        if(e->getCursorX()>0&&e->getCursorX()<80&&e->getCursorY()>320&&e->getCursorY()<380)
        {
            if(a.hero1.gold>2000)
            {
                a.hero1.gold-=2000;
                equip_number++;
                auto att100=Sprite::create("100att.png");
                att100->setScale(2);
                att100->setPosition(equipX[equip_number],equipY[equip_number]);
                layer_set->addChild(att100,10);
                a.hero1.base_damage+=100;
            }
        }
        if(e->getCursorX()>100&&e->getCursorX()<150&&e->getCursorY()>550&&e->getCursorY()<620)
        {
            if(a.hero1.gold>200)
            {
                a.hero1.gold-=200;
                equip_number++;
                auto hp300=Sprite::create("300hp.png");
                hp300->setScale(2);
                hp300->setPosition(equipX[equip_number],equipY[equip_number]);
                layer_set->addChild(hp300,10);
                a.hero1.HP_max+=300;
                a.hero1.HP+=300;
            }
        }
        if(e->getCursorX()>100&&e->getCursorX()<150&&e->getCursorY()>450&&e->getCursorY()<500)
        {
            if(a.hero1.gold>1000)
            {
                a.hero1.gold-=1000;
                equip_number++;
                auto hp1000=Sprite::create("1000hp.png");
                hp1000->setScale(2);
                hp1000->setPosition(equipX[equip_number],equipY[equip_number]);
                layer_set->addChild(hp1000,10);
                a.hero1.HP_max+=1000;
                a.hero1.HP+=1000;
            }
        }
        if(e->getCursorX()>100&&e->getCursorX()<150&&e->getCursorY()>320&&e->getCursorY()<380)
        {
            if(a.hero1.gold>2000)
            {
                a.hero1.gold-=2000;
                equip_number++;
                auto hp2000=Sprite::create("2000hp.png");
                hp2000->setScale(2);
                hp2000->setPosition(equipX[equip_number],equipY[equip_number]);
                layer_set->addChild(hp2000,10);
                a.hero1.HP_max+=2000;
                a.hero1.HP+=2000;
            }
        }
        if(e->getCursorX()>180&&e->getCursorX()<250&&e->getCursorY()>450&&e->getCursorY()<500)
        {
            if(a.hero1.gold>3000)
            {
                a.hero1.gold-=3000;
                equip_number++;
                auto att300=Sprite::create("300att.png");
                att300->setScale(2);
                att300->setPosition(equipX[equip_number],equipY[equip_number]);
                layer_set->addChild(att300,10);
                a.hero1.base_damage+=300;
                
            }
        }
        
        
    }
    
    std::cout<<e->getCursorX()<<" "<<e->getCursorY()<<std::endl;
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







int gamescene_houyi::getCurrentlvl(Sprite *sprite)
{
    int lvlup_experience[14]={50,100,150,200,250,300,350,400,450,500,550,600,650,700};
    int lvl=1;
    if(a.hero1.exp>lvlup_experience[lvl-1])
    {
        a.hero1.exp-=lvlup_experience[lvl-1];
        lvl++;
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
    a.hero1.gold+=2;
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
    layer_set->removeChild(label_time);
    label_time=Label::createWithSystemFont(str, "Arial", 24);
    label_time->setPosition(512,600);
    layer_set->addChild(label_time);
    
    std::string str_gold=std::to_string(a.hero1.gold)+"g";
    layer_set->removeChild(label_gold);
    label_gold=Label::createWithSystemFont(str_gold, "Arial", 24);
    label_gold->setPosition(300,60);
    layer_set->addChild(label_gold);
    
    std::string str_lvl="lv:"+std::to_string(getCurrentlvl(sprite));
    layer_set->removeChild(label_lvl);
    label_lvl=Label::createWithSystemFont(str_lvl, "Arial", 24);
    label_lvl->setPosition(300,120);
    layer_set->addChild(label_lvl);
    
    
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


void gamescene_houyi::update_Melee_creep1_attack(float t)
{
    for(int j=std::max(0,creep_i-4);j<creep_i;j++)
    {
        if(a.melee.HP[j]>0)
        {
            int dis[15];
            int min_dis=100000;
            int flag=std::min(4,creep_i);
            for(int i=0;i<15;i++)
                dis[i]=10000;
            for(int i=0;i<flag;i++)
            {
                if(b.melee.HP[creep_i-i-1]>0)
                {
                dis[i]=abs(Melee_creep2[creep_i-i-1]->getPositionX()-Melee_creep1[j]->getPositionX());
                }
                if(b.range.HP[creep_i-i-1]>0)
                    dis[i+4]=abs(Range_creep2[creep_i-i-1]->getPositionX()-Melee_creep1[j]->getPositionX());
                if(b.catapult.HP[creep_i-i-1]>0)
                    dis[i+8]=abs(Catapult2[creep_i-i-1]->getPositionX()-Melee_creep1[j]->getPositionX());
                if(dis[i]<min_dis)
                {
                    min_dis=dis[i];
                    melee1_target[j]=Melee_creep2[creep_i-i-1];
                }
                if(dis[i+4]<min_dis)
                {
                    min_dis=dis[i];
                    melee1_target[j]=Range_creep2[creep_i-i-1];
                }
                if(dis[i+8]<min_dis)
                {
                    min_dis=dis[i];
                    melee1_target[j]=Catapult2[creep_i-i-1];
                }
            }
            dis[12]=abs(Melee_creep1[j]->getPositionX()-ai->getPositionX());
            dis[13]=abs(Melee_creep1[j]->getPositionX()-Tower2->getPositionX());
            dis[14]=abs(Melee_creep1[j]->getPositionX()-Crystal2->getPositionX());
            if(dis[12]<min_dis)
            {
                min_dis=dis[12];
                melee1_target[j]=ai;
            }
            if(dis[13]<min_dis)
            {
                min_dis=dis[13];
                melee1_target[j]=Tower2;
            }
            if(dis[14]<min_dis)
            {
                min_dis=dis[14];
                melee1_target[j]=Crystal2;
            }
            for(int i=0;i<14;i++)
                std::cout<<dis[i]<<std::endl;
            std::cout<<std::endl;
            if(min_dis<=100)
            {
                if(melee1_target[j]==ai)
                    b.hero1.HP-=20;
                else if(melee1_target[j]==Tower2)
                    b.tower.HP-=20;
                else if(melee1_target[j]==Crystal2)
                    b.crystal.HP-=20;
                else
                {
                    for(int i=0;i<4;i++)
                    {
                        if(melee1_target[j]==Melee_creep2[creep_i-i-1])
                            b.melee.HP[creep_i-i-1]-=20;
                        else if(melee1_target[j]==Range_creep2[creep_i-i-1])
                            b.range.HP[creep_i-i-1]-=20;
                        else if(melee1_target[j]==Catapult2[creep_i-i-1])
                            b.catapult.HP[creep_i-i-1]-=20;
                    }
                }
            }
            else
            {
                int X=melee1_target[j]->getPositionX()-Melee_creep1[j]->getPositionX();
                auto by=MoveBy::create(1,Vec2(std::min(X,100),0));
                Melee_creep1[creep_i-1]->runAction(by);
//                this->schedule(schedule_selector(gamescene_houyi::boundingbox_update),0.1);
            }
        }
    }
    
    
    for(int j=0;j<creep_i;j++)
    {
      
        if(a.melee.HP[j]>0)
            this->getBloodbar(Melee_creep1[j],(200-a.melee.HP[j])/2);


        
        
        if(b.melee.HP[j]<=0)
        {
            this->removeChild(Melee_creep2[j]);
            Melee_creep2[j]=NULL;
            a.hero1.gold+=20;
            a.hero1.exp+=10;
        }
        if(b.range.HP[j]<=0)
        {
            this->removeChild(Range_creep2[j]);
            Range_creep2[j]=NULL;
            a.hero1.gold+=50;
            a.hero1.exp+=15;
            
        }
    }
}

void gamescene_houyi::update_Melee_creep2_attack(float t)
{
    for(int j=std::max(0,creep_i-4);j<creep_i;j++)
    {
        if(b.melee.HP[j]>0)
        {
            int dis[15];
            int min_dis=100000;
            int flag=std::min(4,creep_i);
            for(int i=0;i<15;i++)
                dis[i]=10000;
            for(int i=0;i<flag;i++)
            {
                if(a.melee.HP[creep_i-i-1]>0)
                {
                    dis[i]=abs(Melee_creep1[creep_i-i-1]->getPositionX()-Melee_creep2[j]->getPositionX());
                }
                if(a.range.HP[creep_i-i-1]>0)
                    dis[i+4]=abs(Range_creep1[creep_i-i-1]->getPositionX()-Melee_creep2[j]->getPositionX());
                if(b.catapult.HP[creep_i-i-1]>0)
                    dis[i+8]=abs(Catapult1[creep_i-i-1]->getPositionX()-Melee_creep2[j]->getPositionX());
                if(dis[i]<min_dis)
                {
                    min_dis=dis[i];
                    melee2_target[j]=Melee_creep1[creep_i-i-1];
                }
                if(dis[i+4]<min_dis)
                {
                    min_dis=dis[i];
                    melee2_target[j]=Range_creep1[creep_i-i-1];
                }
                if(dis[i+8]<min_dis)
                {
                    min_dis=dis[i];
                    melee2_target[j]=Catapult1[creep_i-i-1];
                }
            }
            dis[12]=abs(Melee_creep2[j]->getPositionX()-sprite->getPositionX());
            dis[13]=abs(Melee_creep2[j]->getPositionX()-Tower1->getPositionX());
            dis[14]=abs(Melee_creep2[j]->getPositionX()-Crystal1->getPositionX());
            if(dis[12]<min_dis)
            {
                min_dis=dis[12];
                melee2_target[j]=sprite;
            }
            if(dis[13]<min_dis)
            {
                min_dis=dis[13];
                melee2_target[j]=Tower1;
            }
            if(dis[14]<min_dis)
            {
                min_dis=dis[14];
                melee2_target[j]=Crystal1;
            }
            
            if(min_dis<=100)
            {
                if(melee2_target[j]==sprite)
                    a.hero1.HP-=20;
                else if(melee2_target[j]==Tower1)
                    a.tower.HP-=20;
                else if(melee2_target[j]==Crystal1)
                    a.crystal.HP-=20;
                else
                {
                    for(int i=0;i<4;i++)
                    {
                        if(melee2_target[j]==Melee_creep1[creep_i-i-1])
                            a.melee.HP[creep_i-i-1]-=20;
                        else if(melee2_target[j]==Range_creep1[creep_i-i-1])
                            a.range.HP[creep_i-i-1]-=20;
                        else if(melee2_target[j]==Catapult1[creep_i-i-1])
                            a.catapult.HP[creep_i-i-1]-=20;
                    }
                }
            }
            else
            {
                int X=melee2_target[j]->getPositionX()-Melee_creep2[j]->getPositionX();
                auto by=MoveBy::create(1,Vec2(-std::min(-X,100),0));
                Melee_creep2[creep_i-1]->runAction(by);
                //                this->schedule(schedule_selector(gamescene_houyi::boundingbox_update),0.1);
            }
        }
    }
    
    
    for(int j=0;j<creep_i;j++)
    {
        if(b.melee.HP[j]>0)
            this->getBloodbar(Melee_creep2[j],(200-b.melee.HP[j])/2);
    }
}

void gamescene_houyi::update_Range_creep1_attack(float t)
{
    for(int j=std::max(0,creep_i-4);j<creep_i;j++)
    {
        if(a.range.HP[j]>0)
        {
            int dis[15];
            int min_dis=100000;
            int flag=std::min(4,creep_i);
            for(int i=0;i<15;i++)
                dis[i]=10000;
            for(int i=0;i<flag;i++)
            {
                if(b.melee.HP[creep_i-i-1]>0)
                {
                    dis[i]=abs(Melee_creep2[creep_i-i-1]->getPositionX()-Range_creep1[j]->getPositionX());
                }
                if(b.range.HP[creep_i-i-1]>0)
                    dis[i+4]=abs(Range_creep2[creep_i-i-1]->getPositionX()-Range_creep1[j]->getPositionX());
                if(b.catapult.HP[creep_i-i-1]>0)
                    dis[i+8]=abs(Catapult2[creep_i-i-1]->getPositionX()-Range_creep1[j]->getPositionX());
                if(dis[i]<min_dis)
                {
                    min_dis=dis[i];
                    range1_target[j]=Melee_creep2[creep_i-i-1];
                }
                if(dis[i+4]<min_dis)
                {
                    min_dis=dis[i];
                    range1_target[j]=Range_creep2[creep_i-i-1];
                }
                if(dis[i+8]<min_dis)
                {
                    min_dis=dis[i];
                    range1_target[j]=Catapult2[creep_i-i-1];
                }
            }
            dis[12]=abs(Range_creep1[j]->getPositionX()-ai->getPositionX());
            dis[13]=abs(Range_creep1[j]->getPositionX()-Tower2->getPositionX());
            dis[14]=abs(Range_creep1[j]->getPositionX()-Crystal2->getPositionX());
            if(dis[12]<min_dis)
            {
                min_dis=dis[12];
                range1_target[j]=ai;
            }
            if(dis[13]<min_dis)
            {
                min_dis=dis[13];
                range1_target[j]=Tower2;
            }
            if(dis[14]<min_dis)
            {
                min_dis=dis[14];
                range1_target[j]=Crystal2;
            }
            
            if(min_dis<=400)
            {
                if(range1_target[j]==ai)
                    b.hero1.HP-=20;
                else if(range1_target[j]==Tower2)
                    b.tower.HP-=20;
                else if(range1_target[j]==Crystal2)
                    b.crystal.HP-=20;
                else
                {
                    for(int i=0;i<4;i++)
                    {
                        if(range1_target[j]==Melee_creep2[creep_i-i-1])
                            b.melee.HP[creep_i-i-1]-=20;
                        else if(range1_target[j]==Range_creep2[creep_i-i-1])
                            b.range.HP[creep_i-i-1]-=20;
                        else if(range1_target[j]==Catapult2[creep_i-i-1])
                            b.catapult.HP[creep_i-i-1]-=20;
                    }
                }
            }
            else
            {
                int X=range1_target[j]->getPositionX()-Range_creep1[j]->getPositionX();
                auto by=MoveBy::create(1,Vec2(std::min(X,100),0));
                Range_creep1[creep_i-1]->runAction(by);
            }
        }
    }
    
    
    for(int j=0;j<creep_i;j++)
    {
        if(a.range.HP[j]>0)
            this->getBloodbar(Range_creep1[j],100-a.range.HP[j]);
    }
}

void gamescene_houyi::update_Range_creep2_attack(float t)
{
    for(int j=0;j<creep_i;j++)
    {
        int X[5],Y[5],dis[5];
        for(int i=0;i<5;i++)
        {
            X[i]=100000;
            Y[i]=100000;
            dis[i]=1000000000;
        }
        if(b.range.HP[j]>0)
        {
            if(a.melee.HP[j]>0)
            {
                X[0]=-Melee_creep1[j]->getPositionX()+Range_creep2[j]->getPositionX();
                Y[0]=-Melee_creep1[j]->getPositionY()+Range_creep2[j]->getPositionY();
                dis[0]=X[0]*X[0]+Y[0]*Y[0];
            }
            if(a.crystal.HP>0)
            {
                X[1]=-Range_creep2[j]->getPositionX()+Crystal1->getPositionX();
                Y[1]=-Range_creep2[j]->getPositionY()+Crystal1->getPositionY();
                dis[1]=X[1]*X[1]+Y[1]*Y[1];
            }
            if(a.tower.HP>0)
            {
                X[2]=-Range_creep2[j]->getPositionX()+Tower1->getPositionX();
                Y[2]=-Range_creep2[j]->getPositionY()+Tower1->getPositionY();
                dis[2]=X[2]*X[2]+Y[2]*Y[2];
            }
            if(a.range.HP[j]>0)
            {
                X[3]=-Range_creep2[j]->getPositionX()+Range_creep1[j]->getPositionX();
                Y[3]=-Range_creep2[j]->getPositionY()+Range_creep1[j]->getPositionY();
                dis[3]=X[3]*X[3]+Y[3]*Y[3];
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
                    a.melee.HP[j]-=20;
                else if(min_dis==dis[1])
                    a.crystal.HP-=20;
                else if(min_dis==dis[2])
                    a.tower.HP-=20;
                else
                    a.range.HP[j]-=20;
            }
            else
            {
                if(min_dis==dis[0])
                {
                    auto by=MoveBy::create(1, Vec2(-(abs(X[0])-300)/time,abs(Y[0])/time));
                    Range_creep2[j]->runAction(by);
                    
                }
                else if(min_dis==dis[1])
                {
                    auto by=MoveBy::create(1, Vec2(-(abs(X[1])-300)/time,abs(Y[1])/time));
                    Range_creep2[j]->runAction(by);
                }
                else if(min_dis==dis[2])
                {
                    auto by=MoveBy::create(1, Vec2(-(abs(X[2])-300)/time,abs(Y[2])/time));
                    Range_creep2[j]->runAction(by);
                }
                else
                {
                    auto by=MoveBy::create(1, Vec2(-(abs(X[3])-300)/time,abs(Y[3])/time));
                    Range_creep2[j]->runAction(by);
                }
            }
        }
        
        if(a.melee.HP[j]<=0 && Melee_creep1[j]!=NULL)
        {
            this->removeChild(Melee_creep1[j]);
            Melee_creep1[j]=NULL;
        }
        
        if(a.range.HP[j]<=0 && Range_creep1[j]!=NULL)
        {
            this->removeChild(Range_creep1[j]);
            Range_creep1[j]=NULL;
        }
    }
}





void gamescene_houyi::update_tower1_attack(float t)
{
    for(int j=0;j<creep_i;j++)
    {
        int dis_Melee_creep=1000000,dis_hero=1000000;
        if(flag_creep==true)
        {
            if(b.melee.HP[j]>0)
            {
                dis_Melee_creep=abs(Tower1->getPositionX()-Melee_creep2[j]->getPositionX());
                
                if(dis_Melee_creep<300)
                {
                    pb=Sprite::create("PB01.png");
                    pb->setPosition(Tower1->getPositionX(),Tower1->getPositionY()+50);
                    this->addChild(pb);
                    auto to=MoveTo::create(0.2,Vec2(Melee_creep2[j]->getPositionX(),Melee_creep2[j]->getPositionY()));
                    auto hide=Hide::create();
                    pb->runAction(CCSequence::create(to,hide,NULL));
                    b.melee.HP[j]-=a.tower.base_damage;
                    
                }
            }
            else if(b.range.HP[j]>0)
            {
                dis_Melee_creep=abs(Tower1->getPositionX()-Range_creep2[j]->getPositionX());
                if(dis_Melee_creep<300)
                {
                    pb=Sprite::create("PB01.png");
                    pb->setPosition(Tower1->getPositionX(),Tower1->getPositionY()+50);
                    this->addChild(pb);
                    auto to=MoveTo::create(0.2,Vec2(Range_creep2[j]->getPositionX(),Range_creep2[j]->getPositionY()));
                    auto hide=Hide::create();
                    pb->runAction(CCSequence::create(to,hide,NULL));
                    b.range.HP[j]-=a.tower.base_damage;
                    
                }
            }
            else if(b.catapult.HP[j]>0)
            {
                dis_Melee_creep=abs(Tower1->getPositionX() -Catapult2[j]->getPositionX());
                if(dis_Melee_creep<300)
                {
                    pb=Sprite::create("PB01.png");
                    pb->setPosition(Tower1->getPositionX(),Tower1->getPositionY()+50);
                    this->addChild(pb);
                    auto to=MoveTo::create(0.2,Vec2(Catapult2[j]->getPositionX(),Catapult2[j]->getPositionY()));
                    auto hide=Hide::create();
                    pb->runAction(CCSequence::create(to,hide,NULL));
                    b.catapult.HP[j]-=a.tower.base_damage;
                    
                }
            }
        }
        
        if(b.melee.HP[j]<=0 && Melee_creep2[j]!=NULL)
        {
            this->removeChild(Melee_creep2[j]);
            Melee_creep2[j]=NULL;
            a.hero1.gold+=20;
            a.hero1.exp+=10;
        }
        if(b.range.HP[j]<=0 && Range_creep2[j]!=NULL)
        {
            this->removeChild(Range_creep2[j]);
            Range_creep2[j]=NULL;
            a.hero1.gold+=50;
            a.hero1.exp+=15;
        }
        if(b.catapult.HP[j]<=0 && Catapult2[j]!=NULL)
        {
            this->removeChild(Catapult2[j]);
            Catapult2[j]=NULL;
            a.hero1.gold+=50;
            a.hero1.exp+=20;
        }
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
                    if(dis_Melee_creep<300)
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
                    if(dis_Range_creep<300)
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
                    if(dis_Catapult<300)
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
                    if(dis_hero<300)
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
        if(a.hero1.HP>0 && attack_flag==false)
        {
            dis_hero=abs(Tower2->getPositionX()-sprite->getPositionX());
            if(dis_hero<300)
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
    
    
    for(int j=0;j<creep_i;j++)
    {
        
        if(a.melee.HP[j]<=0 && Melee_creep1[creep_i]!=NULL)
        {
            this->removeChild(Melee_creep1[j]);
            Melee_creep1[j]=NULL;
            b.hero1.gold+=20;
            b.hero1.exp+=10;
        }
        if(a.range.HP[j]<=0 && Range_creep1[creep_i]!=NULL)
        {
            this->removeChild(Range_creep1[j]);
            Range_creep1[j]=NULL;
            b.hero1.gold+=50;
            b.hero1.exp+=15;
        }
        if(a.catapult.HP[j]<=0 && Catapult1[creep_i]!=NULL)
        {
            this->removeChild(Catapult1[creep_i]);
            Catapult1[j]=NULL;
            b.hero1.gold+=50;
            b.hero1.exp+=20;
        }
        
    }
    
    
}



int gamescene_houyi::getDistance(Sprite *target1 ,Sprite *target2)
{
    int X=target1->getPositionX()-target2->getPositionX();
    int Y=target1->getPositionY()-target2->getPositionY();
    return sqrt(X*X+Y*Y);
}



//void gamescene_houyi::boundingbox_update(float t)
//{
//    if(a.melee.HP[creep_i]>0 && b.melee.HP[creep_i]>0)
//    {
//        if(Melee_creep1[creep_i]->boundingBox().intersectsRect(Melee_creep2[creep_i]->boundingBox()))
//        {
//            Melee_creep1[creep_i]->stopAllActions();
//        }
//    }
//}

void gamescene_houyi::update_ai(float t)
{
    if(b.hero1.HP>b.hero1.HP_max/2)
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
        dis[12]=abs(ai->getPositionX()-sprite->getPositionX());
        dis[13]=abs(ai->getPositionX()-Tower1->getPositionX());
        dis[14]=abs(ai->getPositionX()-Crystal1->getPositionX());
        if(dis[12]<min_dis)
        {
            min_dis=dis[12];
            target=sprite;
        }
        if(dis[13]<min_dis)
        {
            min_dis=dis[13];
            target=Tower1;
        }
        if(dis[14]<min_dis)
        {
            min_dis=dis[14];
            target=Crystal1;
        }

        if(min_dis<=100)
        {
            if(target==sprite)
                a.hero1.HP-=b.hero1.base_damage;
            else if(target==Tower1)
                a.tower.HP-=b.hero1.base_damage;
            else if(target==Crystal1)
                a.crystal.HP-=b.hero1.base_damage;
            else
            {
                for(int i=0;i<4;i++)
                {
                    if(target==Melee_creep1[creep_i-i-1])
                        a.melee.HP[creep_i-i-1]-=b.hero1.base_damage;
                    else if(target==Range_creep1[creep_i-i-1])
                        a.range.HP[creep_i-i-1]-=b.hero1.base_damage;
                    else if(target==Catapult1[creep_i-i-1])
                        a.catapult.HP[creep_i-i-1]-=b.hero1.base_damage;
                }
            }
        }
        else
        {
            auto by=MoveBy::create(1,Vec2(-100,0));
            ai->runAction(by);
        }
    }
    else if(b.hero1.HP>0)
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
    if(b.tower.HP>0)
        this->getBloodbar(Tower2,(1000-b.tower.HP)/10);
    else if(Tower2!=NULL)
    {
        this->removeChild(Tower2);
        Tower2=NULL;
        a.hero1.gold+=200;
    }
    if(a.tower.HP>0)
        this->getBloodbar(Tower1,(1000-a.tower.HP)/10);
    else if(Tower1!=NULL)
    {
        this->removeChild(Tower1);
        Tower1=NULL;
    }
    if(a.hero1.HP>0)
        this->getBloodbar(sprite,(a.hero1.HP_max-a.hero1.HP)/(a.hero1.HP_max/100));
    if(b.hero1.HP>0)
        this->getBloodbar(ai,(b.hero1.HP_max-b.hero1.HP)/(b.hero1.HP_max/100));
    else if(sprite!=NULL)
    {
        this->removeChild(sprite);
        sprite=NULL;
        flag_heroalive=false;
    }
    if(a.crystal.HP>0)
        this->getBloodbar(Crystal1, (3000-a.crystal.HP)/30);
    else if(Crystal1!=NULL)
    {
        this->removeChild(Crystal1);
        Crystal1=NULL;
        auto label=Label::create("YOU LOSE!","Marker Felt",50);
        label->setPosition(512,384);
        this->addChild(label,8);
    }
    if(b.crystal.HP>0)
        this->getBloodbar(Crystal2, (3000-b.crystal.HP)/30);
    else if(Crystal2!=NULL)
    {
        this->removeChild(Crystal2);
        std::cout<<"win!"<<std::endl;
        Crystal2=NULL;
        auto label=Label::create("YOU WIN!","Marker Felt",50);
        label->setPosition(512,384);
        this->addChild(label,8);
    }
    if(sprite!=NULL)
    {
        if(sprite->getPositionX()<Crystal1->getPositionX()-300)
        {
            if(a.hero1.HP<a.hero1.HP_max)
                a.hero1.HP+=a.hero1.HP_max/50;
            else if(a.hero1.HP>a.hero1.HP_max)
                a.hero1.HP=a.hero1.HP_max;
            this->getBloodbar1(sprite, (a.hero1.HP_max-a.hero1.HP)/(a.hero1.HP_max/100));
        }
    }
    if(ai!=NULL)
    {
        if(ai->getPositionX()>Crystal2->getPositionX()+300)
        {
            if(b.hero1.HP<b.hero1.HP_max)
                b.hero1.HP+=b.hero1.HP_max/50;
            else if(b.hero1.HP>b.hero1.HP_max)
                b.hero1.HP=b.hero1.HP_max;
            this->getBloodbar1(ai, (b.hero1.HP_max-b.hero1.HP)/(b.hero1.HP_max/100));
        }
    }
}


void gamescene_houyi::hero_Attack()
{
    int X=-sprite->getPositionX()+flag_sprite->getPositionX();
    int Y=-sprite->getPositionY()+flag_sprite->getPositionY();
    int t=sqrt(X*X+Y*Y)/200;
    auto by=MoveBy::create(t, Vec2(X,Y));
    this->unschedule(schedule_selector(gamescene_houyi::boundingbox_update1));
    this->schedule(schedule_selector(gamescene_houyi::boundingbox_update1),0.1);
}

void gamescene_houyi::boundingbox_update1(float t)
{
    if(sprite!=NULL && flag_sprite!=NULL)
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
                        b.melee.HP[i]-=a.hero1.base_damage;
                        if(b.melee.HP[i]<=0)
                            flag_sprite=NULL;
                    }
                    else if(flag_sprite==Range_creep2[i])
                    {
                        b.range.HP[i]-=a.hero1.base_damage;
                        if(b.range.HP[i]<=0)
                            flag_sprite=NULL;
                    }
                    else if(flag_sprite==Catapult2[i])
                    {
                        b.catapult.HP[i]-=a.hero1.base_damage;
                        if(b.catapult.HP[i]<=0)
                            flag_sprite=NULL;
                    }
                }
                if(flag_sprite==Tower2)
                {
                    b.tower.HP-=a.hero1.base_damage;
                    if(b.tower.HP<=0)
                        flag_sprite=NULL;
                }
                else if(flag_sprite==Crystal2)
                {
                    b.crystal.HP-=a.hero1.base_damage;
                    if(b.crystal.HP<=0)
                        flag_sprite=NULL;
                }
            }
        }
    }
    if(flag_sprite==NULL)
        hero_attack_target=false;
}

void gamescene_houyi::boundingbox_update(float t)
{
//    if(Melee_creep1[melee1_j]!=NULL)
//    {
//        if(melee1_target!=NULL)
//        {
//            if(Melee_creep1[melee1_j]->boundingBox().intersectsRect(melee1_target->boundingBox()))
//                Melee_creep1[melee1_j]->stopAllActions();
//        }
//    }
}
void gamescene_houyi::boundingbox_update2(float t)
{
    if(Melee_creep2[melee2_j]!=NULL)
    {
        for(int i=0;i<creep_i;i++)
        {
            if(Melee_creep1[i]!=NULL)
            {
                if(Melee_creep2[melee2_j]->boundingBox().intersectsRect(Melee_creep1[i]->boundingBox()))
                    Melee_creep2[melee2_j]->stopAllActions();
            }
        }
    }
    
    
}






