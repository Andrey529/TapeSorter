#include <iostream>
#include "TapeSorter.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Wrong number of arguments. Must be: "
                     "<program name> <input_file> <output_file>";
        return -1;
    }

    TapeSorter::TapeSorter tapeSorter;
    try {
        TapeSorter::TapeImpl tapeImplOrigin(argv[1]);
        TapeSorter::Tape &tapeOrigin = tapeImplOrigin;

        TapeSorter::TapeImpl tapeImplResult(argv[2]);
        TapeSorter::Tape &tapeResult = tapeImplResult;

        std::string outputTempTapeFilesName("../tmp/");
        int countElementsInTempTape = 2;
        tapeSorter.sort(tapeOrigin, tapeResult, outputTempTapeFilesName, countElementsInTempTape);
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
        return -1;
    }

    return 0;
}
