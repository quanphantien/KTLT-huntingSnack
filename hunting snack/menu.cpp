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

void displayMenu(int currentSelection) {
    system("cls"); // Clear the console screen (works on Windows)
    GotoXY(2, 3);
    for (int i = 1; i <= 5; ++i) {
        if (i == currentSelection) {
            std::cout << "-> ";
        }
        std::cout << i << ". ";
        switch (i) {
        case 1:
            std::cout << "New game";
            break;
        case 2:
            std::cout << "Resume";
            break;
        case 3:
            std::cout << "Music";
            break;
        case 4:
            std::cout << "Help";
            break;
        case 5:
            std::cout << "Quit";
            break;
        }
        std::cout << std::endl;
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