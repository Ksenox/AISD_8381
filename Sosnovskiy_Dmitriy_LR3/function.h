#pragma once
#include "stack.h"
#include "QMessageBox"
#include <iostream>
#include <conio.h>
class Function
{
public:
    Function(QString functionString);

    QString getStr();

    int calculate();

    int calculateStepByStep();

    int calculateStepByStepForConsole();
private:
    QString functionString;

};

