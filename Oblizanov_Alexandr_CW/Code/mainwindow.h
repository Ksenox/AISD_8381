#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "strstrtester.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_GPushOk_clicked();

    void on_HPushOk_clicked();

    void on_MPushOk_clicked();

    void on_OutSetPlot_toggled(bool checked);

    void on_OutSaveFile_clicked();

private:
    void setupPlot();
    Ui::MainWindow *ui;
    StrStrWorker ssw;
};
#endif // MAINWINDOW_H
