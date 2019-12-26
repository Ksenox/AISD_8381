#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include <node.h>
#include "binTree.h"
#include "testing.h"

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

    binTree* questionTree;
    binTree* answerTree;

    QGraphicsScene* questionGraphicsScene;
    QGraphicsScene* answerGraphicsScene;
    int mode; // 0-insert 1-delete
    int difficulty;
    int var_count;


private slots:
    void on_resetButton_clicked();

    void on_varButton_clicked();

    void on_genFileButton_clicked();

    void on_varNum_valueChanged(int arg1);

    void on_difficultyBox_valueChanged(int arg1);

    void on_radioInsertButton_toggled(bool checked);

    void on_radioRemoveButton_toggled(bool checked);

    void on_inFIleButton_clicked();

    void on_treeGenButton_clicked();

    void on_insertButton_clicked();

    void on_removeButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
