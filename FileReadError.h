//
// Created by Michał Żądełek on 16.01.2023.
//

#include <stdexcept>
#include <utility>

class FileReadError: public std::exception {
public:
    FileReadError(std::string fileName, std::string errorMessage) : fileName(std::move(fileName)),
                                                                           errorMessage(std::move(errorMessage)) {}
    const std::string& getFileName() const { return fileName; }

    const std::string& getErrorMessage() const { return errorMessage;}


    std::string description() const {
        return "file: " + getFileName() + "\nerror message: " + getErrorMessage();
    }


private:
    std::string fileName;
    std::string errorMessage;
};