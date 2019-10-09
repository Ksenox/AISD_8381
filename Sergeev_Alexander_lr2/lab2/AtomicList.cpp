//
// Created by alex on 9/26/19.
//

#include "AtomicList.h"

using namespace std;

AtomicList::AtomicList(string &expression, unsigned long recursivePosition) {
    int spaceRunner = 0;
    unsigned long lastSpace = 0;
    unsigned long firstPos = 0, secondPos = 0;
    string first, second;

    this->isFilled = false;

    lastSpace = expression.find(' ');
    if (lastSpace == 2) {
        if (isOperator(expression[lastSpace-1])) {
            this->algOperator = expression[lastSpace-1];
        } else {
            throw UnidentifiedOperatorException + expression[lastSpace-1];
        }
    } else {
        throw WrongFormatException + (int) (recursivePosition + lastSpace);
    }

    for (unsigned long i = lastSpace + 1; i < expression.length() - 1; i++) {
        if (expression[i] == '(') spaceRunner++;
        else if (expression[i] == ')') spaceRunner--;
        else if (spaceRunner == 0) {
            if (expression [i] == ' ') {
                firstPos = lastSpace + 1;
                first = expression.substr(firstPos, i - lastSpace - 1);
                secondPos = i + 1;
                second = expression.substr(secondPos, expression.length() - i - 2);
                lastSpace = i;
                break;
            }
        }
    }

    if (lastSpace == 2) {
        this->isUni = true;
        firstPos = lastSpace + 1;
        first = expression.substr(firstPos, expression.length() - lastSpace - 2);
    }

    if (first[0] != '(') {
        this->isFirstNum = true;
        if (first.length() > 1) throw (int) (WrongFormatException + firstPos + recursivePosition + 2);
        this->firstOperand.operand.variable = first[0];
    } else {
        this->isFirstNum = false;
        this->firstOperand.child = new AtomicList(first, recursivePosition + firstPos);
    }

    if (second[0] != '(') {
        this->isSecondNum = true;
        if (second.length() > 1) throw (int) (WrongFormatException + secondPos + recursivePosition + 2);
        this->secondOperand.operand.variable = second[0];
    } else {
        this->isSecondNum = false;
        this->secondOperand.child = new AtomicList(second, recursivePosition + secondPos);
    }
}

AtomicList::~AtomicList() {
    free(this->firstOperand.child);
    free(this->secondOperand.child);
}

bool AtomicList::isOperator(char c) {
    return (c == '+') || (c == '-') || (c == '*') || (c == '^');
}

double AtomicList::bindVariable(string &data, char c) {
    unsigned long varPos = data.find(c);
    unsigned long numEnd = data.find(')', varPos);
    string number = data.substr(varPos + 2, numEnd - varPos - 2);

    char* end;
    if ((number[0] != '0') && (strtod(number.c_str(), &end)) == 0) throw VariableCountingException + c;
    return strtod(number.c_str(), &end);
}

void AtomicList::fill(string &data) {
    this->isFilled = true;

    if (this->isFirstNum) {
        this->firstOperand.operand.num = bindVariable(data, this->firstOperand.operand.variable);
    } else {
        this->firstOperand.child->fill(data);
    }
    if (!this->isUni) {
        if (this->isSecondNum) {
            this->secondOperand.operand.num = bindVariable(data, this->secondOperand.operand.variable);
        } else {
            this->secondOperand.child->fill(data);
        }
    }
}

void AtomicList::toFile(string &fileSign, int recurrentCounter) {
    fileSign.append("\n");

    for (int i = 0; i < recurrentCounter; ++i) {
        fileSign.append("   ");
    }

    fileSign.append("( ").append(1, this->algOperator).append(" ");
    if (this->isFirstNum) {
        if (this->isFilled) {
            fileSign.append(to_string(this->firstOperand.operand.num));
        } else {
            fileSign.append(1, this->firstOperand.operand.variable);
        }
    } else {
        fileSign.append("(...)");
    }
    if (!this->isUni) {
        fileSign.append(" ");
        if (this->isSecondNum) {
            if (this->isFilled) {
                fileSign.append(to_string(this->secondOperand.operand.num));
            } else {
                fileSign.append(1, this->secondOperand.operand.variable);
            }
        } else {
            fileSign.append("(...)");
        }
    }
    fileSign.append(" )");

    if (!this->isFirstNum) this->firstOperand.child->toFile(fileSign, recurrentCounter + 1);
    if (!this->isUni && !this->isSecondNum) this->secondOperand.child->toFile(fileSign, recurrentCounter + 1);
}

double AtomicList::count(string &fileSign, int recurrentCounter) {
    if (!this->isFilled) throw VariableCountingException + this->firstOperand.operand.variable;

        double firstNum = 0, secondNum = 0;
        if (!this->isFirstNum) {
            firstNum = this->firstOperand.child->count(fileSign, recurrentCounter + 1);
        } else {
            firstNum = this->firstOperand.operand.num;
        }
        if (!this->isUni) {
            if (!this->isSecondNum) {
                secondNum = this->secondOperand.child->count(fileSign, recurrentCounter + 1);
            } else {
                secondNum = this->secondOperand.operand.num;
            }
        }

        double result = 0;
        if (!this->isUni) {
            switch (this->algOperator) {
                case '+':
                    result = firstNum + secondNum;
                    break;
                case '-':
                    result = firstNum - secondNum;
                    break;
                case '*':
                    result = firstNum * secondNum;
                    break;
                case '^':
                    result = pow(firstNum, secondNum);
                    break;
                default:
                    throw UnidentifiedOperatorException + this->algOperator;
            }
        } else if (this->algOperator == '-') {
            result = -firstNum;
        } else {
            cout << "LOL" << endl;
            throw UnidentifiedOperatorException + this->algOperator;
        }

        fileSign.append("\n");

        for (int i = 0; i < recurrentCounter; ++i) {
            fileSign.append("   ");
        }

        fileSign.append("( ").append(1, this->algOperator).append(" ");
        fileSign.append(to_string(firstNum));
        if (!this->isUni) {
            fileSign.append(" ");
            fileSign.append(to_string(secondNum));
        }
        fileSign.append(" )");

        fileSign.append(" = ").append(to_string(result));

        return result;
}
