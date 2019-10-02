#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Function.h"

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

    void on_inputDerivativeBasis_editingFinished();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
