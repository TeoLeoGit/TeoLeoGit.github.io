#include "Menu.h"

Menu::Menu()
{
	mbgd.loadFromFile("BackGroundMenu.png");
	bgd.setTexture(mbgd);
	if (font.loadFromFile("Fonts/8-BIT WONDER.TTF")) //Load font chữ
	{
		//Khởi tạo vị trí màu sắc và nội dung cho các tùy chọn
		selectedItem = 0;
		cout << "\nSuccess";
		menu[0].setFont(font);
		menu[0].setFillColor(Color::Yellow);
		menu[0].setString("Play");
		menu[0].setCharacterSize(70);
		FloatRect size0 = menu[0].getGlobalBounds();
		menu[0].setOrigin(size0.width / 2, size0.height / 2);
		menu[0].setPosition(WScreen / 2, HScreen / (Item + 1) * 1);
		menu[0].setStyle(Text::Underlined | Text::Italic);

		menu[1].setFont(font);
		menu[1].setFillColor(Color::White);
		menu[1].setString("Demo");
		menu[1].setCharacterSize(50);
		FloatRect size1 = menu[1].getGlobalBounds();
		menu[1].setOrigin(size1.width / 2, size1.height / 2);
		menu[1].setPosition(WScreen / 2, HScreen / (Item + 1) * 2);
		
		menu[2].setFont(font);
		menu[2].setFillColor(Color::White);
		menu[2].setString("Guide");
		menu[2].setCharacterSize(50);
		FloatRect size2 = menu[2].getGlobalBounds();
		menu[2].setOrigin(size2.width / 2, size2.height / 2);
		menu[2].setPosition(WScreen / 2, HScreen / (Item + 1) * 3);

		menu[3].setFont(font);
		menu[3].setFillColor(Color::White);
		menu[3].setString("Exit");
		menu[3].setCharacterSize(50);
		FloatRect size3 = menu[3].getGlobalBounds();
		menu[3].setOrigin(size3.width / 2, size3.height / 2);
		menu[3].setPosition(WScreen / 2, HScreen / (Item + 1) * 4);

		
	}
	else{
		cout << "\nFail";
	}
	
}
Menu::~Menu()
{
}

void Menu::Draw(RenderWindow& window)
{
	window.draw(bgd);
	for (int i = 0; i < Item; i++)
	{
		window.draw(menu[i]);
	}
}


void Menu::DrawWinner(int win, int Score)
{
	//Khởi tạo vị trí, màu sắc và kiểu chữ cho thông báo
	srand(time(0));
	RenderWindow Window(VideoMode(WScreen, HScreen), "Bricks Breaker", Style::Close | Style::Titlebar); // Tạo màn hình window 
	Window.setFramerateLimit(60);
	Text txt;
	txt.setFillColor(Color::White);
	txt.setFont(font);
	txt.setCharacterSize(30);
	FloatRect size = txt.getGlobalBounds();
	txt.setOrigin(size.width / 2, size.height / 2);
	txt.setPosition(WScreen / 4, HScreen /4 );
	txt.setStyle(Text::Italic);
	while (Window.isOpen())
	{
		Event e;
		while (Window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				Window.close();
			}
			if (win == 1)
			{
				txt.setString("YOU WON \nSCORE " + to_string(Score));
			}
			if (win == 2)
			{
				txt.setString("YOU LOSE \nSCORE " + to_string(Score));
			}
			
			Window.clear();
			Window.draw(bgd);
			Window.draw(txt);
			Window.display();
			if (e.type == Event::KeyReleased)
			{
				if (e.key.code == Keyboard::Return) Window.close(); //Nhấn enter thoát thông báo
			}
		}
	}
}

void Menu::moveUp()
{
	if (selectedItem >= 1)
	{
		menu[selectedItem].setFillColor(Color::White);
		menu[selectedItem].setStyle(Text::Regular);
		menu[selectedItem].setCharacterSize(50);
		selectedItem--;
		menu[selectedItem].setCharacterSize(70);
		menu[selectedItem].setFillColor(Color::Yellow);
		menu[selectedItem].setStyle(Text::Regular);
	}
}

void Menu::DrawGuide()
{
	srand(time(0));
	RenderWindow Window(VideoMode(WScreen, HScreen), "Bricks Breaker", Style::Close | Style::Titlebar); // Tạo màn hình window 
	Window.setFramerateLimit(60);
	Text txt;
	txt.setFillColor(Color::White);
	txt.setFont(font);
	txt.setCharacterSize(13);
	FloatRect size = txt.getGlobalBounds();
	txt.setOrigin(-10 , size.height / 2);
	txt.setPosition(0, HScreen / 3);
	txt.setString("GUIDE\n\nUse A D to control  Paddle \nUse R to repair the ball \nF to change Hard Brick Break Ball \nE to release ball after change ball \nGrab  the  ball and break all the bricks \nto  win\ ");
	while (Window.isOpen())
	{
		Event e;
		while (Window.pollEvent(e))
		{
			Window.clear();
			Window.draw(bgd);
			Window.draw(txt);
			Window.display();
			if (e.type == Event::KeyReleased)
			{
				if (e.key.code == Keyboard::Return) Window.close(); //Nhấn enter để thoát hướng dẫn
			}
		}
	}
}

void Menu::moveDown()
{
	if (selectedItem < Item - 1)
	{
		menu[selectedItem].setFillColor(Color::White);
		menu[selectedItem].setStyle(Text::Regular);
		menu[selectedItem].setCharacterSize(50);
		selectedItem++;
		menu[selectedItem].setCharacterSize(70);
		menu[selectedItem].setFillColor(Color::Yellow);
		menu[selectedItem].setStyle(Text::Regular);
	}
}

void Menu::run()
{	
	bool isGameOver = false; // Kiểm tra kết thúc game
	do
	{
		srand(time(0));
		RenderWindow Window(VideoMode(WScreen, HScreen), "Bricks Breaker", Style::Close | Style::Titlebar); // Tạo màn hình window 
		Window.setFramerateLimit(60); //Giới hạn khung hình cho game
		while (Window.isOpen())
		{
			Event e;
			while (Window.pollEvent(e))
			{
				switch (e.type)
				{
				case Event::KeyReleased:
					switch (e.key.code)
					{
					case Keyboard::Up:
						moveUp();
						break;
					case Keyboard::Down:
						moveDown();
						break;
					case Keyboard::Return:
						switch (selectedItem)
						{
						case 0:
						{
							Game game;
							int winner = game.run(1);
							Window.close();
							DrawWinner(winner, game.SCORE);
							Window.display();
							saveSCORE(game.SCORE);
							break;
						}
						case 1:
						{
							Game game;
							int winner = game.run(2);
							Window.close();
							DrawWinner(winner, game.SCORE);
							Window.display();
							break;
						}
						case 2:
							Window.close();
							DrawGuide();
							Window.display();
							break;
						case 3:
							Window.close();
							isGameOver = true;
						default:
							break;
						}
					default:
						break;
					}
					break;
				case Event::Closed:
					Window.close();
				default:
					break;
				}
				Window.clear();
				Draw(Window);
				Window.display();
			}
		}
		
	} while (isGameOver == false);
}

void Menu::saveSCORE(int Score)
{
	fstream file("SCORES.txt", ios::app);
	if (!file)
		cout << "Khong the luu user lai xuong file." << endl;
	else
	{
		file << "SCORE:\t";
		file << Score << endl;
		file.close();
	}
}


