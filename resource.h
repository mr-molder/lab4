//
// Created by molder on 11/29/22.
//

#ifndef PETERTOWN_RESOURCE_H
#define PETERTOWN_RESOURCE_H

#include <fstream>

class Colony;

class Resource {
private:
    int type = 0;
    int quantity = 1000;
    int x = 0;
    int y = 0;
    Colony* owner = nullptr;
public:
    void setOwner(Colony *owner);
    enum Type{FOOD = 0, ACID, SALT};
public:
    Colony *getOwner() const;

public:
    Resource() {};
    Resource(int _type, int _x, int _y): type(_type), quantity(1000), x(_x), y(_y) {};
    Resource(int _type, int _quantity, int _x, int _y): type(_type), quantity(_quantity), x(_x), y(_y) {};

    void setType(int _type) {type = _type;};
    int getType() {return type;};

    const char * getSymbol();

    int get_resource();

    int getX() {return x;};
    int getY() {return y;};
    bool notEmpty() {return quantity > 0;};

    void writeToFile(std::ofstream &file);
    static Resource readFromFile(std::ifstream & file);
};
#include "colony.h"
#endif //PETERTOWN_RESOURCE_H
