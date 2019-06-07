#include "game.h"
#include "iostream"
#include "string"

Scene* game::createScene()
{
	return game::create();
}

bool game::init()
{
	auto jinenglan = Sprite::create("jineng1.jpg");
	jinenglan->setPosition(800, 110);
	jinenglan->setScale(3);
	this->addChild(jinenglan);

	hero = Sprite::create("66.jpg");
	hero->setPosition(Vec2(800, 600));
	hero->setScale(0.2);
	this->addChild(hero);
	speed = 100;
	spriteleft = Sprite::create("tower.jpg");
	spriteright = Sprite::create("tower.jpg");
	
	spriteleft->setScale(0.3);
	spriteright->setScale(0.3);

	spriteleft->setPosition(Vec2(200, 600));
	spriteright->setPosition(Vec2(1400, 600));
	le = Vec2(200, 600);
	ri = Vec2(1400, 600);
	this->addChild(spriteleft);
	this->addChild(spriteright);
	bri = 500;
	ble = 500;

	game::firstset(1);
	
	auto Listener = EventListenerMouse::create();
	Listener->onMouseDown = CC_CALLBACK_1(game::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Listener, this);
	
	
	auto Listener2 = EventListenerKeyboard::create();
	Listener2->onKeyPressed = CC_CALLBACK_2(game::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Listener2, this);


//	xiaobing();
	this->schedule(SEL_SCHEDULE(&game::xiaobing), 30.0f, kRepeatForever, 0);
	return true;
}



void game::onMouseDown(Event *event)
{
	int x, y, time,re1,re2,re3;
	re1 = 0;
	re2 = 0;
	re3 = 0;
	EventMouse* e = (EventMouse*)event;
	currentPoint = hero->getPosition();
	x = currentPoint.x;
	y = currentPoint.y;
	nx= e->getCursorX();
	ny = e->getCursorY();

	time = sqrt((nx - x)*(nx - x) + (ny - y)*(ny - y));
	time = time / speed;

		re1 = game::react1();
		re2 = game::react2();
		re3 = game::react3();
		if (re1 == 0 && re2 == 0 && re3 == 0)
			hero->runAction(MoveTo::create(time, Vec2(nx, ny)));

	R = false;

}


void game::forw(float dt)
{
	int distance1,distance2,distance3;
	Vec2 po = hero->getPosition();
	distance1 = sqrt((po.x - pos1.x)*(po.x - pos1.x) + (po.y - pos1.y)*(po.y - pos1.y));
	distance2 = sqrt((po.x - pos2.x)*(po.x - pos2.x) + (po.y - pos2.y)*(po.y - pos2.y));
	distance3 = sqrt((po.x - pos3.x)*(po.x - pos3.x) + (po.y - pos3.y)*(po.y - pos3.y));
	if (distance1 <= 60)
	{
		b1 = b1 - 10;
		log("1");
	}
	if (distance2 <= 60)
	{
		b2 = b2 - 10;
		log("2");
	}
	if (distance3 <= 60)
	{
		b3 = b3 - 10;
		log("3");
	}
	
}
void game::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		auto baojian = Sprite::create("baojian1.jpg");
		Vec2 po = hero->getPosition();
		this->addChild(baojian);
		CCPointArray * array = CCPointArray::create(4);
		array->addControlPoint(po + ccp(50, 0));
		array->addControlPoint(po + ccp(0, 50));
		array->addControlPoint(po + ccp(-50, 0));
		array->addControlPoint(po + ccp(0, -50));
		array->addControlPoint(po + ccp(50, 0));

		CCActionInterval  * CardinalSplineTo = CCCardinalSplineTo::create(0.5, array, 0);//完成时间
		CCActionInterval* act = CCRepeat::create(CardinalSplineTo, 4);//持续时间
		baojian->runAction(act);

		this->schedule(SEL_SCHEDULE(&game::forw),0.1f, 40, 0);
		auto fadeOut = FadeOut::create(4.0f);
		baojian->runAction(fadeOut);
		log("W");

	}

	if (keyCode == EventKeyboard::KeyCode::KEY_R)
	{
		auto Listener3 = EventListenerMouse::create();
		R = true;
		log("RRRR");
		Listener3->onMouseDown = CC_CALLBACK_1(game::onMouseDown, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(Listener3, this);

	}
}





