//
// Created by molder on 12/17/22.
//

#ifndef PETERTOWN_CONTROLLER_H
#define PETERTOWN_CONTROLLER_H

#include <iostream>



class Colony;
class Level;

class Controller {
public:
    virtual void control(Colony& colony) = 0;
};

class UserController: public Controller {
private:
    Level* level;
public:
    UserController(Level* _level):level(_level) {};
    void control(Colony& colony) override;
};

class AIController: public Controller {
public:
    void control(Colony& colony) override;
};
#include "colony.h"
#include "level.h"
#endif //PETERTOWN_CONTROLLER_H
