#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hlist.h"
#include "components.h"
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

bool explore(S_expr* list1, S_expr* list2, string & result){
    HList hlist;
    if(!list1 && !list2)
        return true;
    if(!list1 || !list2)
        return false;
    if(hlist.isAtom(list1) && hlist.isAtom(list2)){
        result.append("Found atoms.\n");

        result+=list1->getNode().element;
        result+='\t';
        result+=list2->getNode().element;
        result+='\n';
        if(list1->getNode().element == list2->getNode().element){
            result.append("Atoms are identical.\n");
            return true;
        }
        else
            result.append("Atoms are different.\n");
    }

    if(!hlist.isAtom(list1) && !hlist.isAtom(list2)){
        result.append("Found hierarchical lists.\n");
        if(!explore(list1->getNode().pair.getHead(), list2->getNode().pair.getHead(), result))
            return false;
        else
            return explore(list1->getNode().pair.getTail(), list2->getNode().pair.getTail(), result);
    }
    return false;
}

void MainWindow::on_checkButton_clicked()
{
    checkLists();
}
void MainWindow::checkLists(){
    HList hlist;
    S_expr* list1, *list2;
    QString input1 = ui->list1->text();
    QString input2 = ui->list2->text();
    string result;
    int i=0, k=0;
    if(hlist.read_s_expr(list1, input1.toUtf8().constData(), result, i)){
        ui->resultWindow->setText(QString::fromStdString(result));
    }

    else if(hlist.read_s_expr(list2, input2.toUtf8().constData(), result, k)){
        ui->resultWindow->setText(QString::fromStdString(result));
    }

    else if(explore(list1, list2, result)){
        result.append("These two lists are identical.");
        ui->resultWindow->setText(QString::fromStdString(result));
        hlist.destroy(list1, result);
        hlist.destroy(list2, result);
    }
    else{
        result.append("These two lists are different.\n");
        ui->resultWindow->setText(QString::fromStdString(result));
        hlist.destroy(list1, result);
        hlist.destroy(list2, result);
    }
    this->resize(482, 600);
    this->resize(481, 599);
}
void MainWindow::on_fileButtonForList1_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open TXT File"),  QDir::homePath(),
            tr("TXT text (*.txt);;All Files (*)"));
    ifstream sourceFile(fileName.toUtf8().constData());
    string input;
    sourceFile >> input;
    ui->list1->setText(QString::fromStdString(input));
}

void MainWindow::on_fileButtonForList2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open TXT File"),  QDir::homePath(),
            tr("TXT text (*.txt);;All Files (*)"));
    ifstream sourceFile(fileName.toUtf8().constData());
    string input;
    sourceFile >> input;
    ui->list2->setText(QString::fromStdString(input));
}

void MainWindow::on_saveToFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open TXT File"),  QDir::homePath(),
            tr("TXT text (*.txt);;All Files (*)"));
    ofstream sourceFile(fileName.toUtf8().constData());
    sourceFile << ui->resultWindow->toPlainText().toUtf8().constData();
}
