#include "inout.h"

QString getStrFromFile(QString fileName)
{
    ifstream fin(qPrintable(fileName), ios::in);
    string out;
    getline(fin, out);
    fin.close();
    return QString::fromStdString(out);
}

int saveStrToFile(QString output, QString fileName)
{
    ofstream fout(qPrintable(fileName));
    fout << qPrintable(output);
    fout.close();
    return 0;
}

QStringList getArrayFromStr(QString input)
{
    return input.split(" ");
}


