#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

int splitInputFile(const std::string &inputFileName) {
    std::ifstream inputFile(inputFileName);
    if (inputFile.is_open()) {
        const int partSize = 10;
        int partCount = 0;
        std::string numberInString;
        while (!inputFile.eof()) {
            ++partCount;
            int curruntPartSize = 0;
            std::ofstream outputFile("../tmp/" + std::to_string(partCount) + ".txt");
            while (curruntPartSize < partSize) {
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
        return partCount;
    }
    return -1;
}

void sortParts(const int &partsCount) {
    for (int i = 0; i < partsCount; ++i) {
        std::ifstream inputFile("../tmp/" + std::to_string(i + 1) + ".txt");
        if (inputFile.is_open()) {
            std::vector<int> numbers;
            std::string numberInString;
            while (true) {
                char c = inputFile.get();

                if (inputFile.eof()) {
                    break;
                }

                if (c == ' ') {
                    numbers.push_back(std::stoi(numberInString));
                    numberInString.clear();
                    continue;
                }

                numberInString += c;
            }

            if (inputFile.eof() && !numberInString.empty()) {
                numbers.push_back(std::stoi(numberInString));
            }

            inputFile.close();
            std::sort(numbers.begin(), numbers.end());
            std::ofstream outputFile("../tmp/" + std::to_string(i + 1) + ".txt");
            if (outputFile.is_open()) {
                for (int j = 0; j < numbers.size() - 1; ++j) {
                    outputFile << numbers[j] << ' ';
                }
                outputFile << numbers[numbers.size() - 1];
                outputFile.close();
            }


        }
    }
}

void generateInputFile() {
    std::ofstream outputFile("../tmp/input.txt");
    if (outputFile.is_open()) {
        std::mt19937 generator(std::chrono::steady_clock::now().time_since_epoch().count()); //generator random values
        std::uniform_int_distribution<> range(-1000, 1000);
//        size_t lines = std::abs(range(generator)) % 20;

        size_t lines = 10;
        if (lines == 0) ++lines;

        int numbersCount = 50;
        for (int i = 0; i < lines - 1; ++i) {
            for (int j = 0; j < (numbersCount / lines) - 1; ++j) {
                outputFile << std::to_string(range(generator)) << ' ';
            }
            outputFile << std::to_string(range(generator)) << '\n';
        }

        for (int j = 0; j < (numbersCount / lines) - 1; ++j) {
            outputFile << std::to_string(range(generator)) << ' ';
        }
        outputFile << std::to_string(range(generator));
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Wrong number of arguments. Must be: "
                     "<program name> <input_file> <output_file>";
        return -1;
    }
//    generateInputFile();

    int partsCount = splitInputFile(argv[1]);
    sortParts(partsCount);

    std::vector<std::ifstream> inputFiles;
    std::vector<int> numbers;

    for (int i = 0; i < partsCount; ++i) {
        inputFiles.emplace_back("../tmp/" + std::to_string(i + 1) + ".txt");
        if (inputFiles[i].is_open()) {
            std::string numberInString;
            while (true) {
                char c = inputFiles[i].get();

                if  ((c == ' ') || (inputFiles[i].eof() && !numberInString.empty())) {
                    numbers.push_back(std::stoi(numberInString));
                    break;
                }

                numberInString += c;
            }
            inputFiles[i].close();
        }
    }

    size_t indexMin = 0;
    int min = numbers[0];
    for (int i = 1; i < numbers.size(); ++i) {
        if (numbers[i] < min) {
            indexMin = i;
            min = numbers[i];
        }
    }


    std::ofstream resultFile(argv[2]);
    for (int i = 0; i < numbers.size(); ++i) {
        if (i == indexMin) {

        }
    }

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

    return 0;
}
