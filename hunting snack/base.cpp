#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "base.h"
#include <Windows.h>
#include <iostream>
#include <string.h>
#include <thread>
#include <conio.h>
#include<string>
#include <fstream>
#include "Console.h"
#include <vector>

HIGHLENGTH HighLength[5];
HIGHLENGTH NewLength;
POINT snake[100]; //snake
POINT food[4]; // food
POINT a;
int INDEX_ID;
int CHAR_LOCK;
int MOVING;
int SPEED;
int HEIGH_CONSOLE, WIDTH_CONSOLE;
int FOOD_INDEX;
int SIZE_SNAKE;
int SIZE_PLUS;
int STATE;
int ROUND;
int win;
bool GATE_EXIST;
char highlength[] = "HIGH LENGTH";
char yes[] = "Yes";
char no[] = "No";
char ok[] = "OK";
const char* snake_string = "22120385";

using namespace std;

void drawBox(int width, int height, const std::vector<std::string>& text) {
    // Xác định vị trí bắt đầu vẽ ô
    WIDTH_CONSOLE = 71;
    HEIGH_CONSOLE = 21;
    int xgame = (WIDTH_CONSOLE / 2) - (width / 2);
    int ygame = (HEIGH_CONSOLE / 2) - (height / 2);

    // Vẽ cạnh trên
    GotoXY(xgame, ygame);
    std::cout << (unsigned char)201;
    for (int i = 0; i < width - 2; ++i) std::cout << (unsigned char)205;
    std::cout << (unsigned char)187;

    // Vẽ các dòng giữa
    for (int i = 0; i < height - 2; ++i) {
        GotoXY(xgame, ygame + i + 1);
        std::cout << (unsigned char)186;
        if (i < text.size()) {
            std::cout << " " << text[i];
            int spaces = width - 3 - text[i].length();
            for (int j = 0; j < spaces; ++j) std::cout << " ";
        }
        else {
            for (int j = 0; j < width - 2; ++j) std::cout << " ";
        }
        std::cout << (unsigned char)186;
    }

    // Vẽ cạnh dưới
    GotoXY(xgame, ygame + height - 1);
    std::cout << (unsigned char)200;
    for (int i = 0; i < width - 2; ++i) std::cout << (unsigned char)205;
    std::cout << (unsigned char)188;
}

bool IsValid(int x, int y) {
    for (int i = 0; i < SIZE_SNAKE; i++) {
        if (snake[i].x == x && snake[i].y == y) {
            return false;
        }
    }
    return true;
}

void GenerateFood() {
    int x, y;
    srand(time(NULL));
    for (int i = 0; i < MAX_SIZE_FOOD; i++) {
        do {
            x = rand() % (WIDTH_CONSOLE - 1) + 1;
            y = rand() % (HEIGH_CONSOLE - 1) + 1;
        } while (IsValid(x, y) == false);
        food[i] = { x,y };
    }
}

void ResetData() {
    //Initialize the global values
    CHAR_LOCK = 'A', MOVING = 'D', SPEED = 1; FOOD_INDEX = 0, WIDTH_CONSOLE = 70,
        HEIGH_CONSOLE = 20, SIZE_SNAKE = 6;
    // Initialize default values for snake
    snake[0] = { 10, 5 }; snake[1] = { 11, 5 };
    snake[2] = { 12, 5 }; snake[3] = { 13, 5 };
    snake[4] = { 14, 5 }; snake[5] = { 15, 5 };
    GenerateFood(); // Create food array
}

void DrawBoard(int x, int y, int width, int height, int curPosX, int curPosY) {
    GotoXY(x, y); cout << 'X';
    for (int i = 1; i < width; i++) cout << 'X';
    cout << 'X';
    GotoXY(x, height + y); cout << 'X';
    for (int i = 1; i < width; i++) cout << 'X';
    cout << 'X';
    for (int i = y + 1; i < height + y; i++) {
        GotoXY(x, i); cout << 'X';
        GotoXY(x + width, i); cout << 'X';
    }
    GotoXY(curPosX, curPosY);
}

void StartGame() {
    system("cls");
    ResetData(); // Intialize original data
    DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE); // Draw game
    STATE = 1;//Start running Thread
}

