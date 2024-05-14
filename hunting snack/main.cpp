#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include "base.h"
#include "menu.h"
#include "Graphic.h"
#include "conio.h"
#include "Console.h"

using namespace std; 

// main function
void main() {
    system("color E0");
    setConsoleSize(115, 30);
    ShowConsoleCursor(false);
    DrawFrame({3,0},112,28);

    getch();
    //mainMenu();

}