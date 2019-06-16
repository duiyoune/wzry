#ifndef __win_H__
#define __WIN_H__

#include "cocos2d.h"

class win : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	
	void  onMenuItem(Ref * obj);

	CREATE_FUNC(win);
};

#endif 
