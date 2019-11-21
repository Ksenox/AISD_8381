#ifndef UTILS_VECTOR_H
#define UTILS_VECTOR_H
#include "ilist.h"

template <class T>
class utils_vector : public IList<T>
{
private:
    T* array;
    int capacity;
    int count;
    void resize(int new_capacity);

public:
    utils_vector(int start_capacity = 4);
    utils_vector(const utils_vector& copy);
    T operator[] (int index) override;
    T at (int index) override;
    void clean() override;
    void insert(int index, T element) override;
    T remove(int index) override;

    T back() override;
    void push_back(T element) override;
    T pop_back() override;

    T front() override;
    void push_front(T element) override;
    T pop_front() override;

    int size() override;
    bool empty() override;
    ~utils_vector();
};

template<class T>
void utils_vector<T>::resize(int new_capacity)
{
    auto *arr = new T[count];
    for (int i = 0; i < count; ++i)
    {
        arr[i] = array[i];
    }
    delete [] array;
    array = new T[new_capacity];
    for (int i = 0 ; i < count; ++i)
    {
        array[i] = arr[i];
    }
    delete [] arr;
    capacity = new_capacity;
}

template<class T>
utils_vector<T>::utils_vector(int start_capacity)
{
    capacity = start_capacity;
    count = 0;
    array = new T[capacity];
}

template<class T>
utils_vector<T>::utils_vector(const utils_vector & copy) :
    count(copy.size),
    capacity(copy.capacity)
{
    array = new T[capacity];
    for (int i = 0; i < count; ++i)
    {
        *(array + i) = *(copy.__arr + i);
    }
}

template <class T>
T utils_vector<T>::operator[] (int index)
{
    return array[index];
}

template <class T>
T utils_vector<T>::at (int index)
{
    return operator[](index);
}

template <class T>
void utils_vector<T>::clean ()
{
    count = 0;
}

template <class T>
void utils_vector<T>::insert(int index, T element)
{
    if (capacity == count)
    {
        resize(count + 8);
    }
    if (count > 0) {
        for (int i = count; i > index; i--)
        {
            array[i] = array[i - 1];
        }
    }
    count++;
    array[index] = element;
}

template<class T>
T utils_vector<T>::remove(int index)
{
    auto temp = array[index];
    for (int i = index; i < count - 1; i++)
    {
        array[i] = array[i + 1];
    }
    count--;
    return temp;
}

template<class T>
T utils_vector<T>::back()
{
    return array[count - 1];
}

template<class T>
void utils_vector<T>::push_back(T element)
{
    if (capacity == count)
    {
        resize(count + 8);
    }
    array[count] = element;
    count++;
}

template<class T>
T utils_vector<T>::pop_back()
{
    return array[--count];
}

template<class T>
T utils_vector<T>::front()
{
    return *array;
}

template<class T>
void utils_vector<T>::push_front(T element)
{
    insert(0, element);
}

template<class T>
T utils_vector<T>::pop_front()
{
    return remove(0);
}

template<class T>
int utils_vector<T>::size()
{
    return count;
}

template<class T>
bool utils_vector<T>::empty()
{
    return !count;
}

template<class T>
utils_vector<T>::~utils_vector()
{
    delete [] array;
}

#endif //VECTOR_VECTOR_H
