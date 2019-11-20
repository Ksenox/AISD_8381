#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <QMessageBox>

class ShellSort
{
public:
    ShellSort();
    QString Shell(QString str_n, int sequence, int flag);
private:
    int incrementShell(int inc[], int size);
    int incrementSedgewick(int inc[], int size);
    int incrementHibbard(int inc[], int size);
    int incrementPratt(int inc[], int size);
    void reverseArray(int a[], int b[]);
};

#endif // SHELLSORT_H
