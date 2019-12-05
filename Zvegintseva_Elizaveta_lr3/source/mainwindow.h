#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "headers.h"
#include "postfixform.h"
#include "methods.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_result_clicked();

    void on_step_clicked();

    void on_dataFromFile_clicked();

    void on_saveOutput_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
