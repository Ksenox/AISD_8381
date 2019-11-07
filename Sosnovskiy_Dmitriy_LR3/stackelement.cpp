#include "stackelement.h"

StackElement::StackElement(QChar value):
    value(value)
{
    nextElement = nullptr;
}
