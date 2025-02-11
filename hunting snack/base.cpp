#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "base.h"
#include "menu.h"
#include "Map.h"
#include "Animation.h"
#include "Graphic.h"
#include "GamePlay.h"
#include <string>
#include "Save.h"
#include "Load.h"
#include <sstream>
#include <vector>

using namespace std;

int OLDSPEED = 3;
HIGHLENGTH HighLength[5];
HIGHLENGTH NewLength;
POINT snake[1000]; //snake
POINT food[4]; // food
POINT a;

int score = 0;
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

char highlength[] = "HIGH LENGTH";
char yes[] = "Yes";
char no[] = "No";
char ok[] = "OK";
const char* snake_string = "2212017022120369221203852212039222120437";

// Kiểm tra toạ độ của rắn
bool IsValid(int x, int y) {
    bool flag1=true;
    for (int i = 0; i < SIZE_SNAKE; i++) {
        if (snake[i].x == x && snake[i].y == y) {
            flag1= false;
        }
    }
    return flag1 && (map[x-25][y-5] != 0);
    
}

// Tạo mồi ngẫu nhiên
void GenerateFood() {
    int x, y;
    srand(time(NULL));
    for (int i = 0; i < MAX_SIZE_FOOD; i++) {
        do {
            x = rand() % (WIDTHCONSOLE - 2) + startX+1;
            y = rand() % (HEIGHTCONSOLE -2) + startY+1;
        } while (IsValid(x, y) == false);
        food[i] = { x,y };
    }
}

// Thiết lập lại dữ liệu ban đầu của rắn
void ResetData() {
    //Initialize the global values
    CHAR_LOCK = 'A', MOVING = 'D', SPEED = 3, FOOD_INDEX = 0, WIDTH_CONSOLE = 68,
        HEIGH_CONSOLE = 19, SIZE_SNAKE = 6;
    currentLevel = 0;
    // Initialize default values for snake
    snake[0] = { 21, 15 }; snake[1] = { 22, 15 };//
    snake[2] = { 23, 15 }; snake[3] = { 24, 15 };//
    snake[4] = { 25, 15 }; snake[5] = { 26, 15 };//
    GenerateFood(); // Create food array
}


// Vẽ bảng (có vẻ không cần thiết lắm vì có DrawFrame())
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

// Bắt đầu game
void StartGame() {
    score = 0;
    ResetData(); // Intialize original data
       POINT pBox{ 25,5 };
    int wBox = 66, hBox = 18;
    setColorText(243);
    DrawFrame(pBox, wBox, hBox);
    LoadMap(levels[currentLevel].filename, map);
    STATE = 1;//Start running Thread
}
// Bắt đầu game
void ConsumeGame() {
    score = 0;
     // Intialize original data
    POINT pBox{ 25,5 };
    int wBox = 66, hBox = 18;
    setColorText(243);
    DrawFrame(pBox, wBox, hBox);
    STATE = 1;//Start running Thread
}

// Thoát game
void ExitGame(HANDLE t) {
    system("cls");
    TerminateThread(t, 0);
    exit(0);
}
// In Số
void In(int x, POINT Center) { // ▄ , █
    //SetConsoleOutputCP(CP_UTF8);
    if (x == 3) {
        GotoXY(Center.x - 2, Center.y - 2);
        cout << u8"▄▄▄▄▄";
        GotoXY(Center.x - 2, Center.y);
        cout << u8"▄▄▄▄";
        GotoXY(Center.x - 2, Center.y + 2);
        cout << u8"▄▄▄▄";
        for (int i = 0; i < 4; i++) {
            GotoXY(Center.x + 2, Center.y - 1 + i);
            cout << u8"█";
        }
    }
    else if (x == 2) {
        GotoXY(Center.x - 2, Center.y - 2);
        cout << u8"▄▄▄▄▄";
        GotoXY(Center.x - 2, Center.y);
        cout << u8"▄▄▄▄";
        GotoXY(Center.x - 1, Center.y + 2);
        cout << u8"▄▄▄▄";
        GotoXY(Center.x + 2, Center.y - 1); cout << u8"█";
        GotoXY(Center.x + 2, Center.y); cout << u8"█";
        GotoXY(Center.x - 2, Center.y + 1); cout << u8"█";
        GotoXY(Center.x - 2, Center.y + 2); cout << u8"█";
    }
    else if (x == 1) {
        GotoXY(Center.x, Center.y - 2);
        cout << u8"▄";
        for (int i = 0; i < 4; i++) {
            GotoXY(Center.x, Center.y - 1 + i);
            cout << u8"█";
        }
    }
    else {
        GotoXY(Center.x - 5, Center.y - 1);
        cout << u8"▄▄▄▄ ▄▄▄▄";
        this_thread::sleep_for(chrono::milliseconds(100));
        GotoXY(Center.x - 5, Center.y);
        cout << u8"█ ▄▄ █  █";
        this_thread::sleep_for(chrono::milliseconds(100));
        GotoXY(Center.x - 5, Center.y + 1);
        cout << u8"█▄▄█ █▄▄█";

    }
}

