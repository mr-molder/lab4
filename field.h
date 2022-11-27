//
// Created by vova0 on 26.11.2022.
//

#ifndef PETERTOWN_FIELD_H
#define PETERTOWN_FIELD_H

class Field {
private:
    int width;
    int height;
    Vector<int> cells;
public:
    int getWidth();
    int getHeight();
    void setWidth();
    void setHeight();
    int getCellType();
    int setCellType();
};

#endif //PETERTOWN_FIELD_H
