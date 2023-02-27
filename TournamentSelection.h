//
// Created by Michał Żądełek on 23.01.2023.
//



#include "Selection.h"
#include "Individual.h"
#include "vector"


#ifndef TEP_LAB_MINIPROJEKT_TOURNAMENTSELECTION_H
#define TEP_LAB_MINIPROJEKT_TOURNAMENTSELECTION_H

#endif //TEP_LAB_MINIPROJEKT_TOURNAMENTSELECTION_H

static int MIN_PARTICIPANTS = 2;

class TournamentSelection : public Selection {

private:
    unsigned int tournamentParticipants;
    RandomGenerator generator;
public:

    explicit TournamentSelection(unsigned int tournamentParticipants);

    TournamentSelection(const TournamentSelection &other) = default;

    TournamentSelection(TournamentSelection &&other) = default;

    TournamentSelection &operator=(const TournamentSelection &other) = default;

    TournamentSelection &operator=(TournamentSelection &&other) = default;

    ~TournamentSelection() override = default;

    std::vector<Individual> selectParents(std::vector<Individual> &population) override;

private:
    unsigned int getRandomParentIndex(unsigned int popSize);


};