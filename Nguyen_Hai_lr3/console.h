#ifndef CONSOLE_H
#define CONSOLE_H
#include <method.h>
#include <QString>
#include <QFileDialog>

class console{
public:
    console();
    void Console(bool flagCase_1, bool flagCase_2,int *flagError,string *result, string *analize, QString data);
    method *Method;
};

#endif // CONSOLE_H
