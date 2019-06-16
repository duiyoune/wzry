//
//  main.cpp
//  SimpleGame
//
//  Created by 陈子杰 on 2019/5/7.
//
#include <iostream>
#include "mainscene.h"
#include "scene1.h"
Scene * mainscene::scene()
{
    auto scene=Scene::create();
    auto layer=mainscene::create();
    scene->addChild(layer);
    return scene;
}



bool mainscene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
	auto sprite = Sprite::create("3.jpg");
	sprite->setPosition(visibleSize.width / 2, visibleSize.height /1.3);
	this->addChild(sprite);
	
	
	auto closeItem = MenuItemImage::create("chu.jpg","chu.jpg",CC_CALLBACK_1(mainscene::menuCloseCallback, this));
	auto start = MenuItemImage::create("jin.jpg", "jin.jpg",CC_CALLBACK_1(mainscene::onMenuItem, this));
	auto menust = Menu::create(start, NULL);
    Menu* menu=Menu::create(closeItem,NULL);
	menust->setPosition(visibleSize.width / 2, visibleSize.height / 2.5);
	this->addChild(menust, 1);
    menu->setPosition(visibleSize.width/2,visibleSize.height/7);
    this->addChild(menu);

    return true;
}

void mainscene::onMenuItem(Object *obj)
{
    Scene* scene=scene1::scene();
    auto transitionscene=TransitionFade::create(2, scene);
    Director::getInstance()->replaceScene(transitionscene);
}

void mainscene::menuCloseCallback(Ref* pSender)
{

	Director::getInstance()->end();



}

