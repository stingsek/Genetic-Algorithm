cmake_minimum_required(VERSION 3.21)
project(TEP_LAB_MINIPROJEKT)

set(CMAKE_CXX_STANDARD 14)

add_executable(TEP_LAB_MINIPROJEKT main.cpp Individual.cpp Individual.h GeneticAlgorithm.cpp GeneticAlgorithm.h KnapsackProblem.cpp KnapsackProblem.h Problem.h FileReadError.h RandomGenerator.h Selection.h TournamentSelection.h TournamentSelection.cpp ObjectConstructionError.h)
