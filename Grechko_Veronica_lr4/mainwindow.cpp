#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <functionstree.h>
#include <bintree.h>

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

void MainWindow::on_onPrint_clicked()
{
    QString rinput = ui->lineEdit->text();
    QString input = delSpace(rinput);
    if (input != ""){
        if (input[0] != '(' || input[input.size() - 1] != ')'){
            QMessageBox::critical(this, "Error!", "Дерево введенно некорректно");
            return;
        }
    }
    else {
        QMessageBox::critical(this, "Error!", "Введите дерево");
        return;
    }

    BinTree* BT = new  (BinTree);
    BT->Head = BT->createTree(mySplit(input));
    QString out;
    out.append("Глубина дерева: ");

    int depth = BT->max_depth(BT->Head);
    out.append(QString::number(depth - 1));
    ui->label->setText(out);
    graphic(BT, scene,depth);


}

void MainWindow::on_onLeavesonLevel_clicked()
{
    QString rinput = ui->lineEdit->text();
    QString level_i = ui->lineEdit_2->text();
    int level = level_i.toInt();
    QString input = delSpace(rinput);
    if (input != ""){

    }
    else {
        QMessageBox::critical(this, "Error!", "Введите дерево");
        return;
    }
    BinTree* BT = new  (BinTree);
    BT->Head = BT->createTree(mySplit(input));
    QString out;
    out.append("Количество узлов: ");
    int count = BT->count_node(BT->Head,level, 1, 0);
    out.append(QString::number(count));
    ui->label->setText(out);

}