void game::firstset(int num)
{
	str = '1';
	la = Label::createWithTTF(str, "fonts/Marker Felt.ttf", 24);
	la->setPosition(Vec2(200, 800));
	this->addChild(la);
	jingyan = 0;
	this->schedule(SEL_SCHEDULE(&game::up),1.0f, kRepeatForever, 0);
	log("OK");
}

void game::up(float dt)
{
	jingyan = jingyan + 1;
	if (jingyan >= 5)
		str = '2';
	if (jingyan >= 15)
		str = '3';
	if (jingyan >= 30)
		str = '4';
	if (jingyan >= 50)
		str = '5';
	if (jingyan >= 75)
		str = '6';
	if (jingyan >= 100)
		str = '7';
	if (jingyan >= 130)
		str = '8';
	if (jingyan >= 165)
		str = '9';
	if (jingyan >= 205)
		str = '10';
	if (jingyan >= 250)
		str = '11';
	la = Label::createWithTTF(str, "fonts/Marker Felt.ttf", 24);
	la->setPosition(Vec2(200, 800));
	this->addChild(la);

//	log("jingyan");
}

void game::xiaobing(float dt)   //52.4*42.6
{
	xiaobing1 = Sprite::create("11.jpg");
	xiaobing2 = Sprite::create("11.jpg");
	xiaobing3 = Sprite::create("11.jpg");
	xiaobing4 = Sprite::create("33.jpg");
	xiaobing5 = Sprite::create("33.jpg");
	xiaobing6 = Sprite::create("33.jpg");
	
	
	xiaobing1->setScale(0.1);
	xiaobing2->setScale(0.1);
	xiaobing3->setScale(0.1);
	xiaobing4->setScale(0.2);
	xiaobing5->setScale(0.2);
	xiaobing6->setScale(0.2);
	
	xiaobing1->setPosition(Vec2(300, 300));
	xiaobing2->setPosition(Vec2(300, 600));
	xiaobing3->setPosition(Vec2(300, 900));
	xiaobing4->setPosition(Vec2(1300, 300));
	xiaobing5->setPosition(Vec2(1300, 600));
	xiaobing6->setPosition(Vec2(1300, 900));

	this->addChild(xiaobing1);
	this->addChild(xiaobing2);
	this->addChild(xiaobing3);
	this->addChild(xiaobing4);
	this->addChild(xiaobing5);
	this->addChild(xiaobing6);

	b1 = 100;
	b2 = 100;
	b3 = 100;

	b4 = 100;
	b5 = 100;
	b6 = 100;

	
	

	
	this->schedule(SEL_SCHEDULE(&game::xiaobingsitu), 0.1f, kRepeatForever, 0);
	this->schedule(SEL_SCHEDULE(&game::xiaobingai), 10.0f, kRepeatForever, 0);
}

void game::xiaobingsitu(float dt)
{

	pos1 = xiaobing1->getPosition();

	pos2 = xiaobing2->getPosition();

	pos3 = xiaobing3->getPosition();
	
	if (b1 <= 0)
	{
		auto fadeOut = FadeOut::create(1.0f);
		xiaobing1->runAction(fadeOut);
		xiaobing1->setPosition(-100000, -10000);
	}
	if (b2 <= 0)
	{
		auto fadeOut = FadeOut::create(1.0f);
		xiaobing2->runAction(fadeOut);
		xiaobing2->setPosition(-100000, -10000);
	}
	if (b3 <= 0)
	{
	    auto fadeOut = FadeOut::create(1.0f);
		xiaobing3->runAction(fadeOut);
		xiaobing3->setPosition(-100000, -10000);
	}
//	log("situOK");
}

	

