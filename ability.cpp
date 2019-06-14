#include "gamescene_houyi.hpp"
#include "attr_init.hpp"
auto AbilitySoundEffect = SimpleAudioEngine::getInstance();//音效

//技能
//技能1
void gamescene_houyi::ability1()
{
	//技能1冷却、持续
	this->scheduleOnce(schedule_selector(gamescene_houyi::ability1DurationUpdate), Duration_ability1);
	this->scheduleOnce(schedule_selector(gamescene_houyi::ability1CDUpdate), CD_ability1);
	duration_ability1 = true;
	cd_ability1 = true;
	//技能1音效
	AbilitySoundEffect->playEffect("ability1.wav", false, 1, 0, 1);
	//技能1效果
	switch (LV_ability1)
	{
	case 1:a.hero1.MoveSpeed *= 1.5; a.hero1.AttackInterval *= 0.65; a.hero1.base_damage *= 1.5; break;
	case 2:a.hero1.MoveSpeed *= 1.65; a.hero1.AttackInterval *= 0.6; a.hero1.base_damage *= 1.65; break;
	case 3:a.hero1.MoveSpeed *= 1.8; a.hero1.AttackInterval *= 0.55; a.hero1.base_damage *= 1.8; break;
	case 4:a.hero1.MoveSpeed *= 2; a.hero1.AttackInterval *= 0.5; a.hero1.base_damage *= 2; break;
	}
}
//技能1持续时间
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
//技能1冷却时间
void gamescene_houyi::ability1CDUpdate(float delta)
{
	cd_ability1 = false;
}
//技能2
void gamescene_houyi::ability2()
{
	//技能2冷却
	this->scheduleOnce(schedule_selector(gamescene_houyi::ability2CDUpdate), CD_ability2);
	cd_ability2 = true;
	//技能2音效
	AbilitySoundEffect->playEffect("ability2.wav", false, 1, 0, 1);
	//技能2动画
	auto blade = Sprite::create("blade array.png");
	float positionX = sprite->getPositionX() + 30;
	float positionY = sprite->getPositionY() - 60;
	blade->setPosition(Vec2(positionX, positionY));
	this->addChild(blade, 1);
	auto FadeOut = FadeOut::create(2);
	blade->runAction(FadeOut);
	//技能2效果
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
		//近战
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
		//远程
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
		//攻城
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
//技能2冷却时间
void gamescene_houyi::ability2CDUpdate(float delta)
{
	cd_ability2 = false;
}
//技能3效果
void gamescene_houyi::ability3Effect()
{
	//技能3冷却
	this->scheduleOnce(schedule_selector(gamescene_houyi::ability3CDUpdate), CD_ability3);
	cd_ability3 = true;
	//技能3音效
	AbilitySoundEffect->playEffect("ability3.wav", false, 1, 0, 1);
	//技能3动画
	auto blade = Sprite::create("blade.png");
	float positionX;
	float positionY;
	//ai
	if (ability3_targetAI == true)
	{
		positionX = ai->getPositionX();
		positionY = ai->getPositionY();
	}
	//近战
	if (ability3_targetMelee == true)
	{
		positionX = Melee_creep2[ability3_target]->getPositionX();
		positionY = Melee_creep2[ability3_target]->getPositionY();
	}
	//远程
	if (ability3_targetRange == true)
	{
		positionX = Range_creep2[ability3_target]->getPositionX();
		positionY = Range_creep2[ability3_target]->getPositionY();
	}
	//攻城
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
	//技能3效果
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
	//近战
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
	//远程
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
	//攻城
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
//判断技能3是否作用于敌方单位
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
		//判断敌人是否进入技能3施法范围
		if (Distance(sprite, ai) > CastRange_ability3)
		{
			//移动至施法范围内
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
			//技能3效果
			ability3Effect();
		}
		return;
	}
	//小兵
	for (int i = 0; i < 600; i++)
	{
		//近战
		if (Melee_creep2[i] != nullptr)
		{
			if (InTheArea(X, Y, Melee_creep2[i]) == true)
			{
				ability3_target = i;
				ability3Clicked = false;
				ability3_targetMelee = true;
				cursor->removeFromParent();cursor = nullptr;
				//判断敌人是否进入技能3施法范围
				if (Distance(sprite, Melee_creep2[ability3_target]) > CastRange_ability3)
				{
					//移动至施法范围内
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
					//技能3效果
					ability3Effect();
					break;
				}
			}
		}
		//远程
		if (Range_creep2[i] != nullptr)
		{
			if (InTheArea(X, Y, Range_creep2[i]) == true)
			{
				ability3_target = i;
				ability3Clicked = false;
				ability3_targetRange = true;
				cursor->removeFromParent(); cursor = nullptr;
				//判断敌人是否进入技能3施法范围
				if (Distance(sprite, Range_creep2[ability3_target]) > CastRange_ability3)
				{
					//移动至施法范围内
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
					//技能3效果
					ability3Effect();
					break; 
				}
			}
		}
		//攻城
		if (Catapult2[i] != nullptr)
		{
			if (InTheArea(X, Y, Catapult2[i]) == true)
			{
				ability3_target = i;
				ability3Clicked = false;
				ability3_targetSiege = true;
				cursor->removeFromParent(); cursor = nullptr;
				//判断敌人是否进入技能3施法范围
				if (Distance(sprite, Catapult2[ability3_target]) > CastRange_ability3)
				{
					//移动至施法范围内
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
					//技能3效果
					ability3Effect();
					break; 
				}
			}
		}
	}
}
//技能3冷却时间
void gamescene_houyi::ability3CDUpdate(float delta)
{
	cd_ability3 = false;
}
//技能3光标随鼠标移动
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
//技能4
double gamescene_houyi::ability4()
{
	double CriticalDamage = 1;
	if (LV_ability4 != 0)
	{
		//技能4效果
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