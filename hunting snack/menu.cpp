#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <thread>
#include "base.h"
#include "menu.h"
#include "Console.h"
#include <vector>

using namespace std;


void displayMenu(int currentSelection) 
{

    //system("cls"); // Clear the console screen (works on Windows)
    GotoXY(11, 9);
    for (int i = 1; i <= 5; ++i)
    {
            switch (i)
            {
            case 1:
                std::cout << "NEW GAME";
                break;
            case 2:
                std::cout << "RESUME";
                break;
            case 3:
                std::cout << "MUSIC";
                break;
            case 4:
                std::cout << "HELP";
                break;
            case 5:
                std::cout << "QUIT";
                break;
            }
            GotoXY(11, 9 + i);
    }

}

void mainMenu()
{
    int currentSelection = 1;
    while (true) {
        displayMenu(currentSelection);

        // Get user input
        char input = toupper(_getch());
        if (input == 13) { // Enter key
            // User selected an option
            switch (currentSelection) {
            case 1:
                Newgame();
                break;
            case 2:
                std::cout << "LOAD GAME....(COMING SOON)" << std::endl;
                displayBackMenu();
                
                break;
            case 3:
                std::cout << "SETTING MUSIC...(COMING SOON)" << std::endl;
                displayBackMenu();
                //Xử lý âm lượng nhạc
                //...............
                break;
            case 4:
            {
                std::vector<std::string> instructions = {
                "Instruction:",
                "1. Use A S W D keys to move",
                "2. Press 'P' to pause",
                "3. Press 'Q' to exit",
                "Press 'Enter' to return to menu"
                    };
                int boxWidth = 50;
                int boxHeight = 10;
                drawHelpBox(boxWidth, boxHeight, instructions);
                cout << "\n";

                displayBackMenu();
                break;
            }
            
            case 5:
                std::cout << "Exiting program..." << std::endl;
                exit(0);
            }
            break;
        }
        else if (input == 'W' && currentSelection > 1) { 
            currentSelection--;
        }
        else if (input == 'S' && currentSelection < 5) {
            currentSelection++;
        }
    }
}

void displayBackMenu()
{
        cout << "-> ";
        cout<<"Back to the menu";
        int input = _getch();
        if (input == 13)
            mainMenu();
}