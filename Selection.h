//
// Created by Michał Żądełek on 23.01.2023.
//

#include <vector>
#include "Individual.h"

#ifndef TEP_LAB_MINIPROJEKT_SELECTION_H
#define TEP_LAB_MINIPROJEKT_SELECTION_H

class Selection {
public:
    Selection() = default;

    Selection(const Selection &other) = default;

    Selection(Selection &&other) = default;

    Selection &operator=(const Selection &other) = default;

    Selection &operator=(Selection &&other) = default;

    virtual ~Selection() = default;

    virtual std::vector<Individual> selectParents(std::vector<Individual> &population) = 0;
};

#endif //TEP_LAB_MINIPROJEKT_SELECTION_H

