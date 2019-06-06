#include "Game1Scene.h"
//�¼�
void Game1::_event()
{
	//���̰��¡��ɿ�
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Game1::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Game1::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//��갴�¡��ƶ�
	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseDown = CC_CALLBACK_1(Game1::onMouseDown, this);
	_mouseListener->onMouseMove = CC_CALLBACK_1(Game1::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}
//��갴��
void Game1::onMouseDown(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	//��ȡ�����λ��
	float cursorX = e->getCursorX();
	float cursorY = e->getCursorY();
	//��ȡ����3Ŀ��
	if (ability3Clicked == true || ability3MovingToCreep == true|| ability3MovingToAI == true)
	{
		//�жϼ���3�Ƿ������ڵз���λ
		ability3Hit(cursorX, cursorY);
		return;
	}
	if (hero != nullptr)
	{
		//Ӣ��������ƶ�
		moveWithMouse(cursorX, cursorY);
		//�Ƿ����з�Ӣ���Թ���
		clickAI(cursorX, cursorY);
		//�Ƿ����з�С���Թ���
		clickCreep_enemy(cursorX, cursorY);
	}
}
//����ƶ�
void Game1::onMouseMove(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	//��ȡ�����λ��
	float cursorX = e->getCursorX();
	float cursorY = e->getCursorY();
	//����3���������ƶ�
	if (ability3Clicked == true)
	{
		ability3Cursor(cursorX, cursorY);
	}
}
//���̰���
void Game1::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//����tab�򿪼Ʒְ�
	if (keyCode == EventKeyboard::KeyCode::KEY_TAB)
	{
		scoreBoard();
	}
	//����1����
	if (keyCode == EventKeyboard::KeyCode::KEY_R && hero != nullptr)
	{
		if (cd_ability1 == false)
		{
			if (LV_ability1 != 0)
			{
				ability1();
			}
		}
	}
	//����2����
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
	// ����3����
	if (keyCode == EventKeyboard::KeyCode::KEY_G && hero != nullptr)
	{
		if (cd_ability3 == false)
		{
			if (LV_ability3 != 0)
			{
				//ѡȡĿ��
				ability3Clicked = true;
			}
		}
	}
}
//�����ɿ�
void Game1::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	//�ɿ�tab�رռƷְ�
	if (keyCode == EventKeyboard::KeyCode::KEY_TAB)
	{
		closeScoreBoard();
	}
}