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
    

    
    MenuItemFont *item=MenuItemFont::create("Start",this,menu_selector(mainscene::onMenuItem));
    Menu* menu=Menu::create(item,NULL);
    menu->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(menu);

    return true;
}

void mainscene::onMenuItem(Object *obj)
{
    Scene* scene=scene1::scene();
    auto transitionscene=TransitionFade::create(2, scene);
    Director::getInstance()->replaceScene(transitionscene);
}
