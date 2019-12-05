#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMessageBox>
#include "binarytree.h"
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
    void on_pushButton_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
