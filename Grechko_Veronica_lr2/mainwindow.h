#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include "binary_rock.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    binary_rock* binrock;
private slots:

    void on_choose_file_clicked();

    void on_onconsole_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
