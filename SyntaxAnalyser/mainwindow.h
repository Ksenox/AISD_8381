#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <text_with_brackets_syntax_checker.h>
#include <syntax_mistake.h>
#include <iostream>
#include <QFileDialog>

using namespace std;

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
    void on_A_button_clicked();

    void on_B_button_clicked();

    void on_Square_left_button_clicked();

    void on_Square_right_button_clicked();

    void on_Circle_left_button_clicked();

    void on_Circle_right_button_clicked();

    void on_Waving_left_button_clicked();

    void on_Waving_right_button_clicked();

    void on_Check_syntax_button_clicked();

    void on_Load_from_file_button_clicked();

    void on_Open_logs_file_button_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
