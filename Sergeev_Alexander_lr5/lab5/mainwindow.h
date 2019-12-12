#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

  void enable_input(bool val);
  void step_input(bool val);

private slots:
  void read_from_file();
  void read_from_line();
  void step();
  void step_forward();
  void rush_forward();
  void mult_forward();
};

#endif // MAINWINDOW_H
