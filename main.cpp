#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include "level.h"
using namespace std::chrono_literals;
int main() {
    Level level;

    // main menu
    std::cout << "0: new game\n" << "1 - 9: choose file to load\n";
    char symbol;
    do {
        std::cin >> symbol;
    } while (!std::isdigit(symbol));

    if (symbol == '0') {
        level.generateLevel(std::random_device()());
    } else {
        std::cout << "Loading level: ...\n";
        level.loadGame(symbol);
    }
    int counter = 50;
    while (!level.gameOver()) {
        if (counter < 50) {
            auto t0 = std::chrono::high_resolution_clock::now();
            level.printLevel();
            level.turn();
            auto t1 = std::chrono::high_resolution_clock::now();
            std::cout << std::chrono::duration<double, std::milli>(t1 - t0) << "\n\r";
            std::this_thread::sleep_for(0.1s - (t1 - t0));
            counter++;
        } else {
            counter = 0;
            level.control();
        }
   }

    Colony* winner = level.getWinner();
    std::cout <<"GAME OVER\n\r";
    if (winner)
        std::cout << winner->getSymbol() << " wins!";


    return 0;
}
