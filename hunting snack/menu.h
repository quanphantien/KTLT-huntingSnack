#pragma once

#include "base.h"
#include "Console.h"
#include "Graphic.h"
#include <conio.h>
#include <iostream>
#include <thread>
#include <vector>
#include <Windows.h>

using namespace std;

// Vị trí, kích thước của khung menu
extern int xMenu, yMenu, wMenu, hMenu;

// Vị trí, kích thước của khung chính;
extern int xBox, yBox, wBox, hBox;

// Biến âm thanh
extern bool music, sfx;

void setMenu(int x, int y, int w, int h);
void setBox(int x, int y, int w, int h);

void displaySounds(int currentSoundSel);
void soundSettings();

void displayMenu(int currentSelection, POINT, int width, int height);
void mainMenu(POINT,int,int,int =1);
void displayBackMenu();

void displayCredits();

// CÁI MỚI
void displayBackMenu(int x, int y, POINT start, int width, int height);
void mainMenu_new();
void displayMenu_new(int currentSelection);

void deleteAllBox();
void deleteSmallBox();
void deleteBigBox();