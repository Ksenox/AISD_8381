#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsEffect>
#include <QGraphicsView>
#include <QFileDialog>
#include <QStandardPaths>
#include <QtGui>
#include <QLabel>
#include <QColorDialog>
#include <QInputDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <iostream>
#include <fstream>
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
    string getInfo(string filePath);
    int checkExp(string &expIn, unsigned long &pos, int &funcNum);
    int checkString(string &expIn, unsigned long &pos, int &funcNum);

private slots:
    void on_start_clicked();

    void on_file_clicked();

    void on_save_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
