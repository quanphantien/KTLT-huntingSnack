#include <Windows.h>

#pragma once

#include <iostream>
#include <vector>
#include "Graphic.h"
#include "base.h"
#include "Console.h"

using namespace std;

void DrawFrame(POINT start, int width, int height, vector<string> typebox = { "╔" ,"║" ,"╚" ,"═" ,"╝","╗" }); //Vẽ khung, truyền vào start là vị trí bắt đầu của khung, width: độ rộng khung, height: chiều cao khung
