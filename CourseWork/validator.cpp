#include "validator.h"

Validator::Validator()
{

}

void Validator::checkCorrectness(QString string)
{
    if(string.isEmpty()) throw SyntaxErrorException(EMPTY_STRING, 0, QChar());


    int cnt = 0;
    for(int i = 0; i < string.size(); i++)
    {
        if(string[i] == '(') cnt++;
        if(string[i] == ')') cnt--;
        if(cnt < 0) throw SyntaxErrorException(INCORRECT_SYMBOL, i, string[i]);
    }

    checkStringOfIntegersCorrectness(string);


    return;
}

void Validator::checkStringOfIntegersCorrectness(QString string)
{
    int currentState = 0;

    for(int i = 0; i < string.size(); i++)
    {
        if(string[i] == " ")
        {
            string.remove(i, 1);
            i--;
        }
    }

    for (int i = 0; i < string.size(); i++)
    {
        QChar currentSymbol = string[i];
        currentState = getNextState(currentState, currentSymbol);
        if(currentState == -1) throw SyntaxErrorException(INCORRECT_SYMBOL, i, string[i]);
    }

    checkSymbolsLength(string);
}

int Validator::getNextState(int currentState, QChar currentSymbol)

{
    switch (currentSymbol.unicode()) {
        case '0': return statesTableForInt[currentState][0];
        case '1': return statesTableForInt[currentState][1];
        case '2': return statesTableForInt[currentState][2];
        case '3': return statesTableForInt[currentState][3];
        case '4': return statesTableForInt[currentState][4];
        case '5': return statesTableForInt[currentState][5];
        case '6': return statesTableForInt[currentState][6];
        case '7': return statesTableForInt[currentState][7];
        case '8': return statesTableForInt[currentState][8];
        case '9': return statesTableForInt[currentState][9];
        case '-': return statesTableForInt[currentState][10];
        case '(': return statesTableForInt[currentState][11];
        case ')': return statesTableForInt[currentState][12];
        case ';': return statesTableForInt[currentState][13];
        case ',': return statesTableForInt[currentState][14];
        default: return -1;
    }
}

void Validator::checkSymbolsLength(QString string)
{
    int cnt = 0;
    for(int i = 0; i < string.size(); i++)
    {
        if(string[i].isNumber()) {
            cnt++;
            if(cnt >= 4)
            {
                throw SyntaxErrorException(TOO_LONG_NUMBER, 0, ' ');
            }
        }
        else cnt = 0;
    }
}
