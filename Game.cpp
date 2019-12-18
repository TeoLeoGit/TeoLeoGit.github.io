#include "Game.h"

Game::Game()
{
	if (BALL.mball.loadFromFile("Ball.png")) //Load hình ảnh bóng
	{
		cout << "\nSuccess";
	}
	if (PADDLE.MPaddle.loadFromFile("BaseBallBat.png")) // Load hình ảnh gậy đánh bóng
	{
		cout << "\nSuccess";
	}
	if (mBGD.loadFromFile("PlayingBackground.png")) // Load hình ảnh BackGround
	{
		cout << "\nSuccess";
	}
	if (MBrick1.loadFromFile("Normal Brick.png")) // Load hình ảnh brick
	{
		cout << "\nSuccess";
	}
	if (MBrick2.loadFromFile("Double Score Brick.png")) // Load hình ảnh brick
	{
		cout << "\nSuccess";
	}
	if (MBrick3.loadFromFile("Life Break.png")) // Load hình ảnh brick
	{
		cout << "\nSuccess";
	}
	BALL.BALLSpr.setTexture(BALL.mball); //Gán hình ảnh cho Spite để xử lý
	PADDLE.PADSpr.setTexture(PADDLE.MPaddle);
	BGD.setTexture(mBGD);
	int brickX = 17;
	int brickY = 5;
	for (int j = 0; j < 6; j++)
	{
		int prevX = brickX;
		for (int i = 0; i < 6; i++)
		{
			BRICK[i][j].BRICKSpr.setPosition(brickX, brickY);
			brickX = brickX + 85;
			BRICK[i][j].TYPE = rand() % 6 + 1;
			if (BRICK[i][j].TYPE < 5)
				BRICK[i][j].BRICKSpr.setTexture(MBrick1);
			else
			{
				if (BRICK[i][j].TYPE == 5)
					BRICK[i][j].BRICKSpr.setTexture(MBrick2);
				else
					BRICK[i][j].BRICKSpr.setTexture(MBrick3);
			}
			BRICK[i][j].BREAKED = false;
		}
		brickX = prevX;
		brickY = brickY + 20;
	}
	PADDLE.PADSpr.setPosition(WScreen / 2 , 620);//Khởi tạo vị trí khi game bắt đầu
	BALL.POS = Vector2f(PADDLE.PADSpr.getPosition().x,PADDLE.PADSpr.getPosition().y- 30); //Gắn bóng với vị trí của thanh đõ khi game bắt đầu
	BALL.SPEED = Vector2f (3, -2); // Khởi tạo tốc độ cho bóng
	winner = 0;
	SCORE = 0;
	if (SCOREFont.loadFromFile("Fonts/8-BIT WONDER.TTF"))
		SCOREText.setFont(SCOREFont);
	SCOREText.setFillColor(Color::Yellow);
	SCOREText.setString("SCORE 0");
	SCOREText.setCharacterSize(15);
	FloatRect sizeScore = SCOREText.getGlobalBounds();
	SCOREText.setOrigin(sizeScore.width / 2, sizeScore.height / 2);
	SCOREText.setPosition(WScreen - sizeScore.width - 5 , HScreen - 20);
	BREAKEDBr = 0;
	BALL.BALLMode = 1;
	BALL.DURABIL = 5;
	BRelease = true;
}

Game::~Game()
{

}

