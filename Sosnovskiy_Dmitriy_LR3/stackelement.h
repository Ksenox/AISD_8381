#pragma once
#include "QCharRef"

class StackElement
{
public:
    StackElement(QChar value);

    StackElement* nextElement;

    QChar value;
};
