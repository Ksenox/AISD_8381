#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QLabel>
#include <QString>
#include <QListWidgetItem>
#include <ctime>
#include "model.h"
#include "ilist.h"

#define M_CHECK if (mainmodel->busy) return; \
                mainmodel->busy = true;

#define M_UNLOCK mainmodel->busy = false;

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
    void on_GenerateButton_clicked();

    void on_ProceedButon_clicked();

    void on_LinkedListButton_clicked();

    void on_ArrayListButton_clicked();

    void on_AutoButton_clicked();

    void on_SortButton_clicked();

private:
    void syncState();
    void syncListView(QListWidget* view, IList<int>& list);

    logic_model* mainmodel;
    Ui::MainWindow *ui;

    QLabel *statusLabel;
    QLabel *statusLabel2;
    QProgressBar *statusProgressBar;


};

#endif // MAINWINDOW_H
