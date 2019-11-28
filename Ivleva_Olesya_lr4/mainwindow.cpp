#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "printtree.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->output->setWordWrap(true);
    QPixmap bkgnd("D:\\prog\\Styles\\plant-2004483_640.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    //ui->graphicsView->hide();
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Hello_clicked()
{
    string str;
    string symbol;
    if (!ui->checkBox_2->isChecked()){
        str = qPrintable(ui->input->text());
    }
    else {
        ifstream fin; // создаем объект класса ifstream (считать)
        fin.open("D:\\prog\\cpp\\lab1\\text.txt"); // открываем файл для считывания
        fin >> str;
        fin.close(); // закрываем файл
    }
    tree *symb = new tree;
    if (ui->checkBox->isChecked()){
        symbol = qPrintable(ui->input_char->text());
        derivative(str, symbol);
    }
    symb = maketree(str, 0, nullptr);
    graphic(symb, scene);
    string output = "";
    printTree(symb, output);
    if (ui->checkBox_5->isChecked()){
        calc(symb);
        output += "\n";
        output += "Var = ";
        output += to_string(symb->var);
    }
    if (ui->checkBox_3->isChecked()){
        ofstream fin2; //дозаписать
        fin2.open("D:\\prog\\cpp\\lab1\\text.txt", ios::app); // открываем файл и дозыписываем в него
        fin2 << endl;
        fin2 << output;
        fin2.close(); // закрываем файл
    }
    ui->output->setText(QString::fromStdString(output));
    //graphic(symb, scene);
}
