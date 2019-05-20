//
//  scene1.hpp
//  SimpleGame
//
//  Created by 陈子杰 on 2019/5/8.
//

#ifndef scene1_hpp
#define scene1_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class scene1:public Layer
{
public:
    virtual bool init();
    static Scene* scene();
    CREATE_FUNC(scene1);
private:
    void  onMenuItem1(Ref * obj);
    void  onMenuItem2(Ref * obj);
    void  onMenuItem3(Ref * obj);
};

#endif /* scene1_hpp */