// Đếm ngược
void CountDown(int x, int y, int width, int height) {
    POINT Center = { 59,13 };
    POINT Start = { x,y };
    clearFrame(Start, width, height);
    for (int i = 3; i > -1; i--) {
        if(sfx) if (sfx) PlaySound(TEXT("snd_bell.wav"), NULL, SND_FILENAME | SND_ASYNC);
        GotoXY(Center.x, Center.y);
        In(i, Center);
        this_thread::sleep_for(chrono::seconds(1));
        clearFrame(Start, width, height);
    }

}

// Dừng game
void PauseGame(HANDLE t) {
    if (sfx) PlaySound(TEXT("snd_select.wav"), NULL, SND_FILENAME | SND_ASYNC);
    SuspendThread(t);
    int x = 43; int y = 10; //Vi tri phia tren ben trai cua khung
    int width = 30, height = 7; //Kich thuoc cua khung
    POINT PauseBox = { x,y };
    clearFrame(PauseBox, width - 2, height - 2);
    DrawFrame(PauseBox, width, height);
    GotoXY(x + 10, y + 2);
    cout << "Pause Game";
    GotoXY(x + 3, y + 4);
    cout << "Continue";
    GotoXY(x + 3, y + 5);
    cout << "(Press C)";
    GotoXY(x + 20, y + 4);
    cout << "Save";
    GotoXY(x + 17, y + 5);
    cout << "(Press S)";
    int temp2 = 0;
    while (temp2 != 'C' && temp2 != 'S') {
        temp2 = toupper(getch());
    }
    if (temp2 == 'C') {
        CountDown(x, y, width, height);
        ResumeThread(t);
    }
    else SaveData();
}

// Rắn ăn mồi (Function to update global data)
void Eat() {
    score++;
    GotoXY(10, 6);
    cout << "Score: " << score;
    DrawScoreGraphic(score);
    snake[SIZE_SNAKE] = food[FOOD_INDEX];
    if (FOOD_INDEX == MAX_SIZE_FOOD - 1) {
        FOOD_INDEX = 0;
        SIZE_SNAKE++;
        if (SPEED == MAX_SPEED)
        {
            SPEED = 1;
            SIZE_SNAKE = 6;
        }
        else {
            SPEED++;
        }
        GenerateFood();
    }
    else {
        if (sfx) PlaySound(TEXT("snd_heal_c.wav"), NULL, SND_FILENAME | SND_ASYNC);
        FOOD_INDEX++;
        SIZE_SNAKE++;
    }
}

// Vẽ rắn và mồi (Function to draw)
void DrawSnake(const char* str) {
    int index = 0;
    setColorText(251);
    for (int i = 0; i < SIZE_SNAKE - 1; i++)
    {
        if (snake[i].x >= startX +1 && snake[i].y >= startY+1)//moi
        {
            GotoXY(snake[i].x, snake[i].y);
            cout << str[index];//moi
        }
        else
        {
            snake[i].x = snake[i].y = 0;
        }
        index++;//moi
        if (index >= strlen(str)) index = 0;
    }
    if (snake[SIZE_SNAKE - 1].x > startX && snake[SIZE_SNAKE - 1].y > startY)
    {
        GotoXY(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y);
        setColorText(253);
        switch (MOVING)
        {
        case 'D':
            cout << u8"►";
            break;
        case 'A':
            cout << u8"◄";
            break;
        case 'S':
            cout << u8"▼";
            break;
        default:
            cout << u8"▲";
            break;
        }
    }
}

void DrawFood()
{
    GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
    setColorText(250);
    cout << u8"■";
}

bool IsInsideGameoverArea(int x, int y, POINT game_over, int width, int height) {
    // Kiểm tra xem tọa độ (x, y) có nằm trong phạm vi của bảng game over không
    return (x >= game_over.x && x < game_over.x + width && y >= game_over.y && y < game_over.y + height);
}

void ClearSnakeAndFoodInGameoverArea(POINT game_over, int width, int height) {
    // Xóa rắn nếu nó nằm trong phạm vi của bảng game over
    for (int i = 0; i < SIZE_SNAKE; ++i) {
        if (IsInsideGameoverArea(snake[i].x, snake[i].y, game_over, width, height)) {
            GotoXY(snake[i].x, snake[i].y);
            cout << " "; // Xóa rắn
        }
    }
    // Xóa đồ ăn nếu nó nằm trong phạm vi của bảng game over
    if (IsInsideGameoverArea(food[FOOD_INDEX].x, food[FOOD_INDEX].y, game_over, width, height)) {
        GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
        cout << " "; // Xóa đồ ăn
    }
}

