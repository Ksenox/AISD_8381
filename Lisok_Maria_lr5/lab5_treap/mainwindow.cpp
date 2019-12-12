#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "headers.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fileOpen(new QPushButton),
    drawingTreap(new QPushButton),
    stepDrawingTreap(new QPushButton),
    splitTreap(new QPushButton),
    stepSwitch(new QCheckBox),
    mainGraphicsView(new QGraphicsView),
    mainGraphicsScene(new QGraphicsScene),
    inputLine(new QLineEdit),
    splitKeyInput(new QLineEdit),
    slpitError(new QLineEdit),
    inputExprLabel(new QLabel),
    splitElLabel(new QLabel)
{
    setUpUI();
}

MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::createTreap(){
    string str = inputLine->text().toUtf8().constData();
    string token{};
    slpitError->clear();
    for(ul i=0; i<str.length(); i++){
        if(isdigit(str[i])){
            token += str[i];
        }
        else if(!token.empty()){
            ul priority = rand() % RAND_FACTOR + 1;
            if(!workingTreap) {
                workingTreap = new TreapNode<ul>(static_cast<ul>(stoi(token)), priority);
            }
            else{
                workingTreap = workingTreap->add(static_cast<ul>(stoi(token)), priority);
            }
            if(!(TreapNode<ul>::forErrors.empty())){
                slpitError->setText(QString::fromStdString(TreapNode<ul>::forErrors));
                TreapNode<ul>::forErrors.clear();
                return;
            }
            token.clear();

        }
    }
    if(!token.empty()){
        ul priority = rand() % RAND_FACTOR + 1;
        workingTreap = workingTreap->add(static_cast<ul>(stoi(token)), priority);
        token.clear();
    }

}
void MainWindow::onFileOpenButtonClicked() {
    std::string inputStr;
        QString fileName = QFileDialog::getOpenFileName(this,
                tr("Open TXT File"),  QDir::homePath(),
                tr("TXT text (*.txt);;All Files (*)"));
        if (fileName == nullptr)
        {
            qDebug() << "No file name" << endl;
            return;
        }
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            inputStr.append(stream.readAll().toUtf8().constData());
        }

        if(inputStr.empty())
            return;

        file.close();

        inputLine->setText(QString::fromUtf8(inputStr.c_str()));
}

void MainWindow::onTreapDrawingButtonClicked() {
    //if(isDrawing && stepSwitch->isChecked()){
      //  TreapNode<int>::changeStepByStepMode();
        //return;
   // }
    if(workingTreap){
        qDebug() << "clear" << endl;
        TreapNode<ul>::clear(workingTreap);
        workingTreap = nullptr;
        mainGraphicsScene->clear();
    }
    if(stepSwitch->isChecked()) {
        stepDrawingTreap->setDisabled(false);
        TreapNode<ul>::changeStepByStepMode();
        isDrawing = true;
    }
    else {
        stepDrawingTreap->setDisabled(true);
        TreapNode<ul>::changeLoopState();
        TreapNode<ul>::setDisableStepMode();
    }

    createTreap();
    graphic(workingTreap, true);

}


void MainWindow::onStepTreapDrawingButtonClicked() {
    TreapNode<ul>::changeLoopState();
}

void MainWindow::onTreapSplitingButtonClicked() {
    mainGraphicsScene->clear();
    if(!workingTreap){
        createTreap();
    }
    graphic(workingTreap, true);
    TreapNode<ul>* treapLeft = new TreapNode<ul>();
    TreapNode<ul>* treapRight = new TreapNode<ul>();
    if(!splitKeyInput->text().toUtf8().constData()){
        slpitError->setText(QString::fromStdString("please input key"));
    }
    ul key = static_cast<unsigned long>(splitKeyInput->text().toLong());
    workingTreap->split(key, treapLeft, treapRight);
    if(treapLeft){
        treapLeft->setStartPos(workingTreap->getStartPos().x()+workingTreap->getWidth(), workingTreap->getStartPos().y());
        graphic(treapLeft, false);
    }if(treapRight){
        if(treapLeft)
            treapRight->setStartPos(treapLeft->getStartPos().x()+treapLeft->getWidth(), treapLeft->getStartPos().y());
        else
            treapRight->setStartPos(workingTreap->getStartPos().x()+workingTreap->getWidth(), workingTreap->getStartPos().y());
        graphic(treapRight, false);
    }

}




