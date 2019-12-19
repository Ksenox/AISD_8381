#include <QApplication>
#include <QScreen>
#include <sstream>
#include <iostream>
#include <QDir>
#include "outlog.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow w;
    QRect screen_geometry = QGuiApplication::screens().first()->geometry();
    int x = (screen_geometry.width() - w.geometry().width() - outlog::width) / 2;
    int y = (screen_geometry.height() - w.geometry().height()) / 2;
    w.move(x, y);
    w.setWindowTitle("Treaps");
    w.show();
    return a.exec();
}
