#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "methods.h"
#include <cstring>
#include <fstream>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
Stack<long long int> stack{};
long long int i = 0;
string answer{};
string inputTest{};
string err{};
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_resultButton_clicked()
{
    string  checkInput = ui->inputLine->text().toUtf8().constData();
    if(checkInput.empty()){
        ui->resultWindow->setText(QString::fromStdString("Uncorrect test. Input numbers!\n"));
        return;
    }
    string result;
    string error;

    long answer = calculation(checkInput, result, error);
    if(!error.empty()){
        ui->resultWindow->setText(QString::fromStdString(error));
    }else{
        string str = "Результат вычислений: ";
        str+=to_string(answer);
        ui->resultWindow->setText(QString::fromStdString(str));
    }
    this->resize(439, 572);
    this->resize(438, 571);
}

void MainWindow::on_stepButton_clicked()
{
    QString str = ui->inputLine->text();
    if(inputTest.compare(str.toUtf8().constData())!=0){
        i=0;
        answer.clear();
        err.clear();
        inputTest.clear();
        inputTest.append(str.toUtf8().constData());
        ui->resultWindow->clear();
        stack.clear();
        stack.setSize(inputTest.length());
    }
    if(!err.empty()){
        return;
    }
    if(i>=inputTest.length() && stack.length()==1){
        i=0;
        stack.pop();
        answer.clear();
        err.clear();
    }
    onestep(inputTest[i], stack, answer, err);
    i++;
    if(answer.empty()){
        ui->resultWindow->setText(QString::fromStdString(err));
    }
    else if(err.empty()){
        ui->resultWindow->setText(QString::fromStdString(answer));
    }
    else{
        ui->resultWindow->setText(QString::fromStdString(answer)+QString::fromStdString(err));
    }
    this->resize(439, 572);
    this->resize(438, 571);
}

void MainWindow::on_fileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open TXT File"),  QDir::homePath(),
            tr("TXT text (*.txt);;All Files (*)"));
    ifstream sourceFile(fileName.toUtf8().constData());
    string input;
    sourceFile >> input;
    ui->inputLine->setText(QString::fromStdString(input));
}

void MainWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open TXT File"),  QDir::homePath(),
            tr("TXT text (*.txt);;All Files (*)"));
    ofstream sourceFile(fileName.toUtf8().constData());
    sourceFile << ui->resultWindow->toPlainText().toUtf8().constData();
}