// Rắn chết (Function to process the dead of snake)
void ProcessDead() {
    if (sfx) PlaySound(TEXT("snd_damage_c.wav"), NULL, SND_FILENAME | SND_ASYNC);
    STATE = 0;
    BlinkSnake(6, 200, snake_string);    
    POINT game_over = { 49, 10 };
    //ClearSnakeAndFoodInGameoverArea(game_over, 18, 9);
    DeleteBox(game_over.x + 1, game_over.y + 1, 18, 9);
    DrawFrame(game_over, 18, 9);
    std::vector<std::string> game_over_text = {
        "================",
        "    GAME OVER   ",
        "================",
        "                ",
        "                ",
        "    RESTART?    ",
        "                ",
        " Y:Yes     N:No "
    };
    std::string scoreStr = "    SCORE: "+to_string(score);
    game_over_text.insert(game_over_text.begin() + 4, scoreStr);
    GotoXY(75, 1);
    for (int i = 0; i < game_over_text.size(); ++i) {
        GotoXY(game_over.x + 2, game_over.y + i + 1);
        std::cout << game_over_text[i];
    }
    
}

// Kiểm tra tên file có tồn tại?
bool IsExistedFileName(string FileName)
{
    vector<Saver> savers;
    loadVectorFromFile(savers, "./Data/username.bin");

    for(int i=0;i<savers.size();i++)
        if (savers[i].name == FileName)
        {
            return true;
        }
    return false;
}

// Kiểm tra tên file có hợp lệ?
bool IsValidFileName(string FileName)
{
    for (int i = 0; i < FileName.length(); i++)
        if (FileName[i] == '>' || FileName[i] == '<' || FileName[i] == ':'
            || FileName[i] == '"' || FileName[i] == '/' || FileName[i] == '\\'
            || FileName[i] == '|' || FileName[i] == '?' || FileName[i] == '*')
            return false;
    return true;
}

// Xoá bảng chữ nhật 1
void DeleteBox(int x, int y, int w, int h)
{
    for (int i = 0; i < h; i++)
    {
        GotoXY(x, y + i);
        for (int j = 0; j < w; j++)
        {
            cout << ' ';
        }
    }
}

// Lưu tiến trình
void SaveData()
{
    string FileName;

    int column = 50;
    int row = 10;
    int xgame = (WIDTHCONSOLE / 2) - 15+10;
    int ygame = (HEIGHTCONSOLE / 2) - 3+4;

    for (int i = 0; i < row; i++)
    {
        GotoXY(xgame, ygame + i);
        for (int j = 0; j < column; j++)
        {
            if (i == 0)
                cout << u8"▄";
            else if (i == row - 1)
                cout << u8"▀";
            else if (j == 0 || j == column - 1)
                cout << u8"█";
            else
                cout << " ";
        }
    }

    GotoXY(xgame + 9, ygame + 2);
    cout << "         Save and Exit";
    GotoXY(xgame + 14, ygame + 5);
    setColorText(250);
    GotoXY(xgame + 3, ygame + 3);
    cout << "Name: ";

    do
    {
        GotoXY(xgame + 3, ygame + 4);
        cout << "                           ";
        GotoXY(xgame + 9, ygame + 3);
        char s[12];
        cin.getline(s, 12);
        FileName = s;
        GotoXY(xgame + 3, ygame + 4);
        if (IsExistedFileName(FileName))
            cout << "File existed, please enter again!";
        if (!IsValidFileName(FileName+".bin"))
            cout << "Invalid char, please enter again!";
        if (FileName.length() > 12)
            cout << "Too long, please enter again!";

        if (IsExistedFileName(FileName) || !IsValidFileName(FileName) || FileName.length() > 12)
        {
            GotoXY(xgame + 9, ygame + 3);
            for (int i = 0; i < 25; i++)
                cout << " ";
        }
    } while (IsExistedFileName(FileName) || !IsValidFileName(FileName) || FileName.length() > 12);

    writeBinaryFile(FileName + ".bin", snake, SIZE_SNAKE, food, FOOD_INDEX, MOVING, CHAR_LOCK,currentLevel);

    vector<Saver> savers;
    Saver saver;

    loadVectorFromFile(savers, ".\\Data\\username.bin");

    saver.name = FileName;
    saver.score = score;
    stringstream ss;
    printCurrentDateTime(ss);
    saver.date = ss.str();

    savers.push_back(saver);

    deleteAllBox();
    GotoXY(xgame + 3, ygame + 3);
    cout<<"Save successfully!";
    Sleep(2000);

    int n = savers.size() - 10;
    if (n > 0)
    {
        savers.erase(savers.begin(), savers.begin() + n);
    }

    saveVectorToFile(savers, ".\\Data\\username.bin");

    mainMenu({ 7,4 }, 12, 20);
}

