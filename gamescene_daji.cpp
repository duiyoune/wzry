//
//  gamescene_daji.cpp
//  SimpleGame-mobile
//
//  Created by 陈子杰 on 2019/5/13.
//

#include "gamescene_daji.hpp"
#include "scene1.h"

Scene*gamescene_daji::scene()
{
    auto scene=Scene::create();
    auto layer=gamescene_daji::create();
    scene->addChild(layer);
    return scene;
    
}

bool gamescene_daji::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto sprite=Sprite::create("daji.png");
    sprite->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    this->addChild(sprite);
    
    
    return true;
}
