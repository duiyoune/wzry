#include "Game1Scene.h"
//小兵
void Game1::creep()
{
	//小兵初始血量为1000
	for (int i = 0; i < 600; i++)
	{
		HP_ally[i] = { 1000 };
		HP_enemy[i] = { 1000 };
	}
	move_ally = MoveBy::create(10, Vec2(visibleSize.width, 0));
	move_enemy = MoveBy::create(10, Vec2(-visibleSize.width, 0));
	for (j_creep = 0; j_creep < 3; j_creep++)
	{
		//友方小兵
		creep_ally[j_creep] = Sprite::create("creep_right.png");
		this->addChild(creep_ally[j_creep]);
		//友方小兵血条
		hp_ally[j_creep] = LoadingBar::create("hp.png");
		hp_ally[j_creep]->setDirection(LoadingBar::Direction::RIGHT);
		this->addChild(hp_ally[j_creep]);
		hp_ally[j_creep]->setPercent(100);
		//友方小兵移动
		float positionX_ally = origin.x + 0.5*creep_ally[j_creep]->getContentSize().width;
		float positionY_ally = origin.y + visibleSize.height*(j_creep + 1) / 4;
		creep_ally[j_creep]->setPosition(positionX_ally, positionY_ally);
		creep_ally[j_creep]->runAction(move_ally->clone());
		//敌方小兵
		creep_enemy[j_creep] = Sprite::create("creep_left.png");
		this->addChild(creep_enemy[j_creep]);
		//敌方小兵血条
		hp_enemy[j_creep] = LoadingBar::create("hp.png");
		hp_enemy[j_creep]->setDirection(LoadingBar::Direction::RIGHT);
		this->addChild(hp_enemy[j_creep]);
		hp_enemy[j_creep]->setPercent(100);
		//敌方小兵移动
		float positionX_enemy = visibleSize.width - 0.5*creep_enemy[j_creep]->getContentSize().width;
		float positionY_enemy = origin.y + visibleSize.height*(j_creep + 1) / 4;
		creep_enemy[j_creep]->setPosition(positionX_enemy, positionY_enemy);
		creep_enemy[j_creep]->runAction(move_enemy->clone());
	}
	//定时出兵
	this->schedule(schedule_selector(Game1::creepsUpdate), CreepsSpawnInterval);
	//小兵攻击
	this->schedule(schedule_selector(Game1::attack_creepUpdate), AttackInterval_creep);
}
//定时出兵
void Game1::creepsUpdate(float delta)
{
	move_ally = MoveBy::create(10, Vec2(visibleSize.width, 0));
	move_enemy = MoveBy::create(10, Vec2(-visibleSize.width, 0));
	for (j_creep = i_creep + 3; j_creep < i_creep + 6; j_creep++)
	{
		//友方小兵
		creep_ally[j_creep] = Sprite::create("creep_right.png");
		this->addChild(creep_ally[j_creep]);
		//友方小兵血条
		hp_ally[j_creep] = LoadingBar::create("hp.png");
		hp_ally[j_creep]->setDirection(LoadingBar::Direction::RIGHT);
		this->addChild(hp_ally[j_creep]);
		hp_ally[j_creep]->setPercent(100);
		//友方小兵移动
		float positionX_ally = origin.x + 0.5*creep_ally[j_creep]->getContentSize().width;
		float positionY_ally = origin.y + visibleSize.height*(j_creep - i_creep - 2) / 4;
		creep_ally[j_creep]->setPosition(positionX_ally, positionY_ally);
		creep_ally[j_creep]->runAction(move_ally->clone());
		//敌方小兵
		creep_enemy[j_creep] = Sprite::create("creep_left.png");
		this->addChild(creep_enemy[j_creep]);
		//敌方小兵血条
		hp_enemy[j_creep] = LoadingBar::create("hp.png");
		hp_enemy[j_creep]->setDirection(LoadingBar::Direction::RIGHT);
		this->addChild(hp_enemy[j_creep]);
		hp_enemy[j_creep]->setPercent(100);
		//敌方小兵移动
		float positionX_enemy = visibleSize.width - 0.5*creep_enemy[j_creep]->getContentSize().width;
		float positionY_enemy = origin.y + visibleSize.height*(j_creep - i_creep - 2) / 4;
		creep_enemy[j_creep]->setPosition(positionX_enemy, positionY_enemy);
		creep_enemy[j_creep]->runAction(move_enemy->clone());
	}
	i_creep = i_creep + 3;
}
//小兵进入攻击范围停止和恢复移动
void Game1::creepPauseAndResume()
{
	for (int i = 0; i < 600; i++)
	{
		//敌人进入攻击范围停止移动
		//双方小兵
		for (int j = 0; j < 600; j++)
		{
			if (creep_ally[i] != nullptr && creep_enemy[j] != nullptr)
			{
				if (Distance(creep_ally[i], creep_enemy[j]) <= AttackRange_creep)
				{
					creep_ally[i]->pause();
					creep_enemy[j]->pause();
					pause_ally[i] = true;
					pause_enemy[j] = true;
				}
			}
		}
		//敌方小兵遇见友方英雄
		if (creep_enemy[i] != nullptr&&hero != nullptr)
		{
			if (Distance(hero, creep_enemy[i]) <= AttackRange_creep)
			{
				creep_enemy[i]->pause();
				pause_enemy[i] = true;
				attack_creepAhero[i] = true;
			}
			for (int j = 0; j < 600; j++)
			{
				if (creep_ally[j] != nullptr)
				{
					if (Distance(creep_ally[j], creep_enemy[i]) <= AttackRange_creep)
					{
						attack_creepAhero[i] = false;
					}
				}
			}
		}
		//恢复移动
		if (creep_ally[i] != nullptr)
		{
			if (pause_ally[i] == false)
			{
				creep_ally[i]->resume();
			}
		}
		if (creep_enemy[i] != nullptr)
		{
			if (pause_enemy[i] == false)
			{
				creep_enemy[i]->resume();
			}
		}
	}
	for (int i = 0; i < 600; i++)
	{
		if (creep_ally[i] != nullptr)
		{
			pause_ally[i] = false;
		}
		if (creep_enemy[i] != nullptr)
		{
			pause_enemy[i] = false;
		}
	}
}
//小兵攻击
void Game1::attack_creepUpdate(float delta)
{
	//友方小兵攻击敌方小兵
	for (int i = 0; i < 600; i++)
	{
		for (int j = 0; j < 600; j++)
		{
			if (creep_ally[i] != nullptr && creep_enemy[j] != nullptr)
			{
				if (Distance(creep_ally[i], creep_enemy[j]) <= AttackRange_creep)
				{
					HP_enemy[j] -= Damage_creep;
					hp_enemy[j]->setPercent(100 * HP_enemy[j] / Max_HP_creep);
					continue;
				}
			}
		}
	}
	//敌方小兵攻击友方小兵
	for (int i = 0; i < 600; i++)
	{
		for (int j = 0; j < 600; j++)
		{
			if (creep_ally[j] != nullptr && creep_enemy[i] != nullptr)
			{
				if (Distance(creep_ally[j], creep_enemy[i]) <= AttackRange_creep)
				{
					HP_ally[j] -= Damage_creep;
					hp_ally[j]->setPercent(100 * HP_ally[j] / Max_HP_creep);
					continue;
				}
			}
		}
	}
	//敌方小兵攻击友方英雄
	for (int i = 0; i < 600; i++)
	{
		if (creep_enemy[i] != nullptr&&hero != nullptr)
		{
			if (Distance(hero, creep_enemy[i]) <= AttackRange_creep && attack_creepAhero[i] == true)
			{
				HP_hero -= Damage_creep;
				hp_hero->setPercent(100 * HP_hero / Max_HP_hero);
			}
		}
	}
}
//小兵死亡
void Game1::death_creep()
{
	for (int i = 0; i < 600; i++)
	{
		if (creep_ally[i] != nullptr && creep_enemy[i] != nullptr)
		{
			if (hp_ally[i]->getPercent() <= 0 || HP_ally[i] <= 0)
			{
				creep_ally[i]->removeFromParent();
				hp_ally[i]->removeFromParent();
				creep_ally[i] = nullptr;
				hp_ally[i] = nullptr;
			}
			if (hp_enemy[i]->getPercent() <= 0 || HP_enemy[i] <= 0)
			{
				creep_enemy[i]->removeFromParent();
				hp_enemy[i]->removeFromParent();
				creep_enemy[i] = nullptr;
				hp_enemy[i] = nullptr;
				//获取经验
				xp = xp + 100;
			}
		}
	}
}
//小兵血条跟随
void Game1::hpFollow_creep()
{
	for (int i = 0; i < 10000; i++)
	{
		//友方小兵	
		if (creep_ally[i] != nullptr)
		{
			hp_ally[i]->setPercent(100 * HP_ally[i] / Max_HP_creep);
			float positionX_ally = creep_ally[i]->getPositionX();
			float positionY_ally = creep_ally[i]->getPositionY() + 0.5*creep_ally[i]->getContentSize().height + 0.5*hp_ally[i]->getContentSize().height;
			hp_ally[i]->setPosition(Vec2(positionX_ally, positionY_ally));
		}
		else this->removeChild(hp_ally[i]);
		//敌方小兵
		if (creep_enemy[i] != nullptr)
		{
			hp_enemy[i]->setPercent(100 * HP_enemy[i] / Max_HP_creep);
			float positionX_enemy = creep_enemy[i]->getPositionX();
			float positionY_enemy = creep_enemy[i]->getPositionY() + 0.5*creep_enemy[i]->getContentSize().height + 0.5*hp_enemy[i]->getContentSize().height;
			hp_enemy[i]->setPosition(Vec2(positionX_enemy, positionY_enemy));
		}
		else this->removeChild(hp_enemy[i]);
	}
}