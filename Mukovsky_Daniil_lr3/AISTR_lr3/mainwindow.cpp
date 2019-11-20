#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Сортировка естественным слиянием");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resirvedString(QString str){
    ui->Array->setText(str);
}

void MainWindow::on_arrayCreation_clicked()
{
    random = new randomEntryWindow();
    connect(random,SIGNAL(sendString(QString)),this,SLOT(resirvedString(QString)));
    random->exec();
}

bool MainWindow::array_check(QString inputArray){
    QRegExp reg( "^-?\\d{1,6} *$|^(-?\\d{1,6} )+-?\\d{1,6} *$" );
    return reg.exactMatch(inputArray);
}

void MainWindow::on_pushButton_clicked()
{
    QString inputArray = ui->Array->text();
    if (inputArray.isEmpty()){
        QMessageBox::critical(this,"Ошибка","Вы не задали массив");
        return;
    }
    if (!array_check((inputArray))){
        QMessageBox::critical(this,"Ошибка","Массив задан некорректно ");
        return;
    }
    else{
        while(inputArray[inputArray.size()-1]==' '){
            inputArray.remove(inputArray.size()-1,inputArray.size()-1);
        }
        qmergeForm = new QuickMergeSort();
        connect(this, SIGNAL(sendArray(QString)), qmergeForm, SLOT(recieveArray(QString)));
        emit sendArray(inputArray);
        qmergeForm->exec();
    }
}
