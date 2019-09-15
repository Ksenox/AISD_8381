#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "components.h"
#include "textAnalyze.h"

#include <thread>
#include <qapplication>
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
void MainWindow::on_fileInput_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open TXT File"),  QDir::homePath(),
            tr("TXT text (*.txt);;All Files (*)"));
    ifstream sourceFile(fileName.toUtf8().constData());
    string input;
    sourceFile >> input;
    ui->inputLine->setText(QString::fromStdString(input));
    checkInput();
}

void MainWindow::on_consoleInput_clicked()
{
    checkInput();
}
void MainWindow::checkInput(){
    QString checkInput = ui->inputLine->text();
    string result;
    brasket(checkInput.toUtf8().constData(), result);
    ui->windowResult->setText(QString::fromStdString(result));
    ofstream resultFile("/Users/marialisok/прога/xcode/xcode/recursia/recursia/result.txt");
    resultFile << result;
    resultFile.close();
    this->resize(445, 537);
    this->resize(444, 536);
}
