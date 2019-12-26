#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <QString>
#include "syntaxerrorexception.h"

class Validator
{

private:
    int statesTableForInt[8][15] = {
            //   0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -, (, ), ;, ,
/*q0*/        { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1},
/*q1*/        {  3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2,-1,-1,-1,-1},
/*q2*/        { -1, 4, 4, 4, 4, 4, 4, 4, 4, 4,-1,-1,-1,-1,-1},
/*q3*/        { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 5,-1},
/*q4*/        {  4, 4, 4, 4, 4, 4, 4, 4, 4, 4,-1,-1,-1, 5,-1},
/*q5*/        { -1, 6, 6, 6, 6, 6, 6, 6, 6, 6,-1,-1,-1,-1,-1},
/*q6*/        {  6, 6, 6, 6, 6, 6, 6, 6, 6, 6,-1,-1, 7,-1,-1},
/*q7*/        { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0}
    };

    void checkSymbolsLength(QString string);

    int getNextState(int currentState, QChar currentSymbol);

    void checkStringOfIntegersCorrectness(QString string);

    void checkStringOfCharsCorrectness(QString string);

public:
    Validator();
    void checkCorrectness(QString string);
};

#endif // VALIDATOR_H
