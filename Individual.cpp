//
// Created by Michał Żądełek on 01.01.2023.
//

#include <iostream>
#include "Individual.h"
#include "ObjectConstructionError.h"

/// fitness = -1 points that an individual hasn't been associated with any problem yet
Individual::Individual(unsigned int genotypeSize, RandomGenerator &randomGenerator) : fitness(-1) {
    if (genotypeSize <= 0)
        throw ObjectConstructionError("Individual", "'genotypeSize' must be greater than 0!\nProvided: " +
                                                    std::to_string(genotypeSize));
    genotype.reserve(genotypeSize);
    fillRandomly(genotypeSize, randomGenerator);
}


void Individual::calculateFitness(Problem &problem) {
    fitness = problem.evaluate(genotype);
}

double Individual::getFitness() const {
    return fitness;
}

void Individual::mutate(unsigned int geneIndex) {
    genotype[geneIndex] = (genotype[geneIndex] == 0);
}

std::vector<bool> &Individual::getGenotype() {
    return genotype;
}

///crossing-over done on 2 parents and 2 children are returned
std::pair<Individual, Individual> Individual::crossover(const Individual &other, unsigned int division) const {
    Individual firstChild = Individual((int) genotype.size());
    Individual secondChild = Individual((int) genotype.size());

    for (int i = 0; i < division; i++) {
        firstChild.genotype.push_back(genotype[i]);
        secondChild.genotype.push_back(other.genotype[i]);
    }
    for (unsigned int j = division; j < genotype.size(); j++) {
        firstChild.genotype.push_back(other.genotype[j]);
        secondChild.genotype.push_back(genotype[j]);
    }
    return std::pair<Individual, Individual>{std::move(firstChild), std::move(secondChild)};
}

void Individual::fillRandomly(unsigned int genotypeSize, RandomGenerator &randomGenerator) {
    for (int i = 0; i < genotypeSize; ++i) {
        genotype.push_back(getRandomGene(randomGenerator));
    }
}

Individual::Individual(unsigned int genotypeSize) : fitness(-1) {
    genotype.reserve(genotypeSize);
}


int Individual::getRandomGene(RandomGenerator &randomGenerator) {
    return randomGenerator.generateRandomInt(0, 1);
}





