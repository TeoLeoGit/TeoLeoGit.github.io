#pragma once
#include "Ball.h"
class CBrick
{
private:
	Texture MBrick;
	int TYPE;
	bool BREAKED;
	Sprite BRICKSpr;
public:
	CBrick();
	~CBrick();
	friend class Game;
};

