#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

#define HScreen 680 // Kích thước của màn hình
#define WScreen 540

using namespace sf;
using namespace std;

class CBall
{
private:
	Texture mball; //30x30 input hình dạng bóng
	Sprite BALLSpr; // Hiển thị và xử lý bóng trong trò chơi
	Vector2f POS; //Vị trí của bóng
	Vector2f SPEED; // Tốc độ của bóng
	int BALLMode;//các dạng bóng (bóng thường và bóng phá vật cản)
	int DURABIL;//độ bền của bóng
public:
	CBall();
	~CBall();
	void moveBALL();
	void changeMODE(int &Score);
	friend class Game;
};

