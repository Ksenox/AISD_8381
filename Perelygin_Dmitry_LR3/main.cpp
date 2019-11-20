#include "mainwindow.h"
#include <QtGui>
#include <QApplication>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <clocale>
#include <windows.h>
#include "mainwindow.h"
using namespace std;






int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
