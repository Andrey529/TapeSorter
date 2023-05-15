#include <iostream>
#include "TapeSorter.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Wrong number of arguments. Must be: "
                     "<program name> <input_file> <output_file>";
        return -1;
    }

    TapeSorter::TapeSorter tapeSorter(argv[1], argv[2]);
    try {
        tapeSorter.sort("../tmp/", 2);
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
        return -1;
    }

    return 0;
}
