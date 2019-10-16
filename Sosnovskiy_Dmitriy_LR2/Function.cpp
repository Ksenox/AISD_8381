#include "Function.h"

Function::Function(QString functionString):
    functionString(functionString)
{
    functionTreeRoot = nullptr;
    plotTreeFromFunctionString();
}

Function::~Function()
{
    delete functionTreeRoot;
}

void Function::plotTreeFromFunctionString()
{
    FunctionTreeNode* currentNode = nullptr;
    FunctionTreeNode* temporaryPreviousNode = nullptr;

    for(int currentSymbolPosition = 0; currentSymbolPosition < functionString.size(); currentSymbolPosition++) {

        if(isElementLeftBracketSymbol(functionString[currentSymbolPosition]) == true) {

            if(currentNode == nullptr){
                currentNode = new FunctionTreeNodeWithOperation();
                currentNode->previousNode = temporaryPreviousNode;
                temporaryPreviousNode = currentNode;
            }
            else if(currentNode->leftNode == nullptr){
                currentNode->leftNode = new FunctionTreeNodeWithOperation();
                currentNode->leftNode->previousNode = currentNode;
                currentNode = currentNode->leftNode;
            }
            else if(currentNode->rightNode == nullptr){
                currentNode->rightNode = new FunctionTreeNodeWithOperation();
                temporaryPreviousNode = currentNode;
                currentNode->rightNode->previousNode = currentNode;
                currentNode = currentNode->rightNode;
            }

            if(currentSymbolPosition == 0) functionTreeRoot = currentNode;

        } else if(isElementRightBracketSymbol(functionString[currentSymbolPosition])) {

            currentNode = currentNode->previousNode;

        } else if(functionString[currentSymbolPosition].isNumber() == true) {

            QString numberSubstring = "";

            while(functionString[currentSymbolPosition].isNumber() == true)
            {
                numberSubstring.append(functionString[currentSymbolPosition]);
                currentSymbolPosition++;
            }
            currentSymbolPosition -= 1;

            if(currentNode->leftNode == nullptr) currentNode->leftNode = new FunctionTreeNodeWithOperand(numberSubstring);
            else if(currentNode->rightNode == nullptr) currentNode->rightNode = new FunctionTreeNodeWithOperand(numberSubstring);

        } else if(isElementOperationSymbol(functionString[currentSymbolPosition]) == true) {
            currentNode->symbol = functionString[currentSymbolPosition];
            temporaryPreviousNode = currentNode;
        } else {
            if(currentNode->leftNode == nullptr) currentNode->leftNode = new FunctionTreeNodeWithOperand(QString(functionString[currentSymbolPosition]));
            else if(currentNode->rightNode == nullptr) currentNode->rightNode = new FunctionTreeNodeWithOperand(QString(functionString[currentSymbolPosition]));
        }

    }

}


bool Function::isElementLeftBracketSymbol(QChar element)
{
    switch(element.unicode()) {

        case '(': return true;

        default: return false;

    }
}

bool Function::isElementRightBracketSymbol(QChar element)
{
    switch(element.unicode()) {

        case ')': return true;

        default: return false;

    }
}

bool Function::isElementOperationSymbol(QChar element)
{
    switch(element.unicode()) {

        case '+': return true;
        case '-': return true;
        case '*': return true;

        default: return false;

    }
}

QString Function::getDerivative(QChar derivativeBasis)
{
    return functionTreeRoot->derivate(derivativeBasis);
}

QString Function::simplify()
{
    QString predAns = functionTreeRoot->simplify();

    QMap<QString, int>  ansMap = finalConvertion(predAns);

    QString answer = "";
    for(auto current : ansMap.keys())
    {
        if(ansMap[current] < 0)
            answer += QString::number(ansMap[current]) + current;
        else {
            answer += "+" + QString::number(ansMap[current]) + current;
        }
    }

    if(answer[0] == '+') answer.remove(0,1);
    return answer;
}

QMap<QString,int> Function::finalConvertion(QString string)
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

    QMap<QString, int> ansMap;

    for(auto current : map.keys())
    {
        if(map[current] == 0) continue;
        else{
            ansMap[current] = map[current];
        }
    }


    return ansMap;
}
