#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    mainGraphicsScene(new QGraphicsScene())
{
    ui->setupUi(this);
    ui->graphicsView->setScene(mainGraphicsScene);
    this->setWindowTitle("HUFFMAN CODING☭");
    //this->setWindowFlags(Qt::CustomizeWindowHint);
    QMainWindow::showMaximized();
    QColor color(203,119,47);
    pen.setColor (color);
    brush.setColor(color);
    font.setFamily("Roboto");
    pen.setWidth(3);
    //ui->horizontalSlider->setValue(2);
    ui->graphicsView->resetTransform();
    ui->graphicsView->scale(1.5/2,1.5/2);
    ui->nextStep->hide();
    ui->previousStep->hide();
    ui->stopButton->hide();
    ui->saveButton->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::updateScene(){
    ui->graphicsView->resetTransform();
     ui->graphicsView->scale(1.5/2,1.5/2);
    Node* root = tree->getRoot();
    mainGraphicsScene->clear();
    if (!root) return;
    DrawNode(root,tree->getMaxTreeDepth(root));
}



void MainWindow::DrawNode(Node * n,int maxdepth,int depth,int x,int y){
    if (n==nullptr) return;
    int offset = pow(2,maxdepth+3)/pow(2,depth);
    if (n->left)
        mainGraphicsScene->addLine(x+32,y+32,x-offset+32,y+64+32,pen);
    if (n->right)
        mainGraphicsScene->addLine(x+32,y+32,x+offset+32,y+64+32,pen);
    QColor color_c(46,15,15);
    QBrush brush(color_c);
    QPen pen(color,3);
    if (n->isLast){
        brush.setColor(Qt::blue);
        mainGraphicsScene->addEllipse(x,y,64,64,pen,brush);
    }
    else{
        brush.setColor(color_c);
        mainGraphicsScene->addEllipse(x,y,64,64,pen,brush);
    }
    QGraphicsTextItem *numb = new QGraphicsTextItem();
    numb->setDefaultTextColor(Qt::white);
    QString textRes;
    if (QChar(n->symbol)!='\n'){
        textRes = QString::number(n->value)+':'+QChar(n->symbol);
    }
    else if (n->value==0){
        numb->setDefaultTextColor(Qt::yellow);
        textRes = "★";
    }
    else
        textRes = QString::number(n->value);
    numb->setPlainText(textRes);
    numb->setScale(2);
    numb->setPos(x+10,y+10);
    mainGraphicsScene->addItem(numb);
    DrawNode(n->left,maxdepth,depth+1,x-offset,y+64);
    DrawNode(n->right,maxdepth,depth+1,x+offset,y+64);

}

bool MainWindow::readInput(){
    QString inputString = ui->inputStr->text();
    if (inputString.size()==0){
        QMessageBox::critical(this,"ERROR!","No massage");
        return false;
    }
    if (checkRussian(inputString)){
        QMessageBox::critical(this,"ERROR!","Text contains Russian");
        return false;
    }
    int i;
    inputLen = inputString.size();
    input = new char[inputString.length()+1];
    for (i =0;i<inputString.length();i++){
        input[i] = inputString[i].toLatin1();
    }
    input[i] = '\0';
    return true;
}





void MainWindow::on_startCodingButton_clicked()
{
    ui->answer->clear();
    mainGraphicsScene->clear();
    output.clear();
    resultCode.clear();
    if (!readInput()) return;

    tree = new(BinTree);

    encode(input, output, inputLen, tree,resultCode);
    delete[] input;

    output = output +"\n"+"Result code:\n"+resultCode;
    QString answ = QString::fromStdString(output);
    ui->answer->setText(answ);
    ui->saveButton->show();
    output.clear();
    updateScene();
    Node* root = tree->getRoot();
    tree->freeMem(root);
}

void MainWindow::setMode(bool isMode){
    ui->readFileButton->setEnabled(isMode);
    ui->inputStr->setEnabled(isMode);
    currentInputLen = 0;
    output.clear();
    if (!isMode){
        ui->answer->clear();
        mainGraphicsScene->clear();
        ui->nextStep->show();
        ui->previousStep->show();
        ui->stopButton->show();
        ui->startCodingButton->hide();
        ui->stepByStepStart->hide();
    }
    else{
        ui->nextStep->hide();
        ui->previousStep->hide();
        ui->stopButton->hide();
        ui->startCodingButton->show();
        ui->stepByStepStart->show();
        delete[] input;
    }
}


void MainWindow::on_stepByStepStart_clicked()
{
    ui->saveButton->hide();
    if (!readInput()) return;
    setMode(false);
}



void MainWindow::on_nextStep_clicked()
{

    tree = new(BinTree);
    currentInputLen++;
    if (currentInputLen>inputLen){
        currentInputLen--;
        QMessageBox::about(this,"","Algorithm has reached the end");
        output = output +"\n"+"Result code:\n"+resultCode;
        QString resultAnsw = QString::fromStdString(output);
        ui->saveButton->show();
        ui->answer->setText(resultAnsw);
        setMode(true);
        return;
    }
    output = "";
    resultCode = "";
    encode(input, output, currentInputLen, tree,resultCode);

    QString answ = QString::fromStdString(output);
    ui->answer->setText(answ);

    updateScene();
    Node* root = tree->getRoot();
    tree->freeMem(root);
}






void MainWindow::on_previousStep_clicked()
{
    tree = new(BinTree);
    currentInputLen--;
    if (currentInputLen<=0){
        currentInputLen++;
        QMessageBox::about(this,"","Algorithm has reached start");
        return;
    }
    output = "";
    resultCode = "";
    encode(input, output, currentInputLen, tree,resultCode);
    QString answ = QString::fromStdString(output);
    ui->answer->setText(answ);
    updateScene();
    Node* root = tree->getRoot();
    tree->freeMem(root);
}

void MainWindow::on_stopButton_clicked()
{
    setMode(true);
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
                ui->inputStr->setText(QString::fromStdString(out));
            }
}

bool checkRussian(QString string){
    static QString russian =RUSSIAN;
    foreach(const QChar & ch, russian) {
            if(string.contains(ch)) {
                return true;
            }
        }
        return false;

}



void MainWindow::on_saveButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("save"), QDir::homePath(), tr("*.txt"));
            if (QString::compare(filePath, QString()) != 0)
            {
                std::ofstream ff(qPrintable(filePath));
                ff << qPrintable(ui->answer->toPlainText());
                ff.close();
            }
            ui->saveButton->hide();

}
