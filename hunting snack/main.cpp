#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include "Animation.h"
#include "base.h"
#include "Console.h"
#include "Graphic.h"
#include "menu.h"
#include <mmstream.h>
#include "Load.h"

#pragma comment(lib,"winmm.lib")

using namespace std; 

// Hàm main
void main() {
    SetConsoleOutputCP(CP_UTF8);
    system("color F0");
    vector<string> box1(6, "█");
    setConsoleSize(100, 30);
    FixConsoleWindow();
    ShowConsoleCursor(false);

    // Khung bao quát
    POINT pBase{ 3,0 };
    int wBase = 93, hBase = 27;
    setColorText(254);
    DrawFrame(pBase, wBase, hBase);

    setColorText(200);
    int x = 18, y = 5;
    system("color B0");
    //In chữ Snake mở đầu
    drawText(x, y, "██████████");
    drawText(x, y + 1, "██");
    drawText(x, y + 2, "██");
    drawText(x, y + 3, "██");
    drawText(x, y + 4, "██████████");
    drawText(x, y + 5, "        ██");
    drawText(x, y + 6, "        ██");
    drawText(x, y + 7, "        ██");
    drawText(x, y + 8, "██████████");
    // Vẽ chữ "N"               
    x += 12; // Khoảng cách giữa các chữ
    drawText(x, y, "██      ██");
    drawText(x, y + 1, "███     ██");
    drawText(x, y + 2, "██ ██   ██");
    drawText(x, y + 3, "██  ██  ██");
    drawText(x, y + 4, "██   ██ ██");
    drawText(x, y + 5, "██    ████");
    drawText(x, y + 6, "██     ███");
    drawText(x, y + 7, "██      ██");
    drawText(x, y + 8, "██       █");

    // Vẽ chữ "A"
    x += 10; // Khoảng cách giữa các chữ
    drawText(x, y, "      ███████");
    drawText(x, y + 1, "     ██     ██");
    drawText(x, y + 2, "    ██      ██");
    drawText(x, y + 3, "   ██       ██");
    drawText(x, y + 4, "  ██        ██");
    drawText(x, y + 5, " █████████████");
    drawText(x, y + 6, " ██         ██ ");
    drawText(x, y + 7, " ██         ██  ");
    drawText(x, y + 8, " ██         ██   ");

    // Vẽ chữ "K"
    x += 16; // Khoảng cách giữa các chữ
    drawText(x, y, "██       ███");
    drawText(x, y + 1, "██     ███ ");
    drawText(x, y + 2, "██   ███  ");
    drawText(x, y + 3, "██ ███   ");
    drawText(x, y + 4, "████    ");
    drawText(x, y + 5, "██ ███   ");
    drawText(x, y + 6, "██   ███  ");
    drawText(x, y + 7, "██     ███  ");
    drawText(x, y + 8, "██       ███");

    // Vẽ chữ "E"
    x += 13; // Khoảng cách giữa các chữ
    drawText(x, y, "█████████████");
    drawText(x, y + 1, "██");
    drawText(x, y + 2, "██");
    drawText(x, y + 3, "██");
    drawText(x, y + 4, "█████████████");
    drawText(x, y + 5, "██              ");
    drawText(x, y + 6, "██              ");
    drawText(x, y + 7, "██");
    drawText(x, y + 8, "█████████████");

    GotoXY(38, 25);
    cout << "PRESS ENTER TO CONTINUE";
    char input = toupper(_getch());
    system("color F0");
    while (input != 13) input = toupper(_getch());
    GotoXY(38, 25);
    cout << "                        ";
    DeleteBox(5, 1, 70, 20);

    // Khung menu (nhỏ)
    POINT pMenu{ 7,4 };
    int wMenu = 12, hMenu = 20;
    setColorText(251);
    DrawFrame(pMenu, wMenu, hMenu);

    // Khung game (lớn)
    POINT pBox{ 25,5 };
    int wBox = 66, hBox = 18;
    setColorText(243);
    DrawFrame(pBox, wBox, hBox);

    setMenu(pMenu.x, pMenu.y, wMenu, hMenu);
    setBox(pBox.x, pBox.y, wBox, hBox);
    // Vẽ menu và bắt đầu chạy chương trình
    mainMenu({ 7,4 }, 12, 20);

}