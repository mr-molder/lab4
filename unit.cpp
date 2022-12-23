//
// Created by molder on 12/9/22.
//

#include "unit.h"

void Unit::spawn(int _x, int _y) {
    x = _x;
    y = _y;
    static const char dirs[] = {'s', 'n', 'e', 'w'};
    direction = dirs[Rand::get().Int(0, 3)];
}

int Unit::getX() const {
    return x;
}

int Unit::getY() const {
    return y;
}

Colony *Unit::getColony() const {
    return colony;
}

void Unit::damage(int dmg) {
    hp -= dmg;
}

bool Unit::isAlive() {
    return hp > 0;
}

int Unit::nextX(char dir) {
    if (dir == 'e')
        return getX() + 1;
    if (dir == 'w')
        return getX() - 1;
    return getX();
}

int Unit::nextY(char dir) {
    if (dir == 's')
        return getY() + 1;
    if (dir == 'n')
        return getY() - 1;
    return getY();
}

void Unit::setX(int x) {
    Unit::x = x;
}

void Unit::setY(int y) {
    Unit::y = y;
}

int Unit::getHp() const {
    return hp;
}

void Unit::setColony(Colony *_colony) {
    Unit::colony = _colony;
}

void Unit::step(Pathfinder &pathfinder) {
    int next_x = nextX(direction);
    int next_y = nextY(direction);
    for(int i = 0; !pathfinder.isValidCell(next_x, next_y) && i < 4; i++) {
        static const char dirs[] = {'s', 'n', 'e', 'w'};
        direction = dirs[Rand::get().Int(0, 3)];
        next_x = nextX(direction);
        next_y = nextY(direction);
    }
    if (pathfinder.isValidCell(next_x, next_y)) {
        pathfinder.updateUnit(getX(), getY(), next_x, next_y);
        setX(next_x);
        setY(next_y);
    }
}

void Unit::writeToFile(std::ofstream &file) {
    file << hp << ' ' << x << ' ' << y << ' ' << direction << std::endl;
}

Unit *Unit::readFromFile(std::ifstream &file) {
    char unit_type;
    file >> unit_type;
    int hp;
    file >> hp;
    int x, y;
    file >> x >> y;
    char direction;
    file >> direction;
    Unit* unit;
    switch (unit_type) {
        case 's':
            unit = new Soldja(nullptr);
            break;
        case 'c':
            unit = new Cleaner(nullptr);
            break;
        case 't':
            unit = new Trooper(nullptr);
            break;
        case 'h':
            unit = new Hunter(nullptr);
            break;
    }
    unit->hp = hp;
    unit->x = x;
    unit->y = y;
    unit->direction = direction;
    return unit;
}

const char *Soldja::getSymbol(int id) {
    const char* kinds[] = {
            "\033[38;2;0;0;100m\033[48;2;150;150;0ms\033[0m",
            "\033[38;2;100;0;0m\033[48;2;150;150;0ms\033[0m"
    };
    return kinds[id];
}

void Soldja::step(Pathfinder& pathfinder) {
    Unit::step(pathfinder);
}

void Soldja::capture(Resource &resource) {
    resource.setOwner(getColony());
}

void Soldja::fight(Unit &enemy) {
    enemy.damage(dmg);
}

void Soldja::spawn(int x, int y) {
    Unit::spawn(x, y);
}

void Soldja::turn(Level &level, Pathfinder &pathfinder) {
    for (int dx: {-1, 1}) {
        if(Unit* unit; (unit = level.seekUnit(getX() + dx, getY())) &&
                       unit->getColony()->getId() != getColony()->getId()) {
            fight(*unit);
        }
    }
    for (int dy: {-1, 1}) {
        if(Unit* unit; (unit = level.seekUnit(getX(), getY() + dy)) &&
                       unit->getColony()->getId() != getColony()->getId()) {
            fight(*unit);
        }
    }
    for (int dx: {-1, 1}) {
        if(Resource* res; (res = level.seekResource(getX() + dx, getY())) &&
                !(res->getOwner())) {
            capture(*res);
        }
    }
    for (int dy: {-1, 1}) {
        if(Resource* res; (res = level.seekResource(getX(), getY() + dy)) &&
                          !(res->getOwner())) {
            capture(*res);
        }
    }
}

void Soldja::writeToFile(std::ofstream &file) {
    file << "s ";
    Unit::writeToFile(file);
}


void Trooper::burnHouse(Colony *colony) {
    colony->getLair().damage(dmg);
}

void Trooper::turn(Level &level, Pathfinder &pathfinder) {
    for (int dx: {-1, 1}) {
        if(Unit* unit; (unit = level.seekUnit(getX() + dx, getY())) &&
                       unit->getColony()->getId() != getColony()->getId()) {
            fight(*unit);
        }
    }
    for (int dy: {-1, 1}) {
        if(Unit* unit; (unit = level.seekUnit(getX(), getY() + dy)) &&
                       unit->getColony()->getId() != getColony()->getId()) {
            fight(*unit);
        }
    }
    for (int dx: {-1, 1}) {
        if(Colony* colony; (colony = level.seekColony(getX() + dx, getY())) &&
                          colony != getColony()) {
            burnHouse(colony);
        }
    }
    for (int dy: {-1, 1}) {
        if(Colony* colony; (colony = level.seekColony(getX(), getY() + dy)) &&
                colony != getColony()) {
            burnHouse(colony);
        }
    }
}

const char *Trooper::getSymbol(int id) {
    const char* kinds[] = {
            "\033[38;2;0;0;100m\033[48;2;150;150;0mT\033[0m",
            "\033[38;2;100;0;0m\033[48;2;150;150;0mT\033[0m"
    };
    return kinds[id];
}

void Trooper::writeToFile(std::ofstream &file) {
    file << "t ";
    Unit::writeToFile(file);
}

void Cleaner::turn(Level &level, Pathfinder &pathfinder) {
    for (int dx: {-1, 1}) {
        if(Resource* res; (res = level.seekResource(getX() + dx, getY()))) {
            capture(*res);
        }
    }
    for (int dy: {-1, 1}) {
        if(Resource* res; (res = level.seekResource(getX(), getY() + dy))) {
            capture(*res);
        }
    }
}

const char *Cleaner::getSymbol(int id) {
    const char* kinds[] = {
            "\033[38;2;0;0;100m\033[48;2;150;150;0mC\033[0m",
            "\033[38;2;100;0;0m\033[48;2;150;150;0mC\033[0m"
    };
    return kinds[id];
}

void Cleaner::writeToFile(std::ofstream &file) {
    file << "c ";
    Unit::writeToFile(file);
}

const char *Hunter::getSymbol(int id) {
    const char* kinds[] = {
            "\033[38;2;0;0;100m\033[48;2;150;150;0mH\033[0m",
            "\033[38;2;100;0;0m\033[48;2;150;150;0mH\033[0m"
    };
    return kinds[id];
}

void Hunter::writeToFile(std::ofstream &file) {
    file << "h ";
    Unit::writeToFile(file);
}
