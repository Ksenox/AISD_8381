#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <hash.h>
#include <processing.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->inputht->setPlainText("C:/Users/Adm/Desktop/test.txt");
    //ui->sizeac->setText("1");
    ui->len->setText("5");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_create_clicked()
{
    createHashTable(ui->output, ui->inputht, ui->info);
}

void MainWindow::on_deleteItem_clicked()
{
    deleteItemFromHashTable(ui->output, ui->input, ui->info);
}


void MainWindow::on_averagecase_clicked()
{
    generateAverageCase(ui->inputht, ui->sizeac, ui->len);
}

void MainWindow::on_openfile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("load"), QDir::homePath(), tr("*.txt"));
    ui->inputht->setPlainText(fileName);
}


void MainWindow::on_savefile_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("save"), QDir::homePath(), tr("*.txt"));
        if (QString::compare(filePath, QString()) != 0)
        {
            ofstream ff(qPrintable(filePath));
            ff << qPrintable(ui->output->toPlainText());
            ff.close();
        }
}

void MainWindow::on_pushButton_clicked()
{
    insertItemToHashTable(ui->output, ui->input, ui->info);
}

void MainWindow::on_worstcase_clicked()
{
    generateWorstCase2(ui->inputht, ui->sizeac, ui->len);
}
