#ifndef SAKHAROV_LR2_LABIO_H
#define SAKHAROV_LR2_LABIO_H

#include "LabExec.h"

string ProceedInput (int argc, char *argv[]);
string ReadFromFile (std::string filename = "input.txt");
string ReadFromConsole ();
extern bool errorFlag;
extern int errorPos;
void ProceedError (const std::string & error, int pos);

#endif //LR2_LABIO_H
