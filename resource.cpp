//
// Created by molder on 11/29/22.
//

#include "resource.h"

int Resource::get_resource() {
    if (type == FOOD) {
        int taken = quantity;
        quantity = 0;
        return taken;
    }
    if (type == ACID) {
        return quantity;
    }
    if (type == SALT) {
        return quantity;
    }
    return 0;
}

const char * Resource::getSymbol() {
    const char* kinds[] = {
        "\033[1m\033[38;2;200;100;0m@\033[0m",
        "\033[1m\033[38;2;0;250;0m%\033[0m",
        "\033[1m\033[38;2;0;150;150m$\033[0m"
    };
    return kinds[type];
}

Colony *Resource::getOwner() const {
    return owner;
}

void Resource::setOwner(Colony *_owner) {
    owner = _owner;
}

void Resource::writeToFile(std::ofstream &file) {
    file << type << ' ' << quantity << ' ' << x << ' ' << y << ' ';
    if (owner)
        file << getOwner()->getId() << std::endl;
    else
        file << -1 << std::endl;
}

Resource Resource::readFromFile(std::ifstream &file) {
    int type, quantity;
    file >> type >> quantity;
    int x, y;
    file >> x >> y;
    Resource resource(type, quantity, x , y);
    return resource;
}
