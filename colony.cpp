//
// Created by molder on 12/4/22.
//

#include "colony.h"

const char *Colony::getSymbol() {

    const char* kinds[] = {
            "\033[1m\033[38;2;0;0;100m\033[48;2;255;255;255m1\033[0m",
            "\033[1m\033[38;2;100;0;0m\033[48;2;255;255;255m2\033[0m",
    };

    return kinds[id];
}

int Colony::getLairX() {
    return lair.getLairX();
}

int Colony::getLairY() {
    return lair.getLairY();
}

bool Colony::isEmpty(int x, int y) {
    if (lair.getLairX() == x && lair.getLairY() == y)
        return false;
    for (auto unit:units) {
        if (unit->getX() == x && unit->getY() == y)
            return false;
    }
    return true;
}

const Vector<Unit *> &Colony::getUnits() const {
    return units;
}

void Colony::spawnUnit(Unit* unit) {
    int x, y;
    level->getFreeCell(x, y);
    unit->spawn(x, y);
    units.push_back(unit);
}

Colony::Colony(int _id, int _x, int _y, Level* _level): id(_id), food(2000), acid(500), salt(500), lair(_x, _y), level(_level){
//    units.push_back(new Cleaner(this));
//    units.push_back(new Cleaner(this));
//    int x, y;
//    level->getFreeCell(x, y);
//    units[0]->spawn(x, y);
//    level->getFreeCell(x, y);
//    units[1]->spawn(x, y);
}

int Colony::getId() const {
    return id;
}

void Colony::cleanUp() {

    Vector<Unit*> alive_units;
    for (Unit* unit:units) {
        if (unit->isAlive())
            alive_units.push_back(unit);
        else
            delete unit;
    }
    units = alive_units;

}

void Colony::takeResource(Resource &res) {
    int quantity = res.get_resource();
    switch (res.getType()) {
        case Resource::FOOD:
            food += quantity;
            return;
        case Resource::ACID:
            acid += quantity;
            return;
        case Resource::SALT:
            salt += quantity;

    }
}

int Colony::getFood() const {
    return food;
}

int Colony::getAcid() const {
    return acid;
}

int Colony::getSalt() const {
    return salt;
}

const char *Colony::getResourceBackground() {
    if (getId() == 0)
        return "\033[48;2;0;0;100m";
    if (getId() == 1)
        return "\033[48;2;100;0;0m";
    return nullptr;
}

Lair &Colony::getLair() {
    return lair;
}



Controller *Colony::getController() const {
    return controller;
}

void Colony::setController(Controller *_controller) {
    Colony::controller = _controller;
}

void Colony::spawnTick() {
    lair.tick();
}

void Colony::writeToFile(std::ofstream &file) {
    file << food << ' ' << acid << ' ' << salt << std::endl;
    lair.writeToFile(file);
    file << units.getSize() << std::endl;
    for (int i = 0; i < units.getSize(); ++i) {
        units[i]->writeToFile(file);
    }
}

void Colony::readFromFile(std::ifstream &file) {
    file >> food >> acid >> salt;
    lair.readFromFile(file);
    for (Lair::Larva& larva:lair.getLarvae()) {
        larva.unit->setColony(this);
    }
    int quantity;
    file >> quantity;
    for (int i = 0; i < quantity; ++i) {
        units.push_back(Unit::readFromFile(file));
        units[i]->setColony(this);
    }
}

