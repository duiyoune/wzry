#include "Game1Scene.h"
//令人发狂的电脑
void Game1::hero_ai()
{
	ai = Sprite::create("bm.png");
	float positionX = 1300;
	float positionY = visibleSize.height / 2 + origin.y;
	ai->setPosition(Vec2(positionX, positionY));
	this->addChild(ai, 89);
	//ai血条
	hp_ai = LoadingBar::create("hp.png");
	hp_ai->setDirection(LoadingBar::Direction::RIGHT);
	this->addChild(hp_ai, 88);
	hp_ai->setPercent(100);
	//ai攻击
	this->schedule(schedule_selector(Game1::attack_aiUpdate), AttackInterval_ai);
	//ai自动回血
	this->schedule(schedule_selector(Game1::healthRegen_aiUpdate), 0.01);
}
//ai行动
void Game1::aiAction()
{
	if (ai != nullptr)
	{
		//ai冲锋
		if (HP_ai >= Max_HP_ai)
		{
			aiRetreat = false;
			if (aiAssault == false)
			{
				float X = 0;
				float Y = visibleSize.height / 2 + origin.y;
				float positionX = ai->getPositionX();
				float positionY = ai->getPositionY();
				float distance = sqrt(pow(X-positionX, 2) + pow(Y-positionY, 2));
				float time = distance / MoveSpeed_ai;
				auto assault = MoveTo::create(time, Vec2(X, Y));
				ai->resume();
				ai->stopAllActions();
				ai->runAction(assault->clone());
				aiAssault = true;
			}
			
		}
		//ai撤退
		if (HP_ai <= Max_HP_ai / 2)
		{
			aiAssault = false;
			if (aiRetreat == false)
			{
				float X = 1300;
				float Y = visibleSize.height / 2 + origin.y;
				float positionX = ai->getPositionX();
				float positionY = ai->getPositionY();
				float distance = sqrt(pow(X - positionX, 2) + pow(Y - positionY, 2));
				float time = distance / MoveSpeed_ai;			
				auto retreat = MoveTo::create(time, Vec2(X, Y));
				ai->resume();
				ai->stopAllActions();
				ai->runAction(retreat->clone());
				aiRetreat = true;
			}		
		}
	}	
}
//ai进入攻击范围停止和恢复移动
void Game1::aiPauseAndResume()
{
	//避免ai撤退时停下
	if (aiRetreat == true)
	{
		return;
	}
	//停止移动
	if (ai != nullptr&&hero != nullptr)
	{
		if (Distance(ai, hero) <= AttackRange_ai)
		{
			ai->pause();
			pause_ai = true;
		}
	}
	for (int i = 0; i < 600; i++)
	{
		if (ai != nullptr&&creep_ally[i] != nullptr)
		{
			if (Distance(ai,creep_ally[i] ) <= AttackRange_ai)
			{
				ai->pause();
				pause_ai = true;
				break;
			}
		}
	}
	//恢复移动
	if (ai != nullptr)
	{
		if (pause_ai == false)
		{
			ai->resume();
		}
		pause_ai = false;
	}
}
//ai攻击
void Game1::attack_aiUpdate(float delta)
{
	//攻击英雄
	if (ai != nullptr&&hero != nullptr)
	{
		if (Distance(ai, hero) <= AttackRange_ai)
		{
			HP_hero -= Damage_ai;
			return;
		}
	}
	//攻击小兵
	for (int i = 0; i < 600; i++)
	{
		if (creep_ally[i] != nullptr&&ai != nullptr)
		{
			if (Distance(creep_ally[i], ai) <= AttackRange_ai)
			{
				HP_ally[i] -= Damage_ai;
				break;
			}
		}
	}
}
//ai死亡
void Game1::death_ai()
{
	if (ai != nullptr)
	{
		if (HP_ai <= 0)
		{
			ai->removeFromParent();
			hp_ai->removeFromParent();
			ai = nullptr;
			hp_ai = nullptr;
			//获取经验
			if (lv < 4)
			{
				xp += 1000;
			}			
			kills += 1;
			//击杀音效
			auto SoundEffect = SimpleAudioEngine::getInstance();
			SoundEffect->playEffect("kill.mp3", false, 1, 0, 1);
			//重生
			this->scheduleOnce(schedule_selector(Game1::RespawnAIUpdate), RespawnTime_ai);
		}
	}
}
//ai重生
void Game1::RespawnAIUpdate(float delta)
{
	HP_ai = 1000;
	hero_ai();
}
//ai血条跟随
void Game1::hpFollow_ai()
{
	if (ai != nullptr)
	{
		hp_ai->setPercent(100 * HP_ai / Max_HP_ai);
		float positionX = ai->getPositionX();
		float positionY = ai->getPositionY() + 0.5*ai->getContentSize().height + 0.5*hp_ai->getContentSize().height;
		hp_ai->setPosition(Vec2(positionX, positionY));
	}
}
//ai自动回血
void Game1::healthRegen_aiUpdate(float delta)
{
	if (ai != nullptr)
	{
		if (HP_ai < Max_HP_ai )
		{
			//ai自身回血
			HP_ai += HealthRegen_ai / 100;
			//泉水回血
			float X = ai->getPositionX();
			if (X > 1000)
			{
				HP_ai += HealthRegen / 100;
			}
		}
	}
}