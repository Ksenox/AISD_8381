#include "mainwindow.h"
#include "ui_mainwindow.h"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Hello_clicked()
{
    string input;
    if (!ui->checkBox_2->isChecked()){
        input = qPrintable(ui->input->text());
    }
    else {
        ifstream fin; // создаем объект класса ifstream (считать)
        fin.open("D:\\prog\\cpp\\lab1\\text.txt"); // открываем файл для считывания
        fin >> input;
        fin.close(); // закрываем файл
    }
    string inputChar = qPrintable(ui->inputChar->text());
    string output = "";
    int start = 1;
    int err = 0;
    hlist *head = r_make(input, start, err);
    hlist *del_head = del_x(head, inputChar[0], output, ui->checkBox->isChecked());
    output += "\n";
    output += "\n";
    print_list(del_head, output);
    if (ui->checkBox_3->isChecked()){
        ofstream fin2; //дозаписать
        fin2.open("D:\\prog\\cpp\\lab1\\text.txt", ios::app); // открываем файл и дозыписываем в него
        fin2 << endl;
        fin2 << output;
        fin2.close(); // закрываем файл
    }
    ui->output->setText(QString::fromStdString(output));
}
