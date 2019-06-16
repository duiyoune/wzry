//
//  ai.cpp
//  SimpleGame
//
//  Created by 陈子杰 on 2019/6/11.
//

//#include "ai.hpp"
//void ai::hero_ai(Layer * layer)
//{
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    ai = Sprite::create("HelloWorld.png");
//    ai->setPosition(3000,visibleSize.height/2);
//    layer->addChild(ai, 89);
//    //ai—™Ãı
//    //aiπ•ª˜
//    layer->schedule(schedule_selector(ai::attack_aiUpdate), 1);
//    //ai◊‘∂Øªÿ—™
//    layer->schedule(schedule_selector(ai::healthRegen_aiUpdate), 0.01);
//}
////ai––∂Ø
//void ai::aiAction(Layer *layer)
//{
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    if (ai != nullptr)
//    {
//        if (HP_ai >= Max_HP_ai/2)
//        {
//            aiRetreat = false;
//            if (aiAssault == false)
//            {
//                float X = 0;
//                float Y = visibleSize.height / 2 ;
//                float positionX = ai->getPositionX();
//                float positionY = ai->getPositionY();
//                float distance = sqrt(pow(X-positionX, 2) + pow(Y-positionY, 2));
//                float time = distance / 200;
//                auto assault = MoveTo::create(time, Vec2(X, Y));
//                ai->resume();
//                ai->stopAllActions();
//                ai->runAction(assault->clone());
//                aiAssault = true;
//            }
//            
//        }
//        //ai≥∑ÕÀ
//        if (HP_ai <= Max_HP_ai / 2)
//        {
//            aiAssault = false;
//            if (aiRetreat == false)
//            {
//                float X = 3000;
//                float Y = visibleSize.height / 2;
//                float positionX = ai->getPositionX();
//                float positionY = ai->getPositionY();
//                float distance = sqrt(pow(X - positionX, 2) + pow(Y - positionY, 2));
//                float time = distance / 200;
//                auto retreat = MoveTo::create(time, Vec2(X, Y));
//                ai->resume();
//                ai->stopAllActions();
//                ai->runAction(retreat->clone());
//                aiRetreat = true;
//            }
//        }
//    }
//}
////aiΩ¯»Îπ•ª˜∑∂ŒßÕ£÷π∫Õª÷∏¥“∆∂Ø
//void ai::aiPauseAndResume(Sprite *hero1)
//{
//    //±‹√‚ai≥∑ÕÀ ±Õ£œ¬
//    if (aiRetreat == true)
//    {
//        return;
//    }
//    //Õ£÷π“∆∂Ø
//    if (ai != nullptr && hero1 != NULL)
//    {
//        if (Distance(ai, hero) <= 200)
//        {
//            ai->pause();
//            pause_ai = true;
//        }
//    }
//    for (int i = 0; i < 600; i++)
//    {
//        if (ai != nullptr && creep_ally[i] != nullptr)
//        {
//            if (Distance(ai,creep_ally[i] ) <= AttackRange_ai)
//            {
//                ai->pause();
//                pause_ai = true;
//                break;
//            }
//        }
//    }
//    //ª÷∏¥“∆∂Ø
//    if (ai != nullptr)
//    {
//        if (pause_ai == false)
//        {
//            ai->resume();
//        }
//        pause_ai = false;
//    }
//}
////aiπ•ª˜
//void ai::attack_aiUpdate(float delta)
//{
//    //π•ª˜”¢–€
//    if (ai != nullptr&&hero != nullptr)
//    {
//        if (Distance(ai, hero) <= AttackRange_ai)
//        {
//            HP_hero -= Damage_ai;
//            return;
//        }
//    }
//    //π•ª˜–°±¯
//    for (int i = 0; i < 600; i++)
//    {
//        if (creep_ally[i] != nullptr&&ai != nullptr)
//        {
//            if (Distance(creep_ally[i], ai) <= AttackRange_ai)
//            {
//                HP_ally[i] -= Damage_ai;
//                break;
//            }
//        }
//    }
//}
////aiÀ¿Õˆ
//void ai::death_ai()
//{
//    if (ai != nullptr)
//    {
//        if (HP_ai <= 0)
//        {
//            ai->removeFromParent();ai = nullptr;
//            hp_ai->removeFromParent();hp_ai = nullptr;
//            //ªÒ»°æ≠—È
//            if (lv < 4)
//            {
//                xp += 1000;
//            }
//            kills += 1;
//            //ª˜…±“Ù–ß
//            auto SoundEffect = SimpleAudioEngine::getInstance();
//            SoundEffect->playEffect("kill.mp3", false, 1, 0, 1);
//            //÷ÿ…˙
//            this->scheduleOnce(schedule_selector(Game1::RespawnAIUpdate), RespawnTime_ai);
//        }
//    }
//}
////ai÷ÿ…˙
//void ai::RespawnAIUpdate(float delta)
//{
//    HP_ai = 1000;
//    hero_ai();
//}
////ai—™Ãı∏˙ÀÊ
//void ai::hpFollow_ai()
//{
//    if (ai != nullptr)
//    {
//        hp_ai->setPercent(100 * HP_ai / Max_HP_ai);
//        float positionX = ai->getPositionX();
//        float positionY = ai->getPositionY() + 0.5*ai->getContentSize().height + 0.5*hp_ai->getContentSize().height;
//        hp_ai->setPosition(Vec2(positionX, positionY));
//    }
//}
////ai◊‘∂Øªÿ—™
//void ai::healthRegen_aiUpdate(float delta)
//{
//    if (ai != nullptr)
//    {
//        if (HP_ai < Max_HP_ai )
//        {
//            //ai◊‘…Ìªÿ—™
//            HP_ai += HealthRegen_ai / 100;
//            //»™ÀÆªÿ—™
//            float X = ai->getPositionX();
//            if (X > 1000)
//            {
//                HP_ai += HealthRegen / 100;
//            }
//        }
//    }
//}
