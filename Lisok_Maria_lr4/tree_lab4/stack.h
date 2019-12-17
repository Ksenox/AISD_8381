#ifndef stack_h
#define stack_h

#include "allheaders.h"

template<class T>
class Stack
{
    public:
        Stack(size_t n=50)
        : SIZE{ n }, top{}, items{ new T[SIZE]{} }
        {}
        ~Stack() {delete[] items;}
        void push(T);
        void pop();
        T* onTop() const;
        bool isFull() const{return SIZE == top;}
        bool isEmpty() const{return top==0;}
        size_t size() const {return SIZE;}
        size_t length() const {return top;}
        void clear(){top=0;}
        void setSize(size_t n){SIZE=n; items=new T[SIZE]{}; top=0;}
    private:
        size_t SIZE;
        size_t top;
        T *items;
};

template<class T>
void Stack<T>::push(T item)
{
    if(!isFull()){
        items[top++] = item;
    }
    else
        cout<<"Стек полон\n";
}

template<class T>
void Stack<T>::pop()
{
    if(!isEmpty()){
        top--;
    }
    else
        cout<<"Стек пуст\n";
}

template<class T>
T *Stack<T>::onTop() const
{
    if(!isEmpty())
        return &items[top-1];
    else{
        cout<<"Стек пуст\n";
        return nullptr;
    }
}
#endif
