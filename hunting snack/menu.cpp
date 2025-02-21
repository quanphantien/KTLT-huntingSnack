#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include "menu.h"
#include "Load.h"
#include "Graphic.h"

int xMenu = 0, yMenu = 0, wMenu = 0, hMenu = 0;
int xBox = 0, yBox = 0, wBox = 0, hBox = 0;

bool music = 1, sfx = 1;

// Gán vị trí, kích thước khung menu
void setMenu(int x, int y, int w, int h) {
    xMenu = x, yMenu = y, wMenu = w, hMenu = h;
}

// Gán vị trí, kích thước khung chính
void setBox(int x, int y, int w, int h) {
    xBox = x, yBox = y, wBox = w, hBox = h;
}

void deleteAllBox()
{
    deleteSmallBox();
    deleteBigBox();
}
void deleteSmallBox()
{
    DeleteBox(xMenu + 1, yMenu + 1, wMenu, hMenu);
}

void deleteBigBox()
{
    DeleteBox(xBox + 1, yBox + 1, wBox, hBox);

}

// Hiển thị tuỳ chọn âm thanh
void displaySounds(int currentSoundSel) {
    int x = 0, y = 0;
    string s1 = " MUSIC: ", s2 = " SOUND EFFECT: ";
    x = xBox + (wBox - s2.size()) / 2;

    // Thẩm mỹ
    GotoXY(x + s1.size(), yBox + hBox / 4); cout << "    ";
    GotoXY(x + s2.size(), yBox + hBox / 2); cout << "    ";

    for (int i = 1; i <= 2; ++i)
    {
        if (currentSoundSel == i) setColorText(243);
        else setColorText(241);
        switch (i)
        {
        case 1:
        {
            y = yBox + hBox / 4;
            GotoXY(x, y);
            if (currentSoundSel == 1) cout << "<MUSIC:>";
            else cout << s1;
            if (music) cout << " ON"; else cout << " OFF";
            break;
        }
        case 2:
            y = yBox + hBox / 2;
            GotoXY(x, y);
            if (currentSoundSel == 2) cout << "<SOUND EFFECT:>";
            else cout << s2;
            if (sfx) cout << " ON"; else cout << " OFF";
            break;
        }
    }

    setColorText(241);
    string s = "Press 'F' to change option";
    x = xBox + (wBox - s.size()) / 2, y = yBox + 3 * hBox / 4;
    GotoXY(x, y);
    cout << s;
}

