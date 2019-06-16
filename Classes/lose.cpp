#include "lose.h"


USING_NS_CC;

Scene* lose::createScene()
{
	return lose::create();
}

bool lose::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithSystemFont("You lose", "fonts/Marker Felt.ttf", 60);
	this->addChild(label);
	label->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	MenuItemFont *item1 = MenuItemFont::create("END", this, menu_selector(lose::onMenuItem));
	item1->setPosition(0, 100);
	Menu* menu = Menu::create(item1, NULL);
	this->addChild(menu);
	label->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 4);
}

void lose::onMenuItem(Ref *obj)
{
	Director::getInstance()->end();
}