#ifndef SORT_H
#define SORT_H
#include <string>
#include <QFileDialog>

using namespace std;
class SortSelection
{
public:
    void selectionSort_1(int *arr, int size, string *analize, string *result);
    void selectionSort_2(int *arr, int size, string *analize, string *result);
    void swap(int &a, int &b);
};

#endif // SORT_H
