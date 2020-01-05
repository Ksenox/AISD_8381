#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "bintree.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void reset();
    void visualize();
    void draw(QGraphicsScene* scene, Node *n, int maxdepth, int depth = 0, int x = 0, int y = 0);
    int read(bool& ok);

    QGraphicsScene* graphicsScene;
    Node* tree = nullptr;
    array_list* log = nullptr;
    int index = 0;

    int mode = 0; // 0 - nothing, 1 - inserting, 2 - removing
    int rand_count = 5;
    int rand_max = 99;

    QLabel* status;

private slots:
    void on_fileButton_clicked();

    void on_buildButton_clicked();

    void on_randCountBox_valueChanged(int arg1);

    void on_randMaxBox_valueChanged(int arg1);

    void on_randButton_clicked();

    void on_insertButton_clicked();

    void on_removeButton_clicked();

    void on_nextButton_clicked();

    void on_endButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
