#include "mainwindow.h"
#include "ui_mainwindow.h"
static Stack< int> stack{};
static int i = 0;
static string answer{};
static string inputTest{};
static string err{};
static string postfixForm;
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


void MainWindow::on_result_clicked()
{
    string result, postfixForm, error;
    string str = ui->input->text().toUtf8().constData();
    toPostfixForm(str, postfixForm, error);
    if(!error.empty()){
        ui->output->setText(QString::fromStdString(error));
        return;
    }
    int ans = calc(postfixForm, result, err);
    string str1 = "Результат вычислений: ";
    if(!err.empty())
        str1 += err;
    else
        str1 += to_string(ans);
    ui->output->setText(QString::fromStdString(str1));

}

void MainWindow::on_step_clicked()
{
    string str = ui->input->text().toUtf8().constData(), error;
    if(inputTest.compare(str)!=0){
        i=0;
        answer.clear();
        err.clear();
        inputTest.clear();
        inputTest.append(str);
        toPostfixForm(str, postfixForm, error);
        if(!error.empty()){
            ui->output->setText(QString::fromStdString(error));
            return;
        }
        ui->output->clear();
        stack.clear();
        stack.setSize(postfixForm.length());
    }
    if(!err.empty()){
        return;
    }
    if(i>=postfixForm.length() && stack.length()==1){
        i=0;
        stack.pop();
        answer.clear();
        err.clear();
    }
    onestep(postfixForm[i], stack, answer, err);
    i++;
    if(answer.empty()){
        ui->output->setText(QString::fromStdString(err));
    }
    else if(err.empty()){
        ui->output->setText(QString::fromStdString(answer));
    }
    else{
        ui->output->setText(QString::fromStdString(answer)+QString::fromStdString(err));
    }
}

void MainWindow::on_dataFromFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open TXT File"),  QDir::homePath(),
            tr("TXT text (*.txt);;All Files (*)"));
    ifstream sourceFile(fileName.toUtf8().constData());
    string input;
    sourceFile >> input;
    ui->input->setText(QString::fromStdString(input));
}

void MainWindow::on_saveOutput_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open TXT File"),  QDir::homePath(),
            tr("TXT text (*.txt);;All Files (*)"));
    ofstream sourceFile(fileName.toUtf8().constData());
    sourceFile << ui->output->toPlainText().toUtf8().constData();
}
