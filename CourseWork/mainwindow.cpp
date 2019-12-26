#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAnswer(QString answer)
{
    ui->outputLineEdit->setText(answer);
}

void MainWindow::setInputFromFile(QString input)
{
    ui->inputLineEdit->setText(input);
}

void MainWindow::on_calculatePushButton_clicked()
{
    QString inputString = ui->inputLineEdit->text();

    controller->calculate(inputString);
}

void MainWindow::displayResults(QGraphicsScene* scene)
{
    ui->outputGraphicsView->setScene(scene);
}

void MainWindow::on_downloadFromFileAction_triggered()
{
    controller->openFile();
}

void MainWindow::on_helpAction_triggered()
{
    QMessageBox::information(0, "Помощь", "Вас приветствует программа для работы с рандомизированными пирамидами поиска и генерации текущего контроля!\nВ строку ввода введите записи вида (a;b), где а - значение вершины, b - её приоритет. Сами такие записи можно разделять запятой.\nПо Вашим введённым данным будет сгенерирована рандомизированная пирамида поиска и выведены её элементы в порядке возрастания в соответствующее поле вывода.\n                       Приятного использования!");
}

void MainWindow::on_authorInformationAction_triggered()
{
    QMessageBox::information(0, "Автор программы", "Программа разработана студентом 2-го курса СПбГЭТУ \"ЛЭТИ\" группы 8381 Сосновским Д.Н. \nПреподаватель Жангиров Т.Р.");
}

void MainWindow::on_generationWindowAction_triggered()
{
    controller->startView();
}
