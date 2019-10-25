//
// Created by alex on 10/21/19.
//

#include "universal_exception.h"


const char *universal_exception::what() const noexcept {
    return toString().c_str();
}

universal_exception::universal_exception(int cause_num, long sourcePos, string* source) noexcept(true) : std::exception() {
    this->source = source;
    this->sourcePos = sourcePos;

    switch (cause_num) {
        case OUTPUT_FILE_EXCEPTION_CODE:
            this->cause = OUTPUT_FILE_EXCEPTION_STRING;
            break;
        case INPUT_FILE_EXCEPTION_CODE:
            this->cause = INPUT_FILE_EXCEPTION_STRING;
            break;
        case STACK_SIZE_EXCEPTION_CODE:
            this->cause = STACK_SIZE_EXCEPTION_STRING;
            break;
        case STACK_MISMATCH_EXCEPTION_CODE:
            this->cause = STACK_MISMATCH_EXCEPTION_STRING;
            break;
        case STRANGE_INPUT_EXCEPTION_CODE:
            this->cause = STRANGE_INPUT_EXCEPTION_STRING;
            break;
        default:
            this->cause = UNHANDLED_EXCEPTION_STRING;
            break;
    }
}

universal_exception::universal_exception(int cause_num) noexcept(true) : universal_exception(cause_num, NULL_POS, nullptr) {}

universal_exception::~universal_exception() = default;

string universal_exception::toString() const {
    string out;
    if (sourcePos != NULL_POS) {
        out += *source + "\n";
        for (int i = 0; i < sourcePos; ++i) {
            out += ' ';
        }
        out += "^";
        out += "\n" + cause;
    } else {
        out = cause;
    }
    return out;
}
