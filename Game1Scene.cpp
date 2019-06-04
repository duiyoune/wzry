#include "Game1Scene.h"
#include "SimpleAudioEngine.h"
#include<math.h>
#include<iostream>
#include<string.h>
#include "ui/CocosGUI.h"
#include "ui/UILoadingBar.h"

using namespace ui;
using namespace std;
using namespace CocosDenshion;
USING_NS_CC;

Size visibleSize;
Vec2 origin;
//界面
auto BGM = SimpleAudioEngine::getInstance();//背景音乐
auto SoundEffect = SimpleAudioEngine::getInstance();//音效
int time_min;//时间（分）
int time_sec;//时间（秒）
Label * Time;//时间
Label * ScoreBoard;//计分板
int kills = 0;//击杀数
int deaths = 0;//死亡数
Label * column_xp_and_lv;//经验、等级
int xp = 0;//经验
int lv = 0;//等级
Sprite * cursor;//光标
//小兵
Sprite *  creep_ally[10000];//友方小兵
Sprite *  creep_enemy[10000];//敌方小兵
LoadingBar * hp_ally[10000];//友方小兵血条
LoadingBar * hp_enemy[10000];//敌方小兵血条
MoveBy * move_ally;//友方小兵移动
MoveBy * move_enemy;//敌方小兵移动
bool pause_ally[600] = { 0 };//友方小兵是否停止移动
bool pause_enemy[600] = { 0 };//敌方小兵是否停止移动
bool attack_creepAhero[600] = { 0 };//敌方小兵是否攻击友方英雄
int i_creep = 0;//小兵序号
int j_creep = 0;//小兵序号
//小兵属性
float CreepsSpawnInterval = 3;//出兵间隔
int AttackRange_creep = 150;//小兵攻击范围
float AttackInterval_creep = 1;//小兵攻击间隔
float Damage_creep = 50;//小兵攻击力
float HP_ally[600];//友方小兵血量
float HP_enemy[600];//敌方小兵血量
float Max_HP_creep = 1000;//小兵最大血量
//英雄
Sprite *  hero;//英雄
LoadingBar * hp_hero;//英雄血条
int attack_target = -1;//英雄所攻击的敌方小兵
bool attack_heroAcreep = false;//英雄是否攻击小兵
int tag_hero = 0;//英雄动作
//英雄属性
float MoveSpeed_hero = 500;//英雄移动速度
int AttackRange_hero = 300;//英雄攻击范围
float AttackInterval_hero = 0.5;//英雄攻击间隔
float Damage_hero = 200;//英雄攻击力
float HP_hero = 1000;//英雄血量
float Max_HP_hero = 1000;//英雄最大血量
//技能
//技能1
int LV_ability1 = 4;//技能1等级
bool duration_ability1 = false;//技能1是否处于持续期间
bool cd_ability1 = false;//技能1是否处于冷却期间
//技能1属性
int CD_ability1 = 30;//技能1冷却时间
int Duration_ability1 = 15;//技能1持续时间
//技能2
int LV_ability2 = 4;//技能2等级
bool cd_ability2 = false;//技能2是否处于冷却期间
//技能2属性
int CD_ability2 = 10;//技能2冷却时间
//技能3
int LV_ability3 = 4;//技能3等级
bool cd_ability3 = false;//技能3是否处于冷却期间
bool ability3Clicked = false;//技能3是否被按下
int ability3_target = -1;//技能3所作用的小兵
bool ability3Moving = false;//英雄是否为释放技能3处于移动中
//技能3属性
float CastRange_ability3 = 500;//技能3施法范围
int CD_ability3 = 10;//技能3冷却时间
//技能4
int LV_ability4 = 4;//技能4等级

string str1;
string str2;
string str3;
string str4;
string str5;

Scene* Game1::createScene()
{
	return Game1::create();
}

