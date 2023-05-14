#ifndef TAPESORTER_TAPEIMPL_H
#define TAPESORTER_TAPEIMPL_H

#include "Tape.h"
#include <fstream>

namespace TapeSorter {

    class TapeImpl : public Tape {
    public:

        TapeImpl(const std::string &fileName);
        TapeImpl(std::string &&fileName);
        ~TapeImpl() override;

        [[nodiscard]] std::vector<int> readTape(const size_t &countElements) const override;
        [[nodiscard]] std::vector<int> readFullTape() const override;
        [[nodiscard]] int readFirstElemTape() const override;
        void writeTape(const std::vector<int> &elements) override;
    };
} // namespace TapeSorter

#endif //TAPESORTER_TAPEIMPL_H
