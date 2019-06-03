//
//  gamescene_yase.cpp
//  SimpleGame-mobile
//
//  Created by 陈子杰 on 2019/5/13.
//

#include "gamescene_yase.hpp"
#include "scene1.h"

Scene* gamescene_yase::scene()
{
    auto scene=Scene::create();
    auto layer=gamescene_yase::create();
    scene->addChild(layer);
    return scene;
    
}

bool gamescene_yase::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto sprite=Sprite::create("yase.png");
    sprite->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    this->addChild(sprite);
    
    
    return true;
}
