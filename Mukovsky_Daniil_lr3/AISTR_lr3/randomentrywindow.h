#ifndef RANDOMENTRYWINDOW_H
#define RANDOMENTRYWINDOW_H

#include <QDialog>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <QVector>
#include <QMessageBox>
#include "time.h"

namespace Ui {
class randomEntryWindow;
}

class randomEntryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit randomEntryWindow(QWidget *parent = nullptr);
    ~randomEntryWindow();
private slots:
    void on_pushButton_clicked();

signals:
    void sendString(QString str);

private:
    Ui::randomEntryWindow *ui;
};

#endif // RANDOMENTRYWINDOW_H
