#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    list = array_list();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Generate_clicked()
{
    list.clean();
    for (int i = 0; i < 40; i++)
    {
        list.push_back(rand() % 90 + 10);
    }
    visualize();
}

void MainWindow::on_Input_clicked()
{
    QString input = ui->InputEdit->text();
    if (input.isEmpty()) return;
    list.clean();
    for (QString i : ui->InputEdit->text().split(' '))
    {
        bool ok;
        int a = i.toInt(&ok);
        if (!ok)
        {
            QMessageBox::warning(this, "Warning", "Input is not number");
            ui->InputEdit->setText("");
            return;
        }
        list.push_back(a);
    }
    visualize();
}

void MainWindow::on_Sort_clicked()
{
    string res;
    qsort3way(res, list, 0, list.size() - 1);
    ui->Log->setText(QString::fromStdString(res));
    visualize();
}

void MainWindow::visualize()
{
    QString s = "";
    for (int i = 0; i < list.size(); i++)
    {
        s += QString::number(list[i]) + ' ';
    }
    ui->CurrentArray->setText(s);
}
