#include "FunctionTreeNodeWithOperand.h"

FunctionTreeNodeWithOperand::~FunctionTreeNodeWithOperand()
{

}

FunctionTreeNodeWithOperand::FunctionTreeNodeWithOperand(QString symbol)
{
    this->symbol = symbol;
}

bool stringConsistsFromNumbers(QString string)
{
    for(QChar currentSymbol : string)
    {
        if(currentSymbol.isNumber() == false) return false;
    }
    return true;
}

QString FunctionTreeNodeWithOperand::derivate(QChar derivativeBasis)
{

    if(stringConsistsFromNumbers(symbol) == true) {
        return "0";
    } else if(symbol == derivativeBasis) {
        return "1";
    } else {
        return "0";
    }
}

QString FunctionTreeNodeWithOperand::restoreFunctionString()
{
    return symbol;
}

QString FunctionTreeNodeWithOperand::simplify()
{
    return symbol;
}