int game::react1()
{
	int distance1 = sqrt((nx - pos1.x)*(nx - pos1.x) + (ny - pos1.y)*(ny- pos1.y));
	if (distance1 < 34 && R!=true)
	{
		int x = currentPoint.x;
		int y = currentPoint.y;
		int time = sqrt((nx - x)*(nx - x) + (ny - y)*(ny - y));
		if (time < 200)
		{
			auto gongji=Sprite::create ("baojian1.jpg");
			gongji->setPosition(Vec2(pos1.x+200, pos1.y));
			this->addChild(gongji);
			auto xiaoguo = MoveBy::create(0.5, Vec2(-200,0));
			gongji->runAction(xiaoguo);
			auto fadeOut = FadeOut::create(0.5f);
			gongji->runAction(fadeOut);
			b1 =b1- 30;
		}
		else
		{
			time = sqrt((nx - x)*(nx - x) + (ny - y)*(ny - y))-100;
			time = time / speed;
			hero->runAction(MoveTo::create(time, Vec2(nx+200, ny)));

		}
		log("re1");
		return 1;
	}
	
	if (distance1 < 34 && R == true)
	{
		int x = currentPoint.x;
		int y = currentPoint.y;
		int time = sqrt((nx - x)*(nx - x) + (ny - y)*(ny - y));
		if (time < 200)
		{
			auto dazhao = Sprite::create("dazhao.jpg");
			dazhao->setPosition(Vec2(pos1.x, pos1.y+200));
			this->addChild(dazhao);
			auto xiaoguo = MoveBy::create(0.5, Vec2(0,-200));
			dazhao->runAction(xiaoguo);
			auto fadeOut = FadeOut::create(0.5f);
			dazhao->runAction(fadeOut);
			b2 = b2 - 100;
		}
		else
		{
			time = sqrt((nx - x)*(nx - x) + (ny - y)*(ny - y)) - 100;
			time = time / speed;
			hero->runAction(MoveTo::create(time, Vec2(nx + 200, ny)));

		}

		log("R1OK");
		R = false;
		return 1;
	}	
	return 0;
}


int game::react2()
{
	int distance2 = sqrt((nx - pos2.x)*(nx - pos2.x) + (ny - pos2.y)*(ny - pos2.y));
	if (distance2 < 34 && R!=true)
	{
		int x = currentPoint.x;
		int y = currentPoint.y;
		int time = sqrt((nx - x)*(nx - x) + (ny - y)*(ny - y));
		if (time <	200)
		{
			auto gongji = Sprite::create("baojian1.jpg");
			gongji->setPosition(Vec2(pos2.x+90, pos2.y));
			this->addChild(gongji);
			auto xiaoguo = MoveBy::create(0.5, Vec2(-200,0));
			gongji->runAction(xiaoguo);
			auto fadeOut = FadeOut::create(0.5f);
			gongji->runAction(fadeOut);
			b2 =b2-30;
		}
		else
		{
			time = sqrt((nx - x)*(nx - x) + (ny - y)*(ny - y)) - 100;
			time = time / speed;
			hero->runAction(MoveTo::create(time, Vec2(nx + 200, ny)));

		}
		log("re2");
		return 2;
	}
	if (distance2 < 34 && R == true)
	{
		int x = currentPoint.x;
		int y = currentPoint.y;
		int time = sqrt((nx - x)*(nx - x) + (ny - y)*(ny - y));
		if (time < 200)
		{
			auto dazhao = Sprite::create("dazhao.jpg");
			dazhao->setPosition(Vec2(pos2.x, pos2.y + 200));
			this->addChild(dazhao);
			auto xiaoguo = MoveBy::create(0.5, Vec2(0, -200));
			dazhao->runAction(xiaoguo);
			auto fadeOut = FadeOut::create(0.5f);
			dazhao->runAction(fadeOut);
			b2 = b2 - 100;
		}
		else
		{
			time = sqrt((nx - x)*(nx - x) + (ny - y)*(ny - y)) - 100;
			time = time / speed;
			hero->runAction(MoveTo::create(time, Vec2(nx + 200, ny)));

		}

		log("R2OK");
		R = false;
		return 2;
	}

	return 0;
}


