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
	//����
	void timeUpdate(float delta);//��ʾʱ��
	void scoreBoard();//�Ʒְ�
	void closeScoreBoard();//�رռƷְ�
	void xpANDlv();//��ʾ����ȼ�
	//С��
	void creepsUpdate(float delta);//��ʱ����
	void creepPauseAndResume();//С�����빥����Χֹͣ�ͻָ��ƶ�
	void attack_creepUpdate(float delta);//С������
	void death_creep();//С������
	void hpFollow_creep();//С��Ѫ������
	//Ӣ��
	void heroPauseAttackRange();//Ӣ�۽��빥����Χֹͣ
	void heroPauseCastRange();//Ӣ�۽���ʩ����Χֹͣ
	void attack_heroUpdate(float delta);//Ӣ�۹���
	void moveWithMouse(float X, float Y);//Ӣ��������ƶ�
	void clickCreep_enemy(float X, float Y);//�Ƿ����з�С���Թ���
	void death_hero();//Ӣ������
	void hpFollow_hero();//Ӣ��Ѫ������
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
	float ability4(); //����4
	//�¼�
	void onMouseDown(Event *event);//��갴��
	void onMouseMove(Event *event);//����ƶ�
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);//���̰���
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);//�����ɿ�
	//����
	virtual void update(float delta);//֡��ʱ��
	float Distance(Sprite * A, Sprite * B);//�������
	bool InTheArea(float X,float Y,Sprite * A);//�жϵ��Ƿ���������
	CREATE_FUNC(Game1);
};

#endif // __Game1_SCENE_H__