//
//  mouse_click.cpp
//  SimpleGame
//
//  Created by 陈子杰 on 2019/6/3.
//

//#include "mouse_click.hpp"
//
//
////是否点击敌方小兵以攻击
//void mouse_click::clickCreep_enemy(float X, float Y)
//{
//    for (int i = 0; i < 600; i++)
//    {
//        if (creep_enemy[i] != nullptr)
//        {
//            float positionX_creep = creep_enemy[i]->getPositionX();
//            float positionY_creep = creep_enemy[i]->getPositionY();
//            float contentSizeX = creep_enemy[i]->getContentSize().width;
//            float contentSizeY = creep_enemy[i]->getContentSize().height;
//            float area_creepXmin = positionX_creep - 0.5*contentSizeX;
//            float area_creepXmax = positionX_creep + 0.5*contentSizeX;
//            float area_creepYmin = positionY_creep - 0.5*contentSizeY;
//            float area_creepYmax = positionY_creep + 0.5*contentSizeY;
//            if (X >= area_creepXmin && X <= area_creepXmax && Y >= area_creepYmin && Y <= area_creepYmax)
//            {
//                //攻击
//                attack_heroAcreep = true;
//                attack_target = i;
//                break;
//            }
//        }
//    }
//}
//
//
////鼠标按下
//void mouse_click::onMouseDown(Event *event)
//{
//    EventMouse* e = (EventMouse*)event;
//    //获取鼠标点击位置
//    float cursorX = e->getCursorX();
//    float cursorY = e->getCursorY();
//    //获取技能3目标
//    if (ability3Clicked==true|| ability3Moving==true)
//    {
//        //判断技能3是否作用于敌方单位
//        ability3Hit(cursorX, cursorY);
//        return;
//    }
//    if (hero != nullptr)
//    {
//        //英雄随鼠标移动
//        moveWithMouse(cursorX, cursorY);
//        //是否点击敌方小兵以攻击
//        clickCreep_enemy(cursorX, cursorY);
//    }
//}
