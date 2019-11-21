#ifndef PAIRLIST_H
#define PAIRLIST_H
#include "pair.h"

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
    T *tail;
    unsigned int capacity;
};

//constructors

template <typename T>
CVector<T>::CVector()
{
    tail = new T[1];
    capacity = 1;
};

template <typename T>
CVector<T>::CVector(unsigned int nsize)
{
    capacity = nsize;
    tail = new T[capacity];
}

//get info

template <typename T>
unsigned int CVector<T>::getCapacity()
{
    return capacity;
}

template <typename T>
int CVector<T>::length()
{
    return capacity;
}

//

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
