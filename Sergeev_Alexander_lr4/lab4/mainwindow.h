#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "lab4.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void build();
    void build_file();
    void run();
    void step();

private:
    lab4* lr;
    int stepPointer;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
