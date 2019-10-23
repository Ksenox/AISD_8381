//
// Created by alex on 10/21/19.
//

#ifndef ALG_LAB1_UNIVERSAL_EXCEPTION_H
#define ALG_LAB1_UNIVERSAL_EXCEPTION_H

#include <bits/stdc++.h>


#define EXIT_ERROR_CODE 42
#define NULL_POS -1


#define OUTPUT_FILE_EXCEPTION_CODE -1
#define OUTPUT_FILE_EXCEPTION_STRING "THE EXCEPTION OCCURS WHILE CREATING OUTPUT FILE, APPLICATION TERMINATED"

#define INPUT_FILE_EXCEPTION_CODE -2
#define INPUT_FILE_EXCEPTION_STRING "THE EXCEPTION OCCURS WHILE READING INPUT FILE, APPLICATION TERMINATED"

#define STACK_SIZE_EXCEPTION_CODE 1
#define STACK_SIZE_EXCEPTION_STRING "POP METHOD INVOCED ON 0 LENGTH STACK, APPLICATION TERMINATED"

#define STACK_MISMATCH_EXCEPTION_CODE 10
#define STACK_MISMATCH_EXCEPTION_STRING "STACK SIZE AND CONTENTS SHOW WRONG STRING FORMAT"

#define STRANGE_INPUT_EXCEPTION_CODE 11
#define STRANGE_INPUT_EXCEPTION_STRING "WRONG CHARACTER IN INPUT STRING OR SOMETHING ELSE"

#define UNHANDLED_EXCEPTION_STRING "SOME UNHANDLED EXCEPTION HAPPENS, APPLICATION TERMINATED"


using namespace std;

class universal_exception : public std::exception {
private:
    string cause;
    string* source;
    long sourcePos;

public:
    const char* what() const noexcept override;

    universal_exception(int cause_num, long sourcePos, string* source) noexcept(true);

    explicit universal_exception(int cause_num) noexcept(true);

    ~universal_exception() override;

    string toString() const;
};

#endif //ALG_LAB1_UNIVERSAL_EXCEPTION_H
