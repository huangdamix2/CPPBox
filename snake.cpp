#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

const int ROW = 22;
const int COL = 42;

short map[ROW][COL];

const int UP = 72;
const int DOWN = 80;
const int LEFT = 75;
const int RIGHT = 77;

const int EMPTY = 0;
const int FOOD = 1;
const int HEAD = 2;
const int BODY = 3;
const int WALL = 4;

struct head
{
    short len;
    short x, y;
} sHead;

struct body
{
   short x, y;
} sBody[ROW * COL];

int Rating = 0;

void InitMap();
void InitSnake();
void gotoxy(short x, short y);
void RandFood();
void Judge(short x, short y);
void DrawSnake(short flag);
void MoveSnake(short x, short y);
void Run(short x, short y);
void Game();
int main();

void InitMap()
{
	system("cls");
    for (int i = 0; i < ROW; i ++ )
    {
        for (int j = 0; j < COL; j ++ )
        {
            if (i == 0 || i == ROW - 1)
            {
                map[i][j] = WALL;
                printf("#");
            }
            else if (j == 0 || j == COL - 1)
            {
                map[i][j] = WALL;
                printf("#");
            }
            else printf(" ");
        }
        printf("\n");
    }
}

void InitSnake()
{
	short x = COL / 2, y = ROW / 2;
    sHead.len = 2;
    sHead.x = x;
    sHead.y = y;
    sBody[0].x = x - 1;
    sBody[0].y = y;
    sBody[1].x = x - 2;
    sBody[1].y = y;

    map[sHead.y][sHead.x] = HEAD;
    map[sBody[0].y][sBody[0].x] = BODY;
    map[sBody[1].y][sBody[1].x] = BODY;
}


void gotoxy(short x, short y)
{
    HANDLE hOut;
    COORD pos = {x, y};
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut,pos);
}

void RandFood()
{
	short x, y;
	while (map[y][x] != EMPTY)
	{
		y = rand() % ROW; 
		x = rand() % COL; 
	}

	map[y][x] = FOOD;
	gotoxy(x, y); printf("*");

}

void PrintPos(short x, short y)
{
	gotoxy(0, ROW);
	printf("Rating:%d", Rating);
	Sleep(1);
	gotoxy(x, y);
}

void Judge(short x, short y)
{
	short res = map[sHead.y + y][sHead.x + x];
	if (res == FOOD)
	{
		sHead.len ++ ;
		RandFood();
		Rating += 10;
		PrintPos(sHead.x, sHead.y);
	}
	else if (res == WALL || res == BODY)
	{
		gotoxy(COL / 2, ROW / 2);
		printf("GG\n");
		exit(0);
	}
}



void DrawSnake(short flag)
{
	if (flag) // print
	{
		gotoxy(sHead.x, sHead.y);
		printf("@");
		// PrintPos(sHead.x, sHead.y);

		for (short i = 0; i < sHead.len; i ++ )
		{
			gotoxy(sBody[i].x, sBody[i].y);
			printf("&");
		}
	}
	else // cover
	{
		short len = sHead.len;
		gotoxy(sBody[len - 1].x, sBody[len - 1].y);
		printf(" ");
		// PrintPos(sHead.x, sHead.y);
	}
}

void MoveSnake(short x, short y)
{
	DrawSnake(0);
	map[sBody[sHead.len - 1].y][sBody[sHead.len - 1].x] = EMPTY;
	map[sHead.y][sHead.x] = BODY;
	for (short i = sHead.len - 1; i > 0; i -- )
	{
		sBody[i].y = sBody[i - 1].y;
		sBody[i].x = sBody[i - 1].x;
	}
	sBody[0].x = sHead.x; sBody[0].y = sHead.y;
	sHead.y += y; sHead.x += x;
	DrawSnake(1);
}

void Run(short x, short y)
{
	int t = 0;
	while (1)
	{
		if (t == 0) 
			t = 6000;

		while ( -- t) 
		{
			if (kbhit() != 0) 
				break;
		}

		// printf("%d\n", t);

		if (t == 0)
		{
			// gotoxy(sHead.x, sHead.y);
			// printf("MOVE");
			Judge(x, y);
			MoveSnake(x, y);
		}
		else break;
	}

	// MoveSnake(x, y);
}

void Game()
{
	int dir = RIGHT;
	int tmp;
	goto first;

	while (1)
	{

		dir = getch();
		// printf("%d", dir);
		switch(dir)
		{
			case UP:
			case DOWN: 
			if (tmp != LEFT&&tmp != RIGHT) 
			{
				dir = tmp; 
			}
			break;
			case LEFT:
			case RIGHT: 
				if (tmp != UP&&tmp != DOWN) 
				{
					dir = tmp; 
				}
			case 'R':
				break;
			default:
				dir = tmp; 
				break;
		}

		first:
			switch (dir)
			{

				case UP: Run(0, -1); tmp = UP; break;
				case DOWN: Run(0, 1); tmp = DOWN; break;
				case LEFT: Run(-1, 0); tmp = LEFT; break;
				case RIGHT: Run(1, 0); tmp = RIGHT; break;
				case 'R': system("cls"); main();
			}


	}

}


int main()
{
    InitMap();
    InitSnake();
    DrawSnake(1);
    RandFood();
    // MoveSnake(0, -1);
    Game();
    return 0;
}