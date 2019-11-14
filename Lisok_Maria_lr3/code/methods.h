#ifndef METHODS_H
#define METHODS_H

#include "stack.h"
#include <math.h>
bool isOperation(char);
void step(char, Stack<long long int>&, string&,string&);
long long int calculation(const string&, string&,string&);
void onestep(char, Stack<long long int>&, string &,string&);
#endif
