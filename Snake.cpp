#include "Snake.h"

Snake::Snake(int width, int height)
{
	this->width = width;
	this->height = height;
}

Snake::Snake()
{
	this->width = 50;
	this->height = 20;
}

Snake::~Snake()
{
}

void Snake::Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	do
	{
		fruitX = rand() % width;
		fruitY = rand() % height;
	} while (this->is_crash());
	score = 0;
}

void Snake::Draw() {
	Sleep(75);
	system("cls");
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width+1; j++) {
			if (j == 0 || j == width)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
						if (tailX[k] == j && tailY[k] == i) {
							print = true;
							cout << "o";
						}
				}
				if (!print)
				cout << " ";
			}
		}
		cout << endl;
	} 


	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}

void Snake::Input() 
{
	if (_kbhit()) 
	{
		switch (_getch())
		{
		case 'a':
			if (dir != RIGHT || nTail == 0)dir = LEFT; 
			break;
		case 'd':
			if (dir != LEFT || nTail == 0) dir = RIGHT; 
			break;
		case 'w':
			if (dir != DOWN || nTail == 0) dir = UP; 
			break;
		case 's':
			if (dir != UP || nTail == 0) dir = DOWN; 
			break;
		case 'q':
		case -23:
			dir = STOP; 
			break;
		case 'x':
		case -9:
			gameOver = true;
			break;
		}
	}
}

void Snake::Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
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
	}
		if (x >= width)
			x = 0;
		else if (x < 0)
			x = width - 1;
		if (y >= height)
			y = 0;
		else if (y < 0)
			y = height - 1;


		for (int i = 0; i < nTail; i++) {
			if (tailX[i] == x && tailY[i] == y)
				gameOver = true;
		}

		if (x == fruitX && y == fruitY) 
		{
			score += 10;
			do
			{
				fruitX = rand() % width;
				fruitY = rand() % height;
			} while (this->is_crash());
			nTail++;
			if (nTail == (this->width*this->height - 2))
			{
				gameOver = true;
				cout << "You win!!!\n";
				system("pause");
			}
				
		}
}

bool Snake::is_crash(void)
{
	if (fruitX == x && fruitY == y)
		return true;
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == fruitX && tailY[i] == fruitY)
			return true;
	return false;
}

void Snake::start(void)
{
	Setup();
	Draw();
	while (!gameOver) {
		if (dir != STOP)
			Draw();
		Input();
		if (dir != STOP)
			Logic();
	}
}
