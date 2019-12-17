#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QMessageBox>
#include <iostream>
#include <vector>
#include <sstream>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QColor>
#include <QFileDialog>
#include <QTextStream>
#include <cmath>
#include "binTree.h"
#include "help.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void visualize();
    void draw(Node *n, int maxdepth, int depth = 0, int x = 0, int y = 0);

private slots:
    void on_pushButton_clicked();

    void on_action_triggered();

    void on_stepButton_clicked();

    void on_fileButton_clicked();

private:
    binTree* tree;
    Ui::MainWindow *ui;
    QGraphicsScene *mainGraphicsScene;
    QPen pen;

    Node* first;
    Node* second;
    int a;
    int b;
    array_list elems;
    bool started;
};

#endif // MAINWINDOW_H
