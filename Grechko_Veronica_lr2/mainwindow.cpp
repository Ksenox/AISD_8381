#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    binrock = new (binary_rock);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_choose_file_clicked()
{
    QString file_name = QFileDialog().getOpenFileName();
    if(!file_name.isNull()){
        QFile file(file_name);
        if(file.open(file.ReadOnly)){
            QString data  = file.readAll();
            if(data.toStdString().length() < 13 ){
                QMessageBox::warning(this,"Error", "Incorrect input");
            }
            else{
                Side* side = new (Side);
                binrock->parseString(data.toStdString(), *side);
                if (binrock->Balanced(side->plum->uni.child))
                    QMessageBox::information(this, "Info", "Balanced");
                else
                    QMessageBox::information(this, "Info", "Not balanced");
                delete side;
            }
        }
    }
    else QMessageBox::warning(this,"Error", "Not Found");
}

void MainWindow::on_onconsole_clicked()
{
    QString data = ui->textEdit->toPlainText();
    if(data.toStdString().length() < 13 ){
        QMessageBox::warning(this,"Error", "Incorrect input");
    }
    else{
        Side* side = new (Side);
        binrock->parseString(data.toStdString(), *side);
        if (binrock->Balanced(side->plum->uni.child))
            QMessageBox::information(this, "Info", "Balanced");
        else
            QMessageBox::information(this, "Info", "Not balanced");
        delete side;
    }
}
