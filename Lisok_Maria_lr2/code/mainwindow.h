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
    void checkLists();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_checkButton_clicked();

    void on_fileButtonForList1_clicked();

    void on_fileButtonForList2_clicked();

    void on_saveToFile_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
