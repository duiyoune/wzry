#include "Game1Scene.h"
//英雄
void Game1::hero_BM()
{
	hero = Sprite::create("bm.png");
	float positionX = visibleSize.width / 2 + origin.x;
	float positionY = visibleSize.height / 2 + origin.y;
	hero->setPosition(Vec2(positionX, positionY));
	this->addChild(hero, 99);
	//英雄血条
	hp_hero = LoadingBar::create("hp.png");
	hp_hero->setDirection(LoadingBar::Direction::RIGHT);
	this->addChild(hp_hero, 98);
	hp_hero->setPercent(100);
	//英雄攻击
	this->schedule(schedule_selector(Game1::attack_heroUpdate), AttackInterval_hero);
}
//英雄进入攻击范围停止
void Game1::heroPauseAttackRange()
{
	if (attack_heroAcreep == true && hero != nullptr)
	{
		if (Distance(hero, creep_enemy[attack_target]) <= AttackRange_hero)
		{
			hero->stopActionByTag(tag_hero);
			attack_heroAcreep = false;
		}
	}
}
//英雄进入施法范围停止
void Game1::heroPauseCastRange()
{
	if (ability3Moving == true)
	{
		if (Distance(hero, creep_enemy[ability3_target]) <= CastRange_ability3)
		{
			hero->stopActionByTag(1);
			ability3Moving = false;
			//技能3效果
			ability3Effect();
		}
		//目标小兵死亡中断技能3
		if (HP_enemy[ability3_target] <= 0)
		{
			hero->stopActionByTag(1);
			ability3Moving = false;
		}
	}
}
//英雄攻击
void Game1::attack_heroUpdate(float delta)
{
	if (hero != nullptr&&creep_enemy[attack_target] != nullptr)
	{
		if (Distance(hero, creep_enemy[attack_target]) <= AttackRange_hero)
		{
			HP_enemy[attack_target] -= ability4()*Damage_hero;
			hp_enemy[attack_target]->setPercent(100 * HP_enemy[attack_target] / Max_HP_creep);
		}
	}
}
//英雄随鼠标移动
void Game1::moveWithMouse(float X, float Y)
{
	//技能3选择目标时避免英雄移动
	if (ability3Clicked == true)
	{
		return;
	}
	float positionX = hero->getPositionX();
	float positionY = hero->getPositionY();
	float distance = sqrt(pow(X - positionX, 2) + pow(Y - positionY, 2));
	float time = distance / MoveSpeed_hero;
	auto moveTo = MoveTo::create(time, Vec2(X, Y));
	hero->stopActionByTag(tag_hero);
	hero->resume();
	hero->runAction(moveTo);
	moveTo->setTag(tag_hero);
}
//是否点击敌方小兵以攻击
void Game1::clickCreep_enemy(float X, float Y)
{
	for (int i = 0; i < 600; i++)
	{
		if (creep_enemy[i] != nullptr)
		{
			if (InTheArea(X, Y, creep_enemy[i]) == true)
			{
				//攻击
				attack_heroAcreep = true;
				attack_target = i;
				break;
			}
		}
	}
}
//英雄死亡
void Game1::death_hero()
{
	if (hero != nullptr)
	{
		if (hp_hero->getPercent() <= 0 || HP_hero <= 0)
		{
			hero->removeFromParent();
			hp_hero->removeFromParent();
			hero = nullptr;
			hp_hero = nullptr;
			deaths += 1;
			//死亡音效
			auto BGM = SimpleAudioEngine::getInstance();
			BGM->stopBackgroundMusic(false);
			auto SoundEffect = SimpleAudioEngine::getInstance();
			SoundEffect->playEffect("death.wav", false, 1, 0, 1);
		}
	}
}
//英雄血条跟随
void Game1::hpFollow_hero()
{
	if (hero != nullptr)
	{
		hp_hero->setPercent(100 * HP_hero / Max_HP_hero);
		float positionX_hero = hero->getPositionX();
		float positionY_hero = hero->getPositionY() + 0.5*hero->getContentSize().height + 0.5*hp_hero->getContentSize().height;
		hp_hero->setPosition(Vec2(positionX_hero, positionY_hero));
	}
}