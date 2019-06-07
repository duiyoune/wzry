#include "Game1Scene.h"
//界面
void Game1::UI()
{
	//背景音乐
	auto BGM = SimpleAudioEngine::getInstance();//背景音乐
	BGM->playBackgroundMusic("bgm.mp3", true);
	//显示时间
	this->schedule(schedule_selector(Game1::timeUpdate), 1);
}
//显示时间
void Game1::timeUpdate(float delta)
{
	//显示时间
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
	stringstream Min; Min << time_min;
	stringstream Sec; Sec << time_sec;
	string str1 = "";
	if (time_min < 10)
	{
		str1 = "0";
	}
	string str2 = Min.str();
	string str3 = ":";
	string str4 = "";
	if (time_sec < 10)
	{
		str4 = "0";
	}	
	string str5 = Sec.str();
	string time = str1 + str2 + str3 + str4 + str5;
	Time = Label::createWithSystemFont(time, "fonts/Marker Felt.ttf", 40);
	this->addChild(Time);
	float positionX = visibleSize.width / 2 + origin.x;
	float positionY = visibleSize.height + origin.y - Time->getContentSize().height;
	Time->setPosition(positionX, positionY);
}
//经验等级
void Game1::xpANDlv()
{
	if (column_xp_and_lv != nullptr)
	{
		column_xp_and_lv->removeFromParent();
	}
	if (lv < 4)
	{
		if (xp >= 500)
		{
			lv = lv + xp / 500;
			xp = xp % 500;
			lvUP = true;
		}
	}
	
	//升级
	if (lvUP == true)
	{
		switch (lv)
		{
		case 1:LV_ability1 = 1; LV_ability2 = 1; LV_ability3 = 1; LV_ability4 = 1;
			MoveSpeed_hero += 20; AttackInterval_hero -= 0.1; Damage_hero += 20; HP_hero = HP_hero * 1100 / 1000; Max_HP_hero += 100; break;
		case 2:LV_ability1 = 2; LV_ability2 = 2; LV_ability3 = 2; LV_ability4 = 2;
			MoveSpeed_hero += 20; AttackInterval_hero -= 0.1; Damage_hero += 20; HP_hero = HP_hero * 1200 / 1100; Max_HP_hero += 100; break;
		case 3:LV_ability1 = 3; LV_ability2 = 3; LV_ability3 = 3; LV_ability4 = 3;
			MoveSpeed_hero += 20; AttackInterval_hero -= 0.1; Damage_hero += 20; HP_hero = HP_hero * 1300 / 1200; Max_HP_hero += 100; break;
		case 4:LV_ability1 = 4; LV_ability2 = 4; LV_ability3 = 4; LV_ability4 = 4;
			MoveSpeed_hero += 20; AttackInterval_hero -= 0.1; Damage_hero += 20; HP_hero = HP_hero * 1400 / 1300; Max_HP_hero += 100; break;
		default:break;
		}
		lvUP = false;
	}	
	//显示经验等级
	stringstream Xp; Xp << xp;
	stringstream Lv; Lv << lv;
	string str1 = "Lv:";
	string str2 = Lv.str();
	string str3 = "/4";
	string str4 = " Xp:";
	string str5 = Xp.str();
	string str6 = "/500";
	string xp_and_lv = str1 + str2 + str3 + str4 + str5 + str6;
	column_xp_and_lv = Label::createWithSystemFont(xp_and_lv, "fonts/Marker Felt.ttf", 40);
	this->addChild(column_xp_and_lv);
	column_xp_and_lv->setPosition(300, 100);
}
//计分板
void Game1::scoreBoard()
{
	//显示击杀死亡
	stringstream Kills; Kills << kills;
	stringstream Deaths; Deaths << deaths;
	string str1 = "Kills:";
	string str2 = Kills.str();
	string str3 = " Deaths:";
	string str4 = Deaths.str();
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