//
// Created by vova0 on 26.11.2022.
//

#ifndef PETERTOWN_LEVEL_H
#define PETERTOWN_LEVEL_H

class Level{
private:
    int width;
    int height;
    Field field;
public:
    int getWidth();
    int getHeight();
    void setWidth();
    void setHeight();
};

#endif //PETERTOWN_LEVEL_H
