//
// Created by Michał Żądełek on 01.01.2023.
//

#ifndef TEP_LAB_MINIPROJEKT_KNAPSACKPROBLEM_H
#define TEP_LAB_MINIPROJEKT_KNAPSACKPROBLEM_H

#include <fstream>
#include "Individual.h"

class KnapsackProblem : public Problem {
public:

    explicit KnapsackProblem(const std::string &path);

    KnapsackProblem(unsigned int problemSize, double knapsackCapacity, std::vector<double> &itemsSizes,
                    std::vector<double> &itemsValues);

    ~KnapsackProblem() override = default;

    KnapsackProblem(KnapsackProblem &&other)  noexcept ;

    KnapsackProblem(const KnapsackProblem &other) = default;

    KnapsackProblem &operator=(const KnapsackProblem &other) = default;

    KnapsackProblem &operator=(KnapsackProblem &&other) = default;

    double evaluate(const std::vector<bool> &genotype) override;


private:

    void initialize(unsigned int problemSize, double knapsckCapacity, std::vector<double>& itmsSizes,
                    std::vector<double>& itmsValues);

    void readFromFile(const std::string &path);
    static std::string getProbSizeErrMss();
    static std::string getSizeErrMss();
    static std::string getItemSizeErrMss();
    static std::string getItemValueErrMss();
    static std::string getKnapsackCapacityErrMss();

    double knapsackCapacity{};
    std::vector<double> itemsSizes;
    std::vector<double> itemsValues;
};


#endif //TEP_LAB_MINIPROJEKT_KNAPSACKPROBLEM_H
