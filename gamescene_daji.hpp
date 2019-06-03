//
//  gamescene_daji.hpp
//  SimpleGame-mobile
//
//  Created by 陈子杰 on 2019/5/13.
//

#ifndef gamescene_daji_hpp
#define gamescene_daji_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class gamescene_daji:public Layer
{
public:
    virtual bool init();
    static Scene* scene();
    CREATE_FUNC(gamescene_daji);
private:
    void  onMenuItem(Object * obj);
};


#endif /* gamescene_daji_hpp */
