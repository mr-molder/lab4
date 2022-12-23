//
// Created by molder on 12/2/22.
//

#include "level.h"
#include <future>
#include <thread>
#include <iostream>
#include <chrono>
using namespace std::chrono_literals;

Pathfinder pathfinder;

void Level::resize(int new_width, int new_height) {
    field.resize(new_width, new_height);
    Vector<Resource> new_resources;
    for (Resource& resource:resources) {
        if (resource.getX() < new_width && resource.getY() < new_height) {
            new_resources.push_back(resource);
        }
    }
}

Resource* Level::seekResource(int x, int y) {
    for (Resource& resource:resources) {
        if (resource.getX() == x && resource.getY() == y) {
            return &resource;
        }
    }
    return nullptr;
}

void Level::generateLevel(long long int _seed) {
    seed = _seed;
    std::mt19937_64 gen(seed);
    std::uniform_real_distribution<> distribGen(0, 1);
    std::uniform_int_distribution<> distribRes(0, 2);
    std::uniform_int_distribution<> distribX(0, getWidth() - 1);
    std::uniform_int_distribution<> distribY(0, getHeight() - 1);
    for (int y = 0; y < field.getHeight(); ++y) {
        for (int x = 0; x < field.getWidth(); ++x) {
            if (distribGen(gen) < 0.05) {
                field.setCellKind(x, y, 1);
            } else {
                if (distribGen(gen) < 0.05) {
                    int resType = distribRes(gen);
                    int quantity;
                    if (resType == Resource::FOOD)
                        quantity = 500 * distribRes(gen) + 1000;
                    else
                        quantity = 5 * distribRes(gen) + 10;
                    resources.push_back(Resource (resType, quantity, x, y));
                }
            }
        }
    }

    for (int i = 0; i < 2; ++i) {
        int x, y;
        do {
            x = distribX(gen);
            y = distribY(gen);
        } while (!isCellEmpty(x, y));
        createColony(x, y, i);
    }
    colonies[0].setController(&user_controller);
    colonies[1].setController(&ai_controller);
    for (Colony& colony: colonies) {
        for (Unit* unit:colony.getUnits()) {
            unit->setColony(&colony);
        }
    }
}

void Level::printLevel() {
    std::cout << "\x1b[2J";
    std::cout << "\x1b[f";
    for (int y = 0; y < getHeight(); ++y) {
        for (int x = 0; x < getWidth(); ++x) {
            std::cout << field.getBackground(x, y);
            Resource* resource = seekResource(x, y);
            if (resource) {
                if (Colony *colony;colony = resource->getOwner())
                {
                    std::cout << colony->getResourceBackground();
                }
                std::cout << resource->getSymbol();
                continue;
            }
            Colony* colony = seekColony(x, y);
            if (colony) {
                std::cout << colony->getSymbol();
                continue;
            }
            if(const char* s; s = seekUnitSymbol(y, x)) {
                std::cout << s;
                continue;
            }
            std::cout << " ";
        }
        std::cout << "\033[0m" << "\n\r";
    }
    for (auto colony:colonies) {
        for (auto unit:colony.getUnits()) {
            std::cout << unit->getHp() << ' ';
        }
        std::cout << "\n\r";
        std::cout << colony.getFood() << "@/";
        std::cout << colony.getAcid() << "%/";
        std::cout << colony.getSalt() << "$/";
        std::cout << "\n\r";
    }
}

const char* Level::seekUnitSymbol(int y, int x) {
    for (Colony& colony: colonies) {
        for (Unit* unit:colony.getUnits()) {
            if(unit->getX() == x && unit->getY() == y) {
                return unit->getSymbol(colony.getId());
            }
        }
    }
    return nullptr;
}

Unit* Level::seekUnit(int x, int y) {
    if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight())
        return nullptr;
    for (Colony& colony: colonies) {
        for (Unit* unit:colony.getUnits()) {
            if(unit->getX() == x && unit->getY() == y) {
                return unit;
            }
        }
    }
    return nullptr;
}

