#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_create_clicked();

    void on_openfile_clicked();

    void on_savefile_clicked();

    void on_deleteItem_clicked();

    void on_averagecase_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
