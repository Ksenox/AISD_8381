#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    process = new(console);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString data = ui->textEdit->toPlainText();
    int flagError = 0;
    result = new  (string);
    analize = new  (string);
    process->Console(flagCase_1,flagCase_2,&flagError,result,analize,data);
    if(!flagError){
        ui->textEdit_2->setText(QString::fromStdString(*result));
        ui->textEdit_3->setText(QString::fromStdString(*analize));
    }
    else if (flagError == 2) {
        QMessageBox::warning(this,"Error","Please,select any radio button!");
        flagCase_2 = false;
    }
    else if(flagError == 1){
        QMessageBox::warning(this,"Error","Input incorrect");
        flagCase_1 = false;
    }

}

void MainWindow::on_radioButton_clicked(bool checked)
{
    flagCase_2 = false;
    flagCase_1 = checked;
}

void MainWindow::on_radioButton_2_clicked(bool checked)
{
    flagCase_2 = checked;
    flagCase_1 = false;
}
