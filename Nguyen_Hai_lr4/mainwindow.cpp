#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Console = new console;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString data = ui->textEdit->toPlainText();
    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
    scene->clear();
    flagErr = Console->checkErr(data);

    if(flagErr == 1){
        QMessageBox::warning(this,"Err","Missing character '(' or ')'");
    }
    else if(flagErr == 2){
        QMessageBox::warning(this,"Err","Tree empty.");
    }
    else if(flagErr == 3){
        QMessageBox::warning(this,"Error","Input is not alpharic");
    }
    else if(flagErr == 4){
        QMessageBox::warning(this,"Error","Extra character ')'");
    }
    else if (flagErr == 5){
        QMessageBox::warning(this,"Error","The first tree in forest incorrect.");
    }
    else if (flagErr == 6) {
        QMessageBox::warning(this,"Error","Input incorrect");
    }
    else if (flagErr == 0) {
        if(flagCase_1 == false && flagCase_2 == false)
            QMessageBox::warning(this,"Warning","Please,select any radio button!");
        else if(flagCase_2 == true){
            scene = Console->Console( data);
            ui->graphicsView->setScene(scene);
        }
        else if(flagCase_1 == true){
            scene = Console->Analize(data);
            ui->graphicsView->setScene(scene);
        }
    }


}


void MainWindow::on_radioButton_2_clicked(bool checked)
{
    flagCase_2 = checked;
    flagCase_1 = false;
}

void MainWindow::on_radioButton_clicked(bool checked)
{
    flagCase_2 = false;
    flagCase_1 = checked;
}
