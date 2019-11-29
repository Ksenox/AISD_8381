#ifndef MANUALENTRYWINDOW_H
#define MANUALENTRYWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <QVector>
#include "time.h"

namespace Ui {
class manualEntryWindow;
}

class manualEntryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit manualEntryWindow(QWidget *parent = nullptr);
    ~manualEntryWindow();

private slots:
    void on_pushButton_clicked();

signals:
    void sendString(QString str);
private:
    Ui::manualEntryWindow *ui;
};

#endif // MANUALENTRYWINDOW_H
