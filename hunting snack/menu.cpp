#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "base.h"
#include "menu.h"
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
                string filename;
                cin >> filename;
                loadPlayerData(filename);
            }
            else if (temp == 'T') {
                string filename;
                cin >> filename;
                savePlayerData(filename, a);
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
   /* std::cout << "1. Categories" << std::endl;
    std::cout << "2. Products" << std::endl;
    std::cout << "3. Orders" << std::endl;
    std::cout << "4. Report" << std::endl;
    std::cout << "5. Quit" << std::endl;*/

    // Highlight the current selection
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
                std::cout << "HELP...(COMING SOON)" << std::endl;
                //Thêm hướng dẫn chơi...

                displayBackMenu();
                break;
            case 5:
                std::cout << "Exiting program..." << std::endl;
                exit(0);
            }
            break;
        }
        else if (input == 'W' && currentSelection > 1) { // Arrow up key
            currentSelection--;
        }
        else if (input == 'S' && currentSelection < 5) { // Arrow down key
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

