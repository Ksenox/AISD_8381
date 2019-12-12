#ifndef QUICKSORT3_H
#define QUICKSORT3_H
#include "array_list.h"
#include <string>

using namespace std;

void qsort3way(string& s, array_list& list, int l, int r, int depth = 0);
string log(array_list& list, int min, int max, int center, int depth);

#endif // QUICKSORT3_H
