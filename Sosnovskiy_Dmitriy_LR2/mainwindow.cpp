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
    QString inputFunction = ui->inputFunction->text();
    QString derivativeBasis = ui->inputDerivativeBasis->text();

    if(inputFunction.size() != 0 && derivativeBasis.size() != 0)
    {
        Function function(inputFunction);

        QString derivative = function.getDerivative(derivativeBasis[0]);

        if(ui->simplifyButton->checkState() == Qt::Checked)
        {
            Function derivativeFunction(derivative);
            ui->outputAnswer->setText(derivativeFunction.simplify());
        }
        else
            ui->outputAnswer->setText(derivative);
    }
    QString string = inputFunction;

}

void MainWindow::on_inputDerivativeBasis_editingFinished()
{
    if(ui->inputDerivativeBasis->text() != "")
    {
        if(ui->inputDerivativeBasis->text()[0].isNumber() == true)
        {
            ui->inputDerivativeBasis->clear();
        }
    }
}