// Function exit game
void ExitGame(HANDLE t) {
    system("cls");
    TerminateThread(t, 0);
}
void CountDown() {
    int x = 1;
    int y = 1;
    for (int i = 0; i < HEIGH_CONSOLE - 1; i++) {
        GotoXY(x, y + i);
        for (int j = 0; j < WIDTH_CONSOLE - 1; j++) {
            cout << " ";
        }
    }
    for (int i = 3; i > 0; i--) {
        GotoXY(WIDTH_CONSOLE / 2, HEIGH_CONSOLE / 2);
        cout << i;
        this_thread::sleep_for(chrono::seconds(1));
    }
    GotoXY(WIDTH_CONSOLE / 2, HEIGH_CONSOLE / 2);
    cout << "Go";
    this_thread::sleep_for(chrono::milliseconds(500));
    GotoXY(WIDTH_CONSOLE / 2, HEIGH_CONSOLE / 2);
    cout << "  ";
}

// Function pause game
void PauseGame(HANDLE t) {
    SuspendThread(t);
    int column = 30;
    int row = 8;
    int xgame = (WIDTH_CONSOLE / 2) - 15;
    int ygame = (HEIGH_CONSOLE / 2) - 3;

    for (int i = 0; i < row; i++)
    {
        GotoXY(xgame, ygame + i);
        for (int j = 0; j < column; j++)
        {
            if (i == 0)
                cout << (unsigned char)220;
            else if (i == row - 1)
                cout << (unsigned char)223;
            else if (j == 0 || j == column - 1)
                cout << (unsigned char)219;
            else
                cout << " ";
        }
    }
    GotoXY(xgame + 10, ygame + 2);
    cout << "Pause Game";
    GotoXY(xgame + 3, ygame + 4);
    cout << "Continue";
    GotoXY(xgame + 3, ygame + 5);
    cout << "(Press C)";
    GotoXY(xgame + 20, ygame + 4);
    cout << "Save";
    GotoXY(xgame + 17, ygame + 5);
    cout << "(Press S)";
    int temp2 = 0;
    while (temp2 != 'C' && temp2 != 'S') {
        temp2 = toupper(getch());
    }
    if (temp2 == 'C') {

        CountDown();
        ResumeThread(t);
    }
    else SaveData();
}
// Function pause game


// Function to update global data
void Eat() {
    snake[SIZE_SNAKE] = food[FOOD_INDEX];
    if (FOOD_INDEX == MAX_SIZE_FOOD - 1) {
        FOOD_INDEX = 0;
        SIZE_SNAKE = 6;
        if (SPEED == MAX_SPEED)
            SPEED = 1;
        else
            SPEED++;
        GenerateFood();
    }
    else {
        FOOD_INDEX++;
        SIZE_SNAKE++;
    }
}

// Function to draw
void DrawSnakeAndFood(const char* str) {
    int index = 0;
    for (int i = 0; i < SIZE_SNAKE; i++) {
        GotoXY(snake[i].x, snake[i].y);
        cout << str[index++];
        if (index >= strlen(str)) index = 0;
    }
    GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
    cout << str[index++];
}

// Function to process the dead of snake
void ProcessDead() {
    STATE = 0;
    std::vector<std::string> game_over = {
        "===============================",
        "           GAME OVER           ",
        "===============================",
        " SCORE:        HIGH SCORE:     ",
        "           CONTINUE?           ",
        "    Y:Yes             N:No     "
    };
    int boxWidth = 35;
    int boxHeight = 9;
    drawBox(boxWidth, boxHeight, game_over);
}

bool IsExistedFileName(string FileName)
{
    ifstream f_user(".\\Data\\username.txt");
    string tmp;

    while (f_user >> tmp)
        if (tmp == FileName)
        {
            f_user.close();
            return true;
        }
    f_user.close();
    return false;
}

bool IsValidFileName(string FileName)
{
    for (int i = 0; i < FileName.length(); i++)
        if (FileName[i] == '>' || FileName[i] == '<' || FileName[i] == ':'
            || FileName[i] == '"' || FileName[i] == '/' || FileName[i] == '\\'
            || FileName[i] == '|' || FileName[i] == '?' || FileName[i] == '*')
            return false;
    return true;
}

void DeleteBox()
{
    int column = 30;
    int row = 8;
    int xgame = (WIDTH_CONSOLE / 2) - 15;
    int ygame = (HEIGH_CONSOLE / 2) - 3;

    for (int i = 0; i < row; i++)
    {
        GotoXY(xgame, ygame + i);
        for (int j = 0; j < column; j++)
        {
            if (i == 0)
                cout << " ";
            else if (i == row - 1)
                cout << " ";
            else if (j == 0 || j == column - 1)
                cout << " ";
            else
                cout << " ";
        }
    }
}

