//
// Created by molder on 12/11/22.
//


#include "pathfinder.h"
#include "level.h"

bool Pathfinder::get(int x, int y) {
    return cells[x + y * width];
}

void Pathfinder::set(int x, int y, bool val) {
    cells[x + y * width] = val;
}

void Pathfinder::update(Level &level) {
    if (width != level.getWidth() || height != level.getHeight()) {
        width = level.getWidth();
        height = level.getHeight();
        cells.resize(width * height);
    }
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            set(x, y, level.isCellEmpty(x, y)); // true == void, false == obstacle;
        }
    }
}

bool Pathfinder::isValidCell(int x, int y) {
    if (x < 0 || x >= width || y < 0|| y >= height) {
        return false;
    }
    return get(x, y);
}

void Pathfinder::updateUnit(int old_x, int old_y, int new_x, int new_y) {
    set(old_x, old_y, true);
    set(new_x, new_y, false);
}

