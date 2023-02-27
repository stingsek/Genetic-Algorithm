//
// Created by Michał Żądełek on 01.01.2023.
//

#ifndef TEP_LAB_MINIPROJEKT_GENETICALGORITHM_H
#define TEP_LAB_MINIPROJEKT_GENETICALGORITHM_H


#include "Individual.h"
#include "Selection.h"
#include <random>

class GeneticAlgorithm {

public:
    GeneticAlgorithm(float crossProb, float mutProb, unsigned int popSize, unsigned int iterationCount);

    GeneticAlgorithm(const GeneticAlgorithm &other) = default;

    GeneticAlgorithm(GeneticAlgorithm &&temp) noexcept = default;

    GeneticAlgorithm &operator=(const GeneticAlgorithm &other) = default;

    GeneticAlgorithm &operator=(GeneticAlgorithm &&other) noexcept = default;

    ~GeneticAlgorithm() = default;

    void runIteration(Problem &problem, Selection &selectionMethod);

    double getCurrentBestFitness() const;

    const std::vector<bool> &getCurrentBestSolution() const;

    void printBestSolution();


private:
    std::vector<Individual> generatePopulation(Problem &problem);

    void mutate(Individual &individual);

    std::pair<Individual, Individual> crossingOver(Individual &firstParent, Individual &secondParent);

    void fillNewPopulation(std::vector<Individual> &previousPopulation, std::vector<Individual> &newPopulation,
                           Problem &problem);

    void updateCurrentBest(double fitness, std::vector<bool> solution);

    float generateProbability();

    int getDivisionIndex(int genotypeSize);

    Individual& chooseParentRandomly(std::vector<Individual> &population);

    double currentBestFitness;
    unsigned int popSize;
    float crossProb;
    float mutProb;
    unsigned int iterationCount;
    std::vector<bool> currentBestSolution;
    RandomGenerator randomGenerator;

};


#endif //TEP_LAB_MINIPROJEKT_GENETICALGORITHM_H
