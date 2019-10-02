#pragma once

#include <QString>
#include "FunctionTreeNodeWithOperand.h"
#include "FunctionTreeNodeWithOperation.h"

class Function
{
private:
    QString functionString;

    FunctionTreeNode* functionTreeRoot;

    void plotTreeFromFunctionString();

    bool isElementLeftBracketSymbol(QChar element);

    bool isElementRightBracketSymbol(QChar element);

    bool isElementOperationSymbol(QChar element);

public:
    Function(QString functionString);

    ~Function();

    QString getDerivative(QChar derivativeBasis);

    QString simplify();

    QMap<QString, int> finalConvertion(QString string);
};
