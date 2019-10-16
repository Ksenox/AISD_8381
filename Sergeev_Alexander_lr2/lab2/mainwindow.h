#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AtomicList.h"

#define FILL_TEXT "Fill"
#define REFILL_TEXT "Refill"
#define MAX_CHARS 1000

using namespace std;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void build();
    void fill();
    void calculate();

private:
    Ui::MainWindow *ui;

    void printError(string &errorString, int pos, string& message);
    void convertPower(string &expr);
    void catchErrors(int e);

    string input, data, output;
    AtomicList *list;
};

#endif // MAINWINDOW_H
