#ifndef CONSOLE_H
#define CONSOLE_H
#include <iostream>
#include <string>
#include <cstdlib>
#include "time.h"
using namespace std;

int consoleMain();
void freeFirstSecond(int** firstPart,int** secondPart);
void Merging(int* inputArray, unsigned int size, int** firstPart, int** secondPart);
void splitIntoTwo(int* inputArray, int** firstPart, int** secondPart, unsigned int size);
void NaturalMergingSort(int* inputArray,unsigned int size,int& step);
#endif // CONSOLE_H
