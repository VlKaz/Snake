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

void Input(direction *dir) {
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
            case 'p':
            case 'P':
                *dir = PAUSE;
                break;
            case 'c':
            case 'C':
                *dir = STOP;
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

void Drow(snake_t *snake, frut *frut, direction dir)
{
	system("cls");
	for(int i = 0;i < WIDTH + 1;i++)    // Верхняя граница
		printf("#");
	printf("\n");
	
	for(int i = 0;i < WIDTH; i++)
	{
		for(int j = 0;j < HEIGHT; j++)
		{
			if(j == 0) printf("#");    //Левая граница
			if (i == frut->x && j == frut->y)printf("O");  // фрукт
			else if (snake->x == i && snake->y == j) printf("@");  // Башка
			else
			{
				size_t flag_t = 0;
				for (int k = 0; k < snake->tsize-1; k++)
				{
					if (snake->tail[k].x == i && snake->tail[k].y == j)
					{
						printf("*");
						flag_t = 1;
					}
				}
			if(!flag_t) printf(" ");          //Все не занятое поле
			} 
			
			if(j == WIDTH - 1) printf("#");
		}
		printf("\n");
	}
	
	for(int i = 0;i < WIDTH + 1;i++)    // Нижняя граница
		printf("#");
	printf("\n");
	printf("Eat fruit:%lld",snake->tsize-1);
	printf("\n");
	if (dir == PAUSE) 
	{
	printf("**********PAUSE***********");
	}
}
int main(int argc, char **argv)
{
	direction dir = LEFT;
	gameOver = 1;
	snake_t snake = Setup(WIDTH/2,HEIGHT/2,4);
	frut frut = Frut();
	while(gameOver)
	{
		Drow(&snake,&frut,dir);
		Input(&dir);
		Logic(&snake,&frut,dir);
		Sleep(1000/snake.tsize);    //Скорость
	}
	printf("\n");
	printf("GAME OVER!!!");
	return 0;
}

