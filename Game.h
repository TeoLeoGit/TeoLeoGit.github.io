#pragma once
#include "CBrick.h"
#include<iostream>
#include <vector>
#include "Paddle.h"

class Game
{
private:
	Texture mBGD; // Bằng Kích thước của Màn hình
	Text SCOREText;
	Font SCOREFont;
	int BREAKEDBr; //số gạch đã phá
	CBall BALL;
	bool BRelease;
	vector <CircleShape> BALLPath; // đường đi của bóng;
	CPaddle PADDLE;
	Texture MBrick1; //3 texture cho 3 loại brick
	Texture MBrick2;
	Texture MBrick3;
	CBrick BRICK[6][6]; // tạo 1 bức tường gạch 6x6 (36 viên)
public:
	int SCORE;
	Game();// Khởi tạo các thành phần của trò chơi
	~Game();
	int winner;
	Sprite BGD; //Hiển 
	void controlPad(); // Điều khiển thanh đỡ
	void ballCollision();//Xử lý bóng
	void Drawto(RenderWindow& window); // Hiển thị các thành phần của trò chơi ra màn hình
	void paddleColl(); // Xử lý va chạm và giới hạn khu vực di chuyển cho Thanh đõ
	void autoPad();
	void createPath(vector <CircleShape>& Path);
	int run(int Mode); // Chạy game
};

