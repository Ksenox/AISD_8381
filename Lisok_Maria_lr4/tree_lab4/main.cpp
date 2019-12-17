#include "allheaders.h"
#include "mainwindow.h"
#include "infixtopostfix.h"
#include "stack.h"
#include "btree.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
