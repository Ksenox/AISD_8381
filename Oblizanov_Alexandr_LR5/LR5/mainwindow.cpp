#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inout.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textOutput->setReadOnly(true);
    ui->fileInput->setReadOnly(true);
    ui->pushOk->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushOpenFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose input file (TXT)"), QDir::homePath(), tr("*.txt"));
    if (QString::compare(fileName, QString()) != 0)
    {
        ui->fileInput->setPlainText(fileName);
        QString output = ssw.createHashTable(ssw.getFromFile(ui->fileInput->toPlainText()));
        ui->textOutput->setPlainText(output);
        if (output.contains("Error"))
            ui->pushOk->setVisible(false);
        else
            ui->pushOk->setVisible(true);
    }
}

void MainWindow::on_pushOpenText_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose input file (TXT)"), QDir::homePath(), tr("*.txt"));
    if (QString::compare(fileName, QString()) != 0)
    {
        ui->textInput->setPlainText(ssw.getFromFile(fileName));
    }
}

void MainWindow::on_pushOk_clicked()
{
    if (QString::compare(ui->textInput->toPlainText(), QString()) != 0)
    {
        QString output = ssw.deleteElem(ui->textInput->toPlainText());
        ui->textOutput->setPlainText(output);
    }
}

void MainWindow::on_pushSave_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save to TXT file"), QDir::homePath(), tr("*.txt"));
    if (QString::compare(filePath, QString()) != 0)
    {
        ssw.saveStrToFile(ui->textOutput->toPlainText(), filePath);
    }
}
