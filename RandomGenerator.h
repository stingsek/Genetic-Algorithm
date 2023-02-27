//
// Created by Michał Żądełek on 19.01.2023.
//

#include <random>

#ifndef TEP_LAB_MINIPROJEKT_RANDOMGENERATOR_H
#define TEP_LAB_MINIPROJEKT_RANDOMGENERATOR_H

#endif //TEP_LAB_MINIPROJEKT_RANDOMGENERATOR_H

class RandomGenerator {
private:
    std::mt19937 randEngine;

public:
    RandomGenerator(){
        seedRandomly();
    }

    ~RandomGenerator() = default;
    RandomGenerator(const RandomGenerator& other) = default;
    RandomGenerator(RandomGenerator&& other) = default;
    RandomGenerator& operator=(const RandomGenerator& other) = default;
    RandomGenerator& operator=(RandomGenerator&& other) = default;


    void seedRandomly() {
        std::random_device rd;
        std::seed_seq sd{rd(), rd(), rd(), rd()};
        randEngine = std::mt19937(sd);
    }

    int generateRandomInt(int from, int to) {
        std::uniform_int_distribution<int> dist(from, to);
        return dist(randEngine);
    }

    float generateRandomFloat(float from, float to) {
        std::uniform_real_distribution<float> dist(from, to);
        return dist(randEngine);
    }

};
