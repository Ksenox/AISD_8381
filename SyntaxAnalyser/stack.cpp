#include "stack.h"

Stack::Stack()
{
   stack = nullptr;
   stack_size = 0;
}

void Stack::add_to_stack(char new_stack_element)
{
   //Here we create a new stack and then we copy all elements from previous stack to new one.
   char* previous_stack = stack;

   stack = new char[stack_size + 1];

   for(unsigned i = 0; i < stack_size; i++)
   {
      stack[i] = previous_stack[i];
   }
   stack[stack_size] = new_stack_element;

   stack_size += 1;

   delete[] previous_stack; //Don't forget to delete the previous stack ptr.

   return;
}

void Stack::remove_last_element()
{
    //Here we again create a new stack decreasing the previous stack size by 1 and then copy stack_size-1 elements from it.
    if(stack_size > 0)
    {
        char* previous_stack = stack;

        stack_size -= 1;

        stack = new char[stack_size];

        for(unsigned int i = 0; i < stack_size; i++)
        {
            stack[i] = previous_stack[i];
        }

        delete[] previous_stack; //Again don't forget to delete the previous stack ptr.
    }
    else
    {
        //do nothing
    }

    return;
}

char Stack::get_last_element()
{
   if(stack_size > 0) return stack[stack_size-1];
   else return '\0';
}

bool Stack::is_empty()
{
    if(stack_size == 0) return true;
    else return false;
}