// Tải tiến trình
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

    //DeleteBox();

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

// Kiểm tra dữ liệu (độ dài rắn?)
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

// Lưu dữ liệu BXH
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

// Thiết lập lại BXH
void ResetHighLength()
{
    for (int i = 0; i < 5; i++)
    {
        HighLength[i].name = "[NONE]";
        HighLength[i].length = 4;
    }
    SaveHighLength();
}

// Tải dữ liệu BXH
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

// Màu văn bản
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

// Tạo mới BXH
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

// Sắp xếp BXH
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

// Biểu diễn BXH
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

// Di chuyển phải
void MoveRight() {
    if (snake[SIZE_SNAKE - 1].x >= startX+WIDTHCONSOLE-2) {
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

// Di chuyển trái
void MoveLeft() 
{
    if (snake[SIZE_SNAKE - 1].x - 1 == 25 && snake[SIZE_SNAKE - 1].y == 16
        && FOOD_INDEX == 3)
    {
        processGate();
    }
    if (snake[SIZE_SNAKE - 1].x - 1 <= startX) {
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

// Di chuyển xuống
void MoveDown() {
    if (snake[SIZE_SNAKE - 1].y >= HEIGHTCONSOLE+startY-1) {
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

// Di chuyển lên
void MoveUp() {
    if (snake[SIZE_SNAKE - 1].y -1 <= startY) {
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

// Kiểm tra rắn tự ăn mình (Check if snake's head collides with its body)
void ProcessCollision() {
    for (int i = 0; i < SIZE_SNAKE - 1; i++) 
    {
        if (snake[SIZE_SNAKE - 1].x == snake[i].x
            && snake[SIZE_SNAKE - 1].y == snake[i].y)
            ProcessDead();
    }
    if (map[snake[SIZE_SNAKE - 1].y-5][snake[SIZE_SNAKE - 1].x-25] != 0) 
    ProcessDead();
}

// Subfunction for thread
void ThreadFunc() {
    //mới 
    //levels.push_back({ 1, "level1.txt" });
    //levels.push_back({ 2, "level2.txt" });
    //levels.push_back({ 3, "level3.txt" });

    // ...

    // Load bản đồ cho màn chơi đầu tiên
    LoadMap(levels[currentLevel].filename, map);
    char str[256]; 
    DrawMap(map);//moi
    //mới 
    while (1) {
        if (STATE == 1) { // If my snake is alive
            strcpy(str, " ");
            DrawSnake(str);
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
}

// Game mới
void Newgame()
{
    int temp;
    FixConsoleWindow();
    StartGame();
    score = 0;
    GotoXY(10, 6);
    cout << "Score: " << score;
    thread t1(ThreadFunc); // Create thread for snake
    HANDLE handle_t1 = t1.native_handle(); // Take handle of thread
    while (1)
    {
        temp = toupper(getch());
        if (STATE == 1)
        {
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
            else if (temp == 'Q')
            {
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
            if (temp == 'Y')
            {
                deleteAllBox();
                StartGame();
            }
            else if (temp == 'N') {

                SuspendThread(handle_t1);
                mainMenu({ 7,4 }, 12, 20);
            }
        }
    }
}

void printCurrentDateTime(ostream& os) {
    // Lấy thời gian hiện tại
    std::time_t currentTime = std::time(nullptr);

    // Chuyển đổi thời gian hiện tại sang dạng chuỗi
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTime));
    os <<buffer << std::endl;
}

void Resume(string filename)
{
        PlaySound(0, 0, 0);
        int temp;
        FixConsoleWindow();
        ResumeGame(filename);
        deleteAllBox();
        GotoXY(10, 6);
        cout << "Score: " << score;
        DrawFullScoreGraphic(score);
        thread t1(ThreadFunc); // Create thread for snake
        HANDLE handle_t1 = t1.native_handle(); // Take handle of thread
        while (1)
        {
            temp = toupper(getch());
            if (STATE == 1)
            {
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
                else if (temp == 'Q')
                {
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
                if (temp == 'Y')
                {
                    deleteAllBox();
                    StartGame();
                }
                else if (temp == 'N') {

                    SuspendThread(handle_t1);
                    mainMenu({ 7,4 }, 12, 20);
                }
            }
        }
}

void ResumeGame(string filename)
{
    readBinaryFile(filename, snake, SIZE_SNAKE, food, FOOD_INDEX, MOVING, CHAR_LOCK,currentLevel);
    score = SIZE_SNAKE - 6;
    SPEED = OLDSPEED + score / 4;
    POINT pBox{ 25,5 };
    int wBox = 66, hBox = 18;
    setColorText(243);
    DrawFrame(pBox, wBox, hBox);
    STATE = 1;//Start running Thread
}
