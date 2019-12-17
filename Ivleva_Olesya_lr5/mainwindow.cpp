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
    string str;
    string input;
    //if (!ui->checkBox_2->isChecked()){
    open(str);
    input = qPrintable(ui->input->text());
    string output = "";
    int s = 10000;
    Hash *ri = new Hash[s];
    do_hash_str(ri, str);
    find_el(input, ri, output);
    print_hash(ri, output);
    ui->output->setText(QString::fromStdString(output));
}

