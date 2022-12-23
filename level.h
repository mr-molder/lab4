//
// Created by vova0 on 26.11.2022.
//

#ifndef PETERTOWN_LEVEL_H
#define PETERTOWN_LEVEL_H

#include <random>
#include <fstream>

#include "field.h"
#include "resource.h"
#include "vector.h"
#include "colony.h"
#include "unit.h"
#include "controller.h"
#include "pathfinder.h"

class UserController;
class AIController;
class Controller;
class Pathfinder;
class Resource;
class Colony;
class Unit;


class Level{
private:
    Field field;
    Vector<Resource> resources;
    Vector<Colony> colonies;
    const static int DEFAULT_SIZE_WIDTH = 110;
    const static int DEFAULT_SIZE_HEIGHT = 25;

    int seed;

    UserController user_controller;
    AIController ai_controller;
public:
    Level(): field(DEFAULT_SIZE_WIDTH, DEFAULT_SIZE_HEIGHT), user_controller(this) {};
    int getWidth() {return field.getWidth();};
    int getHeight() {return field.getHeight();};
    void resize(int new_width, int new_height);

    bool isCellEmpty(int x, int y);
    Resource* seekResource(int x, int y);
    Colony* seekColony(int x, int y);

    void createColony(int x, int y, int id);

    void generateLevel(long long int seed);
    void printLevel();

    void turn(); //
    void getFreeCell(int &x, int&y);

    const char* seekUnitSymbol(int y, int x);
    Unit* seekUnit(int y, int x);
    void cleanUpResources();

    bool gameOver();
    Colony* getWinner();
    void control();

public:
    void saveGame(char id);
    void loadGame(char id);
};

#endif //PETERTOWN_LEVEL_H
