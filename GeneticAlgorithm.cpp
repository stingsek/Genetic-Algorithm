//
// Created by Michał Żądełek on 01.01.2023.
//

#include <iostream>
#include "GeneticAlgorithm.h"
#include "ObjectConstructionError.h"


std::vector<Individual> GeneticAlgorithm::generatePopulation(Problem &problem) {

    ///declaration of population
    std::vector<Individual> population;
    population.reserve(popSize);

    ///loop which creates the population
    for (int i = 0; i < popSize; i++) {

        ///creation of individual
        Individual individual = Individual(problem.getProblemSize(), randomGenerator);

        ///seeding randomGenerator randomly to prevent the sameness of the individuals
        randomGenerator.seedRandomly();

        ///calculating fitness for individual
        individual.calculateFitness(problem);

        ///checking if fitness of the individual is greater than 'currentBestFitness'. If it is - calling 'updateCurrentBest'
        if (individual.getFitness() > currentBestFitness)
            updateCurrentBest(individual.getFitness(), individual.getGenotype());

        ///adding the individual to the population
        population.push_back(std::move(individual));
    }

    return population;

}


void GeneticAlgorithm::runIteration(Problem &problem, Selection &selectionMethod) {

    ///clearing results of previous run
    currentBestFitness = -1;
    currentBestSolution.clear();

    currentBestSolution.reserve(problem.getProblemSize());

    ///generating first population for iteration
    std::vector<Individual> population = generatePopulation(problem);

    ///doing iteration
    for (int i = 0; i < iterationCount; i++) {

        ///seeding random generator randomly
        randomGenerator.seedRandomly();


        ///creating 'newPopulation' which will "cover" the last one
        std::vector<Individual> newPopulation;
        newPopulation.reserve(popSize);


        ///selecting parents from previous 'population' and replacing it by these parents (because previous 'population' is no more useful)
        population = selectionMethod.selectParents(population);


        ///this method fills newPopulation with mutated children
        fillNewPopulation(population, newPopulation, problem);


        ///replacing previous population by new population
        population = std::move(newPopulation);
    }

}

GeneticAlgorithm::GeneticAlgorithm(float crossProb, float mutProb, unsigned int popSize, unsigned int iterationCount)
        : crossProb(crossProb), mutProb(mutProb), popSize(popSize), iterationCount(iterationCount),
          currentBestFitness(-1) {
    if (crossProb < 0 || crossProb > 1)
        throw ObjectConstructionError("GeneticAlgorithm", "'crossProb' must be in range [0;1]!");
    if (mutProb < 0 || mutProb > 1)
        throw ObjectConstructionError("GeneticAlgorithm", "'mutProb' must be in range [0;1]!");
    if (popSize <= 0)
        throw ObjectConstructionError("GeneticAlgorithm", "'popSize' must be larger than 0!");
    if (iterationCount <= 0)
        throw ObjectConstructionError("GeneticAlgorithm", "'iterationCount' must be larger than 0!");

}

double GeneticAlgorithm::getCurrentBestFitness() const {
    return currentBestFitness;
}

const std::vector<bool> &GeneticAlgorithm::getCurrentBestSolution() const {
    return currentBestSolution;
}


void GeneticAlgorithm::mutate(Individual &individual) {
    ///for every gene in 'individual' genotype checking if a gene has to be mutated ar not
    for (int j = 0; j < individual.getGenotype().size(); j++) {
        if (mutProb > generateProbability())
            individual.mutate(j);
    }
}

///randomly generating float and checking if it is bigger or equal or not than 'crossProb'
///if it is, return parents, otherwise return created children
std::pair<Individual, Individual> GeneticAlgorithm::crossingOver(Individual &firstParent, Individual &secondParent) {
    if (crossProb <= generateProbability()) {
        return std::pair<Individual, Individual>{firstParent, secondParent};
    }
    return firstParent.crossover(secondParent, getDivisionIndex((int) firstParent.getGenotype().size()));

}


void GeneticAlgorithm::fillNewPopulation(std::vector<Individual> &previousPopulation,
                                         std::vector<Individual> &newPopulation, Problem &problem) {


    ///while loop which checks if newPopulation has already been filled
    while (newPopulation.size() < previousPopulation.size()) {

        ///randomly choosing parents to cross
        Individual& parent1 = chooseParentRandomly(previousPopulation);
        Individual& parent2 = chooseParentRandomly(previousPopulation);

        ///doing crossover(it returns a pair od children if 'crossProb' is large enough, otherwise it returns parents)
        std::pair<Individual, Individual> children = crossingOver(parent1, parent2);

        ///mutating children after crossing-over and calculating for them their fitness
        if (&children.first != &parent1) {
            mutate(children.first);
            mutate(children.second);
            children.first.calculateFitness(problem);
            children.second.calculateFitness(problem);
        }

        ///searching for bestSolution(bestFitness)
        if (children.first.getFitness() > currentBestFitness || children.second.getFitness() > currentBestFitness) {
            children.first.getFitness() > children.second.getFitness()
            ? updateCurrentBest(children.first.getFitness(), children.first.getGenotype()) : updateCurrentBest(
                    children.second.getFitness(), children.second.getGenotype());
        }

        ///adding children to newPopulation
        if (previousPopulation.size() - 1 == newPopulation.size())
            newPopulation.push_back(std::move(
                    children.first.getFitness() > children.second.getFitness() ? children.first : children.second));

        else {
            newPopulation.push_back(std::move(children.first));
            newPopulation.push_back(std::move(children.second));
        }
    }

}

void GeneticAlgorithm::printBestSolution() {
    std::cout << "[|";
    for (auto &&i: currentBestSolution)
        std::cout << i << "|";
    std::cout << "]" << std::endl;

}

void GeneticAlgorithm::updateCurrentBest(double fitness, std::vector<bool> solution) {
    currentBestFitness = fitness;
    currentBestSolution = std::move(solution);
}

float GeneticAlgorithm::generateProbability() {
    return randomGenerator.generateRandomFloat(0.0, 1.0);
}

int GeneticAlgorithm::getDivisionIndex(int genotypeSize) {
    return randomGenerator.generateRandomInt(1, genotypeSize - 1);
}

Individual& GeneticAlgorithm::chooseParentRandomly(std::vector<Individual> &population) {
    return population[randomGenerator.generateRandomInt(0, (int) popSize - 1)];
}


















