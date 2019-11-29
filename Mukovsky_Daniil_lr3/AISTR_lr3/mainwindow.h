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
#include <string>
#include <cstdlib>
#include <QVector>
#include <QRegExp>
#include "time.h"
#include "console.h"
#include "randomentrywindow.h"
#include "quickmergesort.h"

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
    void on_arrayCreation_clicked();
    void resirvedString(QString str);
    bool array_check(QString str);
    void on_pushButton_clicked();

signals:
    void sendArray(QString str);

private:
    Ui::MainWindow *ui;
    QuickMergeSort *qmergeForm;
    randomEntryWindow *random;
};
#endif // MAINWINDOW_H
