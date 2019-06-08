#include "cocos2d.h" 

#define USING_NS_CC using namespace cocos

class About : public cocos2d::CCLayer
{
public:
	About(void);
	~About(void);

	virtual bool init();
	static cocos2d::CCScene *scene();
	CREATE_FUNC(About);

	void clickCallBack1(CCObject *sender);
	void clickCallBack2(CCObject *sender);
	void clickCallBack3(CCObject *sender);

	void addBtn();
	void addHero();


};



