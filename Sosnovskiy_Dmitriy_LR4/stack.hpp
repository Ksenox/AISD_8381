#ifndef STACK_H
#define STACK_H

template<typename StackElementType>
class Stack
{
private:
    class StackElement
    {
        public:
            StackElement(StackElementType value):
                value(value)
            {

            }

            ~StackElement() { }

            StackElement* nextElement = nullptr;

            StackElementType value;
    };

    StackElement* head = nullptr;

public:

    int size = 0;

    Stack() {

    }


    ~Stack() {
        StackElement* deletableElement = head;
        while(head != nullptr)
        {
            deletableElement = head;
            head = head->nextElement;
            delete deletableElement;
        }
    }


    void add(StackElementType newElementValue) {
        if (head == nullptr)
        {
            head = new StackElement(newElementValue);
            head->nextElement = nullptr;
        } else {
            StackElement* addingStackElement = new StackElement(newElementValue);
            addingStackElement->nextElement = head;
            head = addingStackElement;
        }
        size++;
    }


    StackElementType get() {
        StackElementType gettingElementValue = head->value;

        StackElement* nextElement = head->nextElement;
        delete head;
        head = nextElement;
        size -= 1;
        return gettingElementValue;
    }


};

#endif // STACK_H
