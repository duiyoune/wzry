#ifndef __lose_H__
#define __lose_H__

#include "cocos2d.h"

class lose : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void  onMenuItem(Ref * obj);

	CREATE_FUNC(lose);
};

#endif 
