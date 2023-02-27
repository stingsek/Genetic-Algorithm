//
// Created by Michał Żądełek on 01.01.2023.
//

#include "KnapsackProblem.h"
#include "FileReadError.h"
#include "ObjectConstructionError.h"
#include <regex>



KnapsackProblem::KnapsackProblem(unsigned int problemSize, double knapsackCapacity, std::vector<double> &itemsSizes,
                                 std::vector<double> &itemsValues) {
    if (problemSize <= 0)
        throw ObjectConstructionError("KnapsackProblem", getProbSizeErrMss() +
                                                         std::to_string(problemSize));
    if (knapsackCapacity <= 0)
        throw ObjectConstructionError("KnapsackProblem", getKnapsackCapacityErrMss() +
                                                         std::to_string(knapsackCapacity));
    if (!(itemsValues.size() == problemSize && itemsSizes.size() == problemSize))
        throw ObjectConstructionError("KnapsackProblem",
                                      getSizeErrMss() + "ItemsSizes.size(): " +
                                      std::to_string(itemsSizes.size()) + "\nItemsValues.size(): " +
                                      std::to_string(itemsValues.size()) + "\nprobSize: " +
                                      std::to_string(problemSize));
    for (int i = 0; i < problemSize; i++) {
        if (itemsSizes[i] <= 0)
            throw ObjectConstructionError("KnapsackProblem", getItemSizeErrMss() +
                                                             std::to_string(itemsSizes[i]));
        if (itemsValues[i] <= 0)
            throw ObjectConstructionError("KnapsackProblem", getItemValueErrMss() +
                                                             std::to_string(itemsValues[i]));
    }
    initialize(problemSize, knapsackCapacity, itemsSizes, itemsValues);

}

KnapsackProblem::KnapsackProblem(KnapsackProblem &&other) noexcept:
        Problem(std::move(other)),
        knapsackCapacity(other.knapsackCapacity),
        itemsSizes(std::move(other.itemsSizes)),
        itemsValues(std::move(other.itemsValues)) {}


void KnapsackProblem::readFromFile(const std::string &path) {

    /// opening a file
    std::ifstream file(path);
    if (!file.is_open()) {
        throw FileReadError(path, "Couldn't open a file");
    }


    std::string data;
    std::regex positiveIntRegex("^[1-9]\\d*$");
    std::regex positiveDoubleRegex(R"(^\+?[0-9]\d*(\.\d+)?$)");
    double tempDouble;
    int counter = 0;


    /// loading problemSize
    unsigned int probSize;
    file >> data;
    if (!(std::regex_match(data, positiveIntRegex)))
        throw FileReadError(path, getProbSizeErrMss() + data);
    probSize = std::stoi(data);


    /// loading knapsackCapacity
    double knpCapacity;
    file >> data;
    if (!(std::regex_match(data, positiveDoubleRegex)))
        throw FileReadError(path,
                            getKnapsackCapacityErrMss() + data);
    knpCapacity = std::stod(data);


    /// loading itemsSizes
    std::vector<double> itmsSizes;
    itmsSizes.reserve(probSize);


    while (counter < probSize && file >> data) {
        if (!(std::regex_match(data, positiveDoubleRegex)))
            throw FileReadError(path,
                                getItemSizeErrMss() + data);
        tempDouble = std::stod(data);
        itmsSizes.push_back(tempDouble);
        counter++;
    }


    ///loading itemValues
    std::vector<double> itmsValues;
    itmsValues.reserve(probSize);


    counter = 0;
    while (counter < probSize && file >> data) {
        if (!(std::regex_match(data, positiveDoubleRegex)))
            throw FileReadError(path,
                                getItemValueErrMss() + data);
        tempDouble = std::stod(data);
        itmsValues.push_back(tempDouble);
        counter++;
    }


    ///closing the file
    file.close();


    ///checking sizes of weights and values vectors (they should be equal)
    if (!(itmsSizes.size() == probSize && itmsValues.size() == probSize))
        throw FileReadError(path,
                            getSizeErrMss() + "problemSize: " +
                            std::to_string(probSize) + "\nitemsSizes.size(): " + std::to_string(itmsSizes.size()) +
                            "\nitemsValues.size(): " + std::to_string(itmsValues.size()));


    ///initialization of a valid knapsackProblem
    initialize(probSize, knpCapacity, itmsSizes, itmsValues);

}

double KnapsackProblem::evaluate(const std::vector<bool> &genotype) {
    double fitness = 0, totalSize = 0;

    for (int i = 0; i < problemSize; i++) {
        if (genotype[i]) {
            fitness += itemsValues[i];
            totalSize += itemsSizes[i];
        }
    }
    if (totalSize > knapsackCapacity)
        return 0;

    return fitness;
}

KnapsackProblem::KnapsackProblem(const std::string &path) {
    readFromFile(path);
}

void KnapsackProblem::initialize(unsigned int problemSize, double knapsckCapacity, std::vector<double> &itmsSizes,
                                 std::vector<double> &itmsValues) {
    this->problemSize = problemSize;
    this->knapsackCapacity = knapsckCapacity;
    this->itemsSizes = std::move(itmsSizes);
    this->itemsValues = std::move(itmsValues);

}

std::string KnapsackProblem::getProbSizeErrMss() {
    return "Wrong input in data 'probSize':\n Expected: positive int\n Provided: ";
}

std::string KnapsackProblem::getSizeErrMss() {
    return "'itemsValues.size()' and 'itemsSizes.size()' must be equal to 'problemSize'\nProvided:\n";
}

std::string KnapsackProblem::getItemSizeErrMss() {
    return "Wrong input in data 'itemSize':\n Expected: positive double\n Provided: ";
}

std::string KnapsackProblem::getItemValueErrMss() {
    return "Wrong input in data 'itemValue':\n Expected: positive double\n Provided: ";
}

std::string KnapsackProblem::getKnapsackCapacityErrMss() {
    return "Wrong input in data 'itemValue':\n Expected: positive double\n Provided: ";
}













