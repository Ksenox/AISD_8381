#ifndef SYNTAXERROREXCEPTION_H
#define SYNTAXERROREXCEPTION_H
#include <QString>

enum MistakeTypes {TOO_LONG_NUMBER, INCORRECT_SYMBOL, EMPTY_STRING};

class SyntaxErrorException
{
private:
    MistakeTypes mistakeType;

    int mistakePosition;

    QChar errorSymbol;

public:
    SyntaxErrorException(MistakeTypes mistakeType, int mistakePosition, QChar errorSymbol);

    QString getErrorString();
};

#endif // SYNTAXERROREXCEPTION_H
