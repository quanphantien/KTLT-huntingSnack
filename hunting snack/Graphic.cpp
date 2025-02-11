#include <iostream>
#include <vector>
#include "Graphic.h"
#include "base.h"


using namespace std;

// Chỉnh màu văn bản
void setColorText(int n)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, n);
}

// Vẽ khung, truyền vào start là vị trí bắt đầu của khung, width: độ rộng khung, height: chiều cao khung
// Lưu ý: width và height bị vẽ dư 2 đơn vị
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

// Xoá bảng chữ nhật 3
void clearFrame(POINT start, int width, int height) {
	for (int i = 0; i < height + 2; ++i) {
		GotoXY(start.x, start.y + i);
		for (int j = 0; j < width + 2; ++j) {
			std::cout << " ";
		}
	}
}

void drawGate()
{
	GotoXY(25, 15);
	setColorText(252);
	cout << u8"╔═╣";
	GotoXY(25, 17);
	cout << u8"╚═╣";
	setColorText(251);
	GotoXY(25, 16);
	cout << u8"○";
}

void drawText(int x, int y, const string& text) {
	// Di chuyển con trỏ đến vị trí cần vẽ chữ
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

	// In ra chuỗi text
	cout << text;
}

void drawIntroFrame(POINT p, int w, int h, const string& logo, const string& title) {
	setColorText(254); // Màu sắc khung intro
	DrawFrame(p, w, h); // Vẽ khung intro

	// Vẽ logo game
	int logoX = p.x + (w / 2 - logo.length() / 2); // Tính toán vị trí logo theo tâm khung
	int logoY = p.y + h / 3; // Vị trí logo cách đỉnh khung 1/3 chiều cao
	setColorText(251); // Màu sắc logo
	drawText(logoX, logoY, logo); // Vẽ logo

	// Vẽ tên game
	int titleX = p.x + (w / 2 - title.length() / 2); // Tính toán vị trí tên game theo tâm khung
	int titleY = logoY + 4; // Vị trí tên game cách logo 4 dòng
	setColorText(243); // Màu sắc tên game
	drawText(titleX, titleY, title); // Vẽ tên game
}