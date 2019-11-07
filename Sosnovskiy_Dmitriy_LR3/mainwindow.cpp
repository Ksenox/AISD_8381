#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calculateButton_clicked()
{
    QString inp = ui->input->text();

    Function function(inp);
    int ans;
    if(ui->stepByStepChecked->isChecked() == false)
    {
        ans = function.calculate();
    }
    else ans = function.calculateStepByStep();

    ui->output->setText(QString::number(ans));
}
