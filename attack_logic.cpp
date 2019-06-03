//
//  attack_logic.cpp
//  SimpleGame
//
//  Created by 陈子杰 on 2019/5/21.
//
#include "gamescene_houyi.hpp"

void gamescene_houyi::update_Melee_creep1_attack(float t)
{
    int X[5],Y[5],dis[5];
    for(int i=0;i<5;i++)
    {
        X[i]=100000;
        Y[i]=100000;
        dis[i]=1000000000;
    }
    if(a.melee.HP>0)
    {
        if(b.melee.HP>0)
        {
            X[0]=-Melee_creep1->getPositionX()+Melee_creep2->getPositionX();
            Y[0]=-Melee_creep1->getPositionY()+Melee_creep2->getPositionY();
            dis[0]=X[0]*X[0]+Y[0]*Y[0];
        }
        if(b.crystal.HP>0)
        {
            X[1]=-Melee_creep1->getPositionX()+Crystal2->getPositionX();
            Y[1]=-Melee_creep1->getPositionY()+Crystal2->getPositionY();
            dis[1]=X[1]*X[1]+Y[1]*Y[1];
            
        }
        if(b.tower.HP>0)
        {
            X[2]=-Melee_creep1->getPositionX()+Tower2->getPositionX();
            Y[2]=-Melee_creep1->getPositionY()+Tower2->getPositionY();
            
        }
        if(b.range.HP>0)
        {
            X[3]=-Melee_creep1->getPositionX()+Range_creep2->getPositionX();
            Y[3]=-Melee_creep1->getPositionY()+Range_creep2->getPositionY();
            
        }
        int min_dis=1000000000;
        for(int i=0;i<5;i++)
        {
            if(dis[i]<min_dis)
                min_dis=dis[i];
        }
        double time=sqrt(min_dis)/200;
        
        
        if(min_dis<=2500)
        {
            if(min_dis==dis[0])
                b.melee.HP-=20;
            else if(min_dis==dis[1])
                b.crystal.HP-=20;
            else if(min_dis==dis[2])
                b.tower.HP-=20;
            else
                b.range.HP-=20;
        }
        else
        {
            if(min_dis==dis[0])
            {
                auto by=MoveBy::create(1, Vec2((abs(X[0])-50)/time,abs(Y[0])/time));
                Melee_creep1->runAction(by);
                this->schedule(schedule_selector(gamescene_houyi::boundingbox_update),0.1);
            }
            else if(min_dis==dis[1])
            {
                auto by=MoveBy::create(1, Vec2((abs(X[1])-50)/time,abs(Y[1])/time));
                Melee_creep1->runAction(by);
            }
            else if(min_dis==dis[2])
            {
                auto by=MoveBy::create(1, Vec2((abs(X[2])-50)/time,abs(Y[2])/time));
                Melee_creep1->runAction(by);
            }
            else
            {
                auto by=MoveBy::create(1, Vec2((abs(X[3])-50)/time,abs(Y[3])/time));
                Melee_creep1->runAction(by);
            }
        }
    }
    if(b.tower.HP>0)
        this->getBloodbar(Tower2,(1000-b.tower.HP)/10);
    if(a.tower.HP>0)
        this->getBloodbar(Tower1,(1000-a.tower.HP)/10);
    if(a.hero1.HP>0)
        this->getBloodbar(sprite,(1000-a.hero1.HP)/10);
    if(a.melee.HP>0)
        this->getBloodbar(Melee_creep1,(200-a.melee.HP)/2);
    if(b.melee.HP>0)
        this->getBloodbar(Melee_creep2,(200-b.melee.HP)/2);
    if(a.range.HP>0)
        this->getBloodbar(Range_creep1,100-a.range.HP);
    if(b.range.HP>0)
        this->getBloodbar(Range_creep2,100-b.range.HP);
    
    
    
    if(b.melee.HP<=0)
    {
        this->removeChild(Melee_creep2);
        experience_hero1+=10;
    }
    if(b.range.HP<=0)
    {
        this->removeChild(Range_creep2);
        experience_hero1+=20;
    }
    if(b.tower.HP<=0)
        this->removeChild(Tower2);
    if(b.crystal.HP<=0)
        this->removeChild(Crystal2);
}

