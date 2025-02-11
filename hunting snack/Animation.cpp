#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include "Animation.h"
#include "base.h"
#include <iostream>
#include "Console.h"
#include "Map.h"

using namespace std;

void MoveOutFrame()
{
    CHAR_LOCK = 'A'; MOVING = 'D'; FOOD_INDEX = 0;
    GenerateFood();
    int n = SIZE_SNAKE-1;
    char str[256];
    while (n >= 0)
    {
        if (snake[n].x < startX)
        {
            snake[n].x = startX + 1;
            snake[n].y = 15;
        }
        n--;
        strcpy(str, " ");
        DrawSnake(str);
        DrawFood();
        switch (MOVING) {
        case 'A':
            MoveLeft();
            break;
        case 'D':
            MoveRight();
            break;
        case 'W':
            MoveUp();
            break;
        case 'S':
            MoveDown();
            break;
        }
        DrawSnake(snake_string);
        if (FOOD_INDEX != 3)
        {
            DrawFood();
        }
        else
        {
            processGate();
        }
        Sleep(200 / SPEED); // Sleep function with SPEED variable
        ProcessCollision();
    }
        
}

// Hàm làm cho rắn nhấp nháy khi chết
void BlinkSnake(int times, int delay, const char* str) {
    for (int i = 0; i < times; i++) {
        // Xóa rắn
        for (int j = 0; j < SIZE_SNAKE; j++) {
            GotoXY(snake[j].x, snake[j].y);
            cout << " "; // Xóa rắn bằng cách in khoảng trắng
        }
        Sleep(delay); // Tạm dừng

        // Vẽ lại rắn
        DrawSnake(str);
        DrawFood();
        Sleep(delay); // Tạm dừng
    }
}


void BlinkBox(POINT p, int n, int m) {
    clearFrame(p, n, m);
    Sleep(0.5);
    setColorText(252);
    DrawFrame(p, n, m);
    drawGate();
}

void processGate()
{
    drawGate();
    POINT gate = { 25,16 };
        if (snake[SIZE_SNAKE-1].x == gate.x +1 && snake[SIZE_SNAKE-1].y == gate.y)
        {
            if (sfx) PlaySound(TEXT("snd_save.wav"), NULL, SND_FILENAME | SND_ASYNC);
            while (snake[0].x >= 25 && snake[0].y >= 5)
            {
                DrawSnake(" ");
                for (int i = 0; i < SIZE_SNAKE - 1; i++) {
                    snake[i].x = snake[i + 1].x;
                    snake[i].y = snake[i + 1].y;
                }
                snake[SIZE_SNAKE - 1].x--;
                DrawSnake(snake_string);
                Sleep(200 / SPEED);
                 BlinkBox({ 25,5 }, 66, 18);
            }
            NextLevel();
        }
}