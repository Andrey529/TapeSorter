#include <iostream>
#include "TapeSorter.h"

TapeSorter::TapeSorter::TapeSorter(const std::string &inputFileName, const std::string &outputFileName)
        : inputFileName_(inputFileName), outputFileName_(outputFileName) {}

TapeSorter::TapeSorter::TapeSorter(std::string &&inputFileName, std::string &&outputFileName)
        : inputFileName_(std::move(inputFileName)), outputFileName_(std::move(outputFileName)) {}

TapeSorter::TapeSorter::~TapeSorter() = default;


void TapeSorter::TapeSorter::sort(const std::string &outputPartFilesName, const int &countElementsInPart) {
    try {
        size_t partsCount = splitInputTape(outputPartFilesName, countElementsInPart);
        sortParts(partsCount, outputPartFilesName);
        formResultTape(partsCount, outputPartFilesName);
    } catch (const std::exception &exception) {
        throw;
    }
}

size_t TapeSorter::TapeSorter::splitInputTape(const std::string &outputPartFilesName, const int &countElementsInPart) {
    std::ifstream inputFile(inputFileName_);
    if (inputFile.is_open()) {
        int partsCount = 0;
        std::string numberInString;
        while (!inputFile.eof()) {
            ++partsCount;
            int curruntPartSize = 0;
            std::ofstream outputFile(outputPartFilesName + std::to_string(partsCount) + ".txt");
            while (curruntPartSize < countElementsInPart) {
                char c = static_cast<char>(inputFile.get());

                if (c == ' ' || c == '\n') {
                    ++curruntPartSize;
                    outputFile << numberInString << ' ';
                    numberInString.clear();
                    continue;
                }

                if (inputFile.eof()) {
                    ++curruntPartSize;
                    outputFile << numberInString;
                    numberInString.clear();
                    break;
                }


                numberInString += c;
            }
            outputFile.close();
        }
        inputFile.close();
        return partsCount;
    }
    return -1;
}

void TapeSorter::TapeSorter::sortParts(const size_t &partsCount, const std::string &outputPartFilesName) {
    try {
        for (int i = 0; i < partsCount; ++i) {
            std::string fileName(outputPartFilesName + std::to_string(i + 1) + ".txt");
            TapeImpl tapeImple(fileName);
            Tape &tape = tapeImple;

            std::vector<int> elements = tape.readFull();
            if (!elements.empty()) {
                std::sort(elements.begin(), elements.end());

                tape.writeElements(elements);
            }
        }
    } catch (const std::exception &) {
        throw;
    }
}

void TapeSorter::TapeSorter::formResultTape(const size_t &partsCount, const std::string &outputPartFilesName) {

    using index = int;
    using element = int;

    std::unordered_map<index, element> firstElements;

    for (int i = 0; i < partsCount; ++i) {
        std::string fileName(outputPartFilesName + std::to_string(i + 1) + ".txt");
        TapeImpl tapeImple(fileName);
        Tape &tape = tapeImple;

        try {
            firstElements.emplace(i, tape.readFirstElement());
        } catch (const std::exception &) {
            throw;
        }
    }

    std::ofstream resultFile(outputFileName_);

    while (true) {
        index indexMin = -1;
        element minFirstElem;
        for (const auto &elem: firstElements) {
            if (indexMin == -1) {
                indexMin = elem.first;
                minFirstElem = elem.second;
            } else {
                if (elem.second < minFirstElem) {
                    indexMin = elem.first;
                    minFirstElem = elem.second;
                }
            }
        }

        if (indexMin == -1) {
            resultFile.close();
            break;
        }

        resultFile << minFirstElem << ' ';

        std::string fileName(outputPartFilesName + std::to_string(indexMin + 1) + ".txt");
        TapeImpl tapeImple(fileName);
        Tape &tape = tapeImple;

        try {
            tape.eraseFirstElement();
            firstElements[indexMin] = tape.readFirstElement();
        } catch (const EmptyTapeException &) {
            firstElements.erase(indexMin);
        } catch (const std::exception &) {
            resultFile.close();
            throw;
        }
    }

}

