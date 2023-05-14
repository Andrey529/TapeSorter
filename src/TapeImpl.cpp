#include "TapeImpl.h"

TapeSorter::TapeImpl::TapeImpl(const std::string &fileName) : Tape(fileName) { }

TapeSorter::TapeImpl::TapeImpl(std::string &&fileName) : Tape(std::move(fileName)) { }

TapeSorter::TapeImpl::~TapeImpl() = default;


std::vector<int> TapeSorter::TapeImpl::readTape(const size_t &countElements) const {
    std::ifstream inputFile(fileName_);
    if (inputFile.is_open()) {
        std::vector<int> elements;
        std::string elementInString;
        size_t currentCountElements = 0;
        while (currentCountElements < countElements) {
            char c = inputFile.get();

            if (inputFile.eof()) {
                break;
            }

            if (c == ' ') {
                ++currentCountElements;
                elements.push_back(std::stoi(elementInString));
                elementInString.clear();
                continue;
            }

            elementInString += c;
        }

        if (inputFile.eof() && !elementInString.empty()) {
            ++currentCountElements;
            elements.push_back(std::stoi(elementInString));
        }
        inputFile.close();
        return elements;
    }

    return {};
}

std::vector<int> TapeSorter::TapeImpl::readFullTape() const {
    return readTape(INT64_MAX);
}

int TapeSorter::TapeImpl::readFirstElemTape() const {
    return readTape(1)[0];
}

void TapeSorter::TapeImpl::writeTape(const std::vector<int> &elements) {
    std::ofstream outputFile(fileName_);
    if (outputFile.is_open()) {
        for (int i = 0; i < elements.size() - 1; ++i) {
            outputFile << elements[i] << ' ';
        }
        outputFile << elements[elements.size() - 1];
        outputFile.close();
    }
}

