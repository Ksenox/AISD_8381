#include "mainwindow.h"
#include <QApplication>
#include "controller.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow();

    Controller* controller = new Controller();

    controller->attachView(w);

    w->show();

    return a.exec();
}
