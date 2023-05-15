#include "TapeImpl.h"

TapeSorter::TapeImpl::TapeImpl(const std::string &fileName) : Tape(fileName) {}

TapeSorter::TapeImpl::TapeImpl(std::string &&fileName) : Tape(std::move(fileName)) {}

TapeSorter::TapeImpl::~TapeImpl() = default;


std::vector<int> TapeSorter::TapeImpl::read(const size_t &countElements) const {
    std::ifstream inputFile(fileName_);
    if (inputFile.is_open()) {
        std::vector<int> elements;
        std::string elementInString;
        size_t currentCountElements = 0;
        while (currentCountElements < countElements) {
            char c = static_cast<char>(inputFile.get());

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

        if (elements.empty()) {
            throw EmptyTapeException();
        }
        return elements;
    }

    throw UnableToOpenFileException();
}

std::vector<int> TapeSorter::TapeImpl::readFull() const {
    try {
        return read(INT64_MAX);
    }
    catch (const std::exception &) {
        throw;
    }
}

int TapeSorter::TapeImpl::readFirstElement() const {
    try {
        std::vector<int> elements = read(1);
        return elements[0];
    } catch (const std::exception &) {
        throw;
    }
}

void TapeSorter::TapeImpl::writeElements(const std::vector<int> &elements) {
    std::ofstream outputFile(fileName_);
    if (outputFile.is_open()) {
        if (elements.empty()) {
            throw EmptyTapeException();
        }
        for (int i = 0; i < elements.size() - 1; ++i) {
            outputFile << elements[i] << ' ';
        }
        outputFile << elements[elements.size() - 1];
        outputFile.close();
    } else {
        throw UnableToOpenFileException();
    }
}

void TapeSorter::TapeImpl::eraseFirstElement() {
    try {
        std::vector<int> elements = readFull();
        elements.erase(elements.begin());

        writeElements(elements);
    } catch (const std::exception &) {
        throw;
    }
}

