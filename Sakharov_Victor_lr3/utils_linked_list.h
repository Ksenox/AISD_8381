#ifndef UTILS_LINKED_LIST_H
#define UTILS_LINKED_LIST_H
#include "ilist.h"

template<class T>
struct node{
    node* prev;
    T data;
    node* next;

    explicit node<T>(T d) {
        data = d;
    }
};

template <class T>
class utils_linked_list : public IList<T>
{
public:
    explicit utils_linked_list(int start_capacity = 16);
    void insert(int index, T element) override;
    void push(T element) override;
    T remove(int index) override;
    T pop() override;
    T operator[] (int index) override;
    int length() override;
    ~utils_linked_list();

private:
    node<T> *head;
    node<T> *tail;
};

#include "utils_linked_list.h"

template<class T>
void utils_linked_list<T>::insert(int index, T element)
{
    auto temp = head;
    for (int i = 0; i < index; ++i)
    {
        temp = temp->next;
    }

    auto *nNode = new node<T>(element);

    auto tempnNode = temp->next;
    temp->next = nNode;

    nNode->prev = temp;
    nNode->next = tempnNode;

    tempnNode->prev = nNode;
}

template<class T>
void utils_linked_list<T>::push(T element)
{
    auto *newelem = new node<T>(element);
    tail->next = newelem;
    newelem->prev = tail;
    newelem->next = nullptr;
    tail = newelem;
}

template<class T>
T utils_linked_list<T>::remove(int index)
{
    T elem;
    auto temp = head;
    for (int i = 0; i < index; ++i)
    {
        temp = temp->next;
    }
    auto next = temp->next;
    auto prev = temp->prev;
    next->prev = prev;
    prev->next = next;

    auto tdata = temp->data;
    delete temp;

    return tdata;
}

template<class T>
T utils_linked_list<T>::pop()
{
    auto elem = tail->data;
    auto pNode = tail;
    tail = tail->prev;
    delete pNode;
    tail->next = nullptr;
    return elem;
}

template<class T>
T utils_linked_list<T>::operator[](int index)
{
    auto temp = head;
    for (auto i = 0; i < index; ++i)
    {
        if (!temp->next)
        {
            return -1;
        }
        temp = temp->next;
    }
    return temp->data;
}

template<class T>
int utils_linked_list<T>::length()
{
    auto temp = head;
    auto length = 0;
    for (; temp->next != nullptr; ++length)
    {
        temp = temp->next;
    }
    return length;
}

template<class T>
utils_linked_list<T>::utils_linked_list(int start_capacity)
{
    head = new node<T>(0);
    head->prev = nullptr;
    tail = head;

    for (int i = 0; i < start_capacity; ++i)
    {
        auto next = new node<T>(0);
        next->prev = tail;
        tail->next = next;
        tail = next;
    }
    tail->next = nullptr;
}

template<class T>
utils_linked_list<T>::~utils_linked_list()
{
    auto temp = head;
    while (head->next)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
    delete head;
}


#endif // UTILS_LINKED_LIST_H
