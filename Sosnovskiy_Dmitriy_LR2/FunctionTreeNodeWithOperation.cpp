#include "FunctionTreeNodeWithOperation.h"

FunctionTreeNodeWithOperation::~FunctionTreeNodeWithOperation()
{
    if(leftNode != nullptr) delete leftNode;
    if(rightNode != nullptr) delete rightNode;
}

FunctionTreeNodeWithOperation::FunctionTreeNodeWithOperation()
{

}

QString FunctionTreeNodeWithOperation::derivate(QChar derivativeBasis)
{
    switch (symbol[0].unicode()) {
        case '+': {
            QString leftPart = leftNode->derivate(derivativeBasis);
            QString rightPart = rightNode->derivate(derivativeBasis);

            return ("(" + leftPart + "+" + rightPart + ")");

        }
        case '-': {
            QString leftPart = leftNode->derivate(derivativeBasis);
            QString rightPart = rightNode->derivate(derivativeBasis);

            return ("(" + leftPart + "-" + rightPart + ")");
        }
        case '*': {
            QRegExp stringFromFigures("\\d*");

            QString leftOfLeftPart = leftNode->derivate(derivativeBasis);
            QString rightOfLeftPart = rightNode->restoreFunctionString();

           /* if(stringFromFigures.exactMatch(rightOfLeftPart) == false && rightOfLeftPart.size() != 1)
            {
               rightOfLeftPart = "(" + rightOfLeftPart + ")";
            } */

            QString leftOfRightPart = leftNode->restoreFunctionString();
            QString rightOfRightPart = rightNode->derivate(derivativeBasis);

           /* if(stringFromFigures.exactMatch(leftOfRightPart) == false && leftOfRightPart.size() != 1)
            {
               leftOfRightPart = "(" + leftOfRightPart + ")";
            }*/

            QString leftPart = "(" + leftOfLeftPart + "*" + rightOfLeftPart + ")";
            QString rightPart = "(" +leftOfRightPart + "*" + rightOfRightPart + ")";

            return ("(" + leftPart + "+" + rightPart + ")");
        }
    }
}

QString FunctionTreeNodeWithOperation::restoreFunctionString()
{
    QString leftPart = leftNode->restoreFunctionString();
    QString rightPart = rightNode->restoreFunctionString();

    return ("(" + leftPart + symbol + rightPart + ")");
}



QString FunctionTreeNodeWithOperation::simplify()
{
    switch(symbol[0].unicode())
    {
        case '+':{
            QRegExp stringFromFigures("\\d*");

            QString leftPart = leftNode->simplify();

            QString rightPart = rightNode->simplify();

            return summOfTwoStrings(leftPart, rightPart);

        }
        case '-':{

            QString leftPart = leftNode->simplify();

            QString rightPart = rightNode->simplify();

            return substrOfTwoStrings(leftPart, rightPart);
        }
        case '*':{
            QString leftPart = leftNode->simplify();

            QString rightPart = rightNode->simplify();

            return multOfTwoStrings(leftPart, rightPart);
        }

    }
}

QString FunctionTreeNodeWithOperation::summOfTwoStrings(QString string1, QString string2)
{
    QMap<QString, int> map1 = convertStringToMap(string1);

    QMap<QString, int> map2 = convertStringToMap(string2);

    QMap<QString, int> summMap = map1;
    for(auto current : map2.keys())
    {
        if(summMap.contains(current))
        {
            summMap[current] = summMap[current] + map2[current];
        }
        else {
            summMap[current] = map2[current];
        }
    }

    QString summOfStrings = "";
    for(auto current : summMap.keys())
    {
        if(current.isEmpty() == true)
        {
            if(summMap[current] >= 0)
                summOfStrings = summOfStrings + "+" + QString::number(summMap[current]);
            else
                summOfStrings = summOfStrings + QString::number(summMap[current]);
        }
        else {
            if(summMap[current] >= 0)
                if(current[0] == '*')
                    summOfStrings = "+" + QString::number(summMap[current]) + current + summOfStrings;
                else
                    summOfStrings = "+" + QString::number(summMap[current]) + "*" + current + summOfStrings;

            else
                if(current[0] == '*')
                    summOfStrings = QString::number(summMap[current]) + current + summOfStrings;
                else
                    summOfStrings = QString::number(summMap[current]) + "*" + current + summOfStrings;
        }
    }

    if(summOfStrings[0] == '+') summOfStrings.remove(0,1);

    return summOfStrings;
}




QString FunctionTreeNodeWithOperation::substrOfTwoStrings(QString string1, QString string2)
{
    QMap<QString, int> map1 = convertStringToMap(string1);

    QMap<QString, int> map2 = convertStringToMap(string2);

    QMap<QString, int> substrMap = map1;
    for(auto current : map2.keys())
    {
        if(substrMap.contains(current))
        {
            substrMap[current] = substrMap[current] - map2[current];
        }
        else {
            substrMap[current] = (-1)*map2[current];
        }
    }

    QString substrOfStrings = "";
    for(auto current : substrMap.keys())
    {
        if(current.isEmpty() == true)
        {
            if(substrMap[current] >= 0)
                substrOfStrings = substrOfStrings + "+" + QString::number(substrMap[current]);
            else
                substrOfStrings = substrOfStrings + QString::number(substrMap[current]);
        }
        else {
            if(substrMap[current] >= 0)
                if(current[0] == '*')
                    substrOfStrings = "+" + QString::number(substrMap[current]) + current + substrOfStrings;
                else
                    substrOfStrings = "+" + QString::number(substrMap[current]) + "*" + current + substrOfStrings;

            else
                if(current[0] == '*')
                    substrOfStrings = QString::number(substrMap[current]) + current + substrOfStrings;
                else
                    substrOfStrings = QString::number(substrMap[current]) + "*" + current + substrOfStrings;
        }
    }

    if(substrOfStrings[0] == '+') substrOfStrings.remove(0,1);

    return substrOfStrings;
}


