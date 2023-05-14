#include "TapeGenerator.h"

void
TapeSorter::TapeGenerator::generateTape(const std::string &fileName, const size_t &countElements, const int &leftBorder,
                                        const int &rightBorder) {
    std::ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        std::mt19937 generator(std::chrono::steady_clock::now().time_since_epoch().count()); //generator random values
        std::uniform_int_distribution<> range(leftBorder, rightBorder);

        for (int i = 0; i < countElements - 1; ++i) {
            outputFile << std::to_string(range(generator)) << ' ';
        }
        outputFile << std::to_string(range(generator));
    }

}
