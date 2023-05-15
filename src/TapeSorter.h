#ifndef TAPESORTER_TAPESORTER_H
#define TAPESORTER_TAPESORTER_H

#include "TapeImpl.h"
#include "TapeExceptions.h"
#include <unordered_map>

namespace TapeSorter {
    class TapeSorter {
    public:
        TapeSorter(const std::string &inputFileName, const std::string &outputFileName);

        TapeSorter(std::string &&inputFileName, std::string &&outputFileName);

        ~TapeSorter();

        void sort(const std::string &outputTempTapeFilesName, const int &countElementsInTempTape);

    private:
        std::string inputFileName_;
        std::string outputFileName_;

        size_t splitInputTape(const std::string &outputTempTapeFilesName, const int &countElementsInTempTape);

        void sortTempTapes(const size_t &tempTapesCount, const std::string &outputTempTapeFilesName);

        void formResultTape(const size_t &tempTapesCount, const std::string &outputTempTapeFilesName);
    };
} // namespace TapeSorter


#endif //TAPESORTER_TAPESORTER_H
