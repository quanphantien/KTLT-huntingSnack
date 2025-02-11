#pragma once

#include "base.h"
#include "Console.h"
#include <conio.h>
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

void setColorText(int n);
void DrawFrame(POINT start, int width, int height, vector<string> typebox = { "╔" ,"║" ,"╚" ,"═" ,"╝","╗" });
void drawGate();
void clearFrame(POINT start, int width, int height);
void drawText(int x, int y, const string& text);
void drawIntroFrame(POINT p, int w, int h, const string& logo, const string& title);