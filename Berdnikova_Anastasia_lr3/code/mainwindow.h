#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QFileDialog>
#include <QMainWindow>
#include <QFile>
#include <QTextStream>
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
   // bool can = false;

private slots:
    void on_pushButton_clicked();
  //  void MainWindow::on_textInput_textChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
