#include <shellsort.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

int cinput();
void shellSort(int a[], int size, int sequence);
int incrementShell(int inc[], int size);
int incrementSedgewick(int inc[], int size);
int incrementHibbard(int inc[], int size);
int incrementPratt(int inc[], int size);
void reverseArray(int *a, int *b);
