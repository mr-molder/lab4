//
// Created by molder on 12/11/22.
//

#ifndef PETERTOWN_PATHFINDER_H
#define PETERTOWN_PATHFINDER_H

#include "vector.h"


class Level;

class Pathfinder {

private:
    Vector<bool> cells;
    int width = 0;
    int height = 0;
    bool get(int x, int y);
    void set(int x, int y, bool val);
public:
    Pathfinder() {};
    void update(Level& level);
    bool isValidCell(int x, int y);
    void updateUnit(int old_x, int old_y, int new_x, int new_y);
};

#endif //PETERTOWN_PATHFINDER_H
