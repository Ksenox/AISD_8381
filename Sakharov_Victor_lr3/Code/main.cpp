#include "mainwindow.h"
#include "utils_cli.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc > 1 && !strncmp(argv[1], "-c", 2)) //STUB
    {
        return utils_cli::exec(argc - 2, argv + 2);
    }
    else
    {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }
}
