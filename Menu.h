#pragma once
#include"Game.h"
#include <fstream>

#define Item 4 // Có 3 lựa chọn
class Menu
{
private:
	int selectedItem; // Lưu giá trị lựa chọn của người chơi
	Font font; //Lưu Font 
	Text menu[Item];// Các lựa chọn của menu
	Texture mbgd; // Lưu hình ảnh của BackGround
public:
	Menu();// Khởi tạo Màn hình tùy chọn
	~Menu();
	Sprite bgd; // Hiển thị BackGround
	void Draw(RenderWindow& window); //Hiện các tùy chọn ra màn hình
	void DrawWinner(int win, int Score); //Hiện Người chiến thắng
	void moveUp(); // Thao tác di chuyển lên trong tùy chọn
	void moveDown(); // Thao tác di chuyển xuống trong tùy chọn
	void DrawGuide(); //Màn hình Hướng dẫn trò chơi
	void run(); //Hàm dùng để chạy Game
	void saveSCORE(int ); //lưu điểm vào file
};

