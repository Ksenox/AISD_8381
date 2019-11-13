#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cmp_t = new(cmp_type);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
        QString data = ui->textEdit->toPlainText();
        QStringList abc = data.split(' ');
        QStringList result;
        int* mas = new int[100];
        int i =0;
        bool go = true;
        for (auto x:abc){
             bool convertOK;
             x.toInt(&convertOK);
             if(convertOK == false){
                 go = false;

             }
             else{
                mas[i] = x.toInt();
                i++;
             }
        }

        if(go){
            QString out_n;

            auto repr = new string();
            cmp_t->quickSort(mas, 0, i, i, repr);
            out_n.append(QString::fromStdString(*repr));

            for (int k =0; k < i; k++){
                out_n.append(QString::number(mas[k]));
                out_n.append(" ");
            }

            ui->label_3->setText(out_n);
        }
        else QMessageBox::warning(this,"Error", "Incorrect input");
}


