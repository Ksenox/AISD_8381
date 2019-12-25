#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <console.h>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    console *Console;
    bool flagCase_1 = false;
    bool flagCase_2 = false;
    int flagErr;

private slots:
    void on_pushButton_clicked();


    void on_radioButton_2_clicked(bool checked);

    void on_radioButton_clicked(bool checked);


private:
    Ui::MainWindow *ui;
    QGraphicsView *scene;
};

#endif // MAINWINDOW_H
