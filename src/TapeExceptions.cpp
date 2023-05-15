#include "TapeExceptions.h"

TapeSorter::EmptyTapeException::EmptyTapeException() : message_("Tape is empty") {}

TapeSorter::EmptyTapeException::EmptyTapeException(const char *message) : message_(message) {}

const char *TapeSorter::EmptyTapeException::what() const noexcept {
    return message_;
}


TapeSorter::UnableToOpenFileException::UnableToOpenFileException() : message_("Unable to open the file") {}

TapeSorter::UnableToOpenFileException::UnableToOpenFileException(const char *message) : message_(message) {}

const char *TapeSorter::UnableToOpenFileException::what() const noexcept {
    return message_;
}
