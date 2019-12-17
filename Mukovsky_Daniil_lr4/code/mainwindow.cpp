#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "isincorrectsymbols.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Вывод дерева по уровням");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString inputTree_ = ui->inTree->text();
    QString inputTree = deleteSpaces(inputTree_);
    if (inputTree.isEmpty()){
        QMessageBox::critical(this,"Ошибка","Вы не задали дерево");
        return;
    }
    if (!isIncorrectSymbols(inputTree)){
        QMessageBox::critical(this,"Ошибка","Некорректная запись дерева");
        return;
    }
    if (!bracketBalance(inputTree)){
        QMessageBox::critical(this,"Ошибка","Некорректная запись дерева");
        return;
    }

    cusOuput = new customOutput();
    connect(this, SIGNAL(sendArray(QString)), cusOuput, SLOT(recieveArray(QString)));
    emit sendArray(inputTree);
    cusOuput->exec();
}

void MainWindow::on_readFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("load"), QDir::homePath(), tr("*.txt"));

        if (QString::compare(fileName, QString()) != 0)
        {
            std::ifstream f(qPrintable(fileName), std::ios::in);
            std::string out;
            getline(f, out);
            f.close();
            ui->inTree->setText(QString::fromStdString(out));
        }
}