QString FunctionTreeNodeWithOperation::multOfTwoStrings(QString string1, QString string2)
{
    QMap<QString, int> map1 = convertStringToMap(string1);

    QMap<QString, int> map2 = convertStringToMap(string2);

    QMap<QString, int> multMap;

    for(auto current1 : map1.keys())
    {
        for(auto current2 : map2.keys())
        {
            if(current1 == "")
            {
                if(current2 == "")
                {
                    multMap[""] = map1[current1] * map2[current2];
                }
                else
                {
                    if(multMap.contains(current2))
                        multMap[current2] += map1[current1] * map2[current2];
                    else
                        multMap[current2] = map1[current1] * map2[current2];
                }
            }
            else {
                if(current2 == "")
                {
                    if(multMap.contains(current1))
                        multMap[current1] += map1[current1] * map2[current2];
                    else
                        multMap[current1] = map1[current1] * map2[current2];
                }
                else {
                    if(current2[0] != '*')
                    {
                        if(multMap.contains(current1 + "*" + current2))
                            multMap[current1 + "*" + current2] += map1[current1] * map2[current2];
                        else
                            multMap[current1 + "*" + current2] = map1[current1] * map2[current2];
                    }
                    else
                    {
                        if(multMap.contains(current1+current2))
                            multMap[current1+current2] += map1[current1] * map2[current2];
                        else
                            multMap[current1+current2] = map1[current1] * map2[current2];
                    }
                }
            }
        }
    }


    QString multOfStrings = "";

    for(auto current : multMap.keys())
    {
        if(current.isEmpty() == true)
        {
            if(multMap[current] >= 0)
                multOfStrings = multOfStrings + "+" + QString::number(multMap[current]);
            else
                multOfStrings = multOfStrings + QString::number(multMap[current]);
        }
        else {
            if(multMap[current] >= 0)
                if(current[0] == '*')
                    multOfStrings = "+" + QString::number(multMap[current]) + current + multOfStrings;
                else
                    multOfStrings = "+" + QString::number(multMap[current]) + "*" + current + multOfStrings;

            else
                if(current[0] == '*')
                    multOfStrings = QString::number(multMap[current]) + current + multOfStrings;
                else
                    multOfStrings = QString::number(multMap[current]) + "*" + current + multOfStrings;
        }
    }

    if(multOfStrings[0] == '+') multOfStrings.remove(0,1);

    return multOfStrings;
}


QMap<QString, int> FunctionTreeNodeWithOperation::convertStringToMap(QString string)
{
    QMap<QString, int> map;
    if(string[0].isNumber() == false && string[0] != '-') string.push_front('+');

    for(int i = 0; i < string.size(); i++)
    {

        if(string[i] == "+")
        {
            i++;
            QString elementAmount = "";
            while(string[i].isNumber() && i < string.size())
            {
                elementAmount += string[i];
                i++;
            }
            i--;
            if(elementAmount.isEmpty()) elementAmount = "1";
            else {
                i++;
            }
            QString element = "";
            int k = i+1;
            for(k; k < string.size(); k++)
            {
                if(string[k] == '+' || string[k] == '-') break;
                else{
                    element += string[k];
                }
            }

            i = k - 1;

            if(map.contains(element)){
                map[element] = map[element] + elementAmount.toInt();
            }
            else map[element] = elementAmount.toInt();
        }
        else if(string[i] == "-")
        {
            i++;
            QString elementAmount = "-";
            while(string[i].isNumber() && i < string.size())
            {
                elementAmount += string[i];
                i++;
            }
            i--;
            if(elementAmount == "-") elementAmount = "-1";
            else {
                if(i+1 != string.size())
                    if(string[i+1] == "*")
                        i++;
            }
            QString element = "";
            int k = i+1;
            for(k; k < string.size(); k++)
            {
                if(string[k] == '+' || string[k] == '-') break;
                else{
                    element += string[k];
                }
            }

            i = k - 1;

            if(map.contains(element)){
                map[element] = map[element] + elementAmount.toInt();
            }
            else map[element] = elementAmount.toInt();
        }
        else if(string[i].isNumber() == true)
        {
            QString elementAmount = "";
            while(string[i].isNumber() && i < string.size())
            {
                elementAmount += string[i];
                i++;
            }
            i--;

            QString element = "";
            int k = i+1;
            for(k; k < string.size(); k++)
            {
                if(string[k] == '+' || string[k] == '-') break;
                else{
                    element += string[k];
                }
            }

            i = k - 1;

            if(map.contains(element)){
                map[element] = map[element] + elementAmount.toInt();
            }
            else map[element] = elementAmount.toInt();
        }
    }


    return map;
}


bool FunctionTreeNodeWithOperation::isElementOperationSymbol(QChar element)
{
    switch(element.unicode()) {

        case '+': return true;
        case '-': return true;
        case '*': return true;

        default: return false;

    }
}
