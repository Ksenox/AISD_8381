#ifndef PAIRLIST_H
#define PAIRLIST_H
#include "pair.h"

// Class assignment:        Vector of elements any type (dynamic) for HASH TABLE
// Features:                Keeps info about it's CAPACITY
template <typename T>
class CVector
{
public:
    CVector();
    CVector(unsigned int nsize);
    unsigned int getCapacity();
    int length();
    int resize(unsigned int nsize);
    T & operator[](unsigned int index);
    CVector<T> & operator=(const CVector<T> &);
private:
    T *tail;                // Dynamic ARRAY of elements
    unsigned int capacity;  // Vector's CAPACITY
};

// Function assignment:     Empty vector constructor
// Features:                Allocates memory for one ARRAY element (updates CAPACITY)
template <typename T>
CVector<T>::CVector()
{
    tail = new T[1];
    capacity = 1;
};

// Function assignment:     Empty vector with fixed CAPACITY constructor
// Features:                Allocates memory for ARRAY (updates CAPACITY)
template <typename T>
CVector<T>::CVector(unsigned int nsize)
{
    capacity = nsize;
    tail = new T[capacity];
}

// Function assignment:     Returns vector's CAPACITY
template <typename T>
unsigned int CVector<T>::getCapacity()
{
    return capacity;
}

// Function assignment:     Returns vector's CAPACITY
template <typename T>
int CVector<T>::length()
{
    return capacity;
}

// Function assignment:     Reallocates memory for ARRAY (updates CAPACITY)
template <typename T>
int CVector<T>::resize(unsigned int nsize)
{
    if (nsize <= capacity)
        return 1;
    T *temp = new T[nsize];
    for (unsigned int i=0; i<capacity; i++)
    {
        temp[i] = tail[i];
    }
    capacity = nsize;
    delete [] tail;
    tail = temp;
    return 0;
}

template <typename T>
T& CVector<T>::operator[](unsigned int index)
{
    return tail[index];
}

template<class T>
CVector<T> & CVector<T>::operator = (const CVector<T> & v)
{
    delete[] tail;
    capacity = v.capacity;
    tail = new T[capacity];
    for (unsigned int i = 0; i < capacity; i++)
        tail[i] = v.tail[i];
    return *this;
}

#endif // PAIRLIST_H
