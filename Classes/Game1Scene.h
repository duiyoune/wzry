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

	void UI();//����
	void timeUpdate(float delta);//��ʾʱ��
	void scoreBoard();//�Ʒְ�
	void closeScoreBoard();//�رռƷְ�
	void xpANDlv();//����ȼ�

	void creep();//С��
	void creepsUpdate(float delta);//��ʱ����
	void creepPauseAndResume();//С�����빥����Χֹͣ�ͻָ��ƶ�
	void attack_creepUpdate(float delta);//С������
	void death_creep();//С������
	void hpFollow_creep();//С��Ѫ������
	
	void hero_BM();//Ӣ��
	void heroPauseAttackRange();//Ӣ�۽��빥����Χֹͣ
	void heroPauseCastRange();//Ӣ�۽���ʩ����Χֹͣ
	void attack_heroUpdate(float delta);//Ӣ�۹���
	void moveWithMouse(float X, float Y);//Ӣ��������ƶ�
	void clickAI(float X, float Y);//�Ƿ����з�Ӣ���Թ���
	void clickCreep_enemy(float X, float Y);//�Ƿ����з�С���Թ���
	void death_hero();//Ӣ������
	void RespawnHeroUpdate(float delta);//Ӣ������
	void hpFollow_hero();//Ӣ��Ѫ������
	void healthRegen_heroUpdate(float delta);//Ӣ���Զ���Ѫ

	void hero_ai();//���˷���ĵ���
	void aiAction();//ai�ж�
	void aiPauseAndResume();//ai���빥����Χֹͣ�ͻָ��ƶ�
	void attack_aiUpdate(float delta);//ai����
	void death_ai();//ai����
	void RespawnAIUpdate(float delta);//ai����
	void hpFollow_ai();//aiѪ������
	void healthRegen_aiUpdate(float delta);//ai�Զ���Ѫ

    //����
	void ability1();//����1
	void ability1DurationUpdate(float delta);//����1����ʱ��
	void ability1CDUpdate(float delta);//����1��ȴʱ��
	void ability2();//����2
	void ability2CDUpdate(float delta);//����2��ȴʱ��
	void ability3Effect();//����3Ч��
	void ability3CDUpdate(float delta);//����3��ȴʱ��
	void ability3Hit(float X, float Y);//�жϼ���3�Ƿ������ڵз���λ
	void ability3Cursor(float X, float Y);//����3���������ƶ�
	double ability4(); //����4

	void _event();//�¼�
	void onMouseDown(Event *event);//��갴��
	void onMouseMove(Event *event);//����ƶ�
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);//���̰���
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);//�����ɿ�
	
	void tool();//����
	virtual void update(float delta);//֡��ʱ��
	float Distance(Sprite * A, Sprite * B);//�������
	bool InTheArea(float X,float Y,Sprite * A);//�жϵ��Ƿ���������
	
