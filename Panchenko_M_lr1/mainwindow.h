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
    void checkInput();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_fileInput_clicked();

    void on_consoleInput_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
