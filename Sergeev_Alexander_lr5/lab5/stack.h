#ifndef STACK_H
#define STACK_H


#include <cstdlib>
#include <stdexcept>

template <typename T>
class stack {
private:
    class stack_element {
    private:
        T value;
        stack_element* next;
        stack_element* previous;

    public:
        stack_element(T& value, stack_element *previous);

        virtual ~stack_element();

        T& getValue();

        void setNext(stack_element *next);

        stack_element *getNext();

        stack_element *getPrevious();
    };

    int size;
    stack_element* first;
    stack_element* last;

public:
    stack();
    ~stack();

    void push(T element);
    T pop();

    bool isEmpty();
    const int* getStackSize() const;
};



template<typename T>
stack<T>::stack_element::stack_element(T& value, stack::stack_element* previous) {
    this->value = value;
    this->previous = previous;
    this->next = nullptr;
}

template<typename T>
stack<T>::stack_element::~stack_element() {
    free(this->next);
    free(this->previous);
}

template<typename T>
T& stack<T>::stack_element::getValue() {
    return value;
}

template<typename T>
void stack<T>::stack_element::setNext(stack::stack_element *next) {
    stack_element::next = next;
}

template <typename T>
typename stack<T>::stack_element *stack<T>::stack_element::getNext() {
    return this->next;
}

template <typename T>
typename stack<T>::stack_element *stack<T>::stack_element::getPrevious() {
    return this->previous;
}



template<typename T>
const int* stack<T>::getStackSize() const {
    return &size;
}

template<typename T>
stack<T>::stack() {
    this->size = 0;
    this->first = nullptr;
    this->last = nullptr;
}

template<typename T>
stack<T>::~stack() {
    free(this->first);
    free(this->last);
}

template<typename T>
void stack<T>::push(T element) {
    stack_element* SE = new stack_element(element, last);

    if (size == 0) {
        first = SE;
    } else {
        last->setNext(SE);
    }

    size++;

    last = SE;
}

template<typename T>
T stack<T>::pop() {
    if (size == 0)
        throw std::runtime_error("Stack is empty!");

    stack_element *decapitation = last;
    T value = decapitation->getValue();

    last = decapitation->getPrevious();
    if (size > 1) {
        last->setNext(nullptr);
    } else {
        first = nullptr;
    }
    free(decapitation);

    size--;

    return value;
}

template<typename T>
bool stack<T>::isEmpty() {
    return size == 0;
}

#endif // STACK_H
