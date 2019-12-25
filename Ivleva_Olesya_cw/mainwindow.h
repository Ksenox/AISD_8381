#include <QMainWindow>
#include "functions.h"
#pragma once
#include "printhash.h"
#include <fstream>
#include <QMessageBox>
#include <QGraphicsScene>

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
    void on_Push_File_clicked();

    void on_nextStep_clicked();

    void on_prevStep_clicked();

    void on_del_elem_clicked();

    void on_prev_del_clicked();

    void on_next_del_clicked();

    void on_del_all_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Hash_cl<string, string> Hash_;
    Hash_cl<string, string> Hash_st;
    string str;
    string str_step;
    string str_del = "";
    string str_del_step;
    int ind_st = 0;
};

