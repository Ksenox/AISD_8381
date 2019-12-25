#ifndef HASH_H
#define HASH_H
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cstdlib>
#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsEffect>
#include <QFileDialog>
#include <QStandardPaths>
#include <QtGui>
#include <QLabel>
#include <QColorDialog>
#include <QInputDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QStringList>
#include <QTextEdit>
#include <stack>
#define SIZE 37 // 601, 211, 89, 34996 175939

using namespace std;

class Hash
{
    int BUCKET; // No. of buckets

    list <string> *table; // Pointer to an array containing buckets

    public:
        Hash(int n);

        void insertItem(string value);

        void deleteItem(string key);

        int hashFunction(string x);

        int hashFunction2(int x);

        int hashFunction3(int x);

        void displayHash(QTextEdit *&output);

        void displayInfo(QTextEdit *&info);

        void clearHashTable();
};

#endif // HASH_H
