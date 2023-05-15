#ifndef TAPESORTER_TAPE_H
#define TAPESORTER_TAPE_H

#include <string>
#include <vector>

namespace TapeSorter {
    class Tape {
    public:
        const std::string fileName_;

        Tape(const std::string &fileName) : fileName_(fileName) {}

        Tape(std::string &&fileName) : fileName_(std::move(fileName)) {}

        [[nodiscard]] virtual std::vector<int> read(const size_t &countElements) const = 0;

        [[nodiscard]] virtual std::vector<int> readFull() const = 0;

        [[nodiscard]] virtual int readFirstElement() const = 0;

        virtual void writeElements(const std::vector<int> &elements) = 0;

        virtual void eraseFirstElement() = 0;

        virtual ~Tape() = default;
    };

} // namespace TapeSorter


#endif //TAPESORTER_TAPE_H