void gamescene_houyi::update_Melee_creep2_attack(float t)
{
    int X[5],Y[5],dis[5];
    for(int i=0;i<5;i++)
    {
        X[i]=100000;
        Y[i]=100000;
        dis[i]=1000000000;
    }
    if(b.melee.HP>0)
    {
        if(a.melee.HP>0)
        {
            X[0]=-Melee_creep1->getPositionX()+Melee_creep2->getPositionX();
            Y[0]=-Melee_creep1->getPositionY()+Melee_creep2->getPositionY();
            dis[0]=X[0]*X[0]+Y[0]*Y[0];
        }
        if(a.crystal.HP>0)
        {
            X[1]=-Melee_creep2->getPositionX()+Crystal1->getPositionX();
            Y[1]=-Melee_creep2->getPositionY()+Crystal1->getPositionY();
            dis[1]=X[1]*X[1]+Y[1]*Y[1];
        }
        if(a.tower.HP>0)
        {
            X[2]=-Melee_creep2->getPositionX()+Tower1->getPositionX();
            Y[2]=-Melee_creep2->getPositionY()+Tower1->getPositionY();
            dis[2]=X[2]*X[2]+Y[2]*Y[2];
        }
        if(a.range.HP>0)
        {
            X[3]=-Melee_creep2->getPositionX()+Range_creep1->getPositionX();
            Y[3]=-Melee_creep2->getPositionY()+Range_creep1->getPositionY();
            dis[3]=X[3]*X[3]+Y[3]*Y[3];
        }
        
        int min_dis=1000000000;
        for(int i=0;i<5;i++)
        {
            if(dis[i]<min_dis)
                min_dis=dis[i];
        }
        double time=sqrt(min_dis)/200;
        
        
        if(min_dis<=2500)
        {
            if(min_dis==dis[0])
                a.melee.HP-=20;
            else if(min_dis==dis[1])
                a.crystal.HP-=20;
            else if(min_dis==dis[2])
                a.tower.HP-=20;
            else
                a.range.HP-=20;
        }
        else
        {
            if(min_dis==dis[0])
            {
                auto by=MoveBy::create(1, Vec2(-(abs(X[0])-50)/time,abs(Y[0])/time));
                Melee_creep2->runAction(by);
                
            }
            else if(min_dis==dis[1])
            {
                auto by=MoveBy::create(1, Vec2(-(abs(X[1])-50)/time,abs(Y[1])/time));
                Melee_creep2->runAction(by);
            }
            else if(min_dis==dis[2])
            {
                auto by=MoveBy::create(1, Vec2(-(abs(X[2])-50)/time,abs(Y[2])/time));
                Melee_creep2->runAction(by);
            }
            else
            {
                auto by=MoveBy::create(1, Vec2(-(abs(X[3])-50)/time,abs(Y[3])/time));
                Melee_creep2->runAction(by);
            }
            
        }
    }
    this->getBloodbar(Tower2,(1000-b.tower.HP)/10);
    this->getBloodbar(Tower1,(1000-a.tower.HP)/10);
    this->getBloodbar(sprite,(2000-a.hero1.HP)/20);
    
    if(a.melee.HP<=0)
        this->removeChild(Melee_creep1);
    if(a.range.HP<=0)
        this->removeChild(Range_creep1);
    if(a.tower.HP<=0)
        this->removeChild(Tower1);
    if(a.crystal.HP<=0)
        this->removeChild(Crystal1);
}

