#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "base.h"
#include "Load.h"
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

void readBinaryFile(const std::string& filename, POINT snake[], int& snakeLength, POINT food[], int& foodIndex, int& MOVING, int& CHAR_LOCK,int& currentLevel) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    // Đọc độ dài mảng snake
    inFile.read(reinterpret_cast<char*>(&snakeLength), sizeof(snakeLength));

    // Đọc mảng snake
    inFile.read(reinterpret_cast<char*>(snake), sizeof(POINT) * snakeLength);

    // Đọc mảng food
    inFile.read(reinterpret_cast<char*>(food), sizeof(POINT) * 4);

    // Đọc foodIndex
    inFile.read(reinterpret_cast<char*>(&foodIndex), sizeof(foodIndex));

    // Đọc MOVING
    inFile.read(reinterpret_cast<char*>(&MOVING), sizeof(MOVING));

    // Đọc CHAR_LOCK
    inFile.read(reinterpret_cast<char*>(&CHAR_LOCK), sizeof(CHAR_LOCK));

    inFile.read(reinterpret_cast<char*>(&currentLevel), sizeof(int));

    inFile.close();
}

std::vector<Saver> readTextFile(const std::string& filename) {
    std::vector<Saver> data;
    string s;
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return data; // Trả về vector rỗng nếu không thể mở file
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        Saver saver;
        std::getline(iss, saver.name, ',');
        iss >> saver.score;
        std::getline(iss, s, ',');
        std::getline(iss,saver.date);
        data.push_back(saver);
    }
    inFile.close();
    return data;
}

void print(vector<Saver> list,int current)
{
    GotoXY(startX + 2, startY + 2);
    setColorText(244);
    cout << setw(14) << "NAME" << setw(10) << "SCORE" << setw(30) << "DATE";
    for (int i = 0; i < list.size(); ++i)
    {
        if (current == i)
        {
            setColorText(243);
        }
        else
            setColorText(241);
        GotoXY(startX + 2, startY + i + 3);
        cout<< setw(14) << list[i].name << setw(10) << list[i].score <<setw(30) << list[i].date << endl;
    }
}
string menuLoad(vector<Saver> list)
{
    int current = 0;
    while (true) 
    {
        print(list, current);
        // Get user input
        char input = toupper(_getch());
        if (input == 13)
        {
            return list[current].name + ".bin";
        }
        else if (input == 'W' && current > 0) 
        {
            current--;
        }
        else if (input == 'S' && current < list.size()-1) 
        {
            current++;
        }
        else if (input == 'A')
        {
            if (sfx) PlaySound(TEXT("snd_select.wav"), NULL, SND_FILENAME | SND_SYNC);
            mainMenu({ 7,4 }, 12, 20, 2);
        }
    }

}

string LoadProcess()
{
    int current = 1;
    vector<Saver> s;
    loadVectorFromFile(s, ".\\Data\\username.bin");
    return menuLoad(s);
}

void loadVectorFromFile(std::vector<Saver>& vec, const std::string& filename) 
{
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile.is_open()) {
        return;
    }

    // Đọc kích thước vector trước
    size_t size;
    inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
    if (!inFile) {
        std::cerr << "Lỗi khi đọc kích thước từ tệp: " << filename << std::endl;
        return;
    }

    // Thay đổi kích thước vector
    vec.resize(size);

    for (size_t i = 0; i < size; ++i) {
        size_t nameLength, dateLength;

        // Đọc độ dài của name
        inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        if (!inFile) {
            std::cerr << "Lỗi khi đọc độ dài của name từ tệp: " << filename << std::endl;
            vec.clear();
            return;
        }

        // Đọc name
        vec[i].name.resize(nameLength);
        inFile.read(&vec[i].name[0], nameLength);
        if (!inFile) {
            std::cerr << "Lỗi khi đọc name từ tệp: " << filename << std::endl;
            vec.clear();
            return;
        }

        // Đọc score
        inFile.read(reinterpret_cast<char*>(&vec[i].score), sizeof(vec[i].score));
        if (!inFile) {
            std::cerr << "Lỗi khi đọc score từ tệp: " << filename << std::endl;
            vec.clear();
            return;
        }

        // Đọc độ dài của date
        inFile.read(reinterpret_cast<char*>(&dateLength), sizeof(dateLength));
        if (!inFile) {
            std::cerr << "Lỗi khi đọc độ dài của date từ tệp: " << filename << std::endl;
            vec.clear();
            return;
        }

        // Đọc date
        vec[i].date.resize(dateLength);
        inFile.read(&vec[i].date[0], dateLength);
        if (!inFile) {
            std::cerr << "Lỗi khi đọc date từ tệp: " << filename << std::endl;
            vec.clear();
            return;
        }
    }

    inFile.close();
}
