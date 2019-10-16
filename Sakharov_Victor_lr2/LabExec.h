#ifndef LR2_LABEXEC_H
#define LR2_LABEXEC_H

#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

#include "structs.h"

/*22) алгебраическое (+, -, *, sqrt(), log(,)),
 * проверка синтаксической корректности,
 * простая проверка log(,),
 * префиксная форма
 * */

enum OperatorType {
    E_PLUS,
    E_MINUS,
    E_MULTIPLY,
    E_SQRT,
    E_LOG
};

struct Expression;

struct Operand {
    bool isNumber;
    union {
        int number;
        Expression* expression;
    } data;
};

struct OperandList {
    Operand* head;
    OperandList* tail;
};

struct Expression {
    OperatorType operatorType;
    OperandList* operandList;
};

void Skip (std::string& str, int& pos, int n);
int GetNumber (string& str, int& pos);
Operand* ScanOperand (string& input, int& pos);
OperandList* ScanOperandList (string& input, int& pos, bool isClassic);
Expression* ScanExpression (string& input, int& pos);

void CheckSqrt (OperandList* list, int& pos);
void CheckLog (OperandList* list, int& pos);
int Length (OperandList* list);

#endif //EXPRESSIONPARSER_H


#endif //LR2_LABEXEC_H
