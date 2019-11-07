#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "family.h"
#include "about.h"
#include "help.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Family *fml;
    about *abt;
    help *hlp;
    bool can = false;
    bool from_file = false;

private slots:

    void on_resultButtom_clicked();

    void on_Input_textChanged();


    void on_actionOpen_file_triggered();

    void on_actionHelp_triggered();

    void on_actionAbout_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
