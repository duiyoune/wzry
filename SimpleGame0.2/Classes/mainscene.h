//
//  main.hpp
//  SimpleGame
//
//  Created by 陈子杰 on 2019/5/7.
//

#ifndef main_hpp
#define main_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class mainscene:public Layer
{
public:
    virtual bool init();
    static Scene* scene();
    CREATE_FUNC(mainscene);
    
private:
    Sprite* pb;
    Sprite* zom;
    void  onMenuItem(Object * obj);
private:
    Sprite* sp;
    
//private:
//    void update(float t);
};


#endif /* main_hpp */
