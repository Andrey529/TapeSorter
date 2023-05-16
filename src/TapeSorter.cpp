#include <iostream>
#include "TapeSorter.h"

TapeSorter::TapeSorter::TapeSorter() = default;

TapeSorter::TapeSorter::~TapeSorter() = default;


void TapeSorter::TapeSorter::sort(const Tape &inputTape, Tape &outputTape, const std::string &outputTempTapeFilesName, const int &countElementsInTempTape) {
    try {
        size_t tempTapesCount = splitInputTape(inputTape, outputTempTapeFilesName, countElementsInTempTape);
        sortTempTapes(tempTapesCount, outputTempTapeFilesName);
        formResultTape(outputTape, tempTapesCount, outputTempTapeFilesName);
    } catch (const std::exception &exception) {
        throw;
    }
}

size_t TapeSorter::TapeSorter::splitInputTape(const Tape &inputTape, const std::string &outputTempTapeFilesName, const int &countElementsInTempTape) {
    std::ifstream inputFile(inputTape.fileName_);
    if (inputFile.is_open()) {
        int tempTapesCount = 0;
        std::string numberInString;
        while (!inputFile.eof()) {
            ++tempTapesCount;
            int curruntTempTapeSize = 0;
            std::ofstream outputFile(outputTempTapeFilesName + std::to_string(tempTapesCount) + ".txt");
            while (curruntTempTapeSize < countElementsInTempTape) {
                char c = static_cast<char>(inputFile.get());

                if (c == ' ' || c == '\n') {
                    ++curruntTempTapeSize;
                    outputFile << numberInString << ' ';
                    numberInString.clear();
                    continue;
                }

                if (inputFile.eof()) {
                    ++curruntTempTapeSize;
                    outputFile << numberInString;
                    numberInString.clear();
                    break;
                }


                numberInString += c;
            }
            outputFile.close();
        }
        inputFile.close();
        return tempTapesCount;
    }
    return -1;
}

void TapeSorter::TapeSorter::sortTempTapes(const size_t &tempTapesCount, const std::string &outputTempTapeFilesName) {
    try {
        for (int i = 0; i < tempTapesCount; ++i) {
            std::string fileName(outputTempTapeFilesName + std::to_string(i + 1) + ".txt");
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

void TapeSorter::TapeSorter::formResultTape(Tape &outputTape, const size_t &tempTapesCount, const std::string &outputTempTapeFilesName) {

    using index = int;
    using element = int;

    std::unordered_map<index, element> firstElements;

    for (int i = 0; i < tempTapesCount; ++i) {
        std::string fileName(outputTempTapeFilesName + std::to_string(i + 1) + ".txt");
        TapeImpl tapeImple(fileName);
        Tape &tape = tapeImple;

        try {
            firstElements.emplace(i, tape.readFirstElement());
        } catch (const std::exception &) {
            throw;
        }
    }

    std::ofstream resultFile(outputTape.fileName_);

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

        std::string fileName(outputTempTapeFilesName + std::to_string(indexMin + 1) + ".txt");
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

