//
//  gamescene_yase.hpp
//  SimpleGame-mobile
//
//  Created by 陈子杰 on 2019/5/13.
//

#ifndef gamescene_yase_hpp
#define gamescene_yase_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class gamescene_yase:public Layer
{
public:
    virtual bool init();
    static Scene* scene();
    CREATE_FUNC(gamescene_yase);
private:
    void  onMenuItem(Object * obj);
};


#endif /* gamescene_yase_hpp */
