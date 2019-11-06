#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->outputBtn->setChecked(true);
    ui->graphicsView->hide();
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    connectUI(ui->input, ui->output, scene);
}

void MainWindow::on_saveFile_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save to TXT file"), QDir::homePath(), tr("*.txt"));
    if (QString::compare(filePath, QString()) != 0)
    {
        saveStrToFile(ui->output->toPlainText(), filePath);
    }
}

void MainWindow::on_openFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose input file (TXT)"), QDir::homePath(), tr("*.txt"));
    if (QString::compare(fileName, QString()) != 0)
    {
        ui->input->setPlainText(getStrFromFile(fileName));
    }
}

void MainWindow::on_outputBtn_toggled(bool checked)
{
    if (checked)
    {
        ui->graphicsView->hide();
        ui->output->show();
    }
    else
    {
        ui->output->hide();
        ui->graphicsView->show();
    }
}
