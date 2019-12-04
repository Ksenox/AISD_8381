#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    beginning(ui->input, ui->output, scene);
}

void MainWindow::on_openFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("load"), QDir::homePath(), tr("*.txt"));

    if (QString::compare(fileName, QString()) != 0)
    {
        ifstream f(qPrintable(fileName), ios::in);
        string out;
        getline(f, out);
        f.close();
        ui->input->setPlainText(QString::fromStdString(out));
    }
}

void MainWindow::on_saveFile_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("save"), QDir::homePath(), tr("*.txt"));
    if (QString::compare(filePath, QString()) != 0)
    {
        ofstream ff(qPrintable(filePath));
        ff << qPrintable(ui->output->toPlainText());
        ff.close();
    }
}
