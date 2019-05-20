//
//  gamescene.hpp
//  SimpleGame
//
//  Created by 陈子杰 on 2019/5/12.
//

#ifndef gamescene_houyi_hpp
#define gamescene_houyi_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "../extensions/cocos-ext.h"
USING_NS_CC;


class gamescene_houyi:public Layer
{   
public:
    virtual bool init();
    static Scene* scene();
    CREATE_FUNC(gamescene_houyi);


private:
    void onMenuItem(Ref * obj);
    void update_xiaobing(float t);
    void update_xiaobing1_attack(float t);
    void update_xiaobing2_attack(float t);
    void update_tower2_attack(float t);
    void onMouseMove(Event * event);
    void getBloodbar(Sprite *guaisprite ,float a);
//    int getDistance(Sprite *target1 ,Sprite *target2);
private:
    Sprite * sprite;
    Sprite * xiaobing1;
    Sprite * xiaobing2;
    Sprite * crystal1;
    Sprite * crystal2;
    Sprite * tower1;
    Sprite * tower2;
    

};

#endif /* gamescene_houyi_hpp */
