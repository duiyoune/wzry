#include "Game1Scene.h"
//令人发狂的电脑
void Game1::hero_ai()
{
	ai = Sprite::create("bm.png");
	float positionX = 1300;
	float positionY = visibleSize.height / 2 + origin.y;
	ai->setPosition(Vec2(positionX, positionY));
	this->addChild(ai, 89);
	//英雄血条
	hp_ai = LoadingBar::create("hp.png");
	hp_ai->setDirection(LoadingBar::Direction::RIGHT);
	this->addChild(hp_ai, 88);
	hp_ai->setPercent(100);
	//英雄攻击
	//this->schedule(schedule_selector(Game1::attack_aiUpdate), AttackInterval_ai);
}
//ai死亡
void Game1::death_ai()
{
	if (ai != nullptr)
	{
		if (hp_ai->getPercent() <= 0 || HP_ai <= 0)
		{
			ai->removeFromParent();
			hp_ai->removeFromParent();
			ai = nullptr;
			hp_ai = nullptr;
			xp += 1000;
			kills += 1;
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
		float positionX_ai = ai->getPositionX();
		float positionY_ai = ai->getPositionY() + 0.5*ai->getContentSize().height + 0.5*hp_ai->getContentSize().height;
		hp_ai->setPosition(Vec2(positionX_ai, positionY_ai));
	}
}