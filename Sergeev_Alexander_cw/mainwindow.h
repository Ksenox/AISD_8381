#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "generator.h"
#include "core.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
     ~MainWindow();

private:
     Ui::MainWindow *ui;

     void configure_input(int new_step_action);

     void read(bool from_file);

private slots:
     void generate();
     void read_from_file();
     void read_from_line();

     void save();
     void load();
     void clear();

     void back();
     void step();

     void log();
     void about_treap();
     void about_app();

     void merge();
     void split();
     void mult();
};

#endif // MAINWINDOW_H
