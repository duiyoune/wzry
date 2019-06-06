#include "Game1Scene.h"
//事件
void Game1::_event()
{
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
}
//鼠标按下
void Game1::onMouseDown(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	//获取鼠标点击位置
	float cursorX = e->getCursorX();
	float cursorY = e->getCursorY();
	//获取技能3目标
	if (ability3Clicked == true || ability3MovingToCreep == true|| ability3MovingToAI == true)
	{
		//判断技能3是否作用于敌方单位
		ability3Hit(cursorX, cursorY);
		return;
	}
	if (hero != nullptr)
	{
		//英雄随鼠标移动
		moveWithMouse(cursorX, cursorY);
		//是否点击敌方英雄以攻击
		clickAI(cursorX, cursorY);
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