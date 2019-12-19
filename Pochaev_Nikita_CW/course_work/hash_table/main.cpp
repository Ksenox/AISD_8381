#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "allheaders.h"
#include "TableHandler.h"

int main(int argc, char *argv[]) {

    // force initialization of library resources
    Q_INIT_RESOURCE(resources);

    QApplication a(argc, argv);

    MainWindow window;

    window.show();

    return a.exec();
}
