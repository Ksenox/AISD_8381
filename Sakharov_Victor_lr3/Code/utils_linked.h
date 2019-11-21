#ifndef UTILS_LINKED_H
#define UTILS_LINKED_H
#include "ilist.h"

template <class T>
struct node
{
    node* next;
    T data;
    node* prev;

    node(T d)
    {
        next = nullptr;
        data = d;
        prev = nullptr;
    }
};

template <class T>
class utils_linked : public IList<T>
{
private:
    node<T>* head;
    node<T>* tail;

public:
    utils_linked();
    utils_linked(const utils_linked& copy);
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
    ~utils_linked();
};


template<class T>
utils_linked<T>::utils_linked()
{
    head = nullptr;
    tail = nullptr;
}

template<class T>
utils_linked<T>::utils_linked(const utils_linked & copy)
{
//    head = nullptr;
//    tail = nullptr;
//    node<int>* copy_node = copy.head;
//    while (copy_node)
//    {
//        node<int>* t = new node<int>(copy_node->data);
//        head->prev = tail;
//        tail->next = head;
//        t->data
//    }
//    array = new T[capacity];
//    for (int i = 0; i < count; ++i)
//    {
//        *(array + i) = *(copy.__arr + i);
//    }
}


template <class T>
T utils_linked<T>::operator[] (int index)
{
    node<T>* t = head;
    for (int i = 0; i < index; i++)
    {
        t = t->next;
    }
    return t->data;
}

template <class T>
T utils_linked<T>::at (int index)
{
    return operator[](index);
}

template <class T>
void utils_linked<T>::clean ()
{
    node<T>* t = head;
    while (t)
    {
        delete t;
        t = t->next;
    }
    head = nullptr;
    tail = nullptr;
}

template <class T>
void utils_linked<T>::insert(int index, T element)
{
    node<T>* n = new node<T>(element);
    if (empty())
    {
        head = n;
        tail = n;
    }
    else if (index == 0)
    {
        push_front(element);
    }
    else if (index == size())
    {
        push_back(element);
    }
    else
    {
        node<T>* t = head;
        for (int i = 0; i < index; i++)
        {
            t = t->next;
        }
        n->next = t;
        n->prev = t->prev;
        t->prev->next= n;
        t->prev = n;
    }
}

template<class T>
T utils_linked<T>::remove(int index)
{
    T res = at(index);
    if (index == 0)
    {
        pop_front();
    }
    else if (index == size() - 1)
    {
        pop_back();
    }
    else {
        node<T> *t = head;
        for (int i = 0; i < index; i++) {
            t = t->next;
        }
        t->prev->next = t->next;
        t->next->prev = t->prev;
        delete t;
    }
    return res;
}

template<class T>
T utils_linked<T>::back()
{
    return tail->data;
}

template<class T>
void utils_linked<T>::push_back(T element)
{
    node<T>* n = new node<T>(element);
    if (empty())
    {
        head = n;
        tail = n;
    }
    else
    {
        tail->next = n;
        n->prev = tail;
        tail = n;
    }
}

template<class T>
T utils_linked<T>::pop_back()
{
    T data;
    if (size() == 1) {
        if (head != nullptr) {
            data = head->data;
            delete head;
            head = nullptr;
        } else if (tail != nullptr) {
            data = tail->data;
            delete tail;
            tail == nullptr;
        }
    }
    else {
        node<T> *n = tail;
        tail = tail->prev;
        tail->next = nullptr;
        data = n->data;
        delete n;
    }
    return data;
}

template<class T>
T utils_linked<T>::front()
{
    return head->data;
}

template<class T>
void utils_linked<T>::push_front(T element)
{
    node<T>* n = new node<T>(element);
    if (empty())
    {
        head = n;
        tail = n;
    }
    else
    {
        head->prev = n;
        n->next = head;
        head = n;
    }
}

template<class T>
T utils_linked<T>::pop_front()
{
    T data;
    if (size() == 1) {
        if (head != nullptr) {
            data = head->data;
            delete head;
            head = nullptr;
        } else if (tail != nullptr) {
            data = tail->data;
            delete tail;
            tail == nullptr;
        }
    }
    else {
        node<T> *n = head;
        head = head->next;
        head->prev = nullptr;
        data = n->data;
        delete n;
    }
    return data;
}


template<class T>
int utils_linked<T>::size()
{
    int i = 0;
    node<T>* t = head;
    while (t)
    {
        t = t->next;
        i++;
    }
    return i;
}

template<class T>
bool utils_linked<T>::empty()
{
    return !size();
}

template<class T>
utils_linked<T>::~utils_linked()
{
    node<T>* t = head;
    while (t)
    {
        delete t;
        t = t->next;
    }
}

#endif // UTILS_LINKED_H
