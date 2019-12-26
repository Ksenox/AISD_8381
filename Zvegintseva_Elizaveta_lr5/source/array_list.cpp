#ifndef UTILS_VECTOR_H
#define UTILS_VECTOR_H
#include "array_list.h"


void array_list::resize(int new_capacity)
{
    auto *arr = new Node*[count];
    for (int i = 0; i < count; ++i)
    {
        arr[i] = array[i];
    }
    delete [] array;
    array = new Node*[new_capacity];
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
    array = new Node*[capacity];
}

Node*& array_list::operator[] (int index)
{
    return array[index];
}

Node* array_list::at (int index)
{
    return operator[](index);
}

void array_list::clean ()
{
    count = 0;
}

void array_list::insert(int index, Node* element)
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

Node* array_list::remove(int index)
{
    auto temp = array[index];
    for (int i = index; i < count - 1; i++)
    {
        array[i] = array[i + 1];
    }
    count--;
    return temp;
}

Node* array_list::back()
{
    return array[count - 1];
}

void array_list::push_back(Node* element)
{
    if (capacity == count)
    {
        resize(count + 8);
    }
    array[count] = element;
    count++;
}

Node* array_list::pop_back()
{
    return array[--count];
}

Node* array_list::front()
{
    return *array;
}

void array_list::push_front(Node* element)
{
    insert(0, element);
}

Node* array_list::pop_front()
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

array_list::~array_list()
{
    delete [] array;
}

#endif //VECTOR_VECTOR_H
