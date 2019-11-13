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

void isCorrect(QString str)
{
    if(str.size() == 0) throw "Пустая строка";

    for(auto i : str)
    {
        if(i != ',' && i != '(' && i != ')' && i != 'M' && i != 'm' && i != " " && i.isDigit() == false)
        {
            throw "Лишние символы в строке";
        }
    }

    int lcnt = 0;
    int rcnt = 0;

    for(auto i:str)
    {
        if(i == '(') lcnt++;
        else if(i == ')') rcnt++;
    }

    if(lcnt < rcnt)
    {
        throw "Правых скобок больше";
    }
    else if(lcnt > rcnt)
    {
        throw "Левых скобок больше";
    }
}

void MainWindow::on_calculateButton_clicked()
{
    QString inp = ui->input->text();

    try {
        isCorrect(inp);
        Function function(inp);
        int ans = 0;
        if(ui->stepByStepChecked->isChecked() == false)
        {
            ans = function.calculate();
        }
        else
        {
            ans = function.calculateStepByStep();
        }
        ui->output->setText(QString::number(ans));
    } catch (const char* exc) {

        ui->output->setText(QString(exc));
    }


}

