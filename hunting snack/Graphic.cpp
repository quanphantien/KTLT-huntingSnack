#include <iostream>
#include "Graphic.h"
#include "base.h"
#include "Console.h"

using namespace std;


void DrawFrame(POINT start, int width,int height)
{
	FixConsoleWindow();
	int i = 0;
	GotoXY(start.x, 0);
	cout << "╔"<<endl;
	for (i = 0; i < height-1; i++)
	{
		GotoXY(start.x, i + 1);
		std::cout << "║" << endl;
	}
	GotoXY(start.x, i+1);
	cout << "╚";
	GotoXY(start.x+1, 0);
	for (i = 0; i < width-start.x-1; i++)
		std::cout << "═";
	cout << "╗" << endl;
	for (i = 0; i < height; i++)
	{
		GotoXY(width,i+1);
		std::cout << "║" << endl;
	}
	GotoXY(start.x+1, i);
	for (i = 0; i < width - start.x - 1; i++)
		std::cout << "═";
	cout << "╝";
}