#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <time.h>

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
        clock_t time;
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
            time = clock();
            cmp_t->quickSort(mas, 0, i, i + 1, repr);
            time = clock() - time;
            QString time_a;
            time_a.append("Время работы составило: ");
            time_a.append(QString::number((double)time/CLOCKS_PER_SEC));
            time_a.append("     размер массива: ");
            time_a.append(QString::number(i + 1));
            ui->label_3->setText(time_a);
            out_n.append(QString::fromStdString(*repr));
            ui->textEdit_2->setText(out_n);
        }
        else QMessageBox::warning(this,"Error", "Incorrect input");
}


