#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "actions.h"

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
    void on_start_clicked();

    void on_saveFile_clicked();

    void on_openFile_clicked();

    void on_outputBtn_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