bool Level::isCellEmpty(int x, int y) {
    if (field.getCellKind(x, y) == 1)
        return false;
    if (seekResource(x, y))
        return false;
    for (auto& colony:colonies) {
        if (!colony.isEmpty(x, y))
            return false;
    }
    return true;
}

void Level::createColony(int x, int y, int id) {
    colonies.push_back(Colony(id, x, y, this));
}

Colony *Level::seekColony(int x, int y) {
    for (Colony& colony:colonies) {
        if (colony.getLairX() == x && colony.getLairY() == y) {
            return &colony;
        }
    }
    return nullptr;
}

void Level::turn() {

    //-1st part: controller;

    pathfinder.update(*this);
    // 0th part: spawn;
    for (Colony& colony : colonies) {
        colony.spawnTick();
    }
    // 1st part: attack;
    for (Colony& colony:colonies) {
        for (Unit* unit:colony.getUnits()) {
            unit->turn(*this, pathfinder);
        }
    }
    // 2nd part: capture resources;
    for (auto& resource:resources) {
        if (Colony* colony; colony = resource.getOwner())
            colony->takeResource(resource);
    }
    // 3rd part: delete rubbish;
    for (Colony& colony:colonies) {
        colony.cleanUp();
    }
    cleanUpResources();
    // update pathfinding;
    // 4th part: move units;
    for (Colony& colony:colonies) {
        for (Unit* unit:colony.getUnits()) {
            unit->step(pathfinder);
        }
    }
}

void Level::getFreeCell(int &x, int &y) {
    do {
        x = Rand::get().Int(0, getWidth() - 1);
        y = Rand::get().Int(0, getHeight() - 1);
    } while (!isCellEmpty(x, y));
}

void Level::cleanUpResources() {
    Vector<Resource> alive_resources;
    for (Resource res:resources) {
        if (res.notEmpty())
            alive_resources.push_back(res);
//        else
//            //printf(" ");
    }
    resources = alive_resources;
}

bool Level::gameOver() {
    for (Colony& colony:colonies) {
        if(!colony.getLair().isAlive())
            return true;
    }
    return false;
}

Colony *Level::getWinner() {
    for (Colony& colony:colonies)
        if(colony.getLair().isAlive())
            return &colony;
    return nullptr;

}

void Level::control() {
    for (Colony& colony:colonies) {
        colony.getController()->control(colony);
    }
}

void Level::saveGame(char id) {
    char name[] = "@.txt";
    name[0] = id;

    std::ofstream saved_file(name);

    saved_file << seed << std::endl;
    saved_file << getWidth() << std::endl;
    saved_file << getHeight() << std::endl;

    field.writeToFile(saved_file);

    // colony 1:
    colonies[0].writeToFile(saved_file);
    // colony 2:
    colonies[1].writeToFile(saved_file);

    saved_file << resources.getSize() << std::endl;
    for (int i = 0; i < resources.getSize(); ++i) {
        resources[i].writeToFile(saved_file);
    }


}

void Level::loadGame(char id) {
    char name[] = "@.txt";
    name[0] = id;

    std::ifstream saved_file(name);
    int width;
    int height;

    saved_file >> seed;
    saved_file >> width;
    saved_file >> height;
    field.resize(width, height);
    field.readFromFile(saved_file);

    createColony(0, 0, 0);
    createColony(1, 1, 1);

    colonies[0].setController(&user_controller);
    colonies[1].setController(&ai_controller);
    colonies[0].readFromFile(saved_file);
    colonies[1].readFromFile(saved_file);

    int quantity;
    saved_file >> quantity;
//
    int owner_id;
    for (int i = 0; i < quantity; ++i) {
        resources.push_back(Resource::readFromFile(saved_file));
        saved_file >> owner_id;
        resources[i].setOwner(nullptr);
        if (owner_id != -1) {
            resources[i].setOwner(&(colonies[owner_id]));
        }
    }

}


