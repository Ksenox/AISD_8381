#include "generationwindow.h"
#include "ui_generationwindow.h"

GenerationWindow::GenerationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GenerationWindow)
{
    ui->setupUi(this);


}

GenerationWindow::~GenerationWindow()
{
    delete ui;
}

void GenerationWindow::setFilePath(QString path)
{
    ui->filePathLineEdit->setText(path);
}

void GenerationWindow::on_outputFileChoiceButton_clicked()
{
    controller->openFile();
}

void GenerationWindow::on_generateButton_clicked()
{
    controller->generate();
}

QString GenerationWindow::getFilePath()
{
    return ui->filePathLineEdit->text();
}

int GenerationWindow::getSpinNumber()
{
    return ui->spinBox->text().toInt();
}
