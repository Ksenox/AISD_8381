#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->output->setWordWrap(true);
    QPixmap bkgnd("D:\\prog\\Styles\\plant-2004483_640.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    open(str);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Push_File_clicked()
{
    string output = "";
    str += qPrintable(ui->input->text());
    make_str(Hash_, str, output, 0);
    Hash_.print_hash(output);
    ui->output->setText(QString::fromStdString(output));
    str = "";
    graphic(Hash_, scene);
}


void MainWindow::on_nextStep_clicked()
{
    ui->prevStep->setEnabled(true);
    open(str_step);
    string output = "";
    str_step += qPrintable(ui->input->text());
    if (ind_st == str_step.length()){
        Hash_st.print_hash(output);
        output += "Finish!";
        ui->output->setText(QString::fromStdString(output));
        ui->nextStep->setEnabled(false);
        return;
    }
    make_str_step(Hash_st, str_step, output, ind_st, 0);
    Hash_st.print_hash(output);
    ui->output->setText(QString::fromStdString(output));
    graphic(Hash_st, scene);
}

void MainWindow::on_prevStep_clicked()
{
    ui->nextStep->setEnabled(true);
    open(str_step);
    string output = "";
    str_step += qPrintable(ui->input->text());
    if (ind_st == 0){
        Hash_st.print_hash(output);
        output += "No elements!";
        ui->output->setText(QString::fromStdString(output));
        ui->prevStep->setEnabled(false);
        return;
    }
    make_str_del(Hash_st, str_step, output, ind_st, 0);
    Hash_st.print_hash(output);
    ui->output->setText(QString::fromStdString(output));
    graphic(Hash_st, scene);
}

void MainWindow::on_del_elem_clicked()
{
    string output = "";
    str_del += qPrintable(ui->input->text());
    make_str(Hash_, str_del, output, 1);
    Hash_.print_hash(output);
    ui->output->setText(QString::fromStdString(output));
    graphic(Hash_, scene);
    str_del = "";
}

void MainWindow::on_prev_del_clicked()
{
    ui->next_del->setEnabled(true);
    string output = "";
    str_del_step += qPrintable(ui->input->text());
    if (ind_st == 0){
        Hash_.print_hash(output);
        output += "No elements!";
        ui->output->setText(QString::fromStdString(output));
        ui->prev_del->setEnabled(false);
        return;
    }
    make_str_del(Hash_, str_del_step, output, ind_st, 1);
    Hash_.print_hash(output);
    ui->output->setText(QString::fromStdString(output));
    graphic(Hash_, scene);
    str_del_step = "";
}

void MainWindow::on_next_del_clicked()
{
    ui->prev_del->setEnabled(true);
    string output = "";
    str_del_step += qPrintable(ui->input->text());
    if (ind_st == str_del_step.length()){
        Hash_.print_hash(output);
        output += "Finish!";
        ui->output->setText(QString::fromStdString(output));
        ui->next_del->setEnabled(false);
        return;
    }
    make_str_step(Hash_, str_del_step, output, ind_st, 1);
    Hash_.print_hash(output);
    ui->output->setText(QString::fromStdString(output));
    graphic(Hash_, scene);
    str_del_step = "";
}

void MainWindow::on_del_all_clicked()
{
    ind_st = 0;
    str = "";
    open(str);
    string output = "";
    Hash_.delete_all();
    Hash_st.delete_all();
    Hash_.print_hash(output);
    ui->output->setText(QString::fromStdString(output));
    graphic(Hash_, scene);
}
