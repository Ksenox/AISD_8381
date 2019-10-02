#pragma once
#include <QString>
#include "FunctionTreeNode.h"

class FunctionTreeNodeWithOperand : public FunctionTreeNode
{
public:
    FunctionTreeNodeWithOperand(QString symbol);

    ~FunctionTreeNodeWithOperand();

    QString derivate(QChar derivativeBasis);

    QString restoreFunctionString();

    QString simplify();
};

