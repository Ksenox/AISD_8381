#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->output->setReadOnly(true); //запрет ввода в область вывода
    ui->name->setAlignment(Qt::AlignCenter); //выравнивание имени по центру
    ui->checkStep->setEnabled(false); //выбор отображения графики недоступен
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getInfo(string filePath)
{

    ifstream fin(filePath, ios::in);
    string out;
    getline(fin, out);
    ui->inputB->setText(QString::fromStdString(out));
    getline(fin, out);
    ui->inputN->setText(QString::fromStdString(out));
    fin.close();
}


void MainWindow::getOutput()
{
    ifstream fin("output.txt");
    string output;
    string temp;
    while (!fin.eof())
    {
        getline(fin, temp);
        output += temp;
        output += "\n";
    }
    fin.close();
    ui->output->setPlainText(QString::fromStdString(output));
}

void MainWindow::on_openFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose input file (TXT)"), QDir::homePath(), tr("*.txt"));
    if (QString::compare(fileName, QString()) != 0)
    {
        getInfo(qPrintable(fileName));
    }
}

void MainWindow::on_saveFile_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save to TXT file"), QDir::homePath(), tr("*.txt"));
    if (QString::compare(filePath, QString()) != 0)
    {
        ofstream fout(qPrintable(filePath));
        fout << qPrintable(ui->output->toPlainText());
        fout.close();
    }
}

void MainWindow::on_checkInfo_toggled(bool checked)
{
    if (checked)
        ui->checkStep->setEnabled(true);
    else
    {
        ui->checkStep->setChecked(false);
        ui->checkStep->setEnabled(false);
    }
}

void MainWindow::on_start_clicked()
{
    string bolts = qPrintable(ui->inputB->toPlainText());
    string nuts = qPrintable(ui->inputN->toPlainText());
    flags opt;
    opt.info = ui->checkInfo->isChecked();
    opt.step = ui->checkStep->isChecked();
    ofstream fout("output.txt");
    int num = checkStr(bolts, nuts);
    switch (num) {
    case 0:
        fout << "Error! Inputs are empty\n";
        break;
    case ERR_SYMB_B:
        fout << "Error! Bolts input contains not only digits\n";
        break;
    case ERR_SYMB_N:
        fout << "Error! Nuts input contains not only digits\n";
        break;
    case ERR_LENGTH:
        fout << "Error! Number of bolts does not match number of nuts\n";
        break;
    default:
        fout << "Inputs checked!\n\nArrays length: ";
        fout << to_string(num);
        fout << "\n\n";
        dArr boltsArr = makeArray(bolts, num);
        dArr nutsArr = makeArray(nuts, num);
        fout << "Bolts:\n";
        fout << getStrFromArray(boltsArr);
        fout << "Nuts:\n";
        fout << getStrFromArray(nutsArr);
        fout << "\n";
        if (!sortBN(boltsArr, nutsArr, opt, fout))
        {
            if (!checkPairs(boltsArr, nutsArr))
                fout << "There are unpairable bolts and nuts\n";
            else
            {
                fout << "Sorting is finished\nBolts:\n";
                fout << getStrFromArray(boltsArr);
                fout << "Nuts:\n";
                fout << getStrFromArray(nutsArr);
                fout << "Pairs of bolts and nuts:\n";
                fout << getPairs(boltsArr, nutsArr);
            }
        }
        else
        {
            fout << "Sorting was cancelled\n";
        }
    }
    fout.close();
    getOutput();
}




