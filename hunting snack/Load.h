#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "base.h"

using namespace std;

struct Saver
{
	string name;
	int score;
	string date;
};

void readBinaryFile(const std::string& filename, POINT snake[], int& snakeLength, POINT food[], int& foodIndex, int& MOVING, int& CHAR_LOCK, int& currentLevel);

std::vector<Saver> readTextFile(const std::string& filename);

void print(vector<Saver>);

string LoadProcess();

void loadVectorFromFile(std::vector<Saver>& vec, const std::string& filename);