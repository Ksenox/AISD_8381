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
    void on_resultButton_clicked();

    void on_stepButton_clicked();

    void on_fileButton_clicked();

    void on_saveButton_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
