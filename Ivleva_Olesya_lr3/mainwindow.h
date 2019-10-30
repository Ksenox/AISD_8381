#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "functions.h"
#include <fstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Hello_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
