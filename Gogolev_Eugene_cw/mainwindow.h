#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "coding.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    types type;
    methods method;
    int variant_count;
    int length;

private slots:
    void on_type_currentIndexChanged(int index);

    void on_method_currentIndexChanged(int index);

    void on_generate_clicked();

    void on_variants_valueChanged(int arg1);

    void on_file_clicked();

    void on_length_valueChanged(int arg1);

    void on_hand_textChanged(const QString &arg1);

    void on_lr5_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