public:
	//����
	Size visibleSize;
	Vec2 origin;
	int time_min;//ʱ�䣨�֣�
	int time_sec;//ʱ�䣨�룩
	Label * Time;//ʱ��
	Label * ScoreBoard;//�Ʒְ�
	int kills = 0;//��ɱ��
	int deaths = 0;//������
	Label * column_xp_and_lv;//���顢�ȼ�
	bool lvUP=false;//�ж��Ƿ�����
	int xp = 0;//����
	int lv = 0;//�ȼ�
	Sprite * cursor;//���
	//С��
	Sprite *  creep_ally[10000];//�ѷ�С��
	Sprite *  creep_enemy[10000];//�з�С��
	LoadingBar * hp_ally[10000];//�ѷ�С��Ѫ��
	LoadingBar * hp_enemy[10000];//�з�С��Ѫ��
	MoveBy * move_ally;//�ѷ�С���ƶ�
	MoveBy * move_enemy;//�з�С���ƶ�
	bool pause_ally[600] = { 0 };//�ѷ�С���Ƿ�ֹͣ�ƶ�
	bool pause_enemy[600] = { 0 };//�з�С���Ƿ�ֹͣ�ƶ�
	bool attack_creepAai[600] = { 0 };//�ѷ�С���Ƿ񹥻��з�Ӣ��
	bool attack_creepAhero[600] = { 0 };//�з�С���Ƿ񹥻��ѷ�Ӣ��
	int i_creep = 0;//С�����
	int j_creep = 0;//С�����
	//С������
	int CreepsSpawnInterval = 10;//�������
	double MoveSpeed_creep = 150;//С���ƶ��ٶ�
	double AttackRange_creep = 150;//С��������Χ
	double AttackInterval_creep = 1;//С���������
	double Damage_creep = 50;//С��������
	double HP_ally[600];//�ѷ�С��Ѫ��
	double HP_enemy[600];//�з�С��Ѫ��
	double Max_HP_creep = 500;//С�����Ѫ��

	double HealthRegen = 100;//Ȫˮ��Ѫ
	//Ӣ��
	Sprite *  hero;//Ӣ��
	LoadingBar * hp_hero;//Ӣ��Ѫ��
	bool attack_heroAai = false;//Ӣ���Ƿ񹥻��з�Ӣ��
	int attack_target = -1;//Ӣ���������ĵз�С��
	bool attack_heroAcreep = false;//Ӣ���Ƿ񹥻�С��
	int tag_hero = 0;//Ӣ�۶���
	//Ӣ������
	int RespawnTime_hero = 10;//����ʱ��
	double MoveSpeed_hero = 500;//Ӣ���ƶ��ٶ�
	int AttackRange_hero = 300;//Ӣ�۹�����Χ
	double AttackInterval_hero = 0.5;//Ӣ�۹������
	double Damage_hero = 100;//Ӣ�۹�����
	double HP_hero = 1000;//Ӣ��Ѫ��
	double Max_HP_hero = 1000;//Ӣ�����Ѫ��
	double HealthRegen_hero = 10;//Ӣ��ÿ���Ѫ
	//���˷���ĵ���
	Sprite *  ai;//ai
	LoadingBar * hp_ai;//aiѪ��
	bool aiAssault = false;//ai�Ƿ���
	bool aiRetreat = false;//ai�Ƿ���
	bool aiAssaulting = false;//ai�Ƿ����ڳ��
	bool aiRetreating = false;//ai�Ƿ����ڳ���
	bool pause_ai = false;//ai�Ƿ�ֹͣ�ƶ�
	//ai����
	int RespawnTime_ai = 10;//����ʱ��
	double MoveSpeed_ai = 500;//ai�ƶ��ٶ�
	int AttackRange_ai = 300;//ai������Χ
	double AttackInterval_ai = 0.5;//ai�������
	double Damage_ai = 100;//ai������
	double HP_ai = 1000;//aiѪ��
	double Max_HP_ai = 1000;//ai���Ѫ��
	double HealthRegen_ai = 10;//aiÿ���Ѫ
	//����
	//����1
	int LV_ability1 = 0;//����1�ȼ�
	bool duration_ability1 = false;//����1�Ƿ��ڳ����ڼ�
	bool cd_ability1 = false;//����1�Ƿ�����ȴ�ڼ�
	//����1����
	int CD_ability1 = 30;//����1��ȴʱ��
	int Duration_ability1 = 15;//����1����ʱ��
	//����2
	int LV_ability2 = 0;//����2�ȼ�
	bool cd_ability2 = false;//����2�Ƿ�����ȴ�ڼ�
	//����2����
	int CD_ability2 = 10;//����2��ȴʱ��
	//����3
	int LV_ability3 = 0;//����3�ȼ�
	bool cd_ability3 = false;//����3�Ƿ�����ȴ�ڼ�
	bool ability3Clicked = false;//����3�Ƿ񱻰���
	int ability3_target = -1;//����3�����õ�С��
	bool ability3_targetAI = false;//����3�Ƿ�������ai
	bool ability3MovingToCreep = false;//Ӣ���Ƿ�Ϊ�ͷż���3��С���ƶ�
	bool ability3MovingToAI = false;//Ӣ���Ƿ�Ϊ�ͷż���3��ai�ƶ�
	//����3����
	double CastRange_ability3 = 500;//����3ʩ����Χ
	int CD_ability3 = 10;//����3��ȴʱ��
	//����4
	int LV_ability4 = 0;//����4�ȼ�
};

#endif // __Game1_SCENE_H__