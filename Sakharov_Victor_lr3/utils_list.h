#ifndef UTILS_LIST_H
#define UTILS_LIST_H
#include "ilist.h"

template <class T>
class utils_list : public IList<T>
{
public:
    utils_list(int start_capacity = 16);
    void insert(int index, T element) override;
    void push(T element) override;
    T remove(int index) override;
    T pop() override;
    T operator[] (int index) override;
    int length() override;
    ~utils_list();

private:
    T* array;
    int capacity;
    int count;
};

#include "utils_list.h"

template<class T>
utils_list<T>::utils_list(int start_capacity)
{
    capacity = start_capacity;
    count = 0;
    array = new T[capacity];
}

template<class T>
void utils_list<T>::insert(int index, T element)
{
    if (capacity == count)
    {
        capacity += 8;
        auto temp_array = new T[capacity];
        for (int i = 0; i < count; ++i)
        {
            temp_array[i] = array[i];
        }
        delete array;
        array = temp_array;
    }

    if (count > 0) {
        for (int i = count; i > index; i--)
            array[i] = array[i - 1];
    }
    count++;

    array[index] = element;
}

template<class T>
void utils_list<T>::push(T element)
{
    if (capacity == count)
    {
        capacity += 8;
        auto temp_array = new T[capacity];
        for (int i = 0; i < count; ++i)
        {
            temp_array[i] = array[i];
        }
        delete array;
        array = temp_array;
    }
    array[++count] = element;
}

template<class T>
T utils_list<T>::remove(int index)
{
    auto temp = array[index];
    for (int i = index; i < count; i++)
        array[i] = array[i + 1];
    count--;
    return temp;
}

template<class T>
T utils_list<T>::pop()
{
    count--;
    return array[count];
}

template<class T>
T utils_list<T>::operator[](int t_index)
{
    return *(array + t_index);
}

template<class T>
int utils_list<T>::length()
{
    return count;
}

template <class T>
utils_list<T>::~utils_list()
{
    delete [] array;
}


#endif // UTILS_LIST_H
