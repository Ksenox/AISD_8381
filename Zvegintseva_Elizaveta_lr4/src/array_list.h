#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
#include <string>
#include "node.h"

class array_list
{
private:
    Node** array;
    int capacity;
    int count;
    void resize(int new_capacity);

public:
    array_list(int start_capacity = 4);
    Node*& operator[] (int index);
    Node* at (int index);
    void clean();
    void insert(int index, Node* element);
    Node* remove(int index);

    Node* back();
    void push_back(Node* element);
    Node* pop_back();

    Node* front();
    void push_front(Node* element);
    Node* pop_front();

    int size();
    bool empty();
    ~array_list();
};

#endif // ARRAY_LIST_H
