#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "allheaders.h"
#include "btree.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_resultButton_clicked();
    void on_stepButton_clicked();
    void on_deriativeButton_clicked();
    void on_fileOutput_clicked();
    void on_fileInput_clicked();
    void on_stepDraw_clicked();
    void on_drawButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
};

struct Node* createTree(string & checkInput, string&);

#endif // MAINWINDOW_H
