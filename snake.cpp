#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;
bool gameover;
const int wid = 22;
const int hei = 22;
int x, y, fX, fY, points;
int tailX[100], tailY[100];
int nTail;
enum eDirect { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirect dir;

void setup()
{
	gameover = false;
	dir = STOP;
	x = wid / 2;
	y = hei / 2;
	fX = rand() % wid;
	fY = rand() % hei;
	points = 0;
}
void draw()
{
	int i;
	system("cls");
	for ( i = 0; i < wid + 2; i++)
		cout << ".";
	cout << endl;

	for (int i = 0; i < hei; i++)
	{
		for (int j = 0; j < wid; j++)
		{
			if (j == 0)
				cout << ".";
			if (i == y && j == x)
				cout << "O";
			else if (i == fY && j == fX)
				cout << "X";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == wid - 1)
				cout << ".";
		}
		cout << endl;
	}

	for (int i = 0; i < wid + 2; i++)
		cout << ".";
	cout << endl;
	cout << "points:" << points << endl;
}
void keys()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameover = true;
			break;
		}
	}
}
void gamelogic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
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
	default:
		break;
	}
	
	if (x >= wid) x = 0; else if (x < 0) x = wid - 1;
	if (y >= hei) y = 0; else if (y < 0) y = hei - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameover = true;

	if (x == fX && y == fY)
	{
		points += 10;
		fX = rand() % wid;
		fY = rand() % hei;
		nTail++;
	}
}
int main()
{
	setup();
	while (!gameover)
	{
		draw();
		keys();
		gamelogic();
		Sleep(10);
	}
	return 0;
}