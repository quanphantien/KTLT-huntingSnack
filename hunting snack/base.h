#pragma once

#include "base.h"
#include "Console.h"
#include "Graphic.h"
#include "Animation.h"
#include "menu.h"
#include <conio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <thread>
#include <vector>
#include <Windows.h>

using namespace std;

#define MAX_SIZE_SNAKE 1000
#define MAX_SIZE_FOOD 4
#define MAX_SPEED 100
#define WIDTHCONSOLE 68
#define HEIGHTCONSOLE 19
#define startX 25
#define startY 5

struct HIGHLENGTH {
	string name;
	int length;
};

struct Player {
	int score;
};
extern int OLDSPEED;
extern POINT snake[1000]; //snake
extern POINT food[4]; // food
extern POINT a;
extern char highlength[];
extern int CHAR_LOCK;
extern int MOVING;
extern int SPEED;
extern int HEIGH_CONSOLE, WIDTH_CONSOLE;
extern int FOOD_INDEX;
extern int SIZE_SNAKE;
extern int STATE;
extern int score;

extern char yes[];
extern char no[];
extern char ok[];
extern const char* snake_string;
extern bool GATE_EXIST;

bool IsValid(int x, int y);
void GenerateFood();
void ResetData();
void DrawBoard(int x, int y, int width, int height, int curPosX = 0, int curPosY = 0);
void StartGame();
void ExitGame(HANDLE t);
void PauseGame(HANDLE t);
void Eat();

void DrawSnake(const char* str);
void DrawFood();

bool IsInsideGameoverArea(int x, int y, POINT game_over, int width, int height);
void ClearSnakeAndFoodInGameoverArea(POINT game_over, int width, int height);
void ProcessDead();
bool IsExistedFileName(string FileName);
bool IsValidFileName(string FileName);
void DeleteBox(int x, int y, int w, int h);
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
void Newgame();

void printCurrentDateTime(ostream& os);
void Resume(string filename);
void ResumeGame(string filename);