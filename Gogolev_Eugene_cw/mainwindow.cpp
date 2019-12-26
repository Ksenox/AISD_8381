#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(nullptr));
    type = coding;
    method = haffman;
    variant_count = 1;
    length = 5;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_type_currentIndexChanged(int index)
{
    type = (types)index;
}

void MainWindow::on_method_currentIndexChanged(int index)
{
    method = (methods)index;
}

void MainWindow::on_generate_clicked()
{
    string issue;
    string answer;
    generate_var(type, method, length, issue, answer);
    ui->issue->setText(QString::fromStdString(issue));
    ui->answer->setText(QString::fromStdString(answer));
}

void MainWindow::on_variants_valueChanged(int arg1)
{
    variant_count = arg1;
}

void MainWindow::on_length_valueChanged(int arg1)
{
    length = arg1;
}

void MainWindow::on_file_clicked()
{
    string issue = "";
    string answer = "";
    generate_pack(type, method, length, variant_count, issue, answer);
    write_to_file("issue.txt", issue);
    write_to_file("answer.txt", answer);
}


void MainWindow::on_hand_textChanged(const QString &arg1)
{

}

void MainWindow::on_lr5_clicked()
{

}
