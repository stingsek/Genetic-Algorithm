//
// Created by Michał Żądełek on 24.01.2023.
//

#ifndef TEP_LAB_MINIPROJEKT_OBJECTCONSTRUCTIONERROR_H
#define TEP_LAB_MINIPROJEKT_OBJECTCONSTRUCTIONERROR_H

#include <exception>
#include <string>

class ObjectConstructionError: public std::exception {
public:
    ObjectConstructionError(std::string className, std::string errorMessage) : className(std::move(className)),
                                                                              errorMessage(std::move(errorMessage)) {}
    const std::string& getFileName() const { return className; }

    const std::string& getErrorMessage() const { return errorMessage;}


    std::string description() const {
        return "class: " + getFileName() + "\nerror message: " + getErrorMessage();
    }


private:
    std::string className;
    std::string errorMessage;
};


#endif //TEP_LAB_MINIPROJEKT_OBJECTCONSTRUCTIONERROR_H
