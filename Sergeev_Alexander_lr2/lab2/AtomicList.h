//
// Created by alex on 9/26/19.
//

#ifndef ALG_LAB1_MAIN_H
#define ALG_LAB1_MAIN_H

#include <cstdlib>
#include <bits/stdc++.h>

#define WrongFormatException 11000
#define UnidentifiedOperatorException 12000
#define VariableCountingException 13000

class AtomicList;

using namespace std;

union Content {
    AtomicList* child;
    struct Operand {
        char variable;
        double num;
    } operand;
};

class AtomicList {
private:
    char algOperator;
    bool isUni;
    bool isFilled;

    bool isFirstNum;
    Content firstOperand;

    bool isSecondNum;
    Content secondOperand;

    double bindVariable(string &data, char c);

    bool isOperator(char c);

public:
    explicit AtomicList(string &expression, unsigned long recursivePosition = 0);

    virtual ~AtomicList();

    void fill(string &data);

    void toFile(string &fileSign, int recurrentCounter = 0);

    double count(string &fileSign, int recurrentCounter = 0);
};


#endif //ALG_LAB1_MAIN_H
