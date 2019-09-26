#include "mainwindow.h"
#include "hielist.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->output->setWordWrap(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    string expIn = qPrintable(ui->input->text());
    bool logs = ui->logs->isChecked();
    string output;
    string temp;
    int err;
    unsigned long long ptr = 1;
    HieList *list = new HieList;
    createHieList(list);
    if (logs)
        output += "Creating hierarchical list...\n";
    list->head = createHieFromStr(expIn, ptr, err);
    switch (err) {
    case NO_CLOSE:
        output += "\nERROR:\nMissing closing bracket\n";
        break;
    case BAD_CHILD:
        output += "\nERROR:\nOne of the lists (child) is empty\n";
        break;
    case BAD_PARENT:
        output += "\nERROR:\nOne of the lists (parent) do not have operator\n";
        break;
    }
    if (err && logs)
    {
        output += "\nProcessed input:\n";
        output += expIn.substr(0, ptr);
        output += "\nCreated list:\n";
        output += getList(list->head);
    }
    else
    {
        if (logs)
        {
            output += "Successfully completed\n Created list:\n";
            output += getList(list->head);
            output += "\n\nChecking prefix expression...\n";
        }
        checkPrefix(list->head, err);
        if (ptr != expIn.length() && !err)
            err = EXTRA_SYMB;
        switch (err) {
        case EXTRA_SYMB:
            output += "\nERROR:\nExtra symbols after expression\n";
            break;
        case EMPTY:
            output += "\nERROR:\nThere is an empty list in expression\n";
            break;
        case NO_OPERATOR:
            output += "\nERROR:\nNo operator in one of the lists\n";
            break;
        case NO_OPERAND:
            output += "\nERROR:\nNo operands in one of the lists\n";
            break;
        case BAD_OPERAND:
            output += "\nERROR: \nOperands should be digits or letters\n";
            break;
        case BAD_EQUIVALENT:
            output += "\nERROR:\nEquivalent operator should have strictly two operands\n";
            break;
        case 0:
            if (logs)
                output += "Successfully completed\n";
            output += "\nEXPRESSION IS CORRECT\n";
        }
    }
    ui->output->setText(QString::fromStdString(output));
    deleteList(list->head);
    delete list;
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
