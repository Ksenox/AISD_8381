#ifndef DARR_H
#define DARR_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <QMessageBox>
#include <QMainWindow>
#include <QGraphicsEffect>
#include <QGraphicsView>
#include <QFileDialog>
#include <QStandardPaths>
#include <QtGui>
#include <QLabel>
#include <QColorDialog>
#include <QInputDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>

#define ERR_SYMB_B -1
#define ERR_SYMB_N -2
#define ERR_LENGTH -3

using namespace std;

struct dArr
{
    int length;
    int *base;
};

struct flags
{
    bool step;
    bool info;
};

int strCount(string &input);
int checkStr(string &bolts, string &nuts);
dArr makeArray(string &input, int length);
string getStrFromArray(dArr &input);
string getPairs(dArr &bolts, dArr &nuts);
string getStrSwapAction(dArr &input, int ptr1, int ptr2);
string getStrCmpAction(dArr &bolts, int ptr1, dArr &nuts, int ptr2);
int checkPairs(dArr &bolts, dArr &nuts);

int sortBN(dArr &bolts, dArr &nuts, flags &opt, ofstream &fout);

#endif // DARR_H
