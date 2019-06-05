#include "Game1Scene.h"
#include "SimpleAudioEngine.h"
#include<math.h>
#include<iostream>
#include<string.h>
#include "ui/CocosGUI.h"
#include "ui/UILoadingBar.h"
using namespace ui;
using namespace std;
using namespace CocosDenshion;
USING_NS_CC;
Scene* Game1::createScene()
{
	return Game1::create();
}
bool Game1::init()
{
	if (!Scene::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();	
	UI();//界面
	creep();//小兵
	hero_BM();//英雄
	_event();//事件
	tool();//工具
	return true;
}
