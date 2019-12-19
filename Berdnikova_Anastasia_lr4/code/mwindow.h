#ifndef MWINDOW_H
#define MWINDOW_H

#include <QMainWindow>
#include <string>
#include "tree.h"
#include "dialog.h"
#include "help.h"

namespace Ui {
class MWindow;
}

class MWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MWindow(QWidget *parent = 0);
    ~MWindow();

private slots:
    void on_process_clicked();

    void on_show_t_clicked();

    void on_actionHelp_triggered();

private:
    Ui::MWindow *ui;
    Tree* head;
    Help* help;
};

#endif // MWINDOW_H
