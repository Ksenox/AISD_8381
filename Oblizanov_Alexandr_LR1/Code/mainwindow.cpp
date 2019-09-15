#include "mainwindow.h"
#include "ui_mainwindow.h"
#define EMPTY 5
#define NOCLOSE 4
#define NOOPEN 3
#define SIGNERR 2
#define ERR 1
#define OK 0

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

void MainWindow::on_start_clicked()
{
    string expIn = qPrintable(ui->input->text());
    unsigned long pos = 0;
    bool logs = ui->logs->isChecked();
    int funcNum = 1;
    string output;
    int result = checkString(expIn, pos, funcNum);
    if (logs)
    {
        output.append("Recursion depth: ");
        output.append(to_string(funcNum));
        output.append("\n");
        string expOut = expIn;
        expOut.erase(pos);
        output.append("Processed: ");
        output.append(expOut);
        output.append("\n");
    }
    output.append("RESULT:\n");
    switch (result)
    {
        case OK:
            output.append("Brackets\n");
        break;
        case SIGNERR:
            output.append("Wrong or extra character\nNot brackets\n");
        break;
        case NOOPEN:
            output.append("Missing opening bracket\nNot brackets\n");
        break;
        case NOCLOSE:
            output.append("Missing closing bracket\nNot brackets\n");
        break;
        case EMPTY:
            output.append("Missing brackets in  ()\nNot brackets\n");
        break;
    }
    ui->output->setText(QString::fromStdString(output));
}

int MainWindow::checkString(string &expIn, unsigned long &pos, int &funcNum)
{
    int result = checkExp(expIn, pos, funcNum);
    if (pos != expIn.length() && !result)
        return SIGNERR;
    return result;
}

int MainWindow::checkExp(string &expIn, unsigned long &pos, int &funcNum)
{
    bool isOpen = false;
    int k;
    if (expIn[pos] == 'A' || expIn[pos] == 'B')
    {
        pos++;
        return OK;
    }
    if (expIn[pos] == '(')
    {
        isOpen = true;
        pos++;
        for (int i=0; i<2; i++)
        {
            funcNum++;
            k = checkExp(expIn, pos, funcNum);
            if (k)
                return k;
        }
    }
    if (expIn[pos] == ')')
    {
        if (isOpen)
        {
            pos++;
            return OK;
        }
        else
            return EMPTY;
    }
    if (pos == expIn.length() && isOpen)
        return NOCLOSE;
    return SIGNERR;
}

string MainWindow::getInfo(string filePath)
{

    ifstream fin(filePath);
    string out;
    char buff[1010];
    fin.getline(buff, 1000);
    fin.close();
    out.append(buff);
    return out;
}

void MainWindow::on_file_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose input file (TXT)"), QDir::homePath(), tr("*.txt"));
    if (QString::compare(fileName, QString()) != 0)
    {
        string expIn = getInfo(qPrintable(fileName));
        ui->input->setText(QString::fromStdString(expIn));
    }
}

void MainWindow::on_save_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save to TXT file"), QDir::homePath(), tr("*.txt"));
    if (QString::compare(filePath, QString()) != 0)
    {
        ofstream fout(qPrintable(filePath));
        fout << qPrintable(ui->output->text());
        fout.close();
    }
}
