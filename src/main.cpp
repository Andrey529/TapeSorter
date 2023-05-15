#include <iostream>
#include "TapeSorter.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Wrong number of arguments. Must be: "
                     "<program name> <input_file> <output_file>";
        return -1;
    }

    TapeSorter::TapeSorter tapeSorter(argv[1], argv[2]);
    tapeSorter.sort("../tmp/", 10);

    return 0;
}
