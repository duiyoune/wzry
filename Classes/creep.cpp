#include "Game1Scene.h"
//С��
void Game1::creep()
{
	//��ʱ����
	this->schedule(schedule_selector(Game1::creepsUpdate), CreepsSpawnInterval);
	//С������
	this->schedule(schedule_selector(Game1::attack_creepUpdate), AttackInterval_creep);
}
//��ʱ����
void Game1::creepsUpdate(float delta)
{
	float time = visibleSize.width / MoveSpeed_creep;
	move_ally = MoveBy::create(time, Vec2(visibleSize.width, 0));
	move_enemy = MoveBy::create(time, Vec2(-visibleSize.width, 0));
	for (j_creep = i_creep; j_creep < i_creep + 3; j_creep++)
	{
		//�ѷ�С��
		creep_ally[j_creep] = Sprite::create("creep_right.png");
		this->addChild(creep_ally[j_creep]);
		HP_ally[j_creep] = Max_HP_creep;
		//�ѷ�С��Ѫ��
		hp_ally[j_creep] = LoadingBar::create("hp.png");
		hp_ally[j_creep]->setDirection(LoadingBar::Direction::RIGHT);
		this->addChild(hp_ally[j_creep]);
		hp_ally[j_creep]->setPercent(100);
		//�ѷ�С���ƶ�
		float positionX = origin.x + 0.5*creep_ally[j_creep]->getContentSize().width;
		float positionY = origin.y + visibleSize.height*(j_creep - i_creep + 1) / 4;
		creep_ally[j_creep]->setPosition(positionX, positionY);
		creep_ally[j_creep]->runAction(move_ally->clone());
		//�з�С��
		creep_enemy[j_creep] = Sprite::create("creep_left.png");
		this->addChild(creep_enemy[j_creep]);
		HP_enemy[j_creep] = Max_HP_creep;
		//�з�С��Ѫ��
		hp_enemy[j_creep] = LoadingBar::create("hp.png");
		hp_enemy[j_creep]->setDirection(LoadingBar::Direction::RIGHT);
		this->addChild(hp_enemy[j_creep]);
		hp_enemy[j_creep]->setPercent(100);
		//�з�С���ƶ�
		positionX = visibleSize.width - 0.5*creep_enemy[j_creep]->getContentSize().width;
		positionY = origin.y + visibleSize.height*(j_creep - i_creep + 1) / 4;
		creep_enemy[j_creep]->setPosition(positionX, positionY);
		creep_enemy[j_creep]->runAction(move_enemy->clone());
	}
	i_creep = i_creep + 3;
}
//С�����빥����Χֹͣ�ͻָ��ƶ�
void Game1::creepPauseAndResume()
{
	for (int i = 0; i < 600; i++)
	{
		//���˽��빥����Χֹͣ�ƶ�
		//˫��С��
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
		//�з�С�������ѷ�Ӣ��
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
		//�ѷ�С�������з�Ӣ��
		if (creep_ally[i] != nullptr&&ai != nullptr)
		{
			if (Distance(ai, creep_ally[i]) <= AttackRange_creep)
			{
				creep_ally[i]->pause();
				pause_ally[i] = true;
				attack_creepAai[i] = true;
			}
			for (int j = 0; j < 600; j++)
			{
				if (creep_enemy[j] != nullptr)
				{
					if (Distance(creep_enemy[j], creep_ally[i]) <= AttackRange_creep)
					{
						attack_creepAai[i] = false;
					}
				}
			}
		}
		//�ָ��ƶ�
		if (creep_ally[i] != nullptr)
		{
			if (pause_ally[i] == false)
			{
				creep_ally[i]->resume();
			}
			pause_ally[i] = false;
		}
		if (creep_enemy[i] != nullptr)
		{
			if (pause_enemy[i] == false)
			{
				creep_enemy[i]->resume();
			}
			pause_enemy[i] = false;
		}
	}
}
//С������
void Game1::attack_creepUpdate(float delta)
{
	//�ѷ�С�������з�С��
	for (int i = 0; i < 600; i++)
	{
		for (int j = 0; j < 600; j++)
		{
			if (creep_ally[i] != nullptr && creep_enemy[j] != nullptr)
			{
				if (Distance(creep_ally[i], creep_enemy[j]) <= AttackRange_creep)
				{
					HP_enemy[j] -= Damage_creep;
					break;
				}
			}
		}
	}
	//�з�С�������ѷ�С��
	for (int i = 0; i < 600; i++)
	{
		for (int j = 0; j < 600; j++)
		{
			if (creep_ally[j] != nullptr && creep_enemy[i] != nullptr)
			{
				if (Distance(creep_ally[j], creep_enemy[i]) <= AttackRange_creep)
				{
					HP_ally[j] -= Damage_creep;
					break;
				}
			}
		}
	}
	//�з�С�������ѷ�Ӣ��
	for (int i = 0; i < 600; i++)
	{
		if (creep_enemy[i] != nullptr&&hero != nullptr)
		{
			if (Distance(hero, creep_enemy[i]) <= AttackRange_creep && attack_creepAhero[i] == true)
			{
				HP_hero -= Damage_creep;
			}
		}
	}
	//�ѷ�С�������з�Ӣ��
	for (int i = 0; i < 600; i++)
	{
		if (creep_ally[i] != nullptr&&ai != nullptr)
		{
			if (Distance(ai, creep_ally[i]) <= AttackRange_creep && attack_creepAai[i] == true)
			{
				HP_ai -= Damage_creep;
			}
		}
	}
}
//С������
void Game1::death_creep()
{
	for (int i = 0; i < 600; i++)
	{
		if (creep_ally[i] != nullptr)
		{
			if (HP_ally[i] <= 0)
			{
				hp_ally[i]->removeFromParent();
				hp_ally[i] = nullptr;
				creep_ally[i]->removeFromParent();
				creep_ally[i] = nullptr;
			}
		}
		if (creep_enemy[i] != nullptr)
		{
			if (HP_enemy[i] <= 0)
			{
				hp_enemy[i]->removeFromParent();
				hp_enemy[i] = nullptr;
				creep_enemy[i]->removeFromParent();
				creep_enemy[i] = nullptr;
				//��ȡ����
				if (lv < 4)
				{
					xp += 200;
				}
			}
		}	
	}
}
//С��Ѫ������
void Game1::hpFollow_creep()
{
	for (int i = 0; i < 10000; i++)
	{
		//�ѷ�С��	
		if (creep_ally[i] != nullptr)
		{
			hp_ally[i]->setPercent(100 * HP_ally[i] / Max_HP_creep);
			float positionX = creep_ally[i]->getPositionX();
			float positionY = creep_ally[i]->getPositionY() + 0.5*creep_ally[i]->getContentSize().height + 0.5*hp_ally[i]->getContentSize().height;
			hp_ally[i]->setPosition(Vec2(positionX, positionY));
		}
		//�з�С��
		if (creep_enemy[i] != nullptr)
		{
			hp_enemy[i]->setPercent(100 * HP_enemy[i] / Max_HP_creep);
			float positionX = creep_enemy[i]->getPositionX();
			float positionY = creep_enemy[i]->getPositionY() + 0.5*creep_enemy[i]->getContentSize().height + 0.5*hp_enemy[i]->getContentSize().height;
			hp_enemy[i]->setPosition(Vec2(positionX, positionY));
		}
	}
}