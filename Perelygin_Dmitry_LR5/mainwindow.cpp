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
bool started = true;
std::string Name;
int action = 0;
typedef int Type;





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



void MainWindow::on_pushButton_clicked()
{
    text_sreen = new QTextEdit;

    Head_AVL_Tree<Type> head;


        std::string main_str;
        std::ifstream file;


        file.open(Name);
        if (!file.is_open()) {
            std::cout << "Error! File isn't open" << std::endl;
            return;
        }
        getline(file, main_str);
        std::cout << "Input: " << main_str << std::endl;

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
            std::cout << "no one element to tree. Program will end" << std::endl;
            exit(0);
        }


        std::cout << "add something? ";
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
                    break;
                case 1:
                    Type insert_tree_element;
                    QString str= ui->textEdit->toPlainText ();
                    insert_tree_element  = str.toInt();





                        std::cout << "add to tree new element: " << insert_tree_element  << std::endl;
                    /*if(std::cin.fail()){
                        std::cout << "input error. May be it`s not a number or it`s very big number" << std::endl;
                        exit(0);
                    }*/

                    std::cout << std::endl << "find this element in AVL_tree: " << std::endl;


                    //pri(scene,head);


                    if(!head.is_contain(insert_tree_element)){
                        std::cout << "tree does not have this element" << std::endl << std::endl;
                        head.insert(insert_tree_element);
                        std::cout << "THREE AFTER ADD NEW ELEM:" << std::endl;


                        head.print_tree1(scene);
                    }
                    else
                        std::cout << "element already in tree" << std::endl << std::endl;


                       action = 0;
                       std::cout << "More action? ";

                       for( ; ; )
                       {
                       QApplication::processEvents();
                       if(!started)break;


                       }
                       started = true;




                   /*if(std::cin.fail()){
                        std::cout << "input error. May be it`s not a number or it`s very big number" << std::endl;
                        exit(0);
                    }*/
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
