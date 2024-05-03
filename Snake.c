#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>


#define WIDTH 20
#define HEIGHT 20
int gameOver;




typedef struct tail_t{
	int x;
	int y;
	} tail_t;
	
typedef struct snake_t{
	int x;
	int y;
	struct tail_t * tail;
	size_t tsize;
	}snake_t;
	
typedef struct frut{
	int x;
	int y;
}frut;
	
typedef enum {
	PAUSE = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STOP
	} direction;

struct snake_t Setup(int x, int y, size_t tsize) // Базовые установки
{
	snake_t snake;
	snake.x = x;
	snake.y = y;
	snake.tsize = tsize;
	snake.tail = (tail_t *) malloc (sizeof(tail_t) * 100);
	for(int i =0; i < snake.tsize; i++)
	{
		snake.tail[i].x = x;
		snake.tail[i].y = y + i + 1;
	}
	return snake;
}

struct frut Frut()
{
	frut frut;
	frut.x = rand() % WIDTH;
	frut.y = rand() % HEIGHT;
	return frut;
}

void startMenu(int *sel)
{
	int menu = 1;
	while (menu)
	{
		printf("  #####                                 #     #      #####  \n");
		printf(" #     # #    #   ##   #    # ######    #     #     #     # \n");
		printf(" #       ##   #  #  #  #   #  #         #     #           # \n");
		printf("  #####  # #  # #    # ####   #####     #     #      #####  \n");
		printf("       # #  # # ###### #  #   #          #   #  ###       # \n");
		printf(" #     # #   ## #    # #   #  #           # #   ### #     # \n");
		printf("  #####  #    # #    # #    # ######       #    ###  #####  \n");
		printf("************************************************************\n");
		printf("*			Select menu:			   *\n");
		printf("*			1.Player game.			   *\n");
		printf("*			2.Auto game.			   *\n");
		printf("************************************************************\n");
		printf("To PAUSE the game, press P, to EXIT the game, press C.\n");
		switch(getch())
		{
			case '1':
			menu = 0;
			*sel = 1;
			break;
			case '2':
			menu = 0;
			*sel = 2;
			break;
			default:
			system("cls");
			break;
		}
		
	}
}

void Input(direction *dir, direction *dir2,direction *tmp1, direction *tmp2) {
    if(kbhit()) {
        switch(getch()) {
            case 'w':
            case 'W':
                *dir = UP;
                break;
            case 's':
            case 'S':
                *dir = DOWN;
                break;
            case 'a':
            case 'A':
                *dir = LEFT;
                break;
            case 'd':
            case 'D':
                *dir = RIGHT;
                break;
            /*case 'i':
            case 'I':
                *dir2 = UP;
                break;
            case 'k':
            case 'K':
                *dir2 = DOWN;
                break;
            case 'j':
            case 'J':
                *dir2 = LEFT;
                break;
            case 'l':
            case 'L':
                *dir2 = RIGHT;
                break;*/
            case 'p':
            case 'P':
                if(*dir != PAUSE && *dir2 != PAUSE)
            {
				*tmp1 = *dir;
				*tmp2 = *dir2;
				*dir = PAUSE;
                *dir2 = PAUSE;
			}
			else
			{
				*dir = *tmp1;
                *dir2 = *tmp2;
			}
                break;
            case 'c':
            case 'C':
                *dir = STOP;
                *dir2 = STOP;
                break;
        }
    }
}

void InputAuto(direction *dir, direction *dir2, direction *tmp1, direction *tmp2) {
	
    if(kbhit()) {
        switch(getch()) {
            case 'p':
            case 'P':
            if(*dir != PAUSE && *dir2 != PAUSE)
            {
				*tmp1 = *dir;
				*tmp2 = *dir2;
				*dir = PAUSE;
                *dir2 = PAUSE;
			}
			else
			{
				*dir = *tmp1;
                *dir2 = *tmp2;
			}
                break;
            case 'c':
            case 'C':
                *dir = STOP;
                *dir2 = STOP;
                break;
        }
    }
}


void Logic(snake_t *snake,frut *frut, direction dir) {
		int prevX = snake->tail[0].x;
		int prevY = snake->tail[0].y;
		int prev2X, prev2Y;
		snake->tail[0].x = snake->x;
		snake->tail[0].y = snake->y;
		
		
		for (int i = 1; i < snake->tsize; i++) {
			if(dir != PAUSE)
			{
			prev2X = snake->tail[i].x;
			prev2Y = snake->tail[i].y;
			snake->tail[i].x = prevX;
			snake->tail[i].y = prevY;
			prevX = prev2X;
			prevY = prev2Y;
			}
		}
		

		switch(dir)
		{
			case LEFT:
				snake->y--;
				break;
			case RIGHT:
				snake->y++;
				break;
			case UP:
				snake->x--;
				break;
			case DOWN:
				snake->x++;
				break;
			case PAUSE:
				break;
			case STOP:
				gameOver = 0;
				break;
		}

		if (snake->x >= WIDTH)
			snake->x = 0;
		else if (snake->x < 0)
			snake->x = WIDTH - 1;
		
		if (snake->y >= HEIGHT)
			snake->y = 0;
		else if (snake->y < 0)
			snake->y = HEIGHT - 1;
			
		if (snake->x == frut->x && snake->y == frut->y) 
		{
		snake->tsize++;
		frut->x = rand() % WIDTH;
		frut->y = rand() % HEIGHT;
		}
	for(int i = 1; i < snake->tsize; i++)
	{
		if(snake->tail[i].x == snake->x && snake->tail[i].y == snake->y)
		gameOver = 0;
	}
}

