/*#include "stack.hpp"

template<typename StackElementType>
Stack<StackElementType>::Stack()
{

}

template<typename StackElementType>
Stack<StackElementType>::StackElement::StackElement(StackElementType value):
    value(value)
{

}

template<typename StackElementType>
Stack<StackElementType>::~Stack()
{
    StackElement* deletableElement = head;
    while(head != nullptr)
    {
        deletableElement = head;
        head = head->nextElement;
        delete deletableElement;
    }
}

template<typename StackElementType>
void Stack<StackElementType>::add(StackElementType newElementValue)
{
    if (head == nullptr)
    {
        head = new StackElement(newElementValue);
        head->nextElement = nullptr;
    } else {
        StackElement* addingStackElement = new StackElement(newElementValue);
        addingStackElement->nextElement = head;
        head = addingStackElement;
    }
}

template<typename StackElementType>
StackElementType Stack<StackElementType>::get()
{
    StackElementType gettingElementValue = head->value;

    StackElement* nextElement = head->nextElement;
    delete head;
    head = nextElement;

    return gettingElementValue;
}
*/
