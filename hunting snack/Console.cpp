#include "Console.h"

// Thiết lập độ lớn màn hình
void setConsoleSize(int columns, int rows) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD size = { columns, rows };
	SMALL_RECT rect = { 0, 0, columns - 1, rows - 1 };

	SetConsoleScreenBufferSize(console, size);
	SetConsoleWindowInfo(console, TRUE, &rect);
}

// Di chuyển con trỏ đến vị trí (x;y)
void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Sửa kích thước cửa sổ (?)
void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

// Hiện / ẩn con trỏ chuột
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

// Xoá bảng chữ nhật 2
void clearRectangle(int x, int y, int width, int height) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	DWORD charsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD consoleSize;

	// Lấy thông tin màn hình console
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return;
	}

	for (int i = 0; i < height; ++i) {
		coord.X = x;
		coord.Y = y + i;
		consoleSize = width;
		FillConsoleOutputCharacter(hConsole, (TCHAR)' ', consoleSize, coord, &charsWritten);
		FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, coord, &charsWritten);
	}
}