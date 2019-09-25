#ifndef LABIO_H
#define LABIO_H

#include "structs.h"

const char* const Examples[]{
    "NOT(A)",
    "AND(OR(AND(OR(NOT(A)))))",
    "AND(B,   C, AND(A,B) )",
    "AND(TRUE,NOT(FALSE))",
    "AND(TRUE,NOT(FALSE),AND(A,B,NOT(TRUE)))",
    "AND(TRUE,NOT((FALSE))",
    "OR(A)",
    "AAA",
    "NOT(AND(A, NOT(ERR)))",
    "AND(NOT(A,B))"
};

string ProceedInput (int argc, char *argv[]);
string ReadFromFile (std::string filename = "input.txt");
string ReadFromConsole ();
string ReadRandomFromExamples ();
void ProceedOutput (std::string output, int indent);
void ProceedError (const std::string & error, int & pos);

#endif //LABIO_H