void gamescene_houyi::update_Range_creep1_attack(float t)
{
    int X[5],Y[5],dis[5];
    for(int i=0;i<5;i++)
    {
        X[i]=100000;
        Y[i]=100000;
        dis[i]=1000000000;
    }
    if(a.range.HP>0)
    {
        if(b.melee.HP>0)
        {
            X[0]=-Range_creep1->getPositionX()+Melee_creep2->getPositionX();
            Y[0]=-Range_creep1->getPositionY()+Melee_creep2->getPositionY();
            dis[0]=X[0]*X[0]+Y[0]*Y[0];
        }
        if(b.crystal.HP>0)
        {
            X[1]=-Range_creep1->getPositionX()+Crystal2->getPositionX();
            Y[1]=-Range_creep1->getPositionY()+Crystal2->getPositionY();
            dis[1]=X[1]*X[1]+Y[1]*Y[1];
        }
        if(b.tower.HP>0)
        {
            X[2]=-Range_creep1->getPositionX()+Tower2->getPositionX();
            Y[2]=-Range_creep1->getPositionY()+Tower2->getPositionY();
            dis[2]=X[2]*X[2]+Y[2]*Y[2];
        }
        if(b.range.HP>0)
        {
            X[3]=-Range_creep1->getPositionX()+Range_creep2->getPositionX();
            Y[3]=-Range_creep1->getPositionY()+Range_creep2->getPositionY();
            dis[3]=X[3]*X[3]+Y[3]*Y[3];
        }
        
        int min_dis=1000000000;
        for(int i=0;i<5;i++)
        {
            if(dis[i]<min_dis)
                min_dis=dis[i];
        }
        double time=sqrt(min_dis)/200;
        
        
        if(min_dis<=90000)
        {
            if(min_dis==dis[0])
                b.melee.HP-=20;
            else if(min_dis==dis[1])
                b.crystal.HP-=20;
            else if(min_dis==dis[2])
                b.tower.HP-=20;
            else
                b.range.HP-=20;
        }
        else
        {
            if(min_dis==dis[0])
            {
                auto by=MoveBy::create(1, Vec2((abs(X[0])-300)/time,abs(Y[0])/time));
                Range_creep1->runAction(by);
                
            }
            else if(min_dis==dis[1])
            {
                auto by=MoveBy::create(1, Vec2((abs(X[1])-300)/time,abs(Y[1])/time));
                Range_creep1->runAction(by);
            }
            else if(min_dis==dis[2])
            {
                auto by=MoveBy::create(1, Vec2((abs(X[2])-300)/time,abs(Y[2])/time));
                Range_creep1->runAction(by);
            }
            else if(min_dis==dis[3])
            {
                auto by=MoveBy::create(1, Vec2((abs(X[3])-300)/time,abs(Y[3])/time));
                Range_creep1->runAction(by);
            }
        }
    }
    this->getBloodbar(Tower2,(1000-b.tower.HP)/10);
    this->getBloodbar(Tower1,(1000-b.tower.HP)/10);
    this->getBloodbar(sprite,(2000-b.hero1.HP)/20);
    
    if(b.melee.HP<=0)
        this->removeChild(Melee_creep2);
    if(b.tower.HP<=0)
        this->removeChild(Tower2);
    if(b.crystal.HP<=0)
        this->removeChild(Crystal2);
    if(b.range.HP<=0)
        this->removeChild(Range_creep2);
}

void gamescene_houyi::update_Range_creep2_attack(float t)
{
    int X[5],Y[5],dis[5];
    for(int i=0;i<5;i++)
    {
        X[i]=100000;
        Y[i]=100000;
        dis[i]=1000000000;
    }
    if(b.range.HP>0)
    {
        if(a.melee.HP>0)
        {
            X[0]=-Melee_creep1->getPositionX()+Range_creep2->getPositionX();
            Y[0]=-Melee_creep1->getPositionY()+Range_creep2->getPositionY();
            dis[0]=X[0]*X[0]+Y[0]*Y[0];
        }
        if(a.crystal.HP>0)
        {
            X[1]=-Range_creep2->getPositionX()+Crystal1->getPositionX();
            Y[1]=-Range_creep2->getPositionY()+Crystal1->getPositionY();
            dis[1]=X[1]*X[1]+Y[1]*Y[1];
        }
        if(a.tower.HP>0)
        {
            X[2]=-Range_creep2->getPositionX()+Tower1->getPositionX();
            Y[2]=-Range_creep2->getPositionY()+Tower1->getPositionY();
            dis[2]=X[2]*X[2]+Y[2]*Y[2];
        }
        if(a.range.HP>0)
        {
            X[3]=-Range_creep2->getPositionX()+Range_creep1->getPositionX();
            Y[3]=-Range_creep2->getPositionY()+Range_creep1->getPositionY();
            dis[3]=X[3]*X[3]+Y[3]*Y[3];
        }
        
        int min_dis=1000000000;
        for(int i=0;i<5;i++)
        {
            if(dis[i]<min_dis)
                min_dis=dis[i];
        }
        double time=sqrt(min_dis)/200;
        
        
        if(min_dis<=90000)
        {
            if(min_dis==dis[0])
                a.melee.HP-=20;
            else if(min_dis==dis[1])
                a.crystal.HP-=20;
            else if(min_dis==dis[2])
                a.tower.HP-=20;
            else
                a.range.HP-=20;
        }
        else
        {
            if(min_dis==dis[0])
            {
                auto by=MoveBy::create(1, Vec2(-(abs(X[0])-300)/time,abs(Y[0])/time));
                Range_creep2->runAction(by);
                
            }
            else if(min_dis==dis[1])
            {
                auto by=MoveBy::create(1, Vec2(-(abs(X[1])-300)/time,abs(Y[1])/time));
                Range_creep2->runAction(by);
            }
            else if(min_dis==dis[2])
            {
                auto by=MoveBy::create(1, Vec2(-(abs(X[2])-300)/time,abs(Y[2])/time));
                Range_creep2->runAction(by);
            }
            else
            {
                auto by=MoveBy::create(1, Vec2(-(abs(X[3])-300)/time,abs(Y[3])/time));
                Range_creep2->runAction(by);
            }
        }
    }
    this->getBloodbar(Tower2,(1000-b.tower.HP)/10);
    this->getBloodbar(Tower1,(1000-a.tower.HP)/10);
    this->getBloodbar(sprite,(2000-a.hero1.HP)/20);
    
    if(a.melee.HP<=0)
        this->removeChild(Melee_creep1);
    if(a.tower.HP<=0)
        this->removeChild(Tower1);
    if(a.crystal.HP<=0)
        this->removeChild(Crystal1);
    if(a.range.HP<=0)
        this->removeChild(Range_creep1);
}



