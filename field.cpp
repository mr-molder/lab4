//
// Created by molder on 11/28/22.
//

#include "field.h"
#include <iostream>

int Field::getCellKind(int x, int y) {
    return cells[x + y * width];
}

void Field::setCellKind(int x, int y, int kind) {
    cells[x + y * width] = kind;
}

void Field::resize(int new_width, int new_height) {
    Field new_field(new_width, new_height);
    for (int y = 0; y < std::min(height, new_height); ++y) {
        for (int x = 0; x < std::min(width, new_width); ++x) {
            new_field.setCellKind(x, y, getCellKind(x, y));
        }
    }
    *this = new_field;
}

char Field::getSymbol(int x, int y) {
    const char kinds[] = {'.', '~'};
    return kinds[getCellKind(x, y)];
}

const char *Field::getBackground(int x, int y) {
    static const char* bg[] = {"\033[48;2;50;100;0m", "\033[48;2;100;100;100m"};
    return bg[getCellKind(x, y)];
}

void Field::writeToFile(std::ofstream &file) {
    static const char types[] = {'.', '^'};
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            file << types[getCellKind(x, y)];
        }
        file << std::endl;
    }
}

void Field::readFromFile(std::ifstream &file) {
    static const char types[] = {'.', '^'};
    char cell;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            file >> cell;
            setCellKind(x, y, (cell == types[1]) ? 1 : 0);
        }
    }
}
