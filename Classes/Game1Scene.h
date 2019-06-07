#ifndef __Game1_SCENE_H__
#define __Game1_SCENE_H__

#include "cocos2d.h"
#include "ui/UILoadingBar.h"
#include "SimpleAudioEngine.h"

using namespace std;
USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;

class Game1 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Game1);

	void UI();//界面
	void timeUpdate(float delta);//显示时间
	void scoreBoard();//计分板
	void closeScoreBoard();//关闭计分板
	void xpANDlv();//经验等级

	void creep();//小兵
	void creepsUpdate(float delta);//定时出兵
	void creepPauseAndResume();//小兵进入攻击范围停止和恢复移动
	void attack_creepUpdate(float delta);//小兵攻击
	void death_creep();//小兵死亡
	void hpFollow_creep();//小兵血条跟随
	
	void hero_BM();//英雄
	void heroPauseAttackRange();//英雄进入攻击范围停止
	void heroPauseCastRange();//英雄进入施法范围停止
	void attack_heroUpdate(float delta);//英雄攻击
	void moveWithMouse(float X, float Y);//英雄随鼠标移动
	void clickAI(float X, float Y);//是否点击敌方英雄以攻击
	void clickCreep_enemy(float X, float Y);//是否点击敌方小兵以攻击
	void death_hero();//英雄死亡
	void RespawnHeroUpdate(float delta);//英雄重生
	void hpFollow_hero();//英雄血条跟随
	void healthRegen_heroUpdate(float delta);//英雄自动回血

	void hero_ai();//令人发狂的电脑
	void aiAction();//ai行动
	void aiPauseAndResume();//ai进入攻击范围停止和恢复移动
	void attack_aiUpdate(float delta);//ai攻击
	void death_ai();//ai死亡
	void RespawnAIUpdate(float delta);//ai重生
	void hpFollow_ai();//ai血条跟随
	void healthRegen_aiUpdate(float delta);//ai自动回血

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
	double ability4(); //技能4

	void _event();//事件
	void onMouseDown(Event *event);//鼠标按下
	void onMouseMove(Event *event);//鼠标移动
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);//键盘按下
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);//键盘松开
	
	void tool();//工具
	virtual void update(float delta);//帧定时器
	float Distance(Sprite * A, Sprite * B);//计算距离
	bool InTheArea(float X,float Y,Sprite * A);//判断点是否在区域内
	
public:
	//界面
	Size visibleSize;
	Vec2 origin;
	int time_min;//时间（分）
	int time_sec;//时间（秒）
	Label * Time;//时间
	Label * ScoreBoard;//计分板
	int kills = 0;//击杀数
	int deaths = 0;//死亡数
	Label * column_xp_and_lv;//经验、等级
	bool lvUP=false;//判断是否升级
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
	bool attack_creepAai[600] = { 0 };//友方小兵是否攻击敌方英雄
	bool attack_creepAhero[600] = { 0 };//敌方小兵是否攻击友方英雄
	int i_creep = 0;//小兵序号
	int j_creep = 0;//小兵序号
	//小兵属性
	int CreepsSpawnInterval = 10;//出兵间隔
	double MoveSpeed_creep = 150;//小兵移动速度
	double AttackRange_creep = 150;//小兵攻击范围
	double AttackInterval_creep = 1;//小兵攻击间隔
	double Damage_creep = 50;//小兵攻击力
	double HP_ally[600];//友方小兵血量
	double HP_enemy[600];//敌方小兵血量
	double Max_HP_creep = 500;//小兵最大血量

	double HealthRegen = 100;//泉水回血
	//英雄
	Sprite *  hero;//英雄
	LoadingBar * hp_hero;//英雄血条
	bool attack_heroAai = false;//英雄是否攻击敌方英雄
	int attack_target = -1;//英雄所攻击的敌方小兵
	bool attack_heroAcreep = false;//英雄是否攻击小兵
	int tag_hero = 0;//英雄动作
	//英雄属性
	int RespawnTime_hero = 10;//重生时间
	double MoveSpeed_hero = 500;//英雄移动速度
	int AttackRange_hero = 300;//英雄攻击范围
	double AttackInterval_hero = 0.5;//英雄攻击间隔
	double Damage_hero = 100;//英雄攻击力
	double HP_hero = 1000;//英雄血量
	double Max_HP_hero = 1000;//英雄最大血量
	double HealthRegen_hero = 10;//英雄每秒回血
	//令人发狂的电脑
	Sprite *  ai;//ai
	LoadingBar * hp_ai;//ai血条
	bool aiAssault = false;//ai是否冲锋
	bool aiRetreat = false;//ai是否撤退
	bool aiAssaulting = false;//ai是否正在冲锋
	bool aiRetreating = false;//ai是否正在撤退
	bool pause_ai = false;//ai是否停止移动
	//ai属性
	int RespawnTime_ai = 10;//重生时间
	double MoveSpeed_ai = 500;//ai移动速度
	int AttackRange_ai = 300;//ai攻击范围
	double AttackInterval_ai = 0.5;//ai攻击间隔
	double Damage_ai = 100;//ai攻击力
	double HP_ai = 1000;//ai血量
	double Max_HP_ai = 1000;//ai最大血量
	double HealthRegen_ai = 10;//ai每秒回血
	//技能
	//技能1
	int LV_ability1 = 0;//技能1等级
	bool duration_ability1 = false;//技能1是否处于持续期间
	bool cd_ability1 = false;//技能1是否处于冷却期间
	//技能1属性
	int CD_ability1 = 30;//技能1冷却时间
	int Duration_ability1 = 15;//技能1持续时间
	//技能2
	int LV_ability2 = 0;//技能2等级
	bool cd_ability2 = false;//技能2是否处于冷却期间
	//技能2属性
	int CD_ability2 = 10;//技能2冷却时间
	//技能3
	int LV_ability3 = 0;//技能3等级
	bool cd_ability3 = false;//技能3是否处于冷却期间
	bool ability3Clicked = false;//技能3是否被按下
	int ability3_target = -1;//技能3所作用的小兵
	bool ability3_targetAI = false;//技能3是否作用于ai
	bool ability3MovingToCreep = false;//英雄是否为释放技能3向小兵移动
	bool ability3MovingToAI = false;//英雄是否为释放技能3向ai移动
	//技能3属性
	double CastRange_ability3 = 500;//技能3施法范围
	int CD_ability3 = 10;//技能3冷却时间
	//技能4
	int LV_ability4 = 0;//技能4等级
};

#endif // __Game1_SCENE_H__