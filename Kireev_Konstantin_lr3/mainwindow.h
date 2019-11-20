#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <QPixmap>

#include <iostream>
#include <fstream>
#include <shellsort.h>
using namespace std;

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
    void on_array_clicked();

    void on_incrementShell_clicked();

    void on_info1_clicked();

    void on_info2_clicked();

    void on_step1_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
