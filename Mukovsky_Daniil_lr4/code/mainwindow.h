#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "customoutput.h"
#include <QFileDialog>
#include <fstream>
#include <sstream>
#include <iostream>
#include "bracketbalance.h"
#include "console.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void sendArray(QString str);

private slots:
    void on_pushButton_clicked();

    void on_readFileButton_clicked();

private:
    Ui::MainWindow *ui;
    customOutput *cusOuput;
};
#endif // MAINWINDOW_H
