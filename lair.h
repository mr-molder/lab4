//
// Created by molder on 12/3/22.
//

#ifndef PETERTOWN_LAIR_H
#define PETERTOWN_LAIR_H

#include <fstream>

#include "vector.h"


class Unit;

class Lair {
private:
    int x;
    int y;
    int health;
public:
    struct Larva {
        int time_left;
        Unit* unit;

        void writeToFile(std::ofstream & file);
        static Larva readFromFile(std::ifstream & file);
    };
    struct AvailableUnit {
        int food_required;
        int acid_required;
        int salt_required;
        int time;
        Unit* unit;
    };
    Vector<Larva> larvae;
public:
    const Vector<Larva> &getLarvae() const;

private:
    Vector<AvailableUnit> available_units;
public:
    Lair(): x(0), y(0), health(3) {};
    Lair(int _x, int _y): x(_x), y(_y), health(3) {};

    int getLairX() {return x;};
    int getLairY() {return y;};
    void damage(int dmg) {health -= dmg;};
    bool isAlive() {return health > 0;};
    void enqueue(Unit* unit) {larvae.push_back({5, unit});};
    void tick();

    void writeToFile(std::ofstream & file);
    void readFromFile(std::ifstream & file);


};
#include "unit.h"

#endif //PETERTOWN_LAIR_H
