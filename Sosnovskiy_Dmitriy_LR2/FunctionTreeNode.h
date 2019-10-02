#pragma once
#include <QString>

class FunctionTreeNode
{
public:

    FunctionTreeNode();

    virtual ~FunctionTreeNode();

    FunctionTreeNode* leftNode;
    FunctionTreeNode* rightNode;
    FunctionTreeNode* previousNode;

    QString symbol;

    void plotTreeFromString(QString functionString);

    virtual QString derivate(QChar derivativeBasis) = 0;

    virtual QString restoreFunctionString() = 0;

    virtual QString simplify() = 0;
};



