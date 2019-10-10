#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "components.h"
#include "vec.h"

#include <thread>
#include <QApplication>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileInput_clicked()
{
    QString input;
    QString fileName = QFileDialog::getOpenFileName(this,
                tr("open the *.txt"),  QDir::homePath(),
                tr("(*.txt);;All Files (*)"));
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0, "info", file.errorString());
    QTextStream in(&file);
    ui->inputLine->setText(in.readAll());
    checkInput();
}

void MainWindow::on_consoleInput_clicked()
{
    checkInput();
}

void MainWindow::checkInput(){
    QString input = ui->inputLine->text();
    QStringList list = input.split(" ");
    int* arr = new int[list.length()];
    string result;

    //check if string is unsupported
    for (int i = 0; i < input.size(); ++i){
        if((input[i].isLetter()) || (input[i].isPunct()) && (input[i] != '-')){
            QLabel *label = new QLabel("there isn't the number array!");
            label->show();
            label->resize(200, 200);
            ui->windowResult->clear();
            return;
        }
    }
    for (int i = 0; i < list.length(); ++i) {
        arr[i] = list[i].toInt();
    }

    arr = rec(0, list.length(), arr, result);
    result.append("Changed vector:\n");
    for (int i = 0; i < list.length(); ++i) {
        result.append(to_string(arr[i]) + " ");
    }

    ui->windowResult->setText(QString::fromStdString(result));
    ofstream resultFile("C:/a/result.txt", ios_base::out);
    resultFile << result;
    resultFile.close();

    delete[] arr;
}
