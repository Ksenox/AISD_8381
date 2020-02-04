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

void MainWindow::on_run_clicked()
{
    scene = new QGraphicsScene(ui->graphicsView);
    scene->clear();

    input = ui->lineEdit->text();
    encode = ui->lineEdit_2->text();

    int flagErr = cuaso.checkErr(input,encode);

    if(flagErr == 1){
        QMessageBox::critical(this,"ERROR!","Text contains Russian");
        return;
    }
    else if (flagErr == 2) {
        QMessageBox::critical(this,"ERROR!","The text must contain only 0 or 1 characters");
        return;
    }
    else if(flagErr == 3){
        QMessageBox::critical(this,"ERROR!","missing input data");
        return;
    }
    else {
        string input_2 = input.toStdString();
        string encode_2 = encode.toStdString();
        int fl;
        string result = cuaso.result(input_2,encode_2,&fl);
        string analize = cuaso.analize(input_2);

        if(fl == 1){
            QMessageBox::critical(this,"ERROR!","Encode incorrect!");
            return;
        }

        ui->textEdit->setText(QString::fromStdString(analize));
        ui->textEdit_2->setText(QString::fromStdString(result));

        scene = cuaso.Paint(input_2);
        ui->graphicsView->setScene(scene);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose file."), QDir::homePath(), tr("*.txt"));
    if (QString::compare(fileName, QString()) != 0)
    {
        std::ifstream f(qPrintable(fileName), std::ios::in);
        std::string out;
        getline(f, out);
        f.close();
        ui->lineEdit->setText(QString::fromStdString(out));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose file."), QDir::homePath(), tr("*.txt"));
    if (QString::compare(fileName, QString()) != 0)
    {
        std::ifstream f(qPrintable(fileName), std::ios::in);
        std::string out;
        getline(f, out);
        f.close();
        ui->lineEdit_2->setText(QString::fromStdString(out));
    }
}
/*
bool MainWindow::readInput(){
    input = ui->lineEdit->text();
    encode = ui->lineEdit_2->text();
    int fl = checkinput(input,encode);
    if (input.size()==0){
        QMessageBox::critical(this,"ERROR!","No massage");
        return false;
    }
    if (encode.size()==0){
        QMessageBox::critical(this,"ERROR!","No massage");
        return false;
    }
    if (fl == 1){
        QMessageBox::critical(this,"ERROR!","Text contains Russian");
        return false;
    }
    if (fl == 2){
        QMessageBox::critical(this,"ERROR!","The text must contain only 0 or 1 characters");
        return false;
    }
    return  true;
}
*/
