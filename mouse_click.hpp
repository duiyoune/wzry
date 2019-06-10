//
//  mouse_click.hpp
//  SimpleGame
//
//  Created by 陈子杰 on 2019/6/3.
//

#ifndef mouse_click_hpp
#define mouse_click_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "../extensions/cocos-ext.h"
#include "attr_init.hpp"
USING_NS_CC;

class mouse_click:public Layer
{
    void clickCreep_enemy(float X, float Y);
    void onMouseDown(Event *event);
};
#endif /* mouse_click_hpp */
