//
// Created by molder on 12/19/22.
//
#include "lair.h"


void Lair::tick() {
    if(larvae.getSize() == 0){
        return;
    }
    if(larvae[0].time_left == 0){
        larvae[0].unit->getColony()->spawnUnit(larvae[0].unit);
        larvae.remove(0);
        return;
    }
    larvae[0].time_left--;
}

void Lair::writeToFile(std::ofstream &file) {
    file << x << ' ' << y << ' ' << health << std::endl;
    file << larvae.getSize() << std::endl;
    for (int i = 0; i < larvae.getSize(); ++i) {
        larvae[i].writeToFile(file);
    }
}

void Lair::readFromFile(std::ifstream &file) {
    file >> x >> y >> health;
    int quantity;
    file >> quantity;
    for (int i = 0; i < quantity; ++i) {
        larvae.push_back(Larva::readFromFile(file));
    }
}

const Vector<Lair::Larva> &Lair::getLarvae() const {
    return larvae;
}

void Lair::Larva::writeToFile(std::ofstream &file) {
    file << time_left << ' ';
    unit->writeToFile(file);
}

Lair::Larva Lair::Larva::readFromFile(std::ifstream &file) {
    Lair::Larva larva;
    file >> larva.time_left;
    larva.unit = Unit::readFromFile(file);
    return larva;
}
