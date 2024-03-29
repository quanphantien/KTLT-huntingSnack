#include <Windows.h>
#include <iostream>
#include <string.h>
#include <thread>
#include <conio.h>
#include <fstream>
#include <string>
#include <vector>
#pragma once

using namespace std;

#define MAX_SIZE_SNAKE 10
#define MAX_SIZE_FOOD 4
#define MAX_SPEED 3

struct HIGHLENGTH {
	string name;
	int length;
};

struct Player {
	int score;
};

extern POINT snake[10]; //snake
extern POINT food[4]; // food
extern int CHAR_LOCK;
extern int MOVING;
extern int SPEED;
extern int HEIGH_CONSOLE, WIDTH_CONSOLE;
extern int FOOD_INDEX;
extern int SIZE_SNAKE;
extern int STATE;

void FixConsoleWindow();
void GotoXY(int x, int y);
bool IsValid(int x, int y);
void GenerateFood();
void ResetData();
void DrawBoard(int x, int y, int width, int height, int curPosX = 0, int curPosY = 0);
void StartGame();
void ExitGame(HANDLE t);
void PauseGame(HANDLE t);
void Eat();
void DrawSnakeAndFood(const char* str);
void ProcessDead();


bool IsExistedFileName(string FileName);
bool IsValidFileName(string FileName);
void DeleteBox();
void SaveData();
void LoadData();
bool IsEmptyHighLengthFile();
void SaveHighLength();
void ResetHighLength();
void InitializeHighLength();
void TextColor(int color, char* OutputContent);
void CreateNewHighLength();
void SortHighLength();
void ShowHighLength();
void MoveRight();
void MoveLeft();
void MoveDown();
void MoveUp();
void ProcessCollision();
void ThreadFunc();