void gamescene_houyi::update_tower2_attack(float t)
{
    int dis_Melee_creep=1000000,dis_hero=1000000;
    if(flag_creep==true)
    {
        if(a.melee.HP>0)
        {
            dis_Melee_creep=sqrt((Tower2->getPositionX()-Melee_creep1->getPositionX())*(Tower2->getPositionX()-Melee_creep1->getPositionX())+(Tower2->getPositionY()-Melee_creep1->getPositionY())*(Tower2->getPositionY()-Melee_creep1->getPositionY()));
            if(dis_Melee_creep<500)
            {
                pb=Sprite::create("PB01.png");
                pb->setPosition(Tower2->getPositionX(),Tower2->getPositionY()+50);
                this->addChild(pb);
                auto to=MoveTo::create(0.2,Vec2(Melee_creep1->getPositionX(),Melee_creep1->getPositionY()));
                auto hide=Hide::create();
                pb->runAction(CCSequence::create(to,hide,NULL));
                a.melee.HP-=20;
                
            }
        }
        else if(a.range.HP>0)
        {
            dis_Melee_creep=sqrt((Tower2->getPositionX()-Range_creep1->getPositionX())*(Tower2->getPositionX()-Range_creep1->getPositionX())+(Tower2->getPositionY()-Range_creep1->getPositionY())*(Tower2->getPositionY()-Range_creep1->getPositionY()));
            if(dis_Melee_creep<500)
            {
                pb=Sprite::create("PB01.png");
                pb->setPosition(Tower2->getPositionX(),Tower2->getPositionY()+50);
                this->addChild(pb);
                auto to=MoveTo::create(0.2,Vec2(Range_creep1->getPositionX(),Range_creep1->getPositionY()));
                auto hide=Hide::create();
                pb->runAction(CCSequence::create(to,hide,NULL));
                a.range.HP-=20;
                
            }
        }
        else if(a.catapult.HP>0)
        {
            dis_Melee_creep=sqrt((Tower2->getPositionX()-Catapult1->getPositionX())*(Tower2->getPositionX()-Catapult1->getPositionX())+(Tower2->getPositionY()-Catapult1->getPositionY())*(Tower2->getPositionY()-Catapult1->getPositionY()));
            if(dis_Melee_creep<500)
            {
                pb=Sprite::create("PB01.png");
                pb->setPosition(Tower2->getPositionX(),Tower2->getPositionY()+50);
                this->addChild(pb);
                auto to=MoveTo::create(0.2,Vec2(Catapult1->getPositionX(),Catapult1->getPositionY()));
                auto hide=Hide::create();
                pb->runAction(CCSequence::create(to,hide,NULL));
                a.catapult.HP-=20;
                
            }
        }
        if(a.hero1.HP>0)
        {
            dis_hero=sqrt((Tower2->getPositionX()-sprite->getPositionX())*(Tower2->getPositionX()-sprite->getPositionX())+(Tower2->getPositionY()-sprite->getPositionY())*(Tower2->getPositionY()-sprite->getPositionY()));
            if(dis_hero<500 && dis_Melee_creep>500)
            {
                pb=Sprite::create("PB01.png");
                pb->setPosition(Tower2->getPositionX(),Tower2->getPositionY()+50);
                this->addChild(pb);
                auto to=MoveTo::create(0.2,Vec2(sprite->getPositionX(),sprite->getPositionY()));
                auto hide=Hide::create();
                pb->runAction(CCSequence::create(to,hide,NULL));
                a.hero1.HP-=20;
            }
        }
    }
    
    
    if(a.melee.HP<=0)
        this->removeChild(Melee_creep1);
    if(a.range.HP<=0)
        this->removeChild(Range_creep1);
    if(a.catapult.HP<=0)
        this->removeChild(Catapult1);
}


void gamescene_houyi::update_tower1_attack(float t)
{
    int dis_Melee_creep=1000000,dis_hero=1000000;
    if(flag_creep==true)
    {
        if(b.melee.HP>0)
        {
            dis_Melee_creep=sqrt((Tower1->getPositionX()-Melee_creep2->getPositionX())*(Tower1->getPositionX()-Melee_creep2->getPositionX())+(Tower1->getPositionY()-Melee_creep2->getPositionY())*(Tower1->getPositionY()-Melee_creep2->getPositionY()));
            
            if(dis_Melee_creep<500)
            {
                pb=Sprite::create("PB01.png");
                pb->setPosition(Tower1->getPositionX(),Tower1->getPositionY()+50);
                this->addChild(pb);
                auto to=MoveTo::create(0.2,Vec2(Melee_creep2->getPositionX(),Melee_creep2->getPositionY()));
                auto hide=Hide::create();
                pb->runAction(CCSequence::create(to,hide,NULL));
                b.melee.HP-=20;
                
            }
        }
        else if(b.range.HP>0)
        {
            dis_Melee_creep=sqrt((Tower1->getPositionX()-Range_creep2->getPositionX())*(Tower1->getPositionX()-Range_creep2->getPositionX())+(Tower1->getPositionY()-Range_creep2->getPositionY())*(Tower1->getPositionY()-Range_creep2->getPositionY()));
            if(dis_Melee_creep<500)
            {
                pb=Sprite::create("PB01.png");
                pb->setPosition(Tower1->getPositionX(),Tower1->getPositionY()+50);
                this->addChild(pb);
                auto to=MoveTo::create(0.2,Vec2(Range_creep2->getPositionX(),Range_creep2->getPositionY()));
                auto hide=Hide::create();
                pb->runAction(CCSequence::create(to,hide,NULL));
                b.range.HP-=20;
                
            }
        }
        else if(b.catapult.HP>0)
        {
            dis_Melee_creep=sqrt((Tower1->getPositionX()-Catapult2->getPositionX())*(Tower1->getPositionX()-Catapult2->getPositionX())+(Tower1->getPositionY()-Catapult2->getPositionY())*(Tower1->getPositionY()-Catapult2->getPositionY()));
            if(dis_Melee_creep<500)
            {
                pb=Sprite::create("PB01.png");
                pb->setPosition(Tower1->getPositionX(),Tower1->getPositionY()+50);
                this->addChild(pb);
                auto to=MoveTo::create(0.2,Vec2(Catapult2->getPositionX(),Catapult2->getPositionY()));
                auto hide=Hide::create();
                pb->runAction(CCSequence::create(to,hide,NULL));
                b.catapult.HP-=20;
                
            }
        }
    }
    
    if(b.melee.HP<=0)
        this->removeChild(Melee_creep2);
    if(b.range.HP<=0)
        this->removeChild(Range_creep2);
    if(b.catapult.HP<=0)
        this->removeChild(Catapult2);
    
}



int gamescene_houyi::getDistance(Sprite *target1 ,Sprite *target2)
{
    int X=target1->getPositionX()-target2->getPositionX();
    int Y=target1->getPositionY()-target2->getPositionY();
    return sqrt(X*X+Y*Y);
}



void gamescene_houyi::boundingbox_update(float t)
{
    if(a.melee.HP>0 && b.melee.HP>0)
    {
        if(Melee_creep1->boundingBox().intersectsRect(Melee_creep2->boundingBox()))
        {
            Melee_creep1->stopAllActions();
        }
    }
}