void SaveData()
{
    string FileName;

    int column = 30;
    int row = 8;
    int xgame = (WIDTH_CONSOLE / 2) - 15;
    int ygame = (HEIGH_CONSOLE / 2) - 3;

    for (int i = 0; i < row; i++)
    {
        GotoXY(xgame, ygame + i);
        for (int j = 0; j < column; j++)
        {
            if (i == 0)
                cout << (unsigned char)220;
            else if (i == row - 1)
                cout << (unsigned char)223;
            else if (j == 0 || j == column - 1)
                cout << (unsigned char)219;
            else
                cout << " ";
        }
    }

    GotoXY(xgame + 9, ygame + 2);
    cout << "Save and Exit";
    GotoXY(xgame + 14, ygame + 5);
    TextColor(3, ok);
    GotoXY(xgame + 3, ygame + 3);
    cout << "Name: ";

    do
    {
        GotoXY(xgame + 9, ygame + 3);
        cin >> FileName;
        GotoXY(xgame + 3, ygame + 4);
        if (IsExistedFileName(FileName))
            cout << "File existed, re-type!";
        if (!IsValidFileName(FileName))
            cout << "Invalid char, re-type!";
        if (FileName.length() > 18)
            cout << "Too long, re-type!";

        if (IsExistedFileName(FileName) || !IsValidFileName(FileName) || FileName.length() > 18)
        {
            GotoXY(xgame + 9, ygame + 3);
            for (int i = 0; i < 18; i++)
                cout << " ";
        }
    } while (IsExistedFileName(FileName) || !IsValidFileName(FileName) || FileName.length() > 18);

    DeleteBox();

    ofstream fo(".\\Data\\" + FileName);

    ofstream f_user;
    f_user.open(".\\Data\\username.txt", ios::app);
    f_user << FileName << endl;
    f_user.close();

    fo << SIZE_SNAKE << " " << SIZE_PLUS << endl;

    for (int i = 0; i < SIZE_SNAKE; i++)
        fo << snake[i].x << " " << snake[i].y << endl;

    fo << FOOD_INDEX << endl;

    fo << food[FOOD_INDEX].x << " " << food[FOOD_INDEX].y << endl;

    if (GATE_EXIST)
        fo << a.x << " " << a.y << endl;
    else
        fo << -1 << " " << -1 << endl;

    fo << INDEX_ID << endl;

    fo << SPEED << endl;

    fo << ROUND << endl;

    fo << MOVING << endl;

    fo << CHAR_LOCK << endl;

    fo << win;

    fo.close();

    NewLength.name = FileName;
    NewLength.length = SIZE_SNAKE + SIZE_PLUS;

    CreateNewHighLength();
    SortHighLength();
}

void LoadData()
{
    string FileName;
    int column = 30;
    int row = 8;
    int xgame = (WIDTH_CONSOLE / 2) - 15;
    int ygame = (HEIGH_CONSOLE / 2) - 3;

    for (int i = 0; i < row; i++)
    {
        GotoXY(xgame, ygame + i);
        for (int j = 0; j < column; j++)
        {
            if (i == 0)
                cout << (unsigned char)220;
            else if (i == row - 1)
                cout << (unsigned char)223;
            else if (j == 0 || j == column - 1)
                cout << (unsigned char)219;
            else
                cout << " ";
        }
    }

    GotoXY(xgame + 11, ygame + 2);
    cout << "Load data";
    GotoXY(xgame + 14, ygame + 5);
    TextColor(3, ok);
    GotoXY(xgame + 3, ygame + 3);
    cout << "Name: ";

    do
    {
        GotoXY(xgame + 9, ygame + 3);
        cin >> FileName;
        if (!IsExistedFileName(FileName))
        {
            GotoXY(xgame + 3, ygame + 4);
            cout << "Not existed user!";
            GotoXY(xgame + 9, ygame + 3);
            for (int i = 0; i < 18; i++)
                cout << " ";
        }
    } while (!IsExistedFileName(FileName));

    DeleteBox();

    for (int i = 0; i < SIZE_SNAKE; i++)
    {
        GotoXY(snake[i].x, snake[i].y);
        cout << " ";
    }

    ifstream fi(".\\Data\\" + FileName);

    fi >> SIZE_SNAKE >> SIZE_PLUS;

    GotoXY(8, HEIGH_CONSOLE);
    cout << SIZE_SNAKE + SIZE_PLUS;

    for (int i = 0; i < SIZE_SNAKE; i++)
        fi >> snake[i].x >> snake[i].y;

    GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);

    fi >> FOOD_INDEX;
    cout << " ";
    fi >> food[FOOD_INDEX].x >> food[FOOD_INDEX].y;

    fi >> a.x >> a.y;
    if (a.x != -1 && a.y != -1)
    {
        GotoXY(a.x + 1, a.y);
        cout << (unsigned char)223;
        GotoXY(a.x - 1, a.y - 1);
        cout << (unsigned char)219;
        GotoXY(a.x, a.y);
        cout << (unsigned char)223;
        GotoXY(a.x + 1, a.y - 1);
        cout << (unsigned char)219;
        GotoXY(a.x - 1, a.y);
        cout << (unsigned char)223;
        GATE_EXIST = true;
    }

    fi >> INDEX_ID;

    fi >> SPEED;

    fi >> ROUND;

    fi >> MOVING;

    fi >> CHAR_LOCK;

    fi >> win;

    fi.close();
}
bool IsEmptyHighLengthFile()
{
    ifstream fi;
    string name;
    int length;

    fi.open(".\\Data\\highlength.txt");
    if (fi >> name >> length)
    {
        fi.close();
        return false;
    }
    fi.close();
    return true;
}

void SaveHighLength()
{
    remove(".\\Data\\highlength.txt");

    ofstream fo;
    fo.open(".\\Data\\highlength.txt");

    for (int i = 0; i < 4; i++)
        fo << HighLength[i].name << " " << HighLength[i].length << endl;
    fo << HighLength[4].name << " " << HighLength[4].length;

    fo.close();
}

void ResetHighLength()
{
    for (int i = 0; i < 5; i++)
    {
        HighLength[i].name = "[NONE]";
        HighLength[i].length = 4;
    }
    SaveHighLength();
}

void InitializeHighLength()
{
    if (!IsEmptyHighLengthFile())
    {
        string name;
        int length;

        ifstream fi;
        fi.open(".\\Data\\highlength.txt");

        int i = 0;

        while (fi >> name >> length)
        {
            HighLength[i].name = name;
            HighLength[i].length = length;
            i++;
        }

        fi.close();
    }
    else
        ResetHighLength();
}


void TextColor(int color, char* OutputContent)
{
    static int __BACKGROUND;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

    GetConsoleScreenBufferInfo(h, &csbiInfo);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (__BACKGROUND << 4));

    cout << OutputContent;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 + (__BACKGROUND << 4));
}

void CreateNewHighLength()
{
    int minLength = HighLength[0].length;
    int index = 0;
    for (int i = 0; i < 5; i++)
    {
        if (HighLength[i].name == "[NONE]")
        {
            minLength = HighLength[i].length;
            index = i;
            break;
        }
        else if (HighLength[i].length < minLength)
        {
            minLength = HighLength[i].length;
            index = i;
        }
    }

    if (NewLength.length > minLength || (NewLength.length == 4 && HighLength[index].name == "[NONE]"))
    {
        HighLength[index].name = NewLength.name;
        HighLength[index].length = NewLength.length;
    }
}

void SortHighLength()
{
    for (int i = 0; i < 4; i++)
        for (int j = i + 1; j < 5; j++)
            if (HighLength[i].length < HighLength[j].length)
            {
                string name = HighLength[i].name;
                HighLength[i].name = HighLength[j].name;
                HighLength[j].name = name;

                int length = HighLength[i].length;
                HighLength[i].length = HighLength[j].length;
                HighLength[j].length = length;
            }
    SaveHighLength();
}

