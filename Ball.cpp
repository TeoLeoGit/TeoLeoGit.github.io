#include "Ball.h"

CBall::CBall()
{
}

CBall::~CBall()
{
}

void CBall::moveBALL()
{
	POS.x += SPEED.x;
	POS.y += SPEED.y;
	BALLSpr.setPosition(POS); //Đặt vị trí của bóng cho mỗi vòng lặp trong game
}

void CBall::changeMODE(int &Score)
{
	if (DURABIL < 4 && Score > 2)
	{
		BALLMode = 2;
		BALLSpr.setColor(Color::Blue);
		Score = Score - 3;
	}
}
