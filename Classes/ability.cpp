#include "Game1Scene.h"
auto AbilitySoundEffect = SimpleAudioEngine::getInstance();//��Ч
//����
//����1
void Game1::ability1()
{
	//����1��ȴ������
	this->scheduleOnce(schedule_selector(Game1::ability1DurationUpdate), Duration_ability1);
	this->scheduleOnce(schedule_selector(Game1::ability1CDUpdate), CD_ability1);
	duration_ability1 = true;
	cd_ability1 = true;
	//����1��Ч
	AbilitySoundEffect->playEffect("ability1.wav", false, 1, 0, 1);
	//����1Ч��
	switch (LV_ability1)
	{
	case 1:MoveSpeed_hero *= 1.5; AttackInterval_hero *= 0.65; Damage_hero *= 1.5; break;
	case 2:MoveSpeed_hero *= 1.65; AttackInterval_hero *= 0.6; Damage_hero *= 1.65; break;
	case 3:MoveSpeed_hero *= 1.8; AttackInterval_hero *= 0.55; Damage_hero *= 1.8; break;
	case 4:MoveSpeed_hero *= 2; AttackInterval_hero *= 0.5; Damage_hero *= 2; break;
	}
}
//����1����ʱ��
void Game1::ability1DurationUpdate(float delta)
{
	switch (LV_ability1)
	{
	case 1:MoveSpeed_hero /= 1.5; AttackInterval_hero /= 0.65; Damage_hero /= 1.5; break;
	case 2:MoveSpeed_hero /= 1.65; AttackInterval_hero /= 0.6; Damage_hero /= 1.65; break;
	case 3:MoveSpeed_hero /= 1.8; AttackInterval_hero /= 0.55; Damage_hero /= 1.8; break;
	case 4:MoveSpeed_hero /= 2; AttackInterval_hero /= 0.5; Damage_hero /= 2; break;
	}
	duration_ability1 = false;
}
//����1��ȴʱ��
void Game1::ability1CDUpdate(float delta)
{
	cd_ability1 = false;
}
//����2
void Game1::ability2()
{
	//����2��ȴ
	this->scheduleOnce(schedule_selector(Game1::ability2CDUpdate), CD_ability2);
	cd_ability2 = true;
	//����2��Ч
	AbilitySoundEffect->playEffect("ability2.wav", false, 1, 0, 1);
	//����2����
	auto blade = Sprite::create("blade array.png");
	float positionX = hero->getPositionX() + 30;
	float positionY = hero->getPositionY() - 60;
	blade->setPosition(Vec2(positionX, positionY));
	this->addChild(blade, 1);
	auto FadeOut = FadeOut::create(2);
	blade->runAction(FadeOut);
	//����2Ч��
	if (Distance(hero, ai) <= 400)
	{
		switch (LV_ability2)
		{
		case 1:HP_ai -= 200; break;
		case 2:HP_ai -= 400; break;
		case 3:HP_ai -= 600; break;
		case 4:HP_ai -= 800; break;
		}
	}
	for (int i = 0; i < 600; i++)
	{
		if (Distance(hero, creep_enemy[i]) <= 400)
		{
			switch (LV_ability2)
			{
			case 1:HP_enemy[i] -= 200; break;
			case 2:HP_enemy[i] -= 400; break;
			case 3:HP_enemy[i] -= 600; break;
			case 4:HP_enemy[i] -= 800; break;
			}
		}
	}
}
//����2��ȴʱ��
void Game1::ability2CDUpdate(float delta)
{
	cd_ability2 = false;
}
//����3Ч��
void Game1::ability3Effect()
{
	//����3��ȴ
	this->scheduleOnce(schedule_selector(Game1::ability3CDUpdate), CD_ability3);
	cd_ability3 = true;
	//����3��Ч
	AbilitySoundEffect->playEffect("ability3.wav", false, 1, 0, 1);
	//����3����
	auto blade = Sprite::create("blade.png");
	float positionX;
	float positionY;
	if (ability3_targetAI == true)
	{
		positionX = ai->getPositionX();
		positionY = ai->getPositionY();
	}
	else 
	{
		positionX = creep_enemy[ability3_target]->getPositionX();
		positionY = creep_enemy[ability3_target]->getPositionY();
	}
	blade->setPosition(Vec2(positionX, positionY + 50));
	this->addChild(blade, 1);
	auto MoveTo = MoveTo::create(2, Vec2(positionX, positionY));
	blade->runAction(MoveTo);
	auto FadeOut = FadeOut::create(2);
	blade->runAction(FadeOut);
	//����3Ч��
	if (ability3_targetAI == true)
	{
		ability3_targetAI = false;
		switch (LV_ability3)
		{
		case 1:HP_ai -= 500; break;
		case 2:HP_ai -= 1000; break;
		case 3:HP_ai -= 1500; break;
		case 4:HP_ai -= 2000; break;
		}
		return;
	}
	switch (LV_ability3)
	{
	case 1:HP_enemy[ability3_target] -= 500; break;
	case 2:HP_enemy[ability3_target] -= 1000; break;
	case 3:HP_enemy[ability3_target] -= 1500; break;
	case 4:HP_enemy[ability3_target] -= 2000; break;
	}
}
//�жϼ���3�Ƿ������ڵз���λ
void Game1::ability3Hit(float X, float Y)
{
	//ai
	if (InTheArea(X, Y, ai) == true)
	{
		ability3Clicked = false;
		ability3_targetAI = true;
		if (cursor != nullptr)
		{
			cursor->removeFromParent();
			cursor = nullptr;
		}		
		//�жϵ����Ƿ���뼼��3ʩ����Χ
		if (Distance(hero, ai) > CastRange_ability3)
		{
			//�ƶ���ʩ����Χ��
			ability3MovingToAI = true;
			float time = Distance(hero, ai) / MoveSpeed_hero;
			float positionX = ai->getPositionX();
			float positionY = ai->getPositionY();
			auto moveTo = MoveTo::create(time, Vec2(positionX, positionY));
			hero->runAction(moveTo);
			moveTo->setTag(1);
		}
		if (Distance(hero, ai) <= CastRange_ability3)
		{
			//����3Ч��
			ability3Effect();
		}
		return;
	}
	//С��
	for (int i = 0; i < 600; i++)
	{
		if (creep_enemy[i] != nullptr)
		{
			if (InTheArea(X, Y, creep_enemy[i]) == true)
			{
				ability3_target = i;
				ability3Clicked = false;
				cursor->removeFromParent();
				cursor = nullptr;
				//�жϵ����Ƿ���뼼��3ʩ����Χ
				if (Distance(hero, creep_enemy[ability3_target]) > CastRange_ability3)
				{
					//�ƶ���ʩ����Χ��
					ability3MovingToCreep = true;
					float time = Distance(hero, creep_enemy[ability3_target]) / MoveSpeed_hero;
					float positionX = creep_enemy[ability3_target]->getPositionX();
					float positionY = creep_enemy[ability3_target]->getPositionY();
					auto moveTo = MoveTo::create(time, Vec2(positionX, positionY));
					hero->runAction(moveTo);
					moveTo->setTag(1);
				}
				if (Distance(hero, creep_enemy[ability3_target]) <= CastRange_ability3)
				{
					//����3Ч��
					ability3Effect();
					break;
				}
			}
		}
	}
}
//����3��ȴʱ��
void Game1::ability3CDUpdate(float delta)
{
	cd_ability3 = false;
}
//����3���������ƶ�
void Game1::ability3Cursor(float X, float Y)
{
	if (cursor != nullptr)
	{
		cursor->removeFromParent();
	}
	cursor = Sprite::create("cursor.png");
	this->addChild(cursor,100);
	cursor->setPosition(X, Y);
}
//����4
double Game1::ability4()
{
	double CriticalDamage = 1;
	if (LV_ability4 != 0)
	{
		//����4Ч��
		if (random(1, 100) <= 25)
		{
			switch (LV_ability4)
			{
			case 1:CriticalDamage = 2; break;
			case 2:CriticalDamage = 3; break;
			case 3:CriticalDamage = 4; break;
			case 4:CriticalDamage = 5; break;
			}
		}
	}
	return CriticalDamage;
}