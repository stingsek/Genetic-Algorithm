//
// Created by Michał Żądełek on 01.01.2023.
//

#ifndef TEP_LAB_MINIPROJEKT_INDIVIDUAL_H
#define TEP_LAB_MINIPROJEKT_INDIVIDUAL_H


#include <vector>
#include "Problem.h"
#include "RandomGenerator.h"

class Individual {
public:

    Individual(unsigned int genotypeSize, RandomGenerator &randomGenerator);

    ~Individual() = default;

    Individual(const Individual &other) = default;

    Individual(Individual &&other) noexcept = default;

    Individual &operator=(const Individual &other) = default;

    Individual &operator=(Individual &&other) noexcept = default;

    void calculateFitness(Problem &problem);

    void mutate(unsigned int geneIndex);

    std::vector<bool> &getGenotype();

    std::pair<Individual, Individual> crossover(const Individual &other, unsigned int division) const;

    double getFitness() const;


private:
    ///type that ensures 1 bit for every gene instead of 8
    std::vector<bool> genotype;
    double fitness;

    void fillRandomly(unsigned int genotypeSize, RandomGenerator &randomGenerator);

    static int getRandomGene(RandomGenerator &randomGenerator);

    explicit Individual(unsigned int genotypeSize);


};


#endif //TEP_LAB_MINIPROJEKT_INDIVIDUAL_H
