#ifndef STRSTRWORKER_H
#define STRSTRWORKER_H
#include "hashtable.h"

struct hCreateInfo
{
    unsigned int hSize;
    unsigned itemCounter;
    unsigned int sumIterNum;
    unsigned int maxIterNum;
    bool error;
};

class StrStrWorker
{
public:
    StrStrWorker();
    QString getFromFile(QString fileName);
    hCreateInfo createHashTable(QString input, int hFuncNum, int factor, QString fileName);
    QString deleteElem(QString input, bool step);
    void saveStrToFile(QString output, QString fileName);
    int generateFile(int size, int maxLength, QString fileName, bool worstCase, int hFuncNum);
private:
    HashTable <string, string> hTable;
    unsigned int hFunc1(string key, unsigned int size);
    unsigned int hFunc2(string key, unsigned int size);
    unsigned int hFunc3(string key, unsigned int size);
    hCreateInfo info;
    int iter;
};

#endif // STRSTRWORKER_H