bool Game1::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//小兵初始血量为1000
	for (int i = 0; i < 600; i++)
	{
		HP_ally[i] = { 1000 };
		HP_enemy[i] = { 1000 };
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	/*auto map = Sprite::create("map.png");
	auto scaleTo1 = ScaleTo::create(0, 5);
	map->runAction(scaleTo1);
	map->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(map, 0);*/
	//界面
	//背景音乐
	BGM->playBackgroundMusic("bgm.mp3", true);
	//显示时间
	this->schedule(schedule_selector(Game1::timeUpdate), 1);
	//小兵
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
	//英雄
    hero = Sprite::create("bm.png");
	float positionX = visibleSize.width / 2 + origin.x;
	float positionY = visibleSize.height / 2 + origin.y;
	hero->setPosition(Vec2(positionX, positionY));
	this->addChild(hero, 99);
	//英雄血条
	hp_hero = LoadingBar::create("hp.png");
	hp_hero->setDirection(LoadingBar::Direction::RIGHT);
	this->addChild(hp_hero,98);
	hp_hero->setPercent(100);
	//英雄攻击
	this->schedule(schedule_selector(Game1::attack_heroUpdate), AttackInterval_hero);
	//事件
	//键盘按下、松开
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Game1::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Game1::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//鼠标按下、移动
	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseDown = CC_CALLBACK_1(Game1::onMouseDown, this);
	_mouseListener->onMouseMove = CC_CALLBACK_1(Game1::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
	//帧定时器
	this->scheduleUpdate();

	return true;
}
//界面
//显示时间
void Game1::timeUpdate(float delta)
{
	if (Time != nullptr)
	{
		Time->removeFromParent();
	}	
	time_sec += 1;
	if (time_sec == 60)
	{
		time_min += 1;
		time_sec = 0;
	}
	stringstream Min;Min << time_min;
	stringstream Sec;Sec << time_sec;
	if (time_min < 10)
	{
		str1 = "0";
	}
	else str1 = "";
	str2 = Min.str();
	str3 = ":";
	if (time_sec < 10)
	{
		str4 = "0";
	}
	else str4 = "";
	str5 = Sec.str();
	string time = str1 + str2 + str3 + str4 + str5;
	Time = Label::createWithSystemFont(time, "fonts/Marker Felt.ttf", 40);
	this->addChild(Time);
	float positionX = visibleSize.width / 2 + origin.x;
	float positionY = visibleSize.height  + origin.y-Time->getContentSize().height;
	Time->setPosition(positionX, positionY);
}
//显示经验等级
void Game1::xpANDlv()
{
	if (column_xp_and_lv != nullptr)
	{
		column_xp_and_lv->removeFromParent();
	}
	if (xp >= 1000)
	{
		lv = lv + xp / 1000;
		xp = xp % 1000;
	}
	stringstream Xp;Xp << xp;
	stringstream Lv;Lv << lv;
	str1 = "Lv:";
	str2 = Lv.str();
	str3 = " Xp:";
	str4 = Xp.str();
	str5 = "/1000";
	string xp_and_lv = str1 + str2 + str3 + str4 + str5;
	column_xp_and_lv = Label::createWithSystemFont(xp_and_lv, "fonts/Marker Felt.ttf", 40);
	this->addChild(column_xp_and_lv);
	column_xp_and_lv->setPosition(300, 100);
}
//计分板
void Game1::scoreBoard()
{
	//显示击杀死亡
	stringstream Kills;Kills << kills;
	stringstream Deaths;Deaths << deaths;
	str1 = "Kills:";
	str2 = Kills.str();
	str3 = " Deaths:";
	str4 = Deaths.str();
	string KillsDeaths = str1 + str2 + str3 + str4;
	ScoreBoard = Label::createWithSystemFont(KillsDeaths, "fonts/Marker Felt.ttf", 40);
	this->addChild(ScoreBoard);
	ScoreBoard->setAnchorPoint(Vec2(0, 1));
	ScoreBoard->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
}
//关闭计分板
void Game1::closeScoreBoard()
{
	ScoreBoard->removeFromParent();
}
//小兵
//定时出兵
void Game1::creepsUpdate(float delta)
{
	move_ally = MoveBy::create(10, Vec2(visibleSize.width, 0));
	move_enemy = MoveBy::create(10, Vec2(-visibleSize.width, 0));
	for (j_creep =i_creep +3;j_creep <i_creep +6;j_creep++)
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
		float positionY_ally = origin.y + visibleSize.height*(j_creep -i_creep -2) / 4;
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
		float positionY_enemy = origin.y + visibleSize.height*(j_creep -i_creep -2) / 4;
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
				if (Distance(creep_ally[i], creep_enemy[j])<= AttackRange_creep)
				{
					HP_enemy[j] -= Damage_creep;
					hp_enemy[j]->setPercent(100 * HP_enemy[j]/Max_HP_creep);
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
			if (Distance(hero, creep_enemy[i]) <= AttackRange_creep&& attack_creepAhero[i] == true)
			{
				HP_hero -= Damage_creep;
				hp_hero->setPercent(100 * HP_hero/Max_HP_hero);
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
//英雄
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
	if (hero != nullptr&&creep_enemy[attack_target]!=nullptr)
	{
		if (Distance(hero, creep_enemy[attack_target]) <= AttackRange_hero)
		{
			HP_enemy[attack_target] -= ability4()*Damage_hero;
			hp_enemy[attack_target]->setPercent(100 * HP_enemy[attack_target]/Max_HP_creep);
		}		
	}
}
//英雄随鼠标移动
void Game1::moveWithMouse(float X, float Y)
{
	//技能3选择目标时避免英雄移动
	if (ability3Clicked == true )
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
			if (InTheArea(X,Y, creep_enemy[i])==true)
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
			BGM->stopBackgroundMusic(false);
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
//技能
//技能1
void Game1::ability1()
{
	//技能1冷却、持续
	this->scheduleOnce(schedule_selector(Game1::ability1DurationUpdate), Duration_ability1);
	this->scheduleOnce(schedule_selector(Game1::ability1CDUpdate), CD_ability1);
	duration_ability1 = true;
	cd_ability1 = true;
	//技能1音效
	SoundEffect->playEffect("ability1.wav", false, 1, 0, 1);
	//技能1效果
	switch (LV_ability1)
	{
	case 1:HP_hero *= 0.5;
		MoveSpeed_hero *= 1.5;AttackInterval_hero *= 0.65;Damage_hero *= 1.5;break;
	case 2:HP_hero *= 0.5;
		MoveSpeed_hero *= 1.65; AttackInterval_hero *= 0.6; Damage_hero *= 1.65; break;
	case 3:HP_hero *= 0.5;
		MoveSpeed_hero *= 1.8;AttackInterval_hero *= 0.55;Damage_hero *= 1.8;break;
	case 4:HP_hero *= 0.5;
		MoveSpeed_hero *= 2;AttackInterval_hero *= 0.5;Damage_hero *= 2;break;
	}
}
//技能1持续时间
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
//技能1冷却时间
void Game1::ability1CDUpdate(float delta)
{
	cd_ability1 = false;
}
//技能2
void Game1::ability2()
{
	//技能2冷却
	this->scheduleOnce(schedule_selector(Game1::ability2CDUpdate), CD_ability2);
	cd_ability2 = true;
	//技能2音效
	SoundEffect->playEffect("ability2.wav", false, 1, 0, 1);
	//技能2动画
	auto blade = Sprite::create("blade array.png");
	float positionX = hero->getPositionX() + 30;
	float positionY = hero->getPositionY() - 60;
	blade->setPosition(Vec2(positionX, positionY));
	this->addChild(blade, 1);
	auto FadeOut = FadeOut::create(2);
	blade->runAction(FadeOut);
	//技能2效果
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
//技能2冷却时间
void Game1::ability2CDUpdate(float delta)
{
	cd_ability2 = false;
}
//技能3效果
void Game1::ability3Effect()
{
	//技能3冷却
	this->scheduleOnce(schedule_selector(Game1::ability3CDUpdate), CD_ability3);
	cd_ability3 = true;
	//技能3音效
	SoundEffect->playEffect("ability3.wav", false, 1, 0, 1);
	//技能3动画
	auto blade = Sprite::create("blade.png");
	float positionX = creep_enemy[ability3_target]->getPositionX();
	float positionY = creep_enemy[ability3_target]->getPositionY();
	blade->setPosition(Vec2(positionX , positionY +50));
	this->addChild(blade, 1);
	auto MoveTo = MoveTo::create(2, Vec2(positionX, positionY));
	blade->runAction(MoveTo);
	auto FadeOut = FadeOut::create(2);
	blade->runAction(FadeOut);
	//技能3效果
	switch (LV_ability3)
	{
	case 1:HP_enemy[ability3_target] -= 500; break;
	case 2:HP_enemy[ability3_target] -= 1000; break;
	case 3:HP_enemy[ability3_target] -= 1500; break;
	case 4:HP_enemy[ability3_target] -= 2000; break;
	}
}
//判断技能3是否作用于敌方单位
void Game1::ability3Hit(float X, float Y)
{
	for (int i = 0; i < 600; i++)
	{
		if (creep_enemy[i] != nullptr)
		{
			if (InTheArea(X,Y,creep_enemy[i]) == true)
			{
				ability3_target = i;
				ability3Clicked = false;
				cursor->setPosition(-1000, -1000);
				//判断敌人是否进入技能3施法范围
				if (Distance(hero, creep_enemy[ability3_target]) > CastRange_ability3)
				{
					//移动至施法范围内
					ability3Moving = true;
					float time = Distance(hero, creep_enemy[ability3_target]) / MoveSpeed_hero;
					float positionX = creep_enemy[ability3_target]->getPositionX();
					float positionY = creep_enemy[ability3_target]->getPositionY();
					auto moveTo = MoveTo::create(time, Vec2(positionX, positionY));
					hero->runAction(moveTo);
					moveTo->setTag(1);
				}
				if (Distance(hero, creep_enemy[ability3_target]) <= CastRange_ability3)
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
void Game1::ability3CDUpdate(float delta)
{
	cd_ability3 = false;
}
//技能3光标随鼠标移动
void Game1::ability3Cursor(float X, float Y)
{
	if (cursor != nullptr)
	{
		cursor->removeFromParent();
		//cursor->setPosition(-1000,-1000);
	}
	cursor = Sprite::create("cursor.png");
	this->addChild(cursor);
	cursor->setPosition(X, Y);	
}
//技能4
float Game1::ability4()
{
	float CriticalDamage = 1;
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
//事件
//鼠标按下
void Game1::onMouseDown(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	//获取鼠标点击位置
	float cursorX = e->getCursorX();
	float cursorY = e->getCursorY();
	//获取技能3目标
	if (ability3Clicked==true|| ability3Moving==true)
	{
		//判断技能3是否作用于敌方单位
		ability3Hit(cursorX, cursorY);
		return;
	}
	if (hero != nullptr)
	{
		//英雄随鼠标移动
		moveWithMouse(cursorX, cursorY);
		//是否点击敌方小兵以攻击
		clickCreep_enemy(cursorX, cursorY);
	}
}
//鼠标移动
void Game1::onMouseMove(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	//获取鼠标点击位置
	float cursorX = e->getCursorX();
	float cursorY = e->getCursorY();
	//技能3光标随鼠标移动
	if (ability3Clicked == true)
	{
		ability3Cursor(cursorX, cursorY);
	}
}
//键盘按下
void Game1::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//按下tab打开计分板
	if (keyCode == EventKeyboard::KeyCode::KEY_TAB)
	{
		scoreBoard();
	}
	//技能1触发
	if (keyCode == EventKeyboard::KeyCode::KEY_R && hero!=nullptr)
	{
		if (cd_ability1 == false)
		{
			if (LV_ability1 != 0)
			{
				ability1();
			}				
		}
	}
	//技能2触发
	if (keyCode == EventKeyboard::KeyCode::KEY_T && hero != nullptr)
	{
		if (cd_ability2 == false)
		{
			if (LV_ability2 != 0)
			{
				ability2();
			}
		}
	}
	// 技能3触发
	if (keyCode == EventKeyboard::KeyCode::KEY_G && hero != nullptr)
	{
		if (cd_ability3 == false)
		{
			if (LV_ability3 != 0)
			{
				//选取目标
				ability3Clicked = true;
			}
		}
	}
}
//键盘松开
void Game1::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	//松开tab关闭计分板
	if (keyCode == EventKeyboard::KeyCode::KEY_TAB)
	{
		closeScoreBoard(); 
	}
}
//工具
//帧定时器
void Game1::update(float delta)
{
	//小兵进入攻击范围停止和恢复移动
	creepPauseAndResume();
	//英雄进入攻击范围停止
	heroPauseAttackRange();
	//英雄进入施法范围停止
	heroPauseCastRange();
	//英雄血条跟随
	hpFollow_hero();
	//小兵血条跟随
	hpFollow_creep();
	//小兵死亡
	death_creep();
	//英雄死亡
	death_hero();
	//显示经验等级
	xpANDlv();
}
//计算两者距离
float Game1::Distance(Sprite * A, Sprite * B)
{
	if (A != nullptr&&B != nullptr)
	{
		float positionX_A = A->getPositionX();
		float positionY_A = A->getPositionY();
		float positionX_B = B->getPositionX();
		float positionY_B = B->getPositionY();
		float distance = sqrt(pow(positionX_A - positionX_B, 2) + pow(positionY_A - positionY_B, 2));
		return distance;
	}
}
//判断点是否在区域内
bool Game1::InTheArea(float X, float Y,Sprite  * A)
{
	float positionX = A->getPositionX();
	float positionY = A->getPositionY();
	float contentSizeX = A->getContentSize().width;
	float contentSizeY = A->getContentSize().height;
	float area_Xmin = positionX - 0.5*contentSizeX;
	float area_Xmax = positionX + 0.5*contentSizeX;
	float area_Ymin = positionY - 0.5*contentSizeY;
	float area_Ymax = positionY + 0.5*contentSizeY;
	if (X >= area_Xmin && X <= area_Xmax && Y >= area_Ymin && Y <= area_Ymax)
	{
		return true;
	}
	else return false;
}