#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "function.h"
#include <QMainWindow>

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
    void on_calculateButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
