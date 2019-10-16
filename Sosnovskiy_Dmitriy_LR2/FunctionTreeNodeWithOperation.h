#pragma once
#include "FunctionTreeNode.h"
#include <QString>
#include <QRegExp>
#include <QMap>

class FunctionTreeNodeWithOperation : public FunctionTreeNode
{
public:
    FunctionTreeNodeWithOperation();

    ~FunctionTreeNodeWithOperation();

    QString derivate(QChar derivativeBasis);

    QString restoreFunctionString();

    QString simplify();

    QString summOfTwoStrings(QString string1, QString string2);

    QString substrOfTwoStrings(QString string1, QString string2);

    QString multOfTwoStrings(QString string1, QString string2);

    bool isElementOperationSymbol(QChar element);

    QMap<QString, int> convertStringToMap(QString string);

};


