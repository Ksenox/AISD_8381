#ifndef UTILS_VECTOR_H
#define UTILS_VECTOR_H
#include "array_list.h"


void array_list::resize(int new_capacity)
{
    int *arr = new int[count];
    for (int i = 0; i < count; ++i)
    {
        arr[i] = array[i];
    }
    delete [] array;
    array = new int[new_capacity];
    for (int i = 0 ; i < count; ++i)
    {
        array[i] = arr[i];
    }
    delete [] arr;
    capacity = new_capacity;
}

array_list::array_list(int start_capacity)
{
    capacity = start_capacity;
    count = 0;
    array = new int[capacity];
}

int& array_list::operator[] (int index)
{
    return array[index];
}

void array_list::clean ()
{
    count = 0;
}

void array_list::insert(int index, int element)
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

int array_list::remove(int index)
{
    auto temp = array[index];
    for (int i = index; i < count - 1; i++)
    {
        array[i] = array[i + 1];
    }
    count--;
    return temp;
}

int array_list::back()
{
    return array[count - 1];
}

void array_list::push_back(int element)
{
    if (capacity == count)
    {
        resize(count + 8);
    }
    array[count] = element;
    count++;
}

int array_list::pop_back()
{
    return array[--count];
}

int array_list::front()
{
    return *array;
}

void array_list::push_front(int element)
{
    insert(0, element);
}

int array_list::pop_front()
{
    return remove(0);
}

int array_list::size()
{
    return count;
}

bool array_list::empty()
{
    return !count;
}

#endif //VECTOR_VECTOR_H
