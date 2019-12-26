#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMessageBox>
#include "maincontroller.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public MainView
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setAnswer(QString answer) override;

    void setInputFromFile(QString input) override;

private slots:

    void on_calculatePushButton_clicked();

    void displayResults(QGraphicsScene* scene) override;

    void on_downloadFromFileAction_triggered();

    void on_helpAction_triggered();

    void on_authorInformationAction_triggered();

    void on_generationWindowAction_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
