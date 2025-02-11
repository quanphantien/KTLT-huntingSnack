#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Load.h"

void writeBinaryFile(const std::string& filename, POINT snake[], int snakeLength, POINT food[], int foodIndex, int MOVING, int CHAR_LOCK, int currentLevel);

void saveVectorToFile(const std::vector<Saver>& vec, const std::string& filename);
