//
// Created by vova0 on 26.11.2022.
//

#ifndef PETERTOWN_FIELD_H
#define PETERTOWN_FIELD_H

#include <fstream>

#include "vector.h"

class Field {
private:
    int width;
    int height;
    Vector<int> cells;
public:
    Field(int _width, int _height): width(_width), height(_height), cells(_width * _height) {
        for (int i = 0; i < width * height; ++i) {
            cells.push_back(0);
        }
    };

    int getWidth() {return width;};
    int getHeight() {return height;};

    void resize(int new_width, int new_height);

    int getCellKind(int x, int y);
    void setCellKind(int x, int y, int kind); //0 = desert, 1 = lava

    char getSymbol(int x, int y);
    const char* getBackground(int x, int y);

    void writeToFile(std::ofstream & file);
    void readFromFile(std::ifstream & file);
};

#endif //PETERTOWN_FIELD_H
