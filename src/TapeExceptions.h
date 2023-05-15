#ifndef TAPESORTER_TAPEEXCEPTIONS_H
#define TAPESORTER_TAPEEXCEPTIONS_H

#include <exception>
#include <string>

namespace TapeSorter {
    class EmptyTapeException : public std::exception {
    private:
        const char *message_;
    public:
        EmptyTapeException();

        EmptyTapeException(const char *message);

        const char *what() const noexcept override;
    };


    class UnableToOpenFileException : public std::exception {
    private:
        const char *message_;
    public:
        UnableToOpenFileException();

        UnableToOpenFileException(const char *message);

        const char *what() const noexcept override;
    };

} // namespace TapeSorter


#endif //TAPESORTER_TAPEEXCEPTIONS_H
