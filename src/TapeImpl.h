#ifndef TAPESORTER_TAPEIMPL_H
#define TAPESORTER_TAPEIMPL_H

#include <fstream>
#include <iostream>

#include "Tape.h"
#include "TapeExceptions.h"

namespace TapeSorter {

    class TapeImpl : public Tape {
    public:

        TapeImpl(const std::string &fileName);

        TapeImpl(std::string &&fileName);

        ~TapeImpl() override;

        [[nodiscard]] std::vector<int> read(const size_t &countElements) const override;

        [[nodiscard]] std::vector<int> readFull() const override;

        [[nodiscard]] int readFirstElement() const override;

        void writeElements(const std::vector<int> &elements) override;

        void eraseFirstElement() override;

    };
} // namespace TapeSorter

#endif //TAPESORTER_TAPEIMPL_H
