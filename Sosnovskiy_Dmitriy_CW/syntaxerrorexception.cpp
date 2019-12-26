#include "syntaxerrorexception.h"

SyntaxErrorException::SyntaxErrorException(MistakeTypes mistakeType, int mistakePosition, QChar errorSymbol):
    mistakeType(mistakeType), mistakePosition(mistakePosition), errorSymbol(errorSymbol)
{

}


QString SyntaxErrorException::getErrorString()
{
    QString returnable;

    if(mistakeType == TOO_LONG_NUMBER)
        returnable = "Слишком большое число в строке";
    else if(mistakeType == INCORRECT_SYMBOL){
        returnable = QString("Неопознанный символ ") + errorSymbol + " на позиции " + QString::number(mistakePosition);
    } else if (mistakeType == EMPTY_STRING)
        returnable = QString("Пустая строка в поле ввода");

    return returnable;
}
