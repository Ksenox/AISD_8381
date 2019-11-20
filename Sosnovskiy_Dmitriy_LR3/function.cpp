#include "function.h"

Function::Function(QString functionString)
{
    for(auto i : functionString)  //remove spaces from the input functionString
    {
        if(i == " ")
            functionString.remove(i);
    }

    this->functionString = functionString;



    for(int i = 0; i < functionString.size(); i++)
    {
        if(functionString[i] == 'm')
        {
            if(i + 1 >= functionString.size()) throw "Неправильная строка";
            if(functionString[i+1] != '(') throw "Неправильная строка";
        }
        else if(functionString[i] == 'M')
        {
            if(i + 1 >= functionString.size()) throw "Неправильная строка";
            if(functionString[i+1] != '(') throw "Неправильная строка";
        }
        else if(functionString[i] == '(')
        {
            if(i + 3 >= functionString.size()) throw "Неправильная строка";

            if(functionString[i+1] != 'M' && functionString[i+1] != 'm' && functionString[i+1].isDigit() == false) throw "Неправильная строка";

        }
        else if(functionString[i] == ')')
        {
            if(i < 5) throw "Неправильная строка";

            if(functionString[i-1] != 'M' && functionString[i-1] != 'm' && functionString[i-1] != ')' && functionString[i-1].isDigit() == false)  throw "Неправильная строка";
            if(i != functionString.size() - 1)
            if(functionString[i+1] != ')' && functionString[i+1] != ',') throw "Неправильная строка";
        }
        else if(functionString[i] == ',')
        {
            if(i == 0 || i == functionString.size()-1) throw "Неправильная строка";
            else {
                if(functionString[i-1] != ')' && functionString[i-1].isDigit() == false) throw "Неправильная строка";
                else {
                    if(functionString[i+1] != 'm' && functionString[i+1] != 'M' && functionString[i+1].isDigit() == false)
                        throw "Неправильная строка";
                }

            }
        }
        else if(functionString[i].isDigit())
        {
            if(functionString.size() != 1)
            {
                if(i == 0 || i == functionString.size()) throw "Неправильная строка";
                else {
                    if((functionString[i-1] != ',' || functionString[i+1] != ')') && (functionString[i-1] != '(' || functionString[i+1] != ',')) throw "Неправильная строка";
                }
            }
        }
    }
}



bool isLeftBracket(QChar element)
{
    if(element.unicode() == '(') return true;
    else return false;
}

bool isRightBracket(QChar element)
{
    if(element.unicode() == ')') return true;
    else return false;
}

int max(int firstNumber, int secondNumber)
{
    if(firstNumber >= secondNumber) return firstNumber;
    else return secondNumber;
}

int min(int firstNumber, int secondNumber)
{
    if(firstNumber <= secondNumber) return firstNumber;
    else return secondNumber;
}

int doOperation(int firstNumber, int secondNumber, QChar operationLetter)
{
    if(operationLetter == 'M')
    {
        return max(firstNumber, secondNumber);
    }
    else if(operationLetter == 'm')
    {
        return min(firstNumber, secondNumber);
    }
}

int calculateLastKnownExpression(Stack & stack)
{
    int firstNumber = stack.take().digitValue();
    int secondNumber = stack.take().digitValue();
    QChar operationLetter = stack.take();

    int result = doOperation(firstNumber, secondNumber, operationLetter);

    return result;
}

QString Function::getStr() { return functionString; }

int Function::calculate()
{
    Stack stack;

    for(auto currentElement : functionString)
    {
        if(currentElement == ',') continue;
        else if(isRightBracket(currentElement) == false)
        {
            if(isLeftBracket(currentElement) == false)
            {
                stack.add(currentElement);
            }
        }
        else {
            if(stack.size < 3) throw "Неправильная строка";
            int lastExpressionResult = calculateLastKnownExpression(stack);
            stack.add(QString::number(lastExpressionResult).at(0));
        }
    }

    QChar ans = stack.take();
    return ans.digitValue();
}

int Function::calculateStepByStep()
{
    Stack stack;

    for(auto currentElement : functionString)
    {
        if(currentElement == ',') { }
        else if(isRightBracket(currentElement) == false)
        {
           if(isLeftBracket(currentElement) == false) stack.add(currentElement);
        }
        else {
            int lastExpressionResult = calculateLastKnownExpression(stack);
            stack.add(QString::number(lastExpressionResult).at(0));
        }

        QMessageBox msgBox;
        msgBox.setWindowTitle("Состояние стека");
        msgBox.setText(stack.getStr() + "\n" + "Обработанный символ: " + currentElement);
        QPushButton *continueButton = msgBox.addButton(("Continue"), QMessageBox::AcceptRole);
        msgBox.exec();
    }

    QChar ans = stack.take();
    return ans.digitValue();

}


int Function::calculateStepByStepForConsole()
{
    Stack stack;

    for(auto currentElement : functionString)
    {
        if(currentElement == ',') { }
        else if(isRightBracket(currentElement) == false)
        {
           if(isLeftBracket(currentElement) == false) stack.add(currentElement);
        }
        else {
            int lastExpressionResult = calculateLastKnownExpression(stack);
            stack.add(QString::number(lastExpressionResult).at(0));
        }

        std::cout << "Обработанный элемент: " << QString(currentElement).toStdString() << "\n";
        std::cout << "Содержимое стека:" << "\n";
        std::cout << stack.getStr(true).toStdString();
        std::cout << "\n";
        std::cout << "Для продолжения нажмите enter..." << "\n";

        std::cin.get();
    }

    QChar ans = stack.take();
    return ans.digitValue();

}
