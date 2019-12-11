#ifndef STRSTRTESTER_H
#define STRSTRTESTER_H

#include "strstrworker.h"
#include "qcustomplot.h"

struct testInfo
{
    int min;
    int max;
    int step;
    int mode;
    QString fileName;
    bool checkMaxIter;
    bool worstCase;
    int maxLength;
    int size;
    int factor;
};


struct testResult
{
    unsigned int **maxIterArr;
    unsigned int **sumIterArr;
    long **clockArr;
    int **num;
};

int pairNumTester(StrStrWorker &ssw, testInfo info, QCustomPlot *&plot, string &output, testResult &res);

#endif
