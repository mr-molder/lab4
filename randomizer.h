//
// Created by molder on 12/8/22.
//

#ifndef PETERTOWN_RANDOMIZER_H
#define PETERTOWN_RANDOMIZER_H

#include <random>

class Rand {
private:
    std::mt19937_64 engine;
    Rand() {
        engine.seed(std::random_device()());
    };
public:
    static Rand& get() {
        static Rand instance;
        return instance;
    }
    int Int(int min, int max) {
        return std::uniform_int_distribution<int>(min, max)(engine);
    }
    float Float(float min, float max) {
        return std::uniform_real_distribution<float>(min, max)(engine);
    }
};

#endif //PETERTOWN_RANDOMIZER_H
