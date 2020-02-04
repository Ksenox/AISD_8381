#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <huffman.h>
#include <fstream>
#include <string>
#include <QGraphicsScene>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QTextEdit>

#include "huffman.h"
#include "console.h"

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
    void on_run_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    console cuaso;

    QString input;
    QString encode;

};

#endif // MAINWINDOW_H
