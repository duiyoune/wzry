#include "Game1Scene.h"
//����
void Game1::tool()
{
	//֡��ʱ��
	this->scheduleUpdate();
}
//֡��ʱ��
void Game1::update(float delta)
{
	//С�����빥����Χֹͣ�ͻָ��ƶ�
	creepPauseAndResume();
	//Ӣ�۽��빥����Χֹͣ
	heroPauseAttackRange();
	//Ӣ�۽���ʩ����Χֹͣ
	heroPauseCastRange();
	//Ӣ��Ѫ������
	hpFollow_hero();
	//aiѪ������
	hpFollow_ai();
	//С��Ѫ������
	hpFollow_creep();
	//Ӣ������
	death_hero();
	//ai����
	death_ai();
	//С������
	death_creep();
	//��ʾ����ȼ�
	xpANDlv();
}
//�������߾���
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
//�жϵ��Ƿ���������
bool Game1::InTheArea(float X, float Y, Sprite  * A)
{
	if (A != nullptr)
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
}
