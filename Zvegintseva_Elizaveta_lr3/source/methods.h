#ifndef METHODS_H
#define METHODS_H

#include "postfixform.h"
#include "stack.h"
#include <math.h>

void step(char, Stack<int>&, string&,string&);
int calc(const string&, string&,string&);
void onestep(char, Stack<int>&, string &,string&);

#endif // METHODS_H
