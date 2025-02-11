#include "Map.h"
#include "base.h"
#include <iostream>
#include <vector>

using namespace std;

int currentLevel;
int map[MAX_ROW][MAX_COL];
vector<Level> levels = { { 1, "level1.txt" },{ 2, "level2.txt" },{ 3, "level3.txt" } };
bool GATE_EXIST;

void LoadMap(string filename, int map[MAX_ROW][MAX_COL])
{
    ifstream file(filename);
    int gateX = -1, gateY = -1;
    if (file.is_open())
    {
        for (int i = 0; i < MAX_ROW; i++)
        {
            for (int j = 0; j < MAX_COL; j++)
            {
                char c;
                file >> c;
                map[i][j] = c - '0';
            }
        }
    file.close();
    // Cập nhật tọa độ cổng vào biến toàn cục
    a.x = gateX;
    a.y = gateY;

    if (gateX != -1 && gateY != -1) {
        GATE_EXIST = true;
    }
}
    else
    {
        cout << "Can't open file!" << endl;
    }
}
    // In ra bản đồ

vector<string> typebox = {" ", "╔" ,"║" ,"╚" ,"═" ,"╝","╗"};
void DrawMap(int map[MAX_ROW][MAX_COL]) 
{
    setColorText(243);
    for (int i = 0; i < MAX_ROW; i++) 
    {
        for (int j = 0; j < MAX_COL; j++) 
        {
            GotoXY(25 + j, 5 + i);
                 cout << typebox[map[i][j]];
        }
        cout << endl;
    }
}

//Tao cong
void CreateGate() {
    int x, y;
    time_t currentTime = time(NULL);
    srand((unsigned int)currentTime);
    do {
        x = rand() % (WIDTH_CONSOLE - 1) + 1;
        y = HEIGH_CONSOLE - 2;
    } while (!IsValid(x, y));
    a = { x, y };
    GATE_EXIST = true;
}

void CheckGateCollision() {
    if (GATE_EXIST && snake[SIZE_SNAKE - 1].x == a.x && snake[SIZE_SNAKE - 1].y == a.y) {
        NextLevel();
    }
}

void NextLevel() {
    currentLevel++; // Tăng cấp độ
    currentLevel=currentLevel % (levels.size());
    // Load bản đồ mới
    LoadMap(levels[currentLevel].filename, map);
    deleteAllBox();
    DrawMap(map);
    GenerateFood();
    GotoXY(10, 6);
    cout << "Score: " << score;
    MoveOutFrame();
    STATE = 1;//Start running Thread
}