void ShowHighLength()
{
    ifstream fi;
    fi.open(".\\Data\\highlength.txt");

    string name;
    int length;

    system("cls");

    int column = 31;
    int row = 9;
    int xHighLength = (WIDTH_CONSOLE / 2) - 15;
    int yHighLength = (HEIGH_CONSOLE / 2) - 4;

    for (int j = 0; j < row; j++)
    {
        GotoXY(xHighLength, yHighLength + j);
        for (int k = 0; k < column; k++)
        {
            if (j == 0)
                cout << (unsigned char)220;
            else if (j == 2 && k != 0 && k != column - 1)
                cout << "*";
            else if (j == row - 1)
                cout << (unsigned char)223;
            else if (k == 0 || k == column - 1)
                cout << (unsigned char)219;
            else
                cout << " ";
        }
    }

    while (true)
    {
        GotoXY(xHighLength + 10, yHighLength + 1);
        cout << "HIGH LENGTH";

        int i = 0;

        while (fi >> name >> length)
        {
            GotoXY(xHighLength + 4, yHighLength + i + 3);
            cout << "#" << i + 1 << ". ";
            GotoXY(xHighLength + 8, yHighLength + i + 3);
            cout << name;
            GotoXY(xHighLength + 27, yHighLength + i + 3);
            cout << length;
            i++;
        }

        if (_kbhit())
            break;
    }
    fi.close();
}


void MoveRight() {
    if (snake[SIZE_SNAKE - 1].x + 1 >= WIDTH_CONSOLE) {
        ProcessDead();
    }
    else {
        if (snake[SIZE_SNAKE - 1].x + 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
            Eat();
        }
        for (int i = 0; i < SIZE_SNAKE - 1; i++) {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[SIZE_SNAKE - 1].x++;
    }
}

void MoveLeft() {
    if (snake[SIZE_SNAKE - 1].x - 1 <= 0) {
        ProcessDead();
    }
    else {
        if (snake[SIZE_SNAKE - 1].x - 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
            Eat();
        }
        for (int i = 0; i < SIZE_SNAKE - 1; i++) {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[SIZE_SNAKE - 1].x--;
    }
}

void MoveDown() {
    if (snake[SIZE_SNAKE - 1].y + 1 >= HEIGH_CONSOLE) {
        ProcessDead();
    }
    else {
        if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y + 1 == food[FOOD_INDEX].y) {
            Eat();
        }
        for (int i = 0; i < SIZE_SNAKE - 1; i++) {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[SIZE_SNAKE - 1].y++;
    }
}

void MoveUp() {
    if (snake[SIZE_SNAKE - 1].y - 1 <= 0) {
        ProcessDead();
    }
    else {
        if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y - 1 == food[FOOD_INDEX].y) {
            Eat();
        }
        for (int i = 0; i < SIZE_SNAKE - 1; i++) {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[SIZE_SNAKE - 1].y--;
    }
}



// Check if snake's head collides with its body
void ProcessCollision() {
    for (int i = 0; i < SIZE_SNAKE - 1; i++) {
        if (snake[SIZE_SNAKE - 1].x == snake[i].x
            && snake[SIZE_SNAKE - 1].y == snake[i].y)
            ProcessDead();
    }
}

// Subfunction for thread
void ThreadFunc() {
    char str[256];
    while (1) {
        if (STATE == 1) { // If my snake is alive
            strcpy(str, " ");
            DrawSnakeAndFood(str);
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
            strcpy(str, "0");
            DrawSnakeAndFood(snake_string);
            Sleep(200 / SPEED); // Sleep function with SPEED variable
            ProcessCollision();
        }
    }
}

void Newgame()
{
    Player a;
    int temp;
    FixConsoleWindow();
    StartGame();
    thread t1(ThreadFunc); // Create thread for snake
    HANDLE handle_t1 = t1.native_handle(); // Take handle of thread
    while (1) {
        temp = toupper(getch());
        if (STATE == 1) {
            if (temp == 'P') {
                PauseGame(handle_t1);
            }
            else if (temp == 'L')
            {
                PauseGame(handle_t1);
                SaveData();
                ExitGame(handle_t1);

            }
            else if (temp == 'T') {
                PauseGame(handle_t1);
                LoadData();
                ResumeThread(handle_t1);
            }
            else if (temp == 27) {
                ExitGame(handle_t1);
                return;
            }
            else {
                ResumeThread(handle_t1);
                if ((temp != CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S')) {
                    if (temp == 'D') CHAR_LOCK = 'A';
                    else if (temp == 'W') CHAR_LOCK = 'S';
                    else if (temp == 'S') CHAR_LOCK = 'W';
                    else CHAR_LOCK = 'D';
                    MOVING = temp;
                }
            }
        }
        else {
            if (temp == 'Y') StartGame();
            else {
                ExitGame(handle_t1);
                return;
            }
        }
    }
}