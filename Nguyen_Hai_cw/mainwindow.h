#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <string>
#include <QGraphicsScene>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QTextEdit>
#include <QInputDialog>
#include <QDateTime>
#include "console.h"

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
    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    bool flagEncode = false;
    bool flagDecode = false;
    bool flagEasy = false;
    bool flagNormal = false;
    bool flagHard = false;
    console cuaso;
    string input;
    string encode;
    string question_text;
    string analize;
    string result;

};

#endif // MAINWINDOW_H
