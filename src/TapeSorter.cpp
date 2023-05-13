#include "TapeSorter.h"

TapeSorter::TapeSorter::~TapeSorter() {
    if (inputFile_.is_open()) {
        inputFile_.close();
    }
    if (outputFile_.is_open()) {
        outputFile_.close();
    }

}
