#include "mainwindow.h"
#include "utils_cli.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    for(int i = 0; i < argc; i++) {
        if(!strcmp("console", argv[i]) || !strcmp("-console", argv[i]) || !strcmp("-c", argv[i])) {
            return utils_cli::execute(argc - 1, argv + 1);
        }
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
