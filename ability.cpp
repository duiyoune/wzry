#include "gamescene_houyi.hpp"
#include "attr_init.hpp"
auto AbilitySoundEffect = SimpleAudioEngine::getInstance();//��Ч

//����
//����1
void gamescene_houyi::ability1()
{
	//����1��ȴ������
	this->scheduleOnce(schedule_selector(gamescene_houyi::ability1DurationUpdate), Duration_ability1);
	this->scheduleOnce(schedule_selector(gamescene_houyi::ability1CDUpdate), CD_ability1);
	duration_ability1 = true;
	cd_ability1 = true;
	//����1��Ч
	AbilitySoundEffect->playEffect("ability1.wav", false, 1, 0, 1);
	//����1Ч��
	switch (LV_ability1)
	{
	case 1:a.hero1.MoveSpeed *= 1.5; a.hero1.AttackInterval *= 0.65; a.hero1.base_damage *= 1.5; break;
	case 2:a.hero1.MoveSpeed *= 1.65; a.hero1.AttackInterval *= 0.6; a.hero1.base_damage *= 1.65; break;
	case 3:a.hero1.MoveSpeed *= 1.8; a.hero1.AttackInterval *= 0.55; a.hero1.base_damage *= 1.8; break;
	case 4:a.hero1.MoveSpeed *= 2; a.hero1.AttackInterval *= 0.5; a.hero1.base_damage *= 2; break;
	}
}
//����1����ʱ��
void gamescene_houyi::ability1DurationUpdate(float delta)
{
	switch (LV_ability1)
	{
	case 1:a.hero1.MoveSpeed /= 1.5; a.hero1.AttackInterval /= 0.65; a.hero1.base_damage /= 1.5; break;
	case 2:a.hero1.MoveSpeed /= 1.65; a.hero1.AttackInterval /= 0.6; a.hero1.base_damage /= 1.65; break;
	case 3:a.hero1.MoveSpeed /= 1.8; a.hero1.AttackInterval /= 0.55; a.hero1.base_damage /= 1.8; break;
	case 4:a.hero1.MoveSpeed /= 2; a.hero1.AttackInterval /= 0.5; a.hero1.base_damage /= 2; break;
	}
	duration_ability1 = false;
}
//����1��ȴʱ��
void gamescene_houyi::ability1CDUpdate(float delta)
{
	cd_ability1 = false;
}
//����2
void gamescene_houyi::ability2()
{
	//����2��ȴ
	this->scheduleOnce(schedule_selector(gamescene_houyi::ability2CDUpdate), CD_ability2);
	cd_ability2 = true;
	//����2��Ч
	AbilitySoundEffect->playEffect("ability2.wav", false, 1, 0, 1);
	//����2����
	auto blade = Sprite::create("blade array.png");
	float positionX = sprite->getPositionX() + 30;
	float positionY = sprite->getPositionY() - 60;
	blade->setPosition(Vec2(positionX, positionY));
	this->addChild(blade, 1);
	auto FadeOut = FadeOut::create(2);
	blade->runAction(FadeOut);
	//����2Ч��
	if (Distance(sprite, ai) <= 400)
	{
		switch (LV_ability2)
		{
		case 1:b.hero1.HP -= 200; break;
		case 2:b.hero1.HP -= 400; break;
		case 3:b.hero1.HP -= 600; break;
		case 4:b.hero1.HP -= 800; break;
		}
	}
	for (int i = 0; i < 600; i++)
	{
		//��ս
		if (Distance(sprite, Melee_creep2[i]) <= 400)
		{
			switch (LV_ability2)
			{
			case 1:b.melee.HP[i] -= 200; 
			case 2:b.melee.HP[i] -= 400;
			case 3:b.melee.HP[i] -= 600;
			case 4:b.melee.HP[i] -= 800;
			}
		}
		//Զ��
		if (Distance(sprite, Range_creep2[i]) <= 400)
		{
			switch (LV_ability2)
			{
			case 1:b.range.HP[i] -= 200; break;
			case 2:b.range.HP[i] -= 400; break;
			case 3:b.range.HP[i] -= 600; break;
			case 4:b.range.HP[i] -= 800; break;
			}
		}
		//����
		if (Distance(sprite, Catapult2[i]) <= 400)
		{
			switch (LV_ability2)
			{
			case 1:b.catapult.HP[i] -= 200; break;
			case 2:b.catapult.HP[i] -= 400; break;
			case 3:b.catapult.HP[i] -= 600; break;
			case 4:b.catapult.HP[i] -= 800; break;
			}
		}
	}
}
//����2��ȴʱ��
void gamescene_houyi::ability2CDUpdate(float delta)
{
	cd_ability2 = false;
}
//����3Ч��
void gamescene_houyi::ability3Effect()
{
	//����3��ȴ
	this->scheduleOnce(schedule_selector(gamescene_houyi::ability3CDUpdate), CD_ability3);
	cd_ability3 = true;
	//����3��Ч
	AbilitySoundEffect->playEffect("ability3.wav", false, 1, 0, 1);
	//����3����
	auto blade = Sprite::create("blade.png");
	float positionX;
	float positionY;
	//ai
	if (ability3_targetAI == true)
	{
		positionX = ai->getPositionX();
		positionY = ai->getPositionY();
	}
	//��ս
	if (ability3_targetMelee == true)
	{
		positionX = Melee_creep2[ability3_target]->getPositionX();
		positionY = Melee_creep2[ability3_target]->getPositionY();
	}
	//Զ��
	if (ability3_targetRange == true)
	{
		positionX = Range_creep2[ability3_target]->getPositionX();
		positionY = Range_creep2[ability3_target]->getPositionY();
	}
	//����
	if (ability3_targetSiege == true)
	{
		positionX = Catapult2[ability3_target]->getPositionX();
		positionY = Catapult2[ability3_target]->getPositionY();
	}
	blade->setPosition(Vec2(positionX, positionY + 50));
	this->addChild(blade, 1);
	auto MoveTo = MoveTo::create(2, Vec2(positionX, positionY));
	blade->runAction(MoveTo);
	auto FadeOut = FadeOut::create(2);
	blade->runAction(FadeOut);
	//����3Ч��
	//ai
	if (ability3_targetAI == true)
	{
		ability3_targetAI = false;
		switch (LV_ability3)
		{
		case 1:b.hero1.HP -= 500; break;
		case 2:b.hero1.HP -= 1000; break;
		case 3:b.hero1.HP -= 1500; break;
		case 4:b.hero1.HP -= 2000; break;
		}
		return;
	}
	//��ս
	if (ability3_targetMelee = true)
	{
		ability3_targetMelee = false;
		switch (LV_ability3)
		{
		case 1:b.melee.HP[ability3_target] -= 500; break;
		case 2:b.melee.HP[ability3_target] -= 1000; break;
		case 3:b.melee.HP[ability3_target] -= 1500; break;
		case 4:b.melee.HP[ability3_target] -= 2000; break;
		}
		return;
	}	
	//Զ��
	if (ability3_targetRange = true)
	{
		ability3_targetRange = false;
		switch (LV_ability3)
		{
		case 1:b.range.HP[ability3_target] -= 500; break;
		case 2:b.range.HP[ability3_target] -= 1000; break;
		case 3:b.range.HP[ability3_target] -= 1500; break;
		case 4:b.range.HP[ability3_target] -= 2000; break;
		}
		return;
	}
	//����
	if (ability3_targetSiege = true)
	{
		ability3_targetSiege = false;
		switch (LV_ability3)
		{
		case 1:b.catapult.HP[ability3_target] -= 500; break;
		case 2:b.catapult.HP[ability3_target] -= 1000; break;
		case 3:b.catapult.HP[ability3_target] -= 1500; break;
		case 4:b.catapult.HP[ability3_target] -= 2000; break;
		}
		return;
	}
}
//�жϼ���3�Ƿ������ڵз���λ
void gamescene_houyi::ability3Hit(float X, float Y)
{
	//ai
	if (InTheArea(X, Y, ai) == true)
	{
		ability3Clicked = false;
		ability3_targetAI = true;
		if (cursor != nullptr)
		{
			cursor->removeFromParent();cursor = nullptr;		
		}		
		//�жϵ����Ƿ���뼼��3ʩ����Χ
		if (Distance(sprite, ai) > CastRange_ability3)
		{
			//�ƶ���ʩ����Χ��
			ability3MovingToAI = true;
			float time = Distance(sprite, ai) / a.hero1.MoveSpeed;
			float positionX = ai->getPositionX();
			float positionY = ai->getPositionY();
			auto moveTo = MoveTo::create(time, Vec2(positionX, positionY));
			sprite->runAction(moveTo);
			moveTo->setTag(1);
		}
		if (Distance(sprite, ai) <= CastRange_ability3)
		{
			//����3Ч��
			ability3Effect();
		}
		return;
	}
	//С��
	for (int i = 0; i < 600; i++)
	{
		//��ս
		if (Melee_creep2[i] != nullptr)
		{
			if (InTheArea(X, Y, Melee_creep2[i]) == true)
			{
				ability3_target = i;
				ability3Clicked = false;
				ability3_targetMelee = true;
				cursor->removeFromParent();cursor = nullptr;
				//�жϵ����Ƿ���뼼��3ʩ����Χ
				if (Distance(sprite, Melee_creep2[ability3_target]) > CastRange_ability3)
				{
					//�ƶ���ʩ����Χ��
					ability3MovingToMelee = true;
					float time = Distance(sprite, Melee_creep2[ability3_target]) / a.hero1.MoveSpeed;
					float positionX = Melee_creep2[ability3_target]->getPositionX();
					float positionY = Melee_creep2[ability3_target]->getPositionY();
					auto moveTo = MoveTo::create(time, Vec2(positionX, positionY));
					sprite->runAction(moveTo);
					moveTo->setTag(1);
				}
				if (Distance(sprite, Melee_creep2[ability3_target]) <= CastRange_ability3)
				{
					//����3Ч��
					ability3Effect();
					break;
				}
			}
		}
		//Զ��
		if (Range_creep2[i] != nullptr)
		{
			if (InTheArea(X, Y, Range_creep2[i]) == true)
			{
				ability3_target = i;
				ability3Clicked = false;
				ability3_targetRange = true;
				cursor->removeFromParent(); cursor = nullptr;
				//�жϵ����Ƿ���뼼��3ʩ����Χ
				if (Distance(sprite, Range_creep2[ability3_target]) > CastRange_ability3)
				{
					//�ƶ���ʩ����Χ��
					ability3MovingToRange = true;
					float time = Distance(sprite, Range_creep2[ability3_target]) / a.hero1.MoveSpeed;
					float positionX = Range_creep2[ability3_target]->getPositionX();
					float positionY = Range_creep2[ability3_target]->getPositionY();
					auto moveTo = MoveTo::create(time, Vec2(positionX, positionY));
					sprite->runAction(moveTo);
					moveTo->setTag(1);
				}
				if (Distance(sprite, Range_creep2[ability3_target]) <= CastRange_ability3)
				{
					//����3Ч��
					ability3Effect();
					break; 
				}
			}
		}
		//����
		if (Catapult2[i] != nullptr)
		{
			if (InTheArea(X, Y, Catapult2[i]) == true)
			{
				ability3_target = i;
				ability3Clicked = false;
				ability3_targetSiege = true;
				cursor->removeFromParent(); cursor = nullptr;
				//�жϵ����Ƿ���뼼��3ʩ����Χ
				if (Distance(sprite, Catapult2[ability3_target]) > CastRange_ability3)
				{
					//�ƶ���ʩ����Χ��
					ability3MovingToSiege = true;
					float time = Distance(sprite, Catapult2[ability3_target]) / a.hero1.MoveSpeed;
					float positionX = Catapult2[ability3_target]->getPositionX();
					float positionY = Catapult2[ability3_target]->getPositionY();
					auto moveTo = MoveTo::create(time, Vec2(positionX, positionY));
					sprite->runAction(moveTo);
					moveTo->setTag(1);
				}
				if (Distance(sprite, Catapult2[ability3_target]) <= CastRange_ability3)
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
void gamescene_houyi::ability3CDUpdate(float delta)
{
	cd_ability3 = false;
}
//����3���������ƶ�
void gamescene_houyi::ability3Cursor(float X, float Y)
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
double gamescene_houyi::ability4()
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