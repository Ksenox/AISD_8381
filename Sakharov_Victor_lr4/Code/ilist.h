#ifndef ILIST_H
#define ILIST_H

template <class T>
struct IList {
    virtual T operator[] (int index) = 0;
    virtual T at (int index) = 0;
    virtual void clean() = 0;
    virtual void insert(int index, T element) = 0;
    virtual T remove(int index) = 0;

    virtual T back() = 0;
    virtual void push_back(T element) = 0;
    virtual T pop_back() = 0;

    virtual T front() = 0;
    virtual void push_front(T element) = 0;
    virtual T pop_front() = 0;

    virtual int size() = 0;
    virtual bool empty() = 0;
    virtual ~IList(){}
};

#endif // ILIST_H
