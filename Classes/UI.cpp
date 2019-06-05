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
	float positionY = visibleSize.height + origin.y - Time->getContentSize().height;
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
	stringstream Xp; Xp << xp;
	stringstream Lv; Lv << lv;
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
	stringstream Kills; Kills << kills;
	stringstream Deaths; Deaths << deaths;
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