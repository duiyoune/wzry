#ifndef __Game1_SCENE_H__
#define __Game1_SCENE_H__

#include "cocos2d.h"
#include "ui/UILoadingBar.h"

using namespace std;
USING_NS_CC;
using namespace ui;
class Game1 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	//界面
	void timeUpdate(float delta);//显示时间
	void scoreBoard();//计分板
	void closeScoreBoard();//关闭计分板
	void xpANDlv();//显示经验等级
	//小兵
	void creepsUpdate(float delta);//定时出兵
	void creepPauseAndResume();//小兵进入攻击范围停止和恢复移动
	void attack_creepUpdate(float delta);//小兵攻击
	void death_creep();//小兵死亡
	void hpFollow_creep();//小兵血条跟随
	//英雄
	void heroPauseAttackRange();//英雄进入攻击范围停止
	void heroPauseCastRange();//英雄进入施法范围停止
	void attack_heroUpdate(float delta);//英雄攻击
	void moveWithMouse(float X, float Y);//英雄随鼠标移动
	void clickCreep_enemy(float X, float Y);//是否点击敌方小兵以攻击
	void death_hero();//英雄死亡
	void hpFollow_hero();//英雄血条跟随
    //技能
	void ability1();//技能1
	void ability1DurationUpdate(float delta);//技能1持续时间
	void ability1CDUpdate(float delta);//技能1冷却时间
	void ability2();//技能2
	void ability2CDUpdate(float delta);//技能2冷却时间
	void ability3Effect();//技能3效果
	void ability3CDUpdate(float delta);//技能3冷却时间
	void ability3Hit(float X, float Y);//判断技能3是否作用于敌方单位
	void ability3Cursor(float X, float Y);//技能3光标随鼠标移动
	float ability4(); //技能4
	//事件
	void onMouseDown(Event *event);//鼠标按下
	void onMouseMove(Event *event);//鼠标移动
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);//键盘按下
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);//键盘松开
	//工具
	virtual void update(float delta);//帧定时器
	float Distance(Sprite * A, Sprite * B);//计算距离
	bool InTheArea(float X,float Y,Sprite * A);//判断点是否在区域内
	CREATE_FUNC(Game1);
};

#endif // __Game1_SCENE_H__