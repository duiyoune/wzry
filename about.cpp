#include "about.h"
#include "Welcome.h"

USING_NS_CC;

About::About(void)
{
}

About::~About(void)
{
}

CCScene *About::scene()
{
	CCScene *scene = CCScene::create();
	About *layer = About::create();
	scene->addChild(layer);
	return scene;
}

bool About::init()
{
	if (!CCLayer::init())
	{
		return false;
	}


	//CCLabelTTF* pLabel2;pLabel2 = CCLabelTTF::create("LazyGame", "Arial", 24+20);
	//pLabel2->setPosition(ccp(origin.x + vSize.width/2,origin.y + vSize.height - pLabel2->getContentSize().height));
	//this->addChild(pLabel2);
	addHero();
	addBtn();


	return true;
}

void About::addBtn()
{
	CCSize vSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	// add some btns
	CCMenuItemImage *btn1 = CCMenuItemImage::create("about/clickme.png", "about/clickme-down.png", this, menu_selector(About::clickCallBack1));
	CCMenuItemImage *btn2 = CCMenuItemImage::create("about/clickme.png", "about/clickme-down.png", this, menu_selector(About::clickCallBack2));
	CCMenuItemImage *btn3 = CCMenuItemImage::create("about/clickme.png", "about/clickme-down.png", this, menu_selector(About::clickCallBack3));
	btn1->setPosition(ccp(vSize.width - btn1->getContentSize().width / 2, btn1->getContentSize().height));
	btn2->setPosition(ccp(vSize.width - btn1->getContentSize().width / 2, btn1->getContentSize().height * 2));
	btn3->setPosition(ccp(vSize.width - btn1->getContentSize().width / 2, btn1->getContentSize().height * 3));
	btn1->setScale(0.5);
	btn2->setScale(0.5);
	btn3->setScale(0.5);
	CCMenu *menu = CCMenu::create(btn1, btn2, btn3, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);
}


void About::addHero()
{
	// Init Hero
	CCSize vSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCSprite *hero = CCSprite::create("hero/20005_stand_1.png");
	hero->setPosition(ccp(hero->getContentSize().width / 2, vSize.height / 2));
	this->addChild(hero);

	//Õ¾Á¢animate
	CCAnimation *animation = CCAnimation::create();
	for (int i = 1; i <= 7; i += 2)
	{
		char szImageFileName[128] = { 0 };
		sprintf(szImageFileName, "hero/20005_stand_%d.png", i);
		animation->addSpriteFrameWithFileName(szImageFileName);
	}
	//animation->setDelayPerUnit(0.5f / 4.0f);   
	animation->setDelayPerUnit(0.5f / 4.0f);
	//animation->setLoops(-1);
	CCAnimate *actStand = CCAnimate::create(animation);

	//Éä¼ýanimate
	CCAnimation *animationShoot = CCAnimation::create();
	for (int i = 1; i <= 23; i += 2)
	{
		char szImageFileName[128] = { 0 };
		sprintf(szImageFileName, "hero/20005_%d.png", i);
		animationShoot->addSpriteFrameWithFileName(szImageFileName);
	}
	animationShoot->setDelayPerUnit(1.0f / 10.0f);
	//animationShoot->setLoops(-1);
	CCAnimate *actShoot = CCAnimate::create(animationShoot);
	//hero->runAction(actShoot);
}

void About::clickCallBack1(CCObject *sender)
{
	CCLOG("clickCallBack1");
	//hero->runAction(actStand);
	//hero->setScale(3);
}
void About::clickCallBack2(CCObject *sender)
{
	CCLOG("clickCallBack2");
	//hero->setScale(1);
}
void About::clickCallBack3(CCObject *sender)
{
	CCLOG("clickCallBack3");
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCScene *welcome = Welcome::scene();
	pDirector->replaceScene(CCTransitionFade::create(0.5, welcome));

}