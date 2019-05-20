//
//  scene1.cpp
//  SimpleGame
//
//  Created by 陈子杰 on 2019/5/8.
//

#include <iostream>
#include "scene1.h"
#include "gamescene_houyi.hpp"
#include "gamescene_daji.hpp"
#include "gamescene_yase.hpp"
Scene * scene1::scene()
{
    auto scene=Scene::create();
    auto layer=scene1::create();
    scene->addChild(layer);
    return scene;
}



bool scene1::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    
    
    MenuItemFont *item1=MenuItemFont::create("后羿",this,menu_selector(scene1::onMenuItem1));
    item1->setPosition(0,0);
    MenuItemFont *item2=MenuItemFont::create("妲己",this,menu_selector(scene1::onMenuItem2));
    item2->setPosition(0,-100);
    MenuItemFont *item3=MenuItemFont::create("亚瑟",this,menu_selector(scene1::onMenuItem3));
    item3->setPosition(0,100);
    
    Menu* menu=Menu::create(item1,item2,item3,NULL);

    this->addChild(menu);
    

    
    return true;
}

void scene1::onMenuItem1(Ref *obj)
{
    Scene* scene=gamescene_houyi::scene();
    auto transitionscene=TransitionFade::create(2, scene);
    Director::getInstance()->replaceScene(transitionscene);
}

void scene1::onMenuItem2(Ref *obj)
{
    Scene* scene=gamescene_daji::scene();
    auto transitionscene=TransitionFade::create(2, scene);
    Director::getInstance()->replaceScene(transitionscene);
}

void scene1::onMenuItem3(Ref *obj)
{
    Scene* scene=gamescene_yase::scene();
    auto transitionscene=TransitionFade::create(2, scene);
    Director::getInstance()->replaceScene(transitionscene);
}

