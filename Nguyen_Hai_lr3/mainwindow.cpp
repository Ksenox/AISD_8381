#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cmp = new(SortSelection);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString data = ui->textEdit->toPlainText();
    QStringList text_in = data.split(' ');

    int* arr = new int[100];
    int i = 0;
    bool flagError = false;
    for(auto x:text_in){
        bool flagConvert;
        x.toInt(&flagConvert);
        if(flagConvert == false){
            flagError = true;
        }
        else {
            arr[i] = x.toInt();
            i++;
        }
    }

    if(!flagError){
        QString text_out;
        auto analize = new string();
        auto result = new string();
        analize->append("\n\nArrays length : ");
        analize->append(to_string(i));

        if(flagCase_1){
            analize->append("\n\nRecusion deep : ");
            analize->append(to_string(i-1));
            cmp->selectionSort_1(arr,i,analize,result);
            flagCase_1 = false;
        }
        else if(flagCase_2){
            analize->append("\n\nRecusion deep : ");
            analize->append(to_string(int((i+1)/2)));
            cmp->selectionSort_2(arr,i,analize,result);
            flagCase_2 = false;
        }
        else if (flagCase_1 == false && flagCase_2 == false) {
            QMessageBox::warning(this,"Error","Please,select any radio button!");
            return;
        }


        data.append(QString::fromStdString(*analize));
        ui->textEdit_2->setText(data);
        ui->textEdit_3->setText(QString::fromStdString(*result));
    }
    else QMessageBox::warning(this,"Error","Incorrect input");
}

void MainWindow::on_radioButton_clicked(bool checked)
{
    flagCase_1 = checked;
}


void MainWindow::on_radioButton_2_clicked(bool checked)
{
    flagCase_2 = checked;
}