void Drow(snake_t *snake,snake_t *snake2, frut *frut, direction dir, direction dir2)
{
	HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	for(int i = 0;i < WIDTH + 1;i++)    // Верхняя граница
	{
		SetConsoleTextAttribute(hwnd, FOREGROUND_BLUE);
		printf("#");
	}
	printf("\n");
	
	for(int i = 0;i < WIDTH; i++)
	{
		for(int j = 0;j < HEIGHT; j++)
		{
			if(j == 0) printf("#");    //Левая граница
			if (i == frut->x && j == frut->y)
			{
				SetConsoleTextAttribute(hwnd, FOREGROUND_RED);
				printf("O");  // фрукт
			}
			else if (snake->x == i && snake->y == j)
			{
				SetConsoleTextAttribute(hwnd, FOREGROUND_GREEN);
				 printf("@");  // Башка1
			}
			else if (snake2->x == i && snake2->y == j) 
			{
				SetConsoleTextAttribute(hwnd, FOREGROUND_BLUE);
				printf("#");  // Башка2
			}
			else
			{
				size_t flag_t = 0;
				for (int k = 0; k < snake->tsize-1; k++)
				{
					if (snake->tail[k].x == i && snake->tail[k].y == j)
					{
						SetConsoleTextAttribute(hwnd, FOREGROUND_GREEN);
						printf("*");
						flag_t = 1;
					}
					if (snake2->tail[k].x == i && snake2->tail[k].y == j)
					{
						SetConsoleTextAttribute(hwnd, FOREGROUND_BLUE);
						printf("-");
						flag_t = 1;
					}
				}
			if(!flag_t) printf(" ");          //Все не занятое поле
			} 
			
			if(j == WIDTH - 1) 
			{
				SetConsoleTextAttribute(hwnd, FOREGROUND_BLUE);
				printf("#");
			}
		}
		printf("\n");
	}
	
	for(int i = 0;i < WIDTH + 1;i++)    // Нижняя граница
		printf("#");
	printf("\n");
	SetConsoleTextAttribute(hwnd, FOREGROUND_RED);
	printf("Eat fruit snake:%lld",snake->tsize-1);
	printf("\n");
	printf("Eat fruit snake2:%lld",snake2->tsize-1);
	printf("\n");
	if (dir == PAUSE && dir2 == PAUSE) 
	{
	printf("**********PAUSE***********");
	}
}


	void generateSnakeDirection(snake_t *snake2, direction *dir2, frut frut)
	{
	if ((*dir2 == LEFT || *dir2 == RIGHT) && snake2->x == frut.x)
	{
	return;
	}
	if ((*dir2 == LEFT || *dir2 == RIGHT) && snake2->x != frut.x)
		{
			if (frut.y == snake2->y)
			{
				if (abs(frut.x + snake2->x) < WIDTH/2) *dir2 = UP;
				else *dir2 = DOWN;
			return;
			}
		}
	if ((*dir2 == UP || *dir2 == DOWN) && snake2->y == frut.y)
	{
	return;
	}
		if ((*dir2 == UP || *dir2 == DOWN)&& snake2->y != frut.y)
		{
			if (frut.x == snake2->x)
			{
				if (abs(frut.y + snake2->y) < HEIGHT/2) *dir2 = LEFT;
				else *dir2 = RIGHT;
			return;
			}
		}
}

int main(int argc, char **argv)
{
	int sel;
	direction dir = LEFT;
	direction dir2 = LEFT;
	direction tmp1;
	direction tmp2;
	
	gameOver = 1;
	snake_t snake = Setup(WIDTH/2,HEIGHT/2,4);
	snake_t snake2 = Setup(WIDTH - 5,HEIGHT/2,4);
	frut frut = Frut();
	startMenu(&sel);
	switch(sel)
	{
		case 1:
		while(gameOver)
		{
			Drow(&snake, &snake2, &frut, dir, dir2);
			Input(&dir,&dir2,&tmp1,&tmp2);
			generateSnakeDirection(&snake2, &dir2, frut);
			Logic(&snake,&frut,dir);
			Logic(&snake2,&frut,dir2);
			snake.tsize > snake2.tsize ? Sleep(1000/snake.tsize):Sleep(1000/snake2.tsize);    //Скорость
		}
		break;
		
		case 2:
		while(gameOver)
		{
			Drow(&snake, &snake2, &frut, dir, dir2);
			InputAuto(&dir,&dir2,&tmp1,&tmp2);
			generateSnakeDirection(&snake, &dir, frut);
			generateSnakeDirection(&snake2, &dir2, frut);
			Logic(&snake,&frut,dir);
			Logic(&snake2,&frut,dir2);
			snake.tsize > snake2.tsize ? Sleep(1000/snake.tsize):Sleep(1000/snake2.tsize);    //Скорость
		}
		break;
	}
	printf("\n");
	printf("GAME OVER!!!");
	return 0;
}

