#include "Game1Scene.h"
//Ӣ��
void Game1::hero_BM()
{
	hero = Sprite::create("bm.png");
	float positionX = 100;
	float positionY = visibleSize.height / 2 + origin.y;
	hero->setPosition(Vec2(positionX, positionY));
	this->addChild(hero, 99);
	//Ӣ��Ѫ��
	hp_hero = LoadingBar::create("hp.png");
	hp_hero->setDirection(LoadingBar::Direction::RIGHT);
	this->addChild(hp_hero, 98);
	hp_hero->setPercent(100);
	//Ӣ�۹���
	this->schedule(schedule_selector(Game1::attack_heroUpdate), AttackInterval_hero);
}
//Ӣ�۽��빥����Χֹͣ
void Game1::heroPauseAttackRange()
{
	//����Ӣ��
	if (attack_heroAai == true && hero != nullptr)
	{
		if (Distance(hero, ai) <= AttackRange_hero)
		{
			hero->stopActionByTag(tag_hero);
			attack_heroAai = false;
		}
	}
	//����С��
	if (attack_heroAcreep == true && hero != nullptr)
	{
		if (Distance(hero, creep_enemy[attack_target]) <= AttackRange_hero)
		{
			hero->stopActionByTag(tag_hero);
			attack_heroAcreep = false;
		}
	}
}
//Ӣ�۽���ʩ����Χֹͣ
void Game1::heroPauseCastRange()
{
	//ai
	if (ability3MovingToAI == true)
	{
		if (Distance(hero, ai) <= CastRange_ability3)
		{
			hero->stopActionByTag(1);
			ability3MovingToAI = false;
			//����3Ч��
			ability3Effect();
		}
		//Ŀ��Ӣ�������жϼ���3
		if (HP_ai <= 0)
		{
			hero->stopActionByTag(1);
			ability3MovingToAI = false;
		}
		return;
	}
	//С��
	if (ability3MovingToCreep == true)
	{
		if (Distance(hero, creep_enemy[ability3_target]) <= CastRange_ability3)
		{
			hero->stopActionByTag(1);
			ability3MovingToCreep = false;
			//����3Ч��
			ability3Effect();
		}
		//Ŀ��С�������жϼ���3
		if (HP_enemy[ability3_target] <= 0)
		{
			hero->stopActionByTag(1);
			ability3MovingToCreep = false;
		}
	}
}
//Ӣ�۹���
void Game1::attack_heroUpdate(float delta)
{
	//����Ӣ��
	if (hero != nullptr&&ai != nullptr)
	{
		if (Distance(hero, ai) <= AttackRange_hero)
		{
			HP_ai -= ability4()*Damage_hero;
			hp_ai->setPercent(100 * HP_ai / Max_HP_ai);
			return;
		}
	}
	//����С��
	if (hero != nullptr&&creep_enemy[attack_target] != nullptr)
	{
		if (Distance(hero, creep_enemy[attack_target]) <= AttackRange_hero)
		{
			HP_enemy[attack_target] -= ability4()*Damage_hero;
			hp_enemy[attack_target]->setPercent(100 * HP_enemy[attack_target] / Max_HP_creep);
		}
	}
}
//Ӣ��������ƶ�
void Game1::moveWithMouse(float X, float Y)
{
	//����3ѡ��Ŀ��ʱ����Ӣ���ƶ�
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
//�Ƿ����з�Ӣ���Թ���
void Game1::clickAI(float X, float Y)
{
	if (ai != nullptr)
	{
		if (InTheArea(X, Y, ai) == true)
		{
			attack_heroAai = true;
		}
	}
}
//�Ƿ����з�С���Թ���
void Game1::clickCreep_enemy(float X, float Y)
{
	for (int i = 0; i < 600; i++)
	{
		if (creep_enemy[i] != nullptr)
		{
			if (InTheArea(X, Y, creep_enemy[i]) == true)
			{
				attack_heroAcreep = true;
				attack_target = i;
				break;
			}
		}
	}
}
//Ӣ������
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
			//������Ч
			auto BGM = SimpleAudioEngine::getInstance();
			BGM->stopBackgroundMusic(false);
			auto SoundEffect = SimpleAudioEngine::getInstance();
			SoundEffect->playEffect("death.wav", false, 1, 0, 1);
			//����
			this->scheduleOnce(schedule_selector(Game1::RespawnHeroUpdate), RespawnTime_hero);
		}
	}
}
//Ӣ������
void Game1::RespawnHeroUpdate(float delta)
{
	HP_hero = 1000;
	hero_BM();
	auto BGM = SimpleAudioEngine::getInstance();
	BGM->resumeBackgroundMusic();
}
//Ӣ��Ѫ������
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