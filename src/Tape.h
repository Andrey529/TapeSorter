#ifndef TAPESORTER_TAPE_H
#define TAPESORTER_TAPE_H


#include <fstream>

namespace TapeSorter {
    class Tape {
    public:
        virtual void readTape() = 0;
        virtual void writeTape() = 0;

        virtual ~Tape() = default;
    };

} // namespace TapeSorter


#endif //TAPESORTER_TAPE_H
