// My Console Snake

#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <ctime>

using namespace std;

bool gameOver = false;
bool autoPlay = true;
bool WIN;

const int BUFFER = 255;

string Name;
ofstream FScore;


int Level = 2;

int width = 20;
int height = 20;

int x, y, xFruit, yFruit;

enum Direction { STOP, LEFT, RIGHT, UP, DOWN };
Direction dir;

int SPEED = 100;
int score;

int TailX[100], TailY[100];
int nTail;

void Setup()
{
	HWND console = GetConsoleWindow();
	RECT ConsoleRECT;
	GetWindowRect(console, &ConsoleRECT);
	MoveWindow(console, ConsoleRECT.left, ConsoleRECT.top, 600, 400, TRUE);

	srand(time(nullptr));
	x = rand() % height;
	y = rand() % width;

	xFruit = rand() % height;
	yFruit = rand() % width;

	nTail = 2;
	dir = LEFT;


	WIN = false;
	

}

void Draw()
{
	system("cls");

	cout << "----------------------" << endl;
	cout << "||----SNAKE GAME----||" << endl;
	cout << "----------------------" << endl;

	for (size_t i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << "\n";
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{

			if (j == 0)
			{
				cout << "#";
			}
			if (y == i && x == j)
			{
				cout << "H";
			}
			else if (yFruit == i && xFruit == j)
			{
				cout << "F";
			}
			else
			{
				bool print = false;
				for (size_t t = 0; t < nTail; t++)
				{
					if (TailX[t] == j && TailY[t] == i)
					{
						cout << "t";
						print = true;
					}
				}
				if (!print)
				{
					cout << " ";
				}
			}


			if (j == width - 1)
			{
				if (i==0)
				{
					cout << "# Hello " << Name;
				}
				else if (i == 1)
				{
					cout << "# RULES:";
				}
				else if (i == 2)
				{
					cout << "# A - LEFT";
				}
				else if (i==2)
				{
					cout << "# D - RIGHT";
				}
				else if (i == 3)
				{
					cout << "# S - DOWN";
				}
				else if (i == 4)
				{
					cout << "# W - UP";
				}
				else if (i == 5)
				{
					cout << "# X - STOP";
				}
				else if (i == 6)
				{
					cout << "# 1 - AUTOPLAY";
				}
				else if (i == 7)
				{
					cout << "# AUTOPLAY BY DEFAULT";
				}
				else if (i == 9)
				{
					cout << "# TO TAKE OVER THE CONTROL JUST PRESS ANY BUTTON";
				}
				else
				{
					cout << "#";
				}
				
			}


		}
		cout << '\n';
	}
	for (size_t i = 0; i < width + 2; i++)
	{
		cout << "#";
	}

	cout << endl << "SCORE = " << score << endl;
	cout << "LEVEL = " << Level << endl;

}


void Input()
{
	if (_kbhit())
	{
		autoPlay = false;
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'w':
			dir = UP;
			break;
		case 'x':
			dir = STOP;
			break;
		case '1':
			autoPlay = true;
			break;
		}
	}
}

void Game()
{
	int prevX = TailX[0];
	int prevY = TailY[0];
	int prev2X, prev2Y;

	for (size_t i = 0; i < nTail; i++)
	{
		prev2X = TailX[i];
		prev2Y = TailY[i];
		TailX[i] = prevX;
		TailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

	}

	TailX[0] = x;
	TailY[0] = y;

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case STOP:
		gameOver = true;
		break;
	}

	if (x >= width)x = 0;else if (x < 0)x = width - 1;
	if (y >= height)y = 0;else if (y < 0)y = height - 1;

	if (x == xFruit && y == yFruit)
	{
		xFruit = rand() % height;
		yFruit = rand() % width;

		nTail++;

		score += 10;
	}

	for (size_t i = 0; i < nTail; i++)
	{
		if (x == TailX[i] && y == TailY[i])
		{
			gameOver = true;
		}
	}

	if (nTail==6)
	{
		system("cls");
		this_thread::sleep_for(chrono::milliseconds(1000));
		cout << "LEVEL UP" << endl;
		Setup();
		Level++;
		if (SPEED > 100)
		{
			SPEED -= 100;
		}
		else
		{
			SPEED -= 10;
		}
		
	}
	if (Level == 3)
	{
		WIN = true;
	}
}

void AutoPlay()
{
	if (xFruit < x && yFruit == y)
	{
		dir = LEFT;
	}
	else if (xFruit == x && yFruit > y)
	{
		dir = DOWN;
	}
	else if (xFruit > x && yFruit == y)
	{
		dir = RIGHT;
	}
	else if (xFruit == x && yFruit < y)
	{
		dir = UP;
	}
	else if (xFruit > x && yFruit > y)
	{
		dir = DOWN;
	}
	else if (xFruit < x && yFruit < y)
	{
		dir = UP;
	}
	else if (xFruit > x && yFruit < y)
	{
		dir = UP;
	}
	else if (xFruit < x && yFruit > y)
	{
		dir = DOWN;
	}

}

void GameOver()
{
	cout << "   gggg            a         mm           mm   eeeeeeee   \n";
	cout << "  g    g          a a        m m         m m   e          \n";
	cout << " g               a   a       m  m       m  m   e          \n";
	cout << "g    ggg        a     a      m   m     m   m   eeeee      \n";
	cout << "g        g     aaaaaaaaa     m    m   m    m   e          \n";
	cout << " g     g      a         a    m     m m     m   e          \n";
	cout << "  ggggg      a           a   m      m      m   eeeeeeee   \n\n";
	

	cout << "   oo    v       v eeeeee  rrrrr   !  \n";
	cout << " o    o   v     v  e       r    r  ! \n";
	cout << "o      o   v   v   eeee    rrrrr   ! \n";
	cout << " o    o     v v    e       r   r   ! \n";
	cout << "   oo        v     eeeeee  r    r  o\n\n";

	cout << "Your Score is " << score << endl;
	cout << "Your LEVEL is " << Level << endl;
}

void Play()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Game();
		if (autoPlay)
			AutoPlay();

		this_thread::sleep_for(chrono::milliseconds(SPEED));

		if (WIN)
		{
			gameOver = true;
		}
	}
	system("cls");
	if(!WIN)
		GameOver();
	else
	{
		cout << "CONGRATULATIONS YOU ARE A WINNER WITH SCORE " << score << "!!!";
		cout << endl;
	}
}

string Time()
{
	auto now = chrono::system_clock::now();
	time_t t = chrono::system_clock::to_time_t(now);

	char str[BUFFER];
	ctime_s(str, sizeof(str), &t);
	return str;
}

int main()
{
	cout << "Enter your name: ";
	cin >> Name;

	Play();
	FScore.open("score_log.txt", ios::app);
	string Winner = "";
	if (WIN)
	{
		 Winner = "; WINNER!!!";
	}
	FScore << Name << Winner << "; Score = " << score << "; Date = " << Time() << '\n';
	FScore.close();
	return 0;
}