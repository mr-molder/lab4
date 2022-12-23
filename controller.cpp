//
// Created by molder on 12/17/22.
//

#include <string>
#include "controller.h"
#include "randomizer.h"

void UserController::control(Colony &colony) {
std::string s;
    std::getline(std::cin, s);
    for (char c:s) {
        switch (c) {
            case 'S':
            case 's':
                colony.createUnit<Soldja>();
                break;
            case 'T':
            case 't':
                colony.createUnit<Trooper>();
                break;
            case 'C':
            case 'c':
                colony.createUnit<Cleaner>();
                break;
            case 'H':
            case 'h':
                colony.createUnit<Hunter>();
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                level->saveGame(c);
        }
    }

}

void AIController::control(Colony &colony) {
    for (int i = 0; i < 5; ++i) {
        switch(Rand::get().Int(1, 4)) {
            case 1:
                colony.createUnit<Soldja>();
                break;
            case 2:
                colony.createUnit<Trooper>();
                break;
            case 3:
                colony.createUnit<Cleaner>();
                break;
            case 4:
                colony.createUnit<Hunter>();
                break;
        }
    }
}
