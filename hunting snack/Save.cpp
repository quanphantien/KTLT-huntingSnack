#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>
#include "Save.h"

using namespace std;

// Hàm ghi dữ liệu vào file nhị phân
void writeBinaryFile(const std::string& filename, POINT snake[], int snakeLength, POINT food[], int foodIndex, int MOVING, int CHAR_LOCK,int currentLevel) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    // Ghi độ dài mảng snake
    outFile.write(reinterpret_cast<const char*>(&snakeLength), sizeof(snakeLength));

    // Ghi mảng snake
    outFile.write(reinterpret_cast<const char*>(snake), sizeof(POINT) * snakeLength);

    // Ghi mảng food
    outFile.write(reinterpret_cast<const char*>(food), sizeof(POINT) * 4);

    // Ghi foodIndex
    outFile.write(reinterpret_cast<const char*>(&foodIndex), sizeof(foodIndex));

    // Ghi MOVING
    outFile.write(reinterpret_cast<const char*>(&MOVING), sizeof(MOVING));

    // Ghi CHAR_LOCK
    outFile.write(reinterpret_cast<const char*>(&CHAR_LOCK), sizeof(CHAR_LOCK));

    outFile.write(reinterpret_cast<const char*>(&currentLevel), sizeof(int));
    outFile.close();
}

void saveVectorToFile(const std::vector<Saver>& vec, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        return;
    }

    // Lưu kích thước vector
    size_t size = vec.size();
    outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

    for (const auto& saver : vec) {
        // Lưu độ dài và nội dung của name
        size_t nameLength = saver.name.size();
        outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        outFile.write(saver.name.data(), nameLength);

        // Lưu score
        outFile.write(reinterpret_cast<const char*>(&saver.score), sizeof(saver.score));

        // Lưu độ dài và nội dung của date
        size_t dateLength = saver.date.size();
        outFile.write(reinterpret_cast<const char*>(&dateLength), sizeof(dateLength));
        outFile.write(saver.date.data(), dateLength);
   
    }

    outFile.close();
}