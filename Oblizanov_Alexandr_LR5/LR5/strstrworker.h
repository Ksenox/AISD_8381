#ifndef STRSTRWORKER_H
#define STRSTRWORKER_H
#include "hashtable.h"


class StrStrWorker
{
public:
    StrStrWorker();
    QString getFromFile(QString fileName);
    QString createHashTable(QString input);
    QString deleteElem(QString input);
    void saveStrToFile(QString output, QString fileName);
private:
    HashTable <string, string> hTable;
    unsigned int hFunc(string key);
    int iter;
};

#endif // STRSTRWORKER_H
