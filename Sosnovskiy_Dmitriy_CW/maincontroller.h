#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <QString>
#include "mainview.h"
class MainController
{
protected:
    MainView* view;

public:
    void attachView(MainView* view);

    void virtual calculate(QString inputString) = 0;

    void virtual openFile() = 0;

    void virtual startView() = 0;

    void virtual remove(QString string) = 0;

    MainController();
};

#endif // MAINCONTROLLER_H
