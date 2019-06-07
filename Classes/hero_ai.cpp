#include "Game1Scene.h"
//���˷���ĵ���
void Game1::hero_ai()
{
	ai = Sprite::create("bm.png");
	float positionX = 1300;
	float positionY = visibleSize.height / 2 + origin.y;
	ai->setPosition(Vec2(positionX, positionY));
	this->addChild(ai, 89);
	//aiѪ��
	hp_ai = LoadingBar::create("hp.png");
	hp_ai->setDirection(LoadingBar::Direction::RIGHT);
	this->addChild(hp_ai, 88);
	hp_ai->setPercent(100);
	//ai����
	this->schedule(schedule_selector(Game1::attack_aiUpdate), AttackInterval_ai);
	//ai�Զ���Ѫ
	this->schedule(schedule_selector(Game1::healthRegen_aiUpdate), 0.01);
}
//ai�ж�
void Game1::aiAction()
{
	if (ai != nullptr)
	{
		//ai���
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
		//ai����
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
//ai���빥����Χֹͣ�ͻָ��ƶ�
void Game1::aiPauseAndResume()
{
	//����ai����ʱͣ��
	if (aiRetreat == true)
	{
		return;
	}
	//ֹͣ�ƶ�
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
	//�ָ��ƶ�
	if (ai != nullptr)
	{
		if (pause_ai == false)
		{
			ai->resume();
		}
		pause_ai = false;
	}
}
//ai����
void Game1::attack_aiUpdate(float delta)
{
	//����Ӣ��
	if (ai != nullptr&&hero != nullptr)
	{
		if (Distance(ai, hero) <= AttackRange_ai)
		{
			HP_hero -= Damage_ai;
			return;
		}
	}
	//����С��
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
//ai����
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
			//��ȡ����
			if (lv < 4)
			{
				xp += 1000;
			}			
			kills += 1;
			//��ɱ��Ч
			auto SoundEffect = SimpleAudioEngine::getInstance();
			SoundEffect->playEffect("kill.mp3", false, 1, 0, 1);
			//����
			this->scheduleOnce(schedule_selector(Game1::RespawnAIUpdate), RespawnTime_ai);
		}
	}
}
//ai����
void Game1::RespawnAIUpdate(float delta)
{
	HP_ai = 1000;
	hero_ai();
}
//aiѪ������
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
//ai�Զ���Ѫ
void Game1::healthRegen_aiUpdate(float delta)
{
	if (ai != nullptr)
	{
		if (HP_ai < Max_HP_ai )
		{
			//ai�����Ѫ
			HP_ai += HealthRegen_ai / 100;
			//Ȫˮ��Ѫ
			float X = ai->getPositionX();
			if (X > 1000)
			{
				HP_ai += HealthRegen / 100;
			}
		}
	}
}