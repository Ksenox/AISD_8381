#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <hash.h>
#include <processing.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    deleteItemFromHashTable(ui->output, ui->input);
}


void MainWindow::on_averagecase_clicked()
{
    generateAverageCase(ui->inputht, ui->sizeac);
}

void MainWindow::on_openfile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("load"), QDir::homePath(), tr("*.txt"));

        if (QString::compare(fileName, QString()) != 0)
        {
            ifstream f(qPrintable(fileName), ios::in);
            string out;
            getline(f, out);
            f.close();
            ui->inputht->setPlainText(QString::fromStdString(out));
        }
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
