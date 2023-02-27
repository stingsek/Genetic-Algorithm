#include <iostream>
#include "KnapsackProblem.h"
#include "FileReadError.h"
#include "GeneticAlgorithm.h"
#include "TournamentSelection.h"
#include "ObjectConstructionError.h"

const int PROBLEMS_COUNT = 5, POP_SIZE = 20, ITER_COUNT = 10, TOURNAMENT_PART = 2;
const float CROSS_PROB = 0.6, MUT_PROB = 0.1;

int main() {
    std::cout<< "-----------------------------TEST--------------------------------"<< std::endl;

    try {
        std::vector<KnapsackProblem> knapsackProblems;
        knapsackProblems.reserve(PROBLEMS_COUNT);

        knapsackProblems.emplace_back(KnapsackProblem("KnapsackProblem1.txt"));
        knapsackProblems.emplace_back(KnapsackProblem("KnapsackProblem2.txt"));
        knapsackProblems.emplace_back(KnapsackProblem("KnapsackProblem3.txt"));
        knapsackProblems.emplace_back(KnapsackProblem("KnapsackProblem4.txt"));
        knapsackProblems.emplace_back(KnapsackProblem("KnapsackProblem5.txt"));

        GeneticAlgorithm GA = GeneticAlgorithm(CROSS_PROB, MUT_PROB, POP_SIZE, ITER_COUNT);
        TournamentSelection tournamentSelection = TournamentSelection(TOURNAMENT_PART);

        for(int i = 0; i < PROBLEMS_COUNT; i++)
        {
            std::cout<< "*****************KP"<< i + 1 <<"*****************"<< std::endl;
            GA.runIteration(knapsackProblems[i],tournamentSelection);
            std::cout << "BEST SOLUTION: ";
            GA.printBestSolution();
            std::cout << "BEST FITNESS: ";
            std::cout << GA.getCurrentBestFitness() << std::endl;
        }



    } catch (const FileReadError &e) {
        std::cout << e.description() << std::endl;
        return 1;
    }
    catch (const ObjectConstructionError &e) {
        std::cout << e.description() << std::endl;
        return 2;
    }




    return 0;
}
