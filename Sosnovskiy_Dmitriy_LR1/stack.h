#ifndef STACK_H
#define STACK_H

//Stack is an element structure with a LIFO rule.
//class Stack has 4 main methods for working with stack structure.
class Stack
{
public:
    Stack();

    void add_to_stack(char new_stack_element);

    void remove_last_element();

    char get_last_element();

    bool is_empty();

private:
    char* stack;
    unsigned int stack_size;

};

#endif // STACK_H
