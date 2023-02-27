//
// Created by Michał Żądełek on 02.01.2023.
//

#ifndef TEP_LAB_MINIPROJEKT_PROBLEM_H
#define TEP_LAB_MINIPROJEKT_PROBLEM_H


#include <string>
#include <vector>

class Problem {
public:
    Problem() = default;

    explicit Problem(unsigned int problemSize) : problemSize(problemSize) {}

    Problem(const Problem &other) = default;

    Problem(Problem &&other) = default;

    Problem &operator=(const Problem &other) = default;

    Problem &operator=(Problem &&other) = default;

    virtual ~Problem() = default;

    virtual double evaluate(const std::vector<bool> &genotype) = 0;

    unsigned int getProblemSize() const { return problemSize; }

protected:
    unsigned int problemSize{};

};


#endif //TEP_LAB_MINIPROJEKT_PROBLEM_H
