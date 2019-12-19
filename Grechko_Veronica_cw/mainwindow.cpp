#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<bin_struct.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_printTree_clicked()
{

    QString data = ui->input_tree->text();
    QStringList abc = data.split(' ');
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
    if(!go){
        QMessageBox::warning(this,"Error", "Incorrect input");
        return;
    }
    BinTree* BT = new (BinTree);
    for(int j = 0; j < i; j++){
        BT->Head = BT->insert(BT->Head, mas[j]);
    }

    int depth = BT->max_depth(BT->Head);
    ui->input_del->setText(QString::number(depth));
    graphic(BT, scene, depth);

}

void MainWindow::on_delete_elem_clicked()
{
    QString data = ui->input_tree->text();
    QStringList abc = data.split(' ');
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
    if(!go){
        QMessageBox::warning(this,"Error", "Incorrect input");
        return;
    }
    BinTree* BT = new (BinTree);
    for(int j = 0; j < i; j++){
        BT->Head = BT->insert(BT->Head, mas[j]);
    }
    QString elem_ = ui->input_del->text();
    bool convert_;
    int elem = elem_.toInt(&convert_);
    if(!convert_){
        QMessageBox::warning(this,"Error", "Incorrect input");
        return;
    }
    BT->Head = BT->remove(BT->Head, elem);
    int depth = BT->max_depth(BT->Head);
    QString out;
    for(int l = 0; l < i - 1; l++){
        if (mas[l] == elem){
            for(int k = l; k < i - 1; k++){
                mas[k] = mas[k + 1];
            }
        }
        out.append(QString::number(mas[l]));
        if(l != i -2) out.append(" ");
    }
    ui->input_tree->setText(out);
    graphic(BT, scene, depth);
}

void MainWindow::on_choose_file_clicked()
{
    QString file_name = QFileDialog().getOpenFileName();
        if(!file_name.isNull()){
            QFile file(file_name);
            if(file.open(file.ReadOnly)){
                QString data  = file.readAll();
                 if (data == "") {
                     QMessageBox::critical(this, "Error!", "Введите дерево");
                     return;
                 }
                 else{
                     QStringList abc = data.split(' ');
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
                     if(!go){
                             QMessageBox::warning(this,"Error", "Incorrect input");
                             return;
                     }
                     BinTree* BT = new (BinTree);
                     for(int j = 0; j < i; j++){
                         BT->Head = BT->insert(BT->Head, mas[j]);
                     }
                     int depth = BT->max_depth(BT->Head);
                     graphic(BT, scene, depth);
                     }
                 }


        }
        else QMessageBox::warning(this,"Error", "Not Found");
}

