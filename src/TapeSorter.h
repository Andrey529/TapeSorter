#ifndef TAPESORTER_TAPESORTER_H
#define TAPESORTER_TAPESORTER_H


#include <fstream>

namespace TapeSorter {
    class TapeSorter {
    public:
        TapeSorter();
        void process();
        ~TapeSorter();
    private:
        std::ofstream outputFile_;
        std::ifstream inputFile_;
        void readInputTape();
        void writeOutputTape();
    };
} // namespace TapeSorter


#endif //TAPESORTER_TAPESORTER_H
