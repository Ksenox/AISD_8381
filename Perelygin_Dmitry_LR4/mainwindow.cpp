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
#include <QColorDialog>
#include <QInputDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QStringList>
#include <QTextEdit>
#include <stack>
#include <QTextBrowser>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lab.h"
bool started = true;


std::string Name;

void delete_space_symbols(std::string& expression) {
    expression.erase(std::remove_if(expression.begin(), expression.end(), &isspace), expression.end());
}



bool is_brackets_correct(std::string& expression) {

    int brackets_cnt = 0;

    for (size_t i = 0; i < expression.length(); i++) {
        if (brackets_cnt < 0)
            return false;
        else {
            if (expression[i] == '(')
                brackets_cnt++;
            else if (expression[i] == ')')
                brackets_cnt--;
            else continue;
        }
    }
    if (brackets_cnt == 0)
        return true;
    else return false;
}


void console_input(QGraphicsScene *&scene) {
    BinTree tree;

    std::cout << "Please, enter the expression" << std::endl;
    std::string expression;

    //getline(std::cin, expression);
    expression="((A+B)*C)";
    if (is_brackets_correct(expression)) {
        delete_space_symbols(expression);

        tree.replace_with_associative(expression,scene);
    }
    else std::cout << "check if the brackets are correct" << std::endl;
}

void file_input(QGraphicsScene *&scene) {

    std::ifstream file;


    file.open(Name);
    if (!file.is_open()) {
        std::cout << "Error! File isn't open" << std::endl;
        return;
    }

    size_t i = 1;

    std::string expression;

    while (!file.eof()) {

        BinTree tree;
        getline(file, expression);
        std::cout << i << ": " << expression << std::endl;
        if (is_brackets_correct(expression)) {

            delete_space_symbols(expression);

            tree.replace_with_associative(expression,scene);
            for( ; ; )
            {
            QApplication::processEvents();
            if(!started)break;


            }
            started = true;
             tree.pri(scene);
            std::cout << std::endl;
        }
        else std::cout << "check if the brackets are correct" << std::endl;
        i++;
    }

}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    //graphicsView(new QGraphicsView,
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
    ui->textBrowser->clear();
    std::string text;
  //console_input(scene);

  file_input(scene);
  std::ifstream file;
  file.open("D:\\temp.txt");
  for(int i=0;i<4;i++)
  {
  std::getline(file,text);
  if (i==2)
  ui->textBrowser->insertPlainText("\n\n\n");
  ui->textBrowser->insertPlainText(QString::fromStdString(text));
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
}
