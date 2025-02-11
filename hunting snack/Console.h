#pragma once

#include <Windows.h>

void setConsoleSize(int columns, int rows);
void GotoXY(int x, int y);
void FixConsoleWindow();
void ShowConsoleCursor(bool showFlag);
void clearRectangle(int x, int y, int width, int height);