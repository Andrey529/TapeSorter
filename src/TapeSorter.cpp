#include <iostream>
#include "TapeSorter.h"

TapeSorter::TapeSorter::TapeSorter(const std::string &inputFileName, const std::string &outputFileName)
        : inputFileName_(inputFileName), outputFileName_(outputFileName) {}

TapeSorter::TapeSorter::TapeSorter(std::string &&inputFileName, std::string &&outputFileName)
        : inputFileName_(std::move(inputFileName)), outputFileName_(std::move(outputFileName)) {}

TapeSorter::TapeSorter::~TapeSorter() = default;


void TapeSorter::TapeSorter::process() {
    std::string outputPartFilesName = "../tmp/";
    int countElementsInPart = 10;
    size_t partsCount = splitInputTape(inputFileName_, outputPartFilesName, countElementsInPart);
    sortParts(partsCount, outputPartFilesName);
    formResultTape(partsCount, outputPartFilesName);
}

size_t TapeSorter::TapeSorter::splitInputTape(const std::string &inputFileName, const std::string &outputPartFilesName,
                                              const int &countElementsInPart) {
    std::ifstream inputFile(inputFileName);
    if (inputFile.is_open()) {
        int partsCount = 0;
        std::string numberInString;
        while (!inputFile.eof()) {
            ++partsCount;
            int curruntPartSize = 0;
            std::ofstream outputFile(outputPartFilesName + std::to_string(partsCount) + ".txt");
            while (curruntPartSize < countElementsInPart) {
                char c = inputFile.get();

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
    for (int i = 0; i < partsCount; ++i) {
        std::string fileName(outputPartFilesName + std::to_string(i + 1) + ".txt");
        TapeImpl tapeImple(fileName);
        Tape &tape = tapeImple;

        std::vector<int> elements = tape.readFullTape();
        if (!elements.empty()) {
            std::sort(elements.begin(), elements.end());

            tape.writeTape(elements);
        }
    }
}

void TapeSorter::TapeSorter::formResultTape(const size_t &partsCount, const std::string &outputPartFilesName) {

    std::vector<int> firstElements;
    for (int i = 0; i < partsCount; ++i) {
        std::string fileName(outputPartFilesName + std::to_string(i + 1) + ".txt");
        TapeImpl tapeImple(fileName);
        Tape &tape = tapeImple;

        firstElements.emplace_back(tape.readFirstElemTape());
    }


    size_t indexMin = 0;
    int min = firstElements[0];
    for (int i = 1; i < firstElements.size(); ++i) {
        if (firstElements[i] < min) {
            indexMin = i;
            min = firstElements[i];
        }
    }

    for (int i = 0; i < firstElements.size(); ++i) {
        std::cout << firstElements[i] << ' ';
    }


//    std::ofstream resultFile(argv[2]);
//    for (int i = 0; i < numbers.size(); ++i) {
//        if (i == indexMin) {
//
//        }
//    }

//    while (true) {
//
//        int countEmpty = 0;
//        for (int i = 0; i < partsCount; ++i) {
//            if (inputFiles[i].eof()) {
//                countEmpty++;
//            }
//        }
//        if (countEmpty == partsCount) {
//            break;
//        }
//    }


}

