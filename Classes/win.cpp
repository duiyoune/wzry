#include "win.h"


USING_NS_CC;

Scene* win::createScene()
{
	return win::create();
}

bool win::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithSystemFont("You Win", "fonts/Marker Felt.ttf", 60);
	this->addChild(label);
	label->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	MenuItemFont *item1 = MenuItemFont::create("END", this, menu_selector(win::onMenuItem));
	item1->setPosition(0, 100);
	Menu* menu = Menu::create(item1, NULL);
	this->addChild(menu);
	label->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 4);
}

void win::onMenuItem(Ref* pSender)
{
	Director::getInstance()->end();
}