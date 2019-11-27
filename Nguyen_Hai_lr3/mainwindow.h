#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <console.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool flagCase_1 = false;
    bool flagCase_2 = false;
    console *process;
    string *result;
    string *analize;

private slots:
    void on_pushButton_clicked();

    void on_radioButton_clicked(bool checked);


    void on_radioButton_2_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
