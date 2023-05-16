#ifndef TAPESORTER_TAPESORTER_H
#define TAPESORTER_TAPESORTER_H

#include "TapeImpl.h"
#include "TapeExceptions.h"
#include <unordered_map>

namespace TapeSorter {
    class TapeSorter {
    public:
        TapeSorter();

        ~TapeSorter();

        void sort(const Tape &inputTape, Tape &outputTape, const std::string &outputTempTapeFilesName, const int &countElementsInTempTape);

    private:

        size_t splitInputTape(const Tape &inputTape, const std::string &outputTempTapeFilesName, const int &countElementsInTempTape);

        void sortTempTapes(const size_t &tempTapesCount, const std::string &outputTempTapeFilesName);

        void formResultTape(Tape &outputTape, const size_t &tempTapesCount, const std::string &outputTempTapeFilesName);
    };
} // namespace TapeSorter


#endif //TAPESORTER_TAPESORTER_H
