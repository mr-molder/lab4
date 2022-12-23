//
// Created by molder on 12/8/22.
//

#ifndef PETERTOWN_UNIT_H
#define PETERTOWN_UNIT_H

#include "randomizer.h"


#include "pathfinder.h"


class Colony;
class Resource;
class Pathfinder;
class Level;

class Unit {
private:
    Colony* colony;
public:
    void setColony(Colony *colony);

public:
    Colony *getColony() const;
public:
    int getHp() const;

private:
    int hp;
    int x, y;
    char direction = 'e';
public:
    void setY(int y);

public:
    void setX(int x);

public:
    int getY() const;
    int getX() const;
    Unit(Colony* _colony): colony(_colony), hp(2) {};
    virtual ~Unit() {};
    virtual void spawn(int x, int y);
    virtual void step(Pathfinder& pathfinder);
    void damage(int dmg);
    bool isAlive();
    virtual const char* getSymbol(int id) = 0;
    virtual void turn(Level& level, Pathfinder& pathfinder) = 0;
    virtual int getFoodCost() = 0;
    virtual int getSaltCost() = 0;
    virtual int getAcidCost() = 0;

    virtual void writeToFile(std::ofstream & file);
    static Unit* readFromFile(std::ifstream & file);


protected:
    int nextX(char dir);
    int nextY(char dir);
};

class Soldja: public Unit {
protected:
    int dmg = 1;
private:
    static const int food_cost = 500;
    static const int salt_cost = 0;
    static const int acid_cost = 0;
public:
    Soldja(Colony* colony): Unit(colony){};
    virtual void spawn(int x, int y);
    void fight(Unit& enemy);
    virtual void capture(Resource& resource);
    virtual void step(Pathfinder& pathfinder);
    virtual const char* getSymbol(int id);
    virtual void turn(Level& level, Pathfinder& pathfinder);

    virtual int getFoodCost() {return food_cost;};
    virtual int getSaltCost() {return salt_cost;};
    virtual int getAcidCost() {return acid_cost;};

    void writeToFile(std::ofstream & file) override;
};

class Trooper: public Soldja {
private:
    static const int food_cost = 0;
    static const int salt_cost = 1000;
    static const int acid_cost = 1000;
public:
    Trooper(Colony* colony): Soldja(colony){};
    void burnHouse(Colony *colony);
    virtual void turn(Level& level, Pathfinder& pathfinder);
    virtual const char* getSymbol(int id);

    virtual int getFoodCost() {return food_cost;};
    virtual int getSaltCost() {return salt_cost;};
    virtual int getAcidCost() {return acid_cost;};

    void writeToFile(std::ofstream & file) override;
};

class Cleaner: public Soldja {
private:
    static const int food_cost = 500;
    static const int salt_cost = 0;
    static const int acid_cost = 500;
public:
    Cleaner(Colony* colony): Soldja(colony){};
    virtual void turn(Level& level, Pathfinder& pathfinder);
    virtual const char* getSymbol(int id);

    virtual int getFoodCost() {return food_cost;};
    virtual int getSaltCost() {return salt_cost;};
    virtual int getAcidCost() {return acid_cost;};

    void writeToFile(std::ofstream & file) override;
};

class Hunter: public Soldja {
private:
    static const int food_cost = 1000;
    static const int salt_cost = 1000;
    static const int acid_cost = 0;
public:
    Hunter(Colony* colony): Soldja(colony){Soldja::dmg = 2;};
    virtual void capture(Resource& resource) {};
    virtual const char* getSymbol(int id);

    virtual int getFoodCost() {return food_cost;};
    virtual int getSaltCost() {return salt_cost;};
    virtual int getAcidCost() {return acid_cost;};

    void writeToFile(std::ofstream & file) override;
};
#include "colony.h"
#include "resource.h"
#include "level.h"
#endif //PETERTOWN_UNIT_H

