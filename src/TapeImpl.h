#ifndef TAPESORTER_TAPEIMPL_H
#define TAPESORTER_TAPEIMPL_H

#include "Tape.h"

namespace TapeSorter {

    class TapeImpl : Tape {
        void readTape() override;
        void writeTape() override;
    };
} // namespace TapeSorter


#endif //TAPESORTER_TAPEIMPL_H
