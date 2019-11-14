#include "mainwindow.h"

#include <QApplication>
int main(int argc, char *argv[])
{
    bool console = false;
        for(int i=1;i<argc;i++)
        {
            if(!strcmp("console",argv[i]))
                console = true;
        }
        if (console)
        {
            startConsole();
        }
        else
        {
            QApplication a(argc, argv);
            MainWindow w;
            w.show();
            return a.exec();
        }
}
