#include <iostream>
#include <vector>
#include "Graphic.h"
#include "base.h"
#include "Console.h"

using namespace std;


void DrawFrame(POINT start, int width,int height,vector<string> typebox)
{
	int i = 0;
	GotoXY(start.x, start.y);
	cout << typebox[0]<<endl;
	for (i = start.y; i < height+start.y; i++)
	{
		GotoXY(start.x, i + 1);
		std::cout << typebox[1] << endl;
	}
	GotoXY(start.x, i+1);
	cout << typebox[2];
	GotoXY(start.x+1, start.y);
	for (i = 0; i < width; i++)
		std::cout << typebox[3];
	cout << typebox[5];
	GotoXY(start.x + 1, start.y+height+1);
	for (i = 0; i < width; i++)
		std::cout << typebox[3];
	cout << typebox[4] << endl;
	for (i = start.y; i < height + start.y; i++)
	{
		GotoXY(start.x+1+width,i+1);
		std::cout << typebox[1] << endl;
	}
	
}