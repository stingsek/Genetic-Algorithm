//
// Created by Michał Żądełek on 24.01.2023.
//


#include "TournamentSelection.h"
#include "ObjectConstructionError.h"


TournamentSelection::TournamentSelection(unsigned int tournamentParticipants) : tournamentParticipants(tournamentParticipants)
{
    if(tournamentParticipants < MIN_PARTICIPANTS)
        throw ObjectConstructionError("TournamentSelection","'tournamentParticipants' must be greater than: " +
                std::to_string(MIN_PARTICIPANTS));
}


std::vector<Individual> TournamentSelection::selectParents(std::vector<Individual> &population) {
    {
        std::vector<Individual> parents;
        parents.reserve(population.size());
        std::vector<unsigned int> generatedIndexes;
        unsigned int winIndex;

        while (parents.size() != population.size()) {
            for (int i = 0; i < tournamentParticipants; i++) {
                generatedIndexes.push_back(getRandomParentIndex(population.size()));
                if (i == 0)
                    winIndex = generatedIndexes[i];
                if (population[generatedIndexes[i]].getFitness() > population[winIndex].getFitness())
                    winIndex = generatedIndexes[i];
            }
            parents.push_back(population[winIndex]);
        }
        return parents;
    }
}

unsigned int TournamentSelection::getRandomParentIndex(unsigned int popSize) {
    return generator.generateRandomInt(0, (int) popSize - 1);
}

