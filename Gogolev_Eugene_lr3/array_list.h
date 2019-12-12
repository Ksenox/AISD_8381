#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H


struct array_list
{
    int* array;
    int capacity;
    int count;

    void resize(int new_capacity);
    array_list(int start_capacity = 4);
    int& operator[] (int index);
    void clean();
    void insert(int index, int element);
    int remove(int index);

    int back();
    void push_back(int element);
    int pop_back();

    int front();
    void push_front(int element);
    int pop_front();

    int size();
    bool empty();
};

#endif // ARRAY_LIST_H
