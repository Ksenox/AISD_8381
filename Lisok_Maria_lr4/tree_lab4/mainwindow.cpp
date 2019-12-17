#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawing.h"

static Stack<char> workStack;
static vector<string> steps;
static string str;
static string errors;
static int i = 1;

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->resultWindow->setReadOnly(true);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    ui->stepDraw->setDisabled(true);
    // запрещаем вводить что-то кроме одной буквы в диапазоне [a-z]
    ui->variableInput->setValidator(new QRegExpValidator(QRegExp("[a-z]"), ui->variableInput));
    // оставляем для вводной строки только допустимые символы
    ui->inputLine->setValidator(new QRegExpValidator(QRegExp("[a-z0-9+\\-*()]*"), ui->inputLine));
}

MainWindow::~MainWindow() {
    delete ui;
}

struct Node* createTree(string & checkInput, string & err) {
    string postfixForm;
    infixToPrefix(checkInput, postfixForm, err);
    if(!err.empty()){
        return nullptr;
    }
    return constructTree(postfixForm);
}

void MainWindow::on_resultButton_clicked()
{
    string result="result:", err;
    string str = ui->inputLine->text().toUtf8().constData();

    // проверка на отсутсвие двухначных чисел и двух знаков подряд
    regex reg(".*[1-9]{2}.*");
    regex reg2(".*[-+*]{2}.*");
    regex reg3(".*[+\\-\\*][)+\\-\\*]+");
    if(regex_search(str, reg) || regex_search(str, reg2)||regex_search(str, reg3)) {
        err = "Please input correct expression!!!\n";
        ui->resultWindow->setText(QString::fromStdString(err));
        this->resize(1081, 720);
        this->resize(1080, 720);
        return;
    }

    struct Node* tree = createTree(str, err);
    if(!errors.empty()){
        ui->resultWindow->setText(QString::fromStdString(errors));
        this->resize(1081, 720);
        this->resize(1080, 720);
        return;
    }
    int k = eval(tree, err);
    if(!err.empty()){
        ui->resultWindow->setText(QString::fromStdString(err));
        this->resize(1081, 720);
        this->resize(1080, 720);
        return;
    }
    result+=to_string(k);
    ui->resultWindow->setText(QString::fromStdString(result));
    this->resize(1081, 720);
    this->resize(1080, 720);

}

void MainWindow::on_stepButton_clicked() {
    if(str.compare(ui->inputLine->text().toUtf8().constData())!=0){
          str.clear();
          str.append(ui->inputLine->text().toUtf8().constData());

          string err;
          // проверка на отсутсвие двухначных чисел и двух знаков подряд
          regex reg(".*[1-9]{2}.*");
          regex reg2(".*[-+*]{2}.*");
          regex reg3(".*[+\\-\\*][)+\\-\\*]+");
          if(regex_search(str, reg) || regex_search(str, reg2)||regex_search(str, reg3)) {
              err = "Please input correct expression!!!\n";
              ui->resultWindow->setText(QString::fromStdString(err));
              this->resize(1081, 720);
              this->resize(1080, 720);
              return;
          }

          string str1 = ui->inputLine->text().toUtf8().constData();
          i = 1;
          steps.clear();
          workStack.clear();
          errors.clear();
          ui->resultWindow->clear();
          struct Node* root = createTree(str1, errors);
          if(!errors.empty()){
              ui->resultWindow->setText(QString::fromStdString(errors));
              this->resize(1081, 720);
              this->resize(1080, 720);
              return;
          }
          postorder(root, workStack, steps, errors);
    }
    if(!errors.empty()){
        ui->resultWindow->setText(QString::fromStdString(errors));
        this->resize(1081, 720);
        this->resize(1080, 720);
        return;
    }
    string buf="";
    for(unsigned long j = 0; j < static_cast<unsigned long>(i) && j < steps.size(); j++){
        buf += steps[j] + "\n";
    }
    ui->resultWindow->setText(QString::fromStdString(buf));
    i++;
    this->resize(1081, 720);
    this->resize(1080, 720);
}

void MainWindow::on_deriativeButton_clicked()
{
    string str = ui->inputLine->text().toUtf8().constData(), err;
    if(ui->variableInput->text().size() == 0){
        string err = "Please input variable!!!\n";
        ui->resultWindow->setText(QString::fromStdString(err));
        this->resize(1081, 720);
        this->resize(1080, 720);
        return;
    }

    // проверка на отсутсвие двухначных чисел и двух знаков подряд
    regex reg(".*[1-9]{2}.*");
    regex reg2(".*[-+*]{2}.*");
    regex reg3(".*[+\\-\\*][)+\\-\\*]+");
    if(regex_search(str, reg) || regex_search(str, reg2)||regex_search(str, reg3)) {
        err = "Please input correct expression!!!\n";
        ui->resultWindow->setText(QString::fromStdString(err));
        this->resize(1081, 720);
        this->resize(1080, 720);
        return;
    }

    struct Node* tree = createTree(str, err);
    if(!err.empty()){
        ui->resultWindow->setText(QString::fromStdString(err));
        this->resize(1081, 720);
        this->resize(1080, 720);
        return;
    }
    char k = ui->variableInput->text().toUtf8().constData()[0];
    string result = Diff(tree, k);
    ui->resultWindow->setText(QString::fromStdString(result));
    this->resize(1081, 720);
    this->resize(1080, 720);
}

void MainWindow::on_fileOutput_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open TXT File"),  QDir::homePath(),
            tr("TXT text (*.txt);;All Files (*)"));
    ofstream sourceFile(fileName.toUtf8().constData());
    sourceFile << ui->resultWindow->toPlainText().toUtf8().constData();
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
}

void MainWindow::on_stepDraw_clicked()
{
    changeLoopState();
}

void MainWindow::on_drawButton_clicked()
{
    if(ui->checkBox->isChecked()) {
        ui->stepDraw->setDisabled(false);
        changeStepByStepMode();
    }
    else {
        ui->stepDraw->setDisabled(true);
        changeLoopState();
        setDisableStepMode();
    }
    string str = ui->inputLine->text().toUtf8().constData(), err;
    regex reg(".*[1-9]{2}.*");
    regex reg2(".*[-+*]{2}.*");
    regex reg3(".*[+\\-\\*][)+\\-\\*]+");
    if(regex_search(str, reg) || regex_search(str, reg2)||regex_search(str, reg3)) {
        err = "Please input correct expression!!!\n";
        ui->resultWindow->setText(QString::fromStdString(err));
        this->resize(1081, 720);
        this->resize(1080, 720);
        return;
    }
    if(str.empty()){
        ui->resultWindow->setText(QString::fromStdString("Input expression"));
        this->resize(1081, 720);
        this->resize(1080, 720);
        return;
    }
    struct Node* tree = createTree(str, err);
    if(!err.empty()){
        ui->resultWindow->setText(QString::fromStdString(err));
        this->resize(1081, 720);
        this->resize(1080, 720);
        return;
    }
    ui->resultWindow->setText(QString::fromStdString(""));
    this->resize(1081, 720);
    this->resize(1080, 720);
    graphic(tree, scene);
}
