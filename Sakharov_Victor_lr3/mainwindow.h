#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QLabel>
#include <QString>
#include <QListWidgetItem>
#include <ctime>
#include "mainmodel.h"
#include "ilist.h"
#include "utils_list.h"
#include "utils_linked_list.h"
#include "utils_strandsort.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void syncState();

private slots:
    void on_GenerateButton_clicked();

    void on_LinkedListButton_clicked();

    void on_ArrayListButton_clicked();

    void on_BackButton_clicked();

    void on_AutoButton_clicked();

    void on_ForwardButton_clicked();

    void on_SortButton_clicked();

private:
    mainmodel* model;
    Ui::MainWindow *ui;

    QLabel *statusLabel;
    QLabel *statusLabel2;
    QProgressBar *statusProgressBar;


};

#endif // MAINWINDOW_H
