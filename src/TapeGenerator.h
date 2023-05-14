#ifndef TAPESORTER_TAPEGENERATOR_H
#define TAPESORTER_TAPEGENERATOR_H

#include <random>
#include <chrono>

#include "TapeImpl.h"


namespace TapeSorter {
    class TapeGenerator {
    public:
        static void generateTape(const std::string &fileName, const size_t &countElements,
                          const int &leftBorder, const int &rightBorder);

    };

}


#endif //TAPESORTER_TAPEGENERATOR_H
