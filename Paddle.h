#pragma once
#include "Ball.h"
class CPaddle
{
private:
	Texture MPaddle; //90x18
	Sprite PADSpr; //Hiển thị và xử lý Thanh đỡ 
public:
	CPaddle();
	~CPaddle();
	friend class Game;
};

