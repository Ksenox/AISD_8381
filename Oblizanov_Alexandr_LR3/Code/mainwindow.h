#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "console.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void getInfo(string filePath);
    void getOutput();
    ~MainWindow();

private slots:
    void on_openFile_clicked();

    void on_start_clicked();

    void on_saveFile_clicked();

    void on_checkInfo_toggled(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
