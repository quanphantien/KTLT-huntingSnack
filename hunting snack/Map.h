#pragma once
#include "base.h"

#define MAX_ROW 20 // Số hàng của map
#define MAX_COL 68 // Số cột của map
extern int SIZE_PLUS;
extern int ROUND;
extern int win;
extern int currentLevel;
extern bool GATE_EXIST;
extern int map[MAX_ROW][MAX_COL];

struct Level {
	int level;
	string filename;
};

extern vector<Level> levels; 

void DrawMap(int map[MAX_ROW][MAX_COL]);
void NextLevel();
void CheckGateCollision();
void CreateGate();
void LoadMap(string filename, int map[MAX_ROW][MAX_COL]);