#include "mainwindow.h"

#include <QApplication>
#include <sstream>
#include <iostream>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
