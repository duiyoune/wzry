#include "Game1Scene.h"
//¹¤¾ß
void Game1::tool()
{
	//Ö¡¶¨Ê±Æ÷
	this->scheduleUpdate();
}
//Ö¡¶¨Ê±Æ÷
void Game1::update(float delta)
{
	//Ğ¡±ø½øÈë¹¥»÷·¶Î§Í£Ö¹ºÍ»Ö¸´ÒÆ¶¯
	creepPauseAndResume();
	//Ó¢ĞÛ½øÈë¹¥»÷·¶Î§Í£Ö¹
	heroPauseAttackRange();
	//Ó¢ĞÛ½øÈëÊ©·¨·¶Î§Í£Ö¹
	heroPauseCastRange();
	//Ó¢ĞÛÑªÌõ¸úËæ
	hpFollow_hero();
	//aiÑªÌõ¸úËæ
	hpFollow_ai();
	//Ğ¡±øÑªÌõ¸úËæ
	hpFollow_creep();
	//Ó¢ĞÛËÀÍö
	death_hero();
	//aiËÀÍö
	death_ai();
	//Ğ¡±øËÀÍö
	death_creep();
	//ÏÔÊ¾¾­ÑéµÈ¼¶
	xpANDlv();
}
//¼ÆËãÁ½Õß¾àÀë
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
//ÅĞ¶ÏµãÊÇ·ñÔÚÇøÓòÄÚ
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
