#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "binaryrandomtreap.h"
#include "maincontroller.h"
#include "syntaxerrorexception.h"
#include "generationwindow.h"
#include "generationwindowcontroller.h"
#include <QFileDialog>
class Controller : public MainController
{
private:
    BinaryRandomTreap* treap;
public:
    Controller();

    void calculate(QString inputString) override;

    void openFile() override;

    void remove(QString str) override;

    void startView() override;
};

#endif // CONTROLLER_H
