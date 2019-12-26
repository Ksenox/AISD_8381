#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
#include <algorithm>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsEffect>
#include <QFileDialog>
#include <QStandardPaths>
#include <QtGui>
#include <QLabel>
#include <QString>
#include <QColorDialog>
#include <QInputDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QStringList>
#include <QTextEdit>
#include <stack>
 #include <QTextEdit>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Tree.h"
static bool started = true;
static std::string Name;
static int action = 0;
static int del = 0;
typedef int Type;





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    ui->outTextEdit->setReadOnly(true);
    ui->inputTextEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]{3}")));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{

    Head_AVL_Tree<Type> head;


        std::string main_str;
        std::ifstream file;


        file.open(Name);
        if (!file.is_open()) {
            ui->outTextEdit->insertPlainText("Error! File isn't open\n");
            return;
        }
        getline(file, main_str);
        ui->outTextEdit->insertPlainText("Input: " + QString::fromStdString(main_str) +"\n");

        int count_num = 0;
        for(size_t i = 0; i < main_str.size(); i++){
            int temp = 0;
            bool is_num = false;
            for(size_t j = i; isdigit(main_str[j]); j++, i++){ // create tree from string
                temp = temp*10 + main_str[j]-'0';
                is_num = true;
            }
            if(is_num){
                count_num++;
                head.insert(temp);
            }

        }

      head.print_tree1(scene);

        if(!count_num){
            ui->outTextEdit->insertPlainText("no one element to tree. Program will end\n\n");
            exit(0);
        }


        ui->outTextEdit->insertPlainText("WHAT TO DO? \n");
        for( ; ; )
        {
        QApplication::processEvents();
        if(!started)break;


        }
        started = true;

        while(1){
            switch (action) {



                case 0:
                    exit (0);
                case 1:
                    Type insert_tree_element = 0;
                    QString str= ui->inputTextEdit->text();
                    ui->inputTextEdit->clear();
                    insert_tree_element  = str.toInt();




                    if(del == 0)
                    {
                            ui->outTextEdit->insertPlainText("add to tree new element: " + QString::number(insert_tree_element) + "\n");
                        if(insert_tree_element==0){
                            ui->outTextEdit->insertPlainText("input error. May be it`s not a number, very big number or more than 1 number\n");

                        }

                        else{
                            ui->outTextEdit->insertPlainText("find this element in AVL_tree: \n");
                        if(!head.is_contain(insert_tree_element)){
                            ui->outTextEdit->insertPlainText("tree does not have this element\n");
                            head.insert(insert_tree_element);
                            ui->outTextEdit->insertPlainText("\n\n\n");
                            head.print_tree1(scene);
                        }
                        else
                            ui->outTextEdit->insertPlainText("element already in tree\n");

                        }
                    }
                    else
                        if (del==1)
                    {
                        ui->outTextEdit->insertPlainText("try delete element: " + QString::number(insert_tree_element) +"\n");
                        if(insert_tree_element==0)
                        {
                            ui->outTextEdit->insertPlainText("input error. May be it`s not a number, very big number or more than 1 number\n");

                        }

                        else{
                            ui->outTextEdit->insertPlainText("delete element: " + QString::number(insert_tree_element) +"\n");
                                            ui->outTextEdit->insertPlainText("find this element in AVL_tree: ");
                                            if(!head.is_contain(insert_tree_element)){
                                                ui->outTextEdit->insertPlainText("tree does not have this element");
                                                head.print_tree1(scene);
                                            }
                                            else{
                                                head.remove(insert_tree_element);
                                                ui->outTextEdit->insertPlainText("tree after delete: ");
                                                head.print_tree1(scene);
                                                }

                        del = 0;

                    }
                        }
                       action = 0;
                       ui->outTextEdit->insertPlainText("MORE ACTION? ");

                       for( ; ; )
                       {
                       QApplication::processEvents();
                       if(!started)break;


                       }
                       started = true;



                    break;

}
}
}


void MainWindow::on_pushButton_2_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this, "OpenDialog",
    QDir::homePath(), "*.txt;; *.*");
    Name = FileName.toStdString();
}

void MainWindow::on_pushButton_3_clicked()
{
    started=false;
    action = 1;
}




void MainWindow::on_pushButton_4_clicked(){
    started=false;
    action = 0;
}

void MainWindow::on_pushButton_5_clicked()
{
    started=false;
    action = 1;
    del = 1;
}
