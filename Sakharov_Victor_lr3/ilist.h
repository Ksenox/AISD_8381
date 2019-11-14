#ifndef ILIST_H
#define ILIST_H

template <class T>
struct IList {
    virtual void insert(int index, T element) = 0;
    virtual void push(T element) = 0;
    virtual T remove(int index) = 0;
    virtual T pop() = 0;
    virtual T operator[] (int index) = 0;
    virtual int length() = 0;
    virtual ~IList(){}
};

#endif // ILIST_H
