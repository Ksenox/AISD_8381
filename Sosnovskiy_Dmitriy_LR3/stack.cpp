#include "stack.h"

Stack::Stack()
{
    head = nullptr;
}

void Stack::add(QChar element)
{
    StackElement* newStackElement = new StackElement(element);

    newStackElement->nextElement = head;

    head = newStackElement;
    size++;
}

QChar Stack::take()
{
    StackElement* previousHead = head;

    head = previousHead->nextElement;

    QChar answer = previousHead->value;

    delete previousHead;

    size--;
    return answer;
}

QString Stack::getStr(bool isCons)
{
    QString stackAsString = nullptr;
    StackElement* temporary = head;
    while(temporary != nullptr)
    {
        QString valueStr = temporary->value;
        if(valueStr.at(0).isDigit() == true && isCons == false) stackAsString += "|   " + valueStr + "  |" + "\n";
        else if(valueStr.at(0).isDigit() == true && isCons == true) stackAsString += "|  " + valueStr + "  |" + "\n";
        else stackAsString += "|  " + valueStr + "  |" + "\n";
        temporary = temporary->nextElement;
    }

    stackAsString += "|_____|";
    return stackAsString;
}