int game::react3()
{
	int distance3 = sqrt((nx - pos3.x)*(nx - pos3.x) + (ny - pos3.y)*(ny - pos3.y));
	if (distance3 < 34 && R!=true)
	{
		int x = currentPoint.x;
		int y = currentPoint.y;
		int time = sqrt((nx - x)*(nx - x) + (ny - y)*(ny - y));
		if (time < 200)
		{
			auto gongji = Sprite::create("baojian1.jpg");
			gongji->setPosition(Vec2(pos3.x+200, pos3.y));
			this->addChild(gongji);
			auto xiaoguo = MoveBy::create(0.5, Vec2(-200,0));
			gongji->runAction(xiaoguo);
			auto fadeOut = FadeOut::create(0.5f);
			gongji->runAction(fadeOut);
			b3 =b3- 30;
		}
		else
		{
			time = sqrt((nx - x)*(nx - x) + (ny - y)*(ny - y)) - 100;
			time = time / speed;
			hero->runAction(MoveTo::create(time, Vec2(nx + 200, ny )));

		}
		log("re3");
		return 3;
	}
	if (distance3 < 34 && R == true)
	{
		int x = currentPoint.x;
		int y = currentPoint.y;
		int time = sqrt((nx - x)*(nx - x) + (ny - y)*(ny - y));
		if (time < 200)
		{
			auto dazhao = Sprite::create("dazhao.jpg");
			dazhao->setPosition(Vec2(pos3.x, pos3.y + 200));
			this->addChild(dazhao);
			auto xiaoguo = MoveBy::create(0.5, Vec2(0, -200));
			dazhao->runAction(xiaoguo);
			auto fadeOut = FadeOut::create(0.5f);
			dazhao->runAction(fadeOut);
			b2 = b2 - 100;
		}
		else
		{
			time = sqrt((nx - x)*(nx - x) + (ny - y)*(ny - y)) - 100;
			time = time / speed;
			hero->runAction(MoveTo::create(time, Vec2(nx + 200, ny)));

		}
		
		log("R3OK");
		R = false;
		return 3;
	}

		
	return 0;
}

void game::xiaobingai(float dt)
{
	game::ai1();
	game::ai2();
	game::ai3();

}

