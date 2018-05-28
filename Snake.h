#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

class Snake
{
public:
	Snake(int width, int height);
	Snake();
	~Snake();

	void Setup(void);
	void Draw(void);
	void Input(void);
	void Logic(void);
	void start(void);
	bool is_crash(void);

private:
	bool gameOver;
	int width;
	int height;
	int x, y, fruitX, fruitY, score;
	int tailX[100], tailY[100];
	int nTail = 0;
	enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
	eDirection dir;
};

#endif // !SNAKE_H