void soundSettings() {
    int currentSoundSel = 1;

    while (true) {
        displaySounds(currentSoundSel);

        char input = toupper(_getch());
        if (input == 'F') { // Enter key
            // User selected an option
            switch (currentSoundSel) {
            case 1:
                if (sfx) PlaySound(TEXT("snd_select.wav"), NULL, SND_FILENAME | SND_ASYNC);
                if (music == true) music = false;
                else music = true;
                break;
            case 2:
            {
                if (sfx) PlaySound(TEXT("snd_select.wav"), NULL, SND_FILENAME | SND_ASYNC);
                if (sfx == true) sfx = false;
                else sfx = true;
                break;
            }
            }
        }
        else if (input == 'W' && currentSoundSel > 1) {
            if (sfx) PlaySound(TEXT("snd_select.wav"), NULL, SND_FILENAME | SND_ASYNC);
            currentSoundSel--;
        }
        else if (input == 'S' && currentSoundSel < 2) {
            if (sfx) PlaySound(TEXT("snd_select.wav"), NULL, SND_FILENAME | SND_ASYNC);
            currentSoundSel++;
        }
        else if (input == 'A') {
            if (sfx)
            PlaySound(TEXT("snd_select.wav"), NULL, SND_FILENAME | SND_SYNC);
            //isplayBackMenu();
            deleteBigBox();
            if (music) PlaySound(TEXT("checkers.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            return;
        }
    }
}

// Hiển thị chữ trên menu
void displayMenu(int currentSelection, POINT start, int width, int height)
{
    int distance = height / 5;
    POINT position;
    position.x = start.x+2;
    position.y = start.y+2;
    int x; int y = 1;
    //system("cls"); // Clear the console screen (works on Windows)
    for (int i = 1; i <= 5; ++i)
    {
        if (currentSelection == i)
        {
            setColorText(243);
        }
        else
            setColorText(241);
            switch (i)
            {
            case 1:
                if (currentSelection == 1)
                {
                    DeleteBox(25, 1, 70, 4);
                    GotoXY(position.x, position.y);
                    x = 29;
                    cout << "<NEW GAME>";
                    GotoXY(x, y);
                    drawText(x, y,     "▄     ▄");
                    drawText(x, y + 1, "█▀▄   █");
                    drawText(x, y + 2, "█  ▀▄ █");
                    drawText(x, y + 3, "█    ▀█");
                    x += 8;
                    drawText(x, y,     "▄▄▄▄▄▄");
                    drawText(x, y + 1, "█");
                    drawText(x, y + 2, "█▀▀▀▀▀");
                    drawText(x, y + 3, "█▄▄▄▄▄");
                    x += 7;
                    drawText(x, y,     "▄ ▄ ▄ ▄");
                    drawText(x, y + 1, "█ █ █ █");
                    drawText(x, y + 2, " █ █ █");
                    drawText(x, y + 3, "  █ █");
                    x += 15;
                    drawText(x, y,     " ▄■■■▄");
                    drawText(x, y + 1, "█    ");
                    drawText(x, y + 2, "█    ▀█");
                    drawText(x, y + 3, " ▀▄▄▄▀");
                    x += 8;
                    drawText(x, y,     "  ▄▄▄ ");
                    drawText(x, y + 1, "▄▀   ▀▄ ");
                    drawText(x, y + 2, "█▀▀▀▀▀█");
                    drawText(x, y + 3, "█     █");
                    x += 8;
                    drawText(x, y,     "▄     ▄");
                    drawText(x, y + 1, "█▀▄ ▄▀█");
                    drawText(x, y + 2, "█  ▀  █");
                    drawText(x, y + 3, "█     █");
                    x += 8;
                    drawText(x, y,     "▄▄▄▄▄▄");
                    drawText(x, y + 1, "█");
                    drawText(x, y + 2, "█▀▀▀▀▀");
                    drawText(x, y + 3, "█▄▄▄▄▄");
                }
                else
                {
                    GotoXY(position.x, position.y);
                    std::cout << " NEW GAME ";
                }
                break;
            case 2:
                if (currentSelection == 2)
                {
                    x = 38;
                    DeleteBox(25, 1, 70, 4);
                    GotoXY(position.x + 1, position.y);
                    cout << "<RESUME>";
                    drawText(x, y, " ▄▄▄▄▄");
                    drawText(x, y + 1, "█     █");
                    drawText(x, y + 2, "█▀▀▀█▀ ");
                    drawText(x, y + 3, "█    ▀▄");
                    x += 8;
                    drawText(x, y, "▄▄▄▄▄▄");
                    drawText(x, y + 1, "█");
                    drawText(x, y + 2, "█▀▀▀▀▀");
                    drawText(x, y + 3, "█▄▄▄▄▄");
                    x += 6;
                    drawText(x, y, " ▄■■■▄");
                    drawText(x, y + 1, " ▀▄   ");
                    drawText(x, y + 2, "   ▀▀▄");
                    drawText(x, y + 3, " ▀▄▄▄▀");
                    x += 7;
                    drawText(x, y, "▄     ▄");
                    drawText(x, y + 1, "█     █");
                    drawText(x, y + 2, "█     █");
                    drawText(x, y + 3, "▀▄▄▄▄▄▀");
                    x += 8;
                    drawText(x, y, "▄     ▄");
                    drawText(x, y + 1, "█▀▄ ▄▀█");
                    drawText(x, y + 2, "█  ▀  █");
                    drawText(x, y + 3, "█     █");
                    x += 8;
                    drawText(x, y, "▄▄▄▄▄▄");
                    drawText(x, y + 1, "█");
                    drawText(x, y + 2, "█▀▀▀▀▀");
                    drawText(x, y + 3, "█▄▄▄▄▄");
                }
                else
                {
                    GotoXY(position.x + 1, position.y);
                    std::cout << " RESUME ";
                }
                break;
            case 3:
                GotoXY(position.x + 1, position.y);
                if (currentSelection == 3)
                {
                    x = 42;
                    DeleteBox(25, 1, 70, 4);
                    GotoXY(position.x + 1, position.y);
                    cout << "<MUSIC>";
                    drawText(x, y, "▄     ▄");
                    drawText(x, y + 1, "█▀▄ ▄▀█");
                    drawText(x, y + 2, "█  ▀  █");
                    drawText(x, y + 3, "█     █");
                    x += 8;
                    drawText(x, y, "▄     ▄");
                    drawText(x, y + 1, "█     █");
                    drawText(x, y + 2, "█     █");
                    drawText(x, y + 3, "▀▄▄▄▄▄▀");
                    x += 8;
                    drawText(x, y, " ▄■■■▄");
                    drawText(x, y + 1, " ▀▄   ");
                    drawText(x, y + 2, "   ▀▀▄");
                    drawText(x, y + 3, " ▀▄▄▄▀");
                    x += 7;
                    drawText(x, y, "▄▄▄");
                    drawText(x, y + 1, " █");
                    drawText(x, y + 2, " █");
                    drawText(x, y + 3, "▄█▄");
                    x += 5;
                    drawText(x, y, "▄▄▄▄▄");
                    drawText(x, y + 1, "█");
                    drawText(x, y + 2, "█");
                    drawText(x, y + 3, "█▄▄▄▄");
                }
                else
                {
                    GotoXY(position.x + 1, position.y);
                    std::cout << " MUSIC ";
                }
                break;
            case 4:
                GotoXY(position.x + 1, position.y);
                if (currentSelection == 4)
                {
                    x = 47;
                    DeleteBox(25, 1, 70, 4);
                    GotoXY(position.x + 1, position.y);
                    cout << "<HELP>";
                    drawText(x, y, "▄    ▄");
                    drawText(x, y + 1, "█    █");
                    drawText(x, y + 2, "█▀▀▀▀█");
                    drawText(x, y + 3, "█    █");
                    x += 7;
                    drawText(x, y, "▄▄▄▄▄▄");
                    drawText(x, y + 1, "█");
                    drawText(x, y + 2, "█▀▀▀▀▀");
                    drawText(x, y + 3, "█▄▄▄▄▄");
                    x += 7;
                    drawText(x, y, "▄");
                    drawText(x, y + 1, "█");
                    drawText(x, y + 2, "█");
                    drawText(x, y + 3, "█▄▄▄▄▄");
                    x += 7;
                    drawText(x, y, " ▄▄▄▄");
                    drawText(x, y + 1, "█    █");
                    drawText(x, y + 2, "█▀▀▀▀");
                    drawText(x, y + 3, "█");
                }
                else
                {
                    GotoXY(position.x + 1, position.y);
                    std::cout << " HELP ";
                }
                break;
            case 5:
                GotoXY(position.x + 1, position.y);
                if (currentSelection == 5)
                {
                    DeleteBox(25, 1, 70, 4);
                    GotoXY(position.x + 1, position.y);
                    x = 42; y = 1;
                    cout << "<QUIT>";
                    drawText(x, y, " ▄▀▀▀▀▀▄ ");
                    drawText(x, y + 1, "█       █");
                    drawText(x, y + 2, "█     ▄ █");
                    drawText(x, y + 3, " ▀▄▄▄▄▄▀▄");
                    x += 11;
                    drawText(x, y, "█      █");
                    drawText(x, y + 1, "█      █");
                    drawText(x, y + 2, "█      █");
                    drawText(x, y + 3, "▀▄▄▄▄▄▄▀");
                    x += 10;
                    drawText(x, y, "▀█▀");
                    drawText(x, y + 1, " █");
                    drawText(x, y + 2, " █");
                    drawText(x, y + 3, "▄█▄");
                    x += 5;
                    drawText(x, y, "▀▀▀█▀▀▀");
                    drawText(x, y + 1, "   █");
                    drawText(x, y + 2, "   █");
                    drawText(x, y + 3, "   █");
                }
                else
                {
                    GotoXY(position.x + 1, position.y);
                    std::cout << " QUIT ";
                }
                break;
            }
            position.y += distance;
    }
}

// Hiển thị credits
void displayCredits() {
    vector <string> credits = {
        "A C++ game about a very hungry snake...",
        "",
        "",
		"Developed by:",
        "Nguyen Trung Kien",
        "Quan Phan Tien",
        "Nguyen Minh Tri",
        "Nguyen Quoc Trong",
        "Le Dinh Hoang Vu",

    };
    for (int i = 0; i < credits.size(); i++) {
        GotoXY(xBox + (wBox - credits[i].length()) / 2, yBox + hBox / 2 - 6 + i);
        cout << credits[i];
    }
}

// Khởi tạo menu (tham số là vị trí và kích thước của khung menu)
void mainMenu(POINT start, int width, int height,int currentSelection)
{
    // Khung menu (nhỏ)
    POINT pMenu{ 7,4 };
    int wMenu = 12, hMenu = 20;
    setColorText(251);
    DrawFrame(pMenu, wMenu, hMenu);
    //Khung game lớn
    POINT pBox{ 25,5 };
    int wBox = 66, hBox = 18;
    setColorText(243);
    DrawFrame(pBox, wBox, hBox);

    DeleteBox(xBox + 1, yBox + 1, wBox, hBox);
    DeleteBox(xMenu + 1, yMenu + 1, wMenu, hMenu);
    displayCredits();

    if (music) PlaySound(TEXT("checkers.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    int size = height / 5;
    while (true) {
        displayMenu(currentSelection, start, width, height);

        // Get user input
        char input = toupper(_getch());
        if (input == 13) { // Enter key
            // User selected an option
            DeleteBox(xBox + 1, yBox + 1, wBox, hBox);
            switch (currentSelection) {
            case 1:
                if (sfx) PlaySound(TEXT("snd_select.wav"), NULL, SND_FILENAME | SND_SYNC);
                deleteSmallBox();
                Newgame();
                break;
            case 2:
            {
                if (sfx) PlaySound(TEXT("snd_select.wav"), NULL, SND_FILENAME | SND_SYNC);
                if (music) PlaySound(TEXT("hip_shop.wav"), NULL, SND_FILENAME | SND_ASYNC);
                string s = LoadProcess();
                Resume(s);
                displayBackMenu();
                deleteBigBox();
                continue;
            }
            case 3:
            {
                if (sfx) PlaySound(TEXT("snd_select.wav"), NULL, SND_FILENAME | SND_SYNC);
                PlaySound(0, 0, 0);
                soundSettings();
                
                //Xử lý âm lượng nhạc
                //...............
                continue;
            }
            case 4:
            {
                if (sfx) PlaySound(TEXT("snd_select.wav"), NULL, SND_FILENAME | SND_SYNC);
                if (music) PlaySound(TEXT("thrashmachine.wav"), NULL, SND_FILENAME | SND_ASYNC);
                POINT HelpBox = { 27,6 };
                DrawFrame(HelpBox, 62, 15);
                std::vector<std::string> instructions = {
                "                        INSTRUCTION                         ",
                "============================================================",
                " Use 'A' 'S' 'W' 'D' keys to move                        ",
                " Press 'P' to pause                                      ",
                " Press 'Q' to exit                                       ",
                " When you reach the required number of points, enter the  ",
                "gate to pass the level                                      ",
                " The higher the level, the faster the snake's speed will be",
                "                                                            "
                };
                GotoXY(28, 9);
                for (int i = 0; i < instructions.size(); ++i) {
                    GotoXY(HelpBox.x + 2, HelpBox.y + i + 1);
                    std::cout << instructions[i];
                }
                displayBackMenu();
                deleteBigBox();
                if (music) PlaySound(TEXT("checkers.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                continue;
            }
            
            case 5:
            {
                POINT QuitBox = { 43,13 };
                clearFrame(QuitBox, 31, 2);
                DrawFrame(QuitBox, 31, 2);
                std::vector<std::string> quit = {
                "            QUIT?            ",
                "      Y:Yes       N:No       "          
                };
                GotoXY(28, 9);
                for (int i = 0; i < quit.size(); ++i) {
                    GotoXY(QuitBox.x + 2, QuitBox.y + i + 1);
                    std::cout << quit[i];
                }
                while (true) {
                    char backInput = toupper(_getch());
                    if (backInput == 'N') {
                        if (sfx) PlaySound(TEXT("snd_select.wav"), NULL, SND_FILENAME | SND_SYNC);
                        return mainMenu(start, width, height,5);
                    }
                    else if (backInput == 'Y') {
                        if (sfx) PlaySound(TEXT("charjoined.wav"), NULL, SND_FILENAME | SND_SYNC);
                        HWND hwnd = GetConsoleWindow();
                        if (hwnd != NULL) {
                            PostMessage(hwnd, WM_CLOSE, 0, 0);
                        }
                    }
                }                
            }
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

// Hiển thị tuỳ chọn "quay trở về menu"
void displayBackMenu()
{
    //string s = "Press '<-' to return to menu";
    //int x = xBox + (wBox - s.size()) / 2, y = yBox + 3 * hBox / 4;
    //GotoXY(x, y);
    //cout << s;
    while (true) {
        char backInput = toupper(_getch());
        if (backInput == 'A') {
            if (sfx) PlaySound(TEXT("snd_select.wav"), NULL, SND_FILENAME | SND_SYNC);
            break;
        }
    }
}



// CÁI MỚI

// Gán vị trí, kích thước khung menu
void setMenuFrameSize(int xFrame2, int yFrame2, int wFrame2, int hFrame2) {
    xMenu = xFrame2, yMenu = yFrame2, wMenu = wFrame2, hMenu = hFrame2;
}

void displayMenu_new(int currentSelection) {
    string m[5] = { "NEW GAME","LOAD GAME", "MUSIC","HELP","QUIT" };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < 5; i++) {
        SetConsoleTextAttribute(hConsole, 240);
        if (i == currentSelection) SetConsoleTextAttribute(hConsole, 31);
        GotoXY(xMenu + (wMenu - m[i].size()) / 2, yMenu + 3 + i * 3);
        cout << m[i];
    }
}

// Khởi tạo menu
//void mainMenu_new()
//{
//    FixConsoleWindow();
//
//    int currentSelection = 0;
//    while (true) {
//        displayMenu_new(currentSelection);
//        // Cho người dùng nhập
//        char input = toupper(_getch());
//        if (input == 13) 
//        { // 13 = phím Enter
//            int y = HEIGH_CONSOLE / 2;
//
//            switch (currentSelection) {
//            case 0:
//            {
//                Newgame();
//                break;
//            }
//            case 1:
//            {
//                string s = "LOAD GAME....(COMING SOON)";
//                int x = (WIDTH_CONSOLE - s.size()) / 2;
//                GotoXY(x, y);
//                std::cout << s << std::endl;
//                displayBackMenu(x, y, start, width, height);
//                break;
//            }
//            case 2:
//            {
//                string s = "SETTING MUSIC...(COMING SOON)";
//                int x = (WIDTH_CONSOLE - s.size()) / 2;
//                GotoXY(x, y);
//                std::cout << s << std::endl;
//                displayBackMenu(x, y + 1);
//                //Xử lý âm lượng nhạc
//                //...............
//                break;
//            }
//            case 3:
//            {
//                POINT HelpBox = { 27,8 };
//                DrawFrame(HelpBox, 63, 15);
//                std::vector<std::string> instructions = {
//                "                        INSTRUCTION                         ",
//                "============================================================",
//                " 1. Use 'A' 'S' 'W' 'D' keys to move                        ",
//                " 2. Press 'P' to pause                                      ",
//                " 3. Press 'Q' to exit                                       ",
//                " 4.When you reach the required number of points, enter the  ",
//                "gate to pass the level                                      ",
//                " 5.The higher the level, the faster the snake's speed will be",
//                "                                                            ",
//                "              Press 'Enter' to return to menu               "
//                };
//                GotoXY(28, 9);
//                for (int i = 0; i < instructions.size(); ++i) {
//                    GotoXY(HelpBox.x + 2, HelpBox.y + i + 1);
//                    std::cout << instructions[i];
//                }
//                
//                break;
//            }
//            case 4:
//            {
//                system("cls");
//                std::cout << "See you soon!" << std::endl;
//                exit(0);
//            }
//            }
//        }
//        else if (input == 'W' && currentSelection > 0) { // Arrow up key
//            currentSelection--;
//        }
//        else if (input == 'S' && currentSelection < 4) { // Arrow down key
//            currentSelection++;
//        }
//    }
//}
//
//void displayBackMenu(int x, int y, POINT start, int width, int height)
//{
//    GotoXY(x, y);
//    cout << "Press 'Enter' to return to menu";
//    while (true) {
//        char backInput = toupper(_getch());
//        if (backInput == 13) return mainMenu(start, width, height);
//    }
//}
//
//void clearSmallFrame()
//{
//    clearRectangle(8, 5, 12, 19);
//}