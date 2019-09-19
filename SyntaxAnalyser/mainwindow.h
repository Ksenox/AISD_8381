#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <text_with_brackets_syntax_checker.h>
#include <syntax_mistake.h>
#include <iostream>
#include <string>
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
    void on_Check_syntax_button_clicked();

    void on_Load_from_file_button_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
