#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "array_list.h"
#include "quicksort3.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include <QMessageBox>

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
    void on_Generate_clicked();

    void on_Input_clicked();

    void on_Sort_clicked();

private:
    Ui::MainWindow *ui;
    array_list list;
    void visualize();
};

#endif // MAINWINDOW_H