void Game::controlPad()
{
	if (Keyboard::isKeyPressed(Keyboard::A)) //điều khiển qua trái
	{
		PADDLE.PADSpr.move(-10, 0);
		if (!BRelease)
		{
			BALL.POS = Vector2f(PADDLE.PADSpr.getPosition().x + 35, PADDLE.PADSpr.getPosition().y - 30);
			BALL.SPEED.y = -abs(BALL.SPEED.y);
			BALL.BALLSpr.setPosition(BALL.POS);
			BALLPath.clear();
			createPath(BALLPath);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) //điều khiển qua phải
	{
		PADDLE.PADSpr.move(10, 0);
		if (!BRelease)
		{
			BALL.POS = Vector2f(PADDLE.PADSpr.getPosition().x + 35, PADDLE.PADSpr.getPosition().y - 30);
			BALL.SPEED.y = -abs(BALL.SPEED.y);
			BALL.BALLSpr.setPosition(BALL.POS);
			BALLPath.clear();
			createPath(BALLPath);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::F) && BRelease && SCORE > 2 ) //đổi bóng xịn khi bóng đang chạy và tích đước 3 điểm thưởng trở lên
	{
		SCORE = SCORE - 3;
		BRelease = false; //bóng đang bị giữ ở thanh đẩy
		BALL.BALLSpr.setColor(Color::Blue); //đổi màu sang xanh
		BALL.DURABIL = 5;//độ bền của bóng đặt lại = 5
		BALL.BALLMode = 2; //đổi sang dạng bóng phá vật cản
		BALL.POS = Vector2f(PADDLE.PADSpr.getPosition().x + 35, PADDLE.PADSpr.getPosition().y - 30);//đặt lại bóng tại thanh đẩy
		BALL.SPEED.y = - abs(BALL.SPEED.y); //đặt lại tốc độ bóng hướng đến những viên gạch
		BALL.BALLSpr.setPosition(BALL.POS); //đặt vị trí Sprite bóng để vẽ ra window
		BALLPath.clear(); //tạo mới đường đi
		createPath(BALLPath); //vẽ đường đi
		SCOREText.setString("Score " + to_string(SCORE)); //đặt lại điểm
	}
	if (Keyboard::isKeyPressed(Keyboard::R) && BALL.DURABIL < 4) //sửa bóng khi độ bền < 4
	{
		if (SCORE > 1) //phải tích đủ 2 điểm trở lên
		{
			BALL.DURABIL = 5;
			SCORE = SCORE - 2; //trừ điểm khi sửa bóng
			BALL.BALLSpr.setColor(Color::White); //đổi lại màu bóng thường
			SCOREText.setString("Score " + to_string(SCORE)); //đặt lại điểm
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::E) && !BRelease) //thả bóng chạy tự do sau khi đổi bóng sang dạng phá vật cản
	{
		BALLPath.clear(); //xóa đường đi
		BRelease = true; //thả bóng
	}
	if (Keyboard::isKeyPressed(Keyboard::Q) && !BRelease) //đổi đường đi của bóng (theo trục x)
	{
		BALL.SPEED.x = -BALL.SPEED.x;
		BALLPath.clear();
		createPath(BALLPath);
	}
}

void Game::ballCollision()
{
	if (BRelease) //nếu bóng đang chạy tự do thì mới chạy function
		BALL.moveBALL();
	else
		return;
	if (BALL.POS.y < 150)
	{
		if (BALL.BALLMode == 1 && BALL.DURABIL == 5)
			BALL.BALLSpr.setColor(Color::White);
		SCOREText.setString("Score " + to_string(SCORE)); //update điểm
		if (BALL.POS.y - 5 < 0 ) //Nếu Bóng vượt quá chiều dài của màn hình thì sẽ dội ngược lại
		{
			BALL.SPEED.y = -BALL.SPEED.y;
		}
		if (BALL.POS.x < 0 || BALL.POS.x  +30 > WScreen) //Nếu Bóng vượt quá chiều dài của màn hình thì sẽ dội ngược lại
		{
			BALL.SPEED.x = -BALL.SPEED.x;
		}
		for (int j = 0; j < 6; j++)
			for (int i = 0; i < 6;i++)
			{
				if (FloatRect(BALL.POS.x, BALL.POS.y, 30 + 5, 30 + 5 ).intersects(BRICK[i][j].BRICKSpr.getGlobalBounds()) && !BRICK[i][j].BREAKED) //kiểm tra bóng có va vào gạch kg
				{
					if (BALL.SPEED.y < 0) // kiểm tra xem nếu bóng đã va chạm vào gạch trc đó 
						BALL.SPEED.y = -BALL.SPEED.y; // va vào viên gạch đầu tiên thì đổi tốc độ y
					else
						BALL.SPEED.x = -BALL.SPEED.x; //va vào viên gạch thứ 2 trở đi thì đổi tốc độ x
					if (BRICK[i][j].TYPE < 5) //kiểm tra loại gạch va chạm
					{
						BRICK[i][j].BREAKED = true; // gạch ở vị trí va chạm đã bị phá
						BREAKEDBr++; // số gạch bị phá tăng lên 1
						SCORE++;//gạch thường thưởng 1 điểm
						BALL.BALLMode = 1; //gạch đã va chạm sẽ set về dạng gạch thường
						return;
					}
					else
					{
						if (BRICK[i][j].TYPE == 5)
						{
							BRICK[i][j].BREAKED = true; // gạch ở vị trí va chạm đã bị phá
							BREAKEDBr++; // số gạch bị phá tăng lên 1
							SCORE = SCORE + 2; // gạch vật phẩm x2 điểm
							BALL.BALLMode = 1;
							return;
						}
						else //gạch vật cản nên không phá được
						{
							if (BALL.BALLMode == 1) //kiểm tra dạng bóng (nếu dạng thường (1) thì kg phá đc gạch vật cản)
							{
								BALL.DURABIL--; //độ bền của bóng bị giảm
								switch (BALL.DURABIL)
								{
								case(4):
									BALL.BALLSpr.setColor(Color::Green);//độ bền = 4 thì bóng có màu xanh lá cây
									break;
								case(3):
									BALL.BALLSpr.setColor(Color::Yellow);//độ bền =3 thì bóng có màu xanh lá cây
									break;
								default:
									BALL.BALLSpr.setColor(Color::Red);//độ bền nguy hiếm (>3) bóng có màu đỏ
									break;
								}
								return;
							}
							else //bóng dạng phá gạch ngăn cản
							{
								BRICK[i][j].BREAKED = true; // gạch ở vị trí va chạm đã bị phá
								BREAKEDBr++; // số gạch bị phá tăng lên 1
								SCORE = SCORE + 1;
								BALL.BALLMode = 1; //bóng phá vật cản trở thành gạch thường sau khi sử dụng
								BALL.BALLSpr.setColor(Color::White); //đổi lại màu bóng thường
								return;
							}
						}
					}
					return;
				}
			}
	}
	else
	{
		if (BALL.POS.x < 0  || BALL.POS.x + 30 > WScreen) //Nếu Bóng vượt quá chiều dài của màn hình thì sẽ dội ngược lại
		{
			BALL.SPEED.x = -BALL.SPEED.x;
		}

		if (FloatRect(BALL.POS.x , BALL.POS.y , 30 + BALL.SPEED.x, 30 + BALL.SPEED.y).intersects(PADDLE.PADSpr.getGlobalBounds())) //Nếu bóng va chạm thanh đỡ 
		{
			if (BALL.POS.y + 30 <= PADDLE.PADSpr.getPosition().y) //nếu vị trí y không vượt quá thanh đỡ
			{
				if (BALL.SPEED.y < 5) //giới hạn tốc độ tối đa
				{
					BALL.SPEED.y = -BALL.SPEED.y * 1.1; // tăng tốc độ thêm 10%
					BALL.SPEED.x = BALL.SPEED.x * 1.1;
				}
				else //nếu bóng đã vượt quá giới hạn tốc đa thì bóng chỉ dội lại
				{
					BALL.SPEED.y = -BALL.SPEED.y; 
				}
			}
			else //nếu bóng đã vượt quá vị trí y của thanh đỡ
			{
				if (BALL.POS.x < PADDLE.PADSpr.getPosition().x) //nếu bóng đến từ bên trái thanh đỡ
					BALL.SPEED.x = -10; //bóng sẽ dội theo hướng ngược lại
				else                    //bóng đến từ bên phải thanh đỡ
					BALL.SPEED.x = 10;
			}
		}
	}
}
void Game::Drawto(RenderWindow& window)
{
	window.draw(BGD);
	window.draw(BALL.BALLSpr); //Hiện thị các obj của game
	window.draw(SCOREText);
	window.draw(PADDLE.PADSpr);
	for (int j = 0; j < 6;j++)
		for (int i = 0;i < 6; i++)
			if (!BRICK[i][j].BREAKED)
				window.draw(BRICK[i][j].BRICKSpr);
	if (!BRelease) //nếu bóng vẫn chưa được thả thì mới vẽ đường đi
		for (int i = 0; i < BALLPath.size();i++)
			window.draw(BALLPath[i]);
}

void Game::paddleColl()
{
	Vector2f posPad = PADDLE.PADSpr.getPosition();// lấy vị trí của thanh đỡ
	// Xử lý cho thanh đỡ va vào biên
	if (posPad.x < 0) posPad.x = 0;
	if (posPad.x + 90 > WScreen) posPad.x = WScreen - 90;
	PADDLE.PADSpr.setPosition(posPad); //Đặt lại vị trí cho thanh đỡ
}

void Game::autoPad() //thanh đẩy tự động
{
	if (BALL.POS.x < PADDLE.PADSpr.getPosition().x) //chạy theo bóng
		PADDLE.PADSpr.move(-10, 0);
	if (BALL.POS.x > PADDLE.PADSpr.getPosition().x)
		PADDLE.PADSpr.move(10, 0);
	if (SCORE > 3 && BALL.DURABIL == 2)
		BALL.changeMODE(SCORE);
}

void Game::createPath(vector<CircleShape>& Path)
{
	float prevSpeed_x = BALL.SPEED.x;
	float prevPoint_x = BALL.POS.x;
	float prevPoint_y = BALL.POS.y;
	while (150 < prevPoint_y)
	{
		prevPoint_x = prevPoint_x + BALL.SPEED.x * 10;
		prevPoint_y = prevPoint_y + BALL.SPEED.y * 10;
		if (prevPoint_x > WScreen) //xử lý khi đường đi đụng biên
		{
			
			prevPoint_y = prevPoint_y + BALL.SPEED.y / BALL.SPEED.x * (WScreen - prevPoint_x - 25);//xử lý điểm đánh dấu theo hình học 
			prevPoint_x = WScreen - 15;
			BALL.SPEED.x = -BALL.SPEED.x;
		}
		else
		{
			if (prevPoint_x < 0)
			{
				prevPoint_y = prevPoint_y + BALL.SPEED.y / BALL.SPEED.x * (0 - prevPoint_x + 25);//xử lý cho y về biên
				prevPoint_x = 15;//cho điểm về biên
				BALL.SPEED.x = -BALL.SPEED.x;
			}
			else
			{
				CircleShape path(5);
				path.setFillColor(Color(255, 255, 255, 128));//cho màu của điểm là màu trắng trong suốt 1 nửa
				path.setPosition(prevPoint_x, prevPoint_y + 10); //Set vị trí đặt rào chắn
				Path.push_back(path);
			}
		}
	}
	while (150 >= prevPoint_y) //kiểm tra xem đương đi có vượt giới hạn khung hình
	{
		if (prevPoint_y < 0)
		{
			BALL.SPEED.x = prevSpeed_x;
			return;
		}
		prevPoint_x = prevPoint_x + BALL.SPEED.x * 10;
		prevPoint_y = prevPoint_y + BALL.SPEED.y * 10;
		if (prevPoint_x > WScreen)
		{
			prevPoint_y = prevPoint_y + BALL.SPEED.y / BALL.SPEED.x * (WScreen - prevPoint_x - 25);//v
			prevPoint_x = WScreen;
			BALL.SPEED.x = -BALL.SPEED.x;
		}
		else 
		{
			if (prevPoint_x < 0)
			{
				prevPoint_y = prevPoint_y + BALL.SPEED.y / BALL.SPEED.x * (0 - prevPoint_x + 25);//v
				prevPoint_x = 0;
				BALL.SPEED.x = -BALL.SPEED.x;
			}
			else
			{
				CircleShape path(5);
				path.setFillColor(Color(255, 255, 255, 128));//cho màu của điểm là màu trắng trong suốt 1 nửa
				path.setPosition(prevPoint_x, prevPoint_y + 10); //Set vị trí điểm
				for (int i = 0; i < 6;i++)
					for (int j = 0; j < 6;j++)
					{
						if (FloatRect(path.getPosition().x, path.getPosition().y, 15, 15).intersects(BRICK[i][j].BRICKSpr.getGlobalBounds()) && !BRICK[i][j].BREAKED)
						{
							BALL.SPEED.x = prevSpeed_x;
							return;
						}
					}
				Path.push_back(path);
			}
		}
	}
	BALL.SPEED.x = prevSpeed_x;
}

int Game::run(int Mode)
{
	srand(time(0));
	RenderWindow Window(VideoMode(WScreen, HScreen), "Bricks Breaker", Style::Close | Style::Titlebar); // Tạo màn hình window 
	Window.setFramerateLimit(60);
	
	while (Window.isOpen())
	{
		Event evnt;
		
		while (Window.pollEvent(evnt))
		{
			if (evnt.type == Event::Closed)
			{
				Window.close();
			}
			
		}
		if (Mode == 1) //người chơi
			controlPad();
		else
			autoPad(); //máy chơi
		ballCollision(); 
		paddleColl();
		Window.clear();
		
		Drawto(Window);
		Window.display();
		if (BREAKEDBr == 36) //kết thúc game khi phá hết gạch
		{
			Window.close();
			return 1;
		}
		if (BALL.POS.y > HScreen || BALL.DURABIL == 0)//kết thúc game khi kg hứng được bóng hoặc độ bền của bóng = 0
		{
			Window.close();
			return 2;
		}
	}
	return 1;
}
