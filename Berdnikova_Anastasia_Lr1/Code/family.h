//
// Created by kot on 14.09.2019.
//

#ifndef FAMILY_H
#define FAMILY_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <QString>
#include <cstring>
#include <QVector>
#include <QStringList>

enum errors{
    WRONG_STRING
};

using namespace std;
class Family {


public:
    QVector<QVector<QString>> families;
    QStringList all_names;

    int COUNT = 1;
    int number = 0;
    void addWord(QString &name);
    void split(QString &row);
    void input(QString in);
    void save_file(const char *name);
    void open_file(const char *file_name);
    bool is_parent(QString p1, QString p2);
    bool is_relative(const QString& p1, const QString& p2, int deep=0);

};


#endif //FAMILY_H
