#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include "base.h"
#include "menu.h"
#include "Graphic.h"
#include "conio.h"
#include "Console.h"
#include <vector>

using namespace std; 

// main function
void main() {
    system("color F0");
    vector<string> box1(6, "█");
    setConsoleSize(100, 30);
    FixConsoleWindow();
    ShowConsoleCursor(false);
    DrawFrame({3,0},93,27);
    DrawFrame({ 7,7 }, 15, 17);
    DrawFrame({ 25,7 }, 66, 17);
    mainMenu();

}