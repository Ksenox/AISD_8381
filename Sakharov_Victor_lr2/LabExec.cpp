#include "LabExec.h"
#include "LabIo.h"

// // Удаление пробелов в начале строки
// void SkipSpaces (string& str) {
//     while (str.length() > 0 && str[0] == ' ') {
//         str = str.substr(1);
//     }
// }

// Удалить n символов из начала строки
void Skip (std::string& str, int& pos, int n) {
    if (str.length() >= n) {
        str = str.substr(n);
        //cout << str << endl;
        pos += n;
    }
}

int GetNumber (string& str, int& pos) {
    string strnum = "";
    while (isdigit(str[0]) || (strnum.length() == 0 && str[0] == '-')) {
        strnum += str[0];
        Skip(str, pos, 1);
    }
    return stoi(strnum);
}

// int|Expression
Operand* ScanOperand (string& input, int& pos) {
    //cout << "oper" << endl;
    if (input.empty() || input[0] == ')') {
        return nullptr;
    }
    Operand* operand = new Operand;
    operand->isNumber = isdigit(input[0]) || (input.length() > 1 && input[0] == '-' && isdigit(input[1]));
    if (operand->isNumber) {
        operand->data.number = GetNumber(input, pos);
        //cout << "NUMBER " << operand->data.number << endl;
    }
    else {
        operand->data.expression = ScanExpression(input, pos);
    }
    return operand;
}

// Operand[,| ][OperandList]
OperandList* ScanOperandList (string& input, int& pos, bool isClassic) {
    //cout << "list" << endl;
    OperandList* operandList = new OperandList;
    operandList->head = ScanOperand(input, pos);
    if (operandList->head == nullptr) {
        delete operandList;
        return nullptr;
    }
    char sep = isClassic ? ',' : ' ';
    if (!input.empty() && input[0] == sep) {
        Skip(input, pos, 1);
        operandList->tail = ScanOperandList(input, pos, isClassic);
    }
    else {
        operandList->tail = nullptr;
    }
    return operandList;
}

// (OperatorType OperandList)
Expression* ScanExpression (string& input, int& pos) {
    //cout << "expr" << endl;
    bool isClassic = input[0] != '(';
    Expression* expression = new Expression;
    if (isClassic) {
        if (input.find("sqrt") == 0) {
            expression->operatorType = E_SQRT;
            Skip(input, pos, 4);
        }
        else if (input.find("log") == 0) {
            expression->operatorType = E_LOG;
            Skip(input, pos, 3);
        }
        else {
            ProceedError("Function unknown operator", pos);
        }
        if (input.empty() || input[0] != '(') ProceedError("Function open bracket not found", pos);
        Skip(input, pos, 1);
        expression->operandList = ScanOperandList(input, pos, true);
        if (expression->operandList == nullptr) ProceedError("Function operands not found", pos);
        if (expression->operatorType == E_SQRT) {
            CheckSqrt(expression->operandList, pos);
        }
        else if (expression->operatorType == E_LOG) {
            CheckLog(expression->operandList,pos);
        }
        if (input.empty() || input[0] != ')') ProceedError("Function close bracket not found", pos);
        Skip(input, pos, 1);
    }
    else {
        Skip(input, pos, 1);
        if (input.find('+') == 0) {
            expression->operatorType = E_PLUS;
            Skip(input, pos, 1);
        }
        else if (input.find('-') == 0) {
            expression->operatorType = E_MINUS;
            Skip(input, pos, 1);
        }
        else if (input.find('*') == 0) {
            expression->operatorType = E_MULTIPLY;
            Skip(input, pos, 1);
        }
        else {
            ProceedError("Expression unknown operator", pos);
        }
        if (input.empty() || input[0] != ' ') ProceedError("Expression operands not found", pos);
        Skip(input, pos, 1);
        expression->operandList = ScanOperandList(input, pos, false);
        if (expression->operandList == nullptr) ProceedError("Expression operands size = 0", pos);
        if (input.empty() || input[0] != ')') ProceedError("Expression close bracket not found", pos);
        Skip(input, pos, 1);
    }
    return expression;
}

void CheckSqrt (OperandList* list, int& pos) {
    if (Length(list) == 1) {
        if (list->head->isNumber && list->head->data.number < 0) {
            ProceedError("Sqrt from negative number", pos);
        }
    }
    else {
        ProceedError("Sqrt must have 1 argument", pos);
    }
}

void CheckLog (OperandList* list, int& pos) {
    if (Length(list) == 2) {
        if (list->head->isNumber && (list->head->data.number == 1 || list->head->data.number <= 0)) {
            ProceedError("Log base can't be negative or equals 1", pos);
        }
        if (list->tail->head->isNumber && list->tail->head->data.number <= 0) {
            ProceedError("Log argument can't be negative", pos);
        }
    }
    else {
        ProceedError("Log must have 2 arguments", pos);
    }
}

int Length (OperandList* list) {
    OperandList* operandList = list;
    if (operandList != nullptr && operandList->head != nullptr) {
        int len = 0;
        while (operandList != nullptr) {
            len++;
            operandList = operandList->tail;
        }
        return len;
    }
    else {
        return 0;
    }
}