void game::ai1()
{
	int dis4, dis5, dis6, disri;
	dis4 = sqrt((pos4.x - pos1.x)*(pos4.x - pos1.x) + (pos4.y - pos1.y)* (pos4.y - pos1.y));
	dis5 = sqrt((pos5.x - pos1.x)*(pos5.x - pos1.x) + (pos5.y - pos1.y)* (pos5.y - pos1.y));
	dis6 = sqrt((pos6.x - pos1.x)*(pos6.x - pos1.x) + (pos6.y - pos1.y)* (pos6.y - pos1.y));
	disri = sqrt((ri.x - pos1.x)*(ri.x - pos1.x) + (ri.y - pos1.y)* (ri.y - pos1.y));

	if (dis4 < dis5)
	{
		if (dis4 < dis6)
		{
			if (dis4 < disri)
			{
				int x = pos1.x;
				int y = pos1.y;
				int time = sqrt((pos4.x - x)*(pos4.x - x) + (pos4.y - y)*(pos4.y - y));
				if (time < 100)
				{
					b4 = b4 - 50;
				}
				else
				{
					time = sqrt((pos4.x - x)*(pos4.x - x) + (pos4.y - y)*(pos4.y - y)) - 100;
					time = time / 40;
					xiaobing1->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

				}
			}
			else
			{
				int x = pos1.x;
				int y = pos1.y;
				int time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y));
				if (time < 100)
				{
					bri = bri - 50;
				}
				else
				{
					time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y)) - 100;
					time = time / 40;
					xiaobing1->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

				}


			}
		}
		else if (dis6 < disri)
		{
			int x = pos1.x;
			int y = pos1.y;
			int time = sqrt((pos6.x - x)*(pos6.x - x) + (pos6.y - y)*(pos6.y - y));
			if (time < 100)
			{
				b6 = b6 - 50;
			}
			else
			{
				time = sqrt((pos6.x - x)*(pos6.x - x) + (pos6.y - y)*(pos6.y - y)) - 100;
				time = time / 40;
				xiaobing1->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

			}
		}
		else
		{
			int x = pos1.x;
			int y = pos1.y;
			int time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y));
			if (time < 100)
			{
				bri = bri - 50;
			}
			else
			{
				time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y)) - 100;
				time = time / 40;
				xiaobing1->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

			}


		}
	}
	
	else if (dis5 < dis6)
	{
		if (dis5 < disri)
		{
			int x = pos1.x;
			int y = pos1.y;
			int time = sqrt((pos5.x - x)*(pos5.x - x) + (pos5.y - y)*(pos5.y - y));
			if (time < 100)
			{
				b5 = b5 - 50;
			}
			else
			{
				time = sqrt((pos5.x - x)*(pos5.x - x) + (pos5.y - y)*(pos5.y - y)) - 100;
				time = time / 40;
				xiaobing1->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

			}
		}
		else 
		{
			int x = pos1.x;
			int y = pos1.y;
			int time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y));
			if (time < 100)
			{
				bri = bri - 50;
			}
			else
			{
				time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y)) - 100;
				time = time / 40;
				xiaobing1->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

			}


		}
	}
	else if (dis6 < disri)
	{
	        int x = pos1.x;
			int y = pos1.y;
			int time = sqrt((pos6.x - x)*(pos6.x - x) + (pos6.y - y)*(pos6.y - y));
			if (time < 100)
			{
				b6 = b6 - 50;
			}
			else
			{
				time = sqrt((pos6.x - x)*(pos6.x - x) + (pos6.y - y)*(pos6.y - y)) - 100;
				time = time / 40;
				xiaobing1->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

			}

	}
	else
	{
			int x = pos1.x;
			int y = pos1.y;
			int time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y));
			if (time < 100)
			{
				bri = bri - 50;
			}
			else
			{
				time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y)) - 100;
				time = time / 40;
				xiaobing1->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

			}


		}
}
void game::ai2()
{
	int dis4, dis5, dis6, disri;
	dis4 = sqrt((pos4.x - pos2.x)*(pos4.x - pos2.x) + (pos4.y - pos2.y)* (pos4.y - pos2.y));
	dis5 = sqrt((pos5.x - pos2.x)*(pos5.x - pos2.x) + (pos5.y - pos2.y)* (pos5.y - pos2.y));
	dis6 = sqrt((pos6.x - pos2.x)*(pos6.x - pos2.x) + (pos6.y - pos2.y)* (pos6.y - pos2.y));
	disri = sqrt((ri.x - pos2.x)*(ri.x - pos2.x) + (ri.y - pos2.y)* (ri.y - pos2.y));

	if (dis4 < dis5)
	{
		if (dis4 < dis6)
		{
			if (dis4 < disri)
			{
				int x = pos2.x;
				int y = pos2.y;
				int time = sqrt((pos4.x - x)*(pos4.x - x) + (pos4.y - y)*(pos4.y - y));
				if (time < 100)
				{
					b4 = b4 - 50;
				}
				else
				{
					time = sqrt((pos4.x - x)*(pos4.x - x) + (pos4.y - y)*(pos4.y - y)) - 100;
					time = time / 40;
					xiaobing2->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

				}
			}
			else
			{
				int x = pos2.x;
				int y = pos2.y;
				int time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y));
				if (time < 100)
				{
					bri = bri - 50;
				}
				else
				{
					time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y)) - 100;
					time = time / 40;
					xiaobing2->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

				}


			}
		}
		else if (dis6 < disri)
		{
			int x = pos2.x;
			int y = pos2.y;
			int time = sqrt((pos6.x - x)*(pos6.x - x) + (pos6.y - y)*(pos6.y - y));
			if (time < 100)
			{
				b6 = b6 - 50;
			}
			else
			{
				time = sqrt((pos6.x - x)*(pos6.x - x) + (pos6.y - y)*(pos6.y - y)) - 100;
				time = time / 40;
				xiaobing2->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

			}
		}
		else
		{
			int x = pos2.x;
			int y = pos2.y;
			int time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y));
			if (time < 100)
			{
				bri = bri - 50;
			}
			else
			{
				time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y)) - 100;
				time = time / 40;
				xiaobing2->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

			}


		}
	}

	else if (dis5 < dis6)
	{
		if (dis5 < disri)
		{
			int x = pos2.x;
			int y = pos2.y;
			int time = sqrt((pos5.x - x)*(pos5.x - x) + (pos5.y - y)*(pos5.y - y));
			if (time < 100)
			{
				b5 = b5 - 50;
			}
			else
			{
				time = sqrt((pos5.x - x)*(pos5.x - x) + (pos5.y - y)*(pos5.y - y)) - 100;
				time = time / 40;
				xiaobing2->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

			}
		}
		else
		{
			int x = pos2.x;
			int y = pos2.y;
			int time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y));
			if (time < 100)
			{
				bri = bri - 50;
			}
			else
			{
				time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y)) - 100;
				time = time / 40;
				xiaobing2->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

			}


		}
	}
	else if (dis6 < disri)
	{
		int x = pos2.x;
		int y = pos2.y;
		int time = sqrt((pos6.x - x)*(pos6.x - x) + (pos6.y - y)*(pos6.y - y));
		if (time < 100)
		{
			b6 = b6 - 50;
		}
		else
		{
			time = sqrt((pos6.x - x)*(pos6.x - x) + (pos6.y - y)*(pos6.y - y)) - 100;
			time = time / 40;
			xiaobing2->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

		}

	}
	else
	{
		int x = pos2.x;
		int y = pos2.y;
		int time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y));
		if (time < 100)
		{
			bri = bri - 50;
		}
		else
		{
			time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y)) - 100;
			time = time / 40;
			xiaobing2->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

		}


	}
}
void game::ai3()
{
	int dis4, dis5, dis6, disri;
	dis4 = sqrt((pos4.x - pos3.x)*(pos4.x - pos3.x) + (pos4.y - pos3.y)* (pos4.y - pos3.y));
	dis5 = sqrt((pos5.x - pos3.x)*(pos5.x - pos3.x) + (pos5.y - pos3.y)* (pos5.y - pos3.y));
	dis6 = sqrt((pos6.x - pos3.x)*(pos6.x - pos3.x) + (pos6.y - pos3.y)* (pos6.y - pos3.y));
	disri = sqrt((ri.x - pos3.x)*(ri.x - pos3.x) + (ri.y - pos3.y)* (ri.y - pos3.y));

	if (dis4 < dis5)
	{
		if (dis4 < dis6)
		{
			if (dis4 < disri)
			{
				int x = pos3.x;
				int y = pos3.y;
				int time = sqrt((pos4.x - x)*(pos4.x - x) + (pos4.y - y)*(pos4.y - y));
				if (time < 100)
				{
					b4 = b4 - 50;
				}
				else
				{
					time = sqrt((pos4.x - x)*(pos4.x - x) + (pos4.y - y)*(pos4.y - y)) - 100;
					time = time / 40;
					xiaobing3->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

				}
			}
			else
			{
				int x = pos3.x;
				int y = pos3.y;
				int time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y));
				if (time < 100)
				{
					bri = bri - 50;
				}
				else
				{
					time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y)) - 100;
					time = time / 40;
					xiaobing3->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

				}


			}
		}
		else if (dis6 < disri)
		{
			int x = pos3.x;
			int y = pos3.y;
			int time = sqrt((pos6.x - x)*(pos6.x - x) + (pos6.y - y)*(pos6.y - y));
			if (time < 100)
			{
				b6 = b6 - 50;
			}
			else
			{
				time = sqrt((pos6.x - x)*(pos6.x - x) + (pos6.y - y)*(pos6.y - y)) - 100;
				time = time / 40;
				xiaobing3->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

			}
		}
		else
		{
			int x = pos3.x;
			int y = pos3.y;
			int time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y));
			if (time < 100)
			{
				bri = bri - 50;
			}
			else
			{
				time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y)) - 100;
				time = time / 40;
				xiaobing3->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

			}


		}
	}

	else if (dis5 < dis6)
	{
		if (dis5 < disri)
		{
			int x = pos3.x;
			int y = pos3.y;
			int time = sqrt((pos5.x - x)*(pos5.x - x) + (pos5.y - y)*(pos5.y - y));
			if (time < 100)
			{
				b5 = b5 - 50;
			}
			else
			{
				time = sqrt((pos5.x - x)*(pos5.x - x) + (pos5.y - y)*(pos5.y - y)) - 100;
				time = time / 40;
				xiaobing3->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

			}
		}
		else
		{
			int x = pos3.x;
			int y = pos3.y;
			int time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y));
			if (time < 100)
			{
				bri = bri - 50;
			}
			else
			{
				time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y)) - 100;
				time = time / 40;
				xiaobing3->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

			}


		}
	}
	else if (dis6 < disri)
	{
		int x = pos3.x;
		int y = pos3.y;
		int time = sqrt((pos6.x - x)*(pos6.x - x) + (pos6.y - y)*(pos6.y - y));
		if (time < 100)
		{
			b6 = b6 - 50;
		}
		else
		{
			time = sqrt((pos6.x - x)*(pos6.x - x) + (pos6.y - y)*(pos6.y - y)) - 100;
			time = time / 40;
			xiaobing3->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

		}

	}
	else
	{
		int x = pos3.x;
		int y = pos3.y;
		int time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y));
		if (time < 100)
		{
			bri = bri - 50;
		}
		else
		{
			time = sqrt((ri.x - x)*(ri.x - x) + (ri.y - y)*(ri.y - y)) - 100;
			time = time / 40;
			xiaobing3->runAction(MoveTo::create(time, Vec2(nx - 100, ny)));

		}


	}
}