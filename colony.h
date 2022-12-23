//
// Created by molder on 12/3/22.
//

#ifndef PETERTOWN_COLONY_H
#define PETERTOWN_COLONY_H

#include "lair.h"
#include "level.h"
#include "unit.h"
#include "resource.h"
#include "controller.h"

class Controller;
class Resource;
class Unit;
class Level;
class Lair;

class Colony {
private:
    int id;
public:
    int getId() const;
    void spawnUnit(Unit* unit);
private:
    Level *level;
    Lair lair;
    Controller* controller;
public:
    Controller *getController() const;

    void setController(Controller *controller);
    void spawnTick();
public:
    Lair &getLair();

private:
    Vector<Unit *> units;
public:
    const Vector<Unit *> &getUnits() const;

private:

    int food;
public:
    int getFood() const;

    int getAcid() const;

    int getSalt() const;


private:
    int acid;
    int salt;

//    int acidPerTick();
//    int saltPerTick();
public:
    Colony() : id(0), food(0), acid(0), salt(0) {};

    Colony(int _id, int _x, int _y, Level *_level);

    const char *getSymbol();

    int getLairX();

    int getLairY();

    bool isEmpty(int x, int y);

    template<typename U>
    void createUnit();

    void cleanUp();

    void takeResource(Resource &res);

    const char* getResourceBackground();

    void writeToFile(std::ofstream & file);
    void readFromFile(std::ifstream & file);
};

template<typename U>
void Colony::createUnit() {
    Unit * unit = new U(this);
    if(getSalt() < unit->getSaltCost() || getFood() < unit->getFoodCost() || getAcid() < unit->getAcidCost()) {
        delete unit;
        return;
    }
    food -= unit->getFoodCost();
    salt -= unit->getSaltCost();
    acid -= unit->getAcidCost();
    lair.enqueue(unit);
}

#endif //PETERTOWN_COLONY_H
