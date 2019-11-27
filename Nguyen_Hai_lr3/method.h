#ifndef METHOD_H
#define METHOD_H
#include <string>
#include <QString>

using namespace std;

class method
{
public:
    void swap(int &a, int &b);
    void selectionSort_1(int *arr, int size, string *analize, string *result);
    void selectionSort_2(int *arr, int size, string *analize, string *result);
};

#endif // METHOD_H
