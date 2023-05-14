#include <iostream>
#include "TapeSorter.h"
//#include "TapeGenerator.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Wrong number of arguments. Must be: "
                     "<program name> <input_file> <output_file>";
        return -1;
    }

//    TapeSorter::TapeGenerator::generateTape(argv[1], 100, -1000, 1000);

    TapeSorter::TapeSorter tapeSorter(argv[1], argv[2]);
    tapeSorter.process();

    return 0;
}
