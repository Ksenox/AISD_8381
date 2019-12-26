#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
#include <sstream>
#include <fstream>
#include <QRegExpValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    queue=nullptr;
    keys = nullptr;
    avr = 0;
    getNumRand();
    ui->input->setValidator(new QRegExpValidator(QRegExp("[0-9\\s]*"), ui->input));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAddRandUnit_triggered()
{
    int data = std::rand()%1000;
    queue->Push(&data);
}

void MainWindow::generateKeys(){
    for(int i=0; i<100; i++){
        keys->push_back(std::rand() % length);
    }
}

void MainWindow::generateValues(){
    for(int i=0; i<length; i++){
        on_actionAddRandUnit_triggered();
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->input->text().isEmpty())
        return;
    if(queue){
        queue->~MergeQueue();
    }
    if(keys){
        keys->clear();
    }
    queue = new MergeQueue<int>();
    string str = ui->input->text().toUtf8().constData();
    this->length = stoi(str);
    keys = new vector<size_t>();
    generateKeys();
    generateValues();
}

void MainWindow::findMinIter(vector<size_t>* alliterations){
    avr = 0;
    minKey = static_cast<long>(alliterations->at(0));
    maxKey = static_cast<long>(alliterations->at(0));
    for(int i=1; i<static_cast<int>(alliterations->size());i++){
        if(minKey > static_cast<int>(alliterations->at(i))){
            minKey = static_cast<int>(alliterations->at(i));
        }
        if(maxKey < static_cast<int>(alliterations->at(i))){
            maxKey = alliterations->at(i);
        }
    }
    int len=1;
    for(int i=1; i<static_cast<int>(alliterations->size());i++){
        if(minKey == static_cast<int>(alliterations->at(i)) || maxKey == static_cast<int>(alliterations->at(i))){
            continue;
        }else{
            len++;
            avr+= alliterations->at(i);
        }
    }
    avr = avr/len;
    qDebug() << "min" << minKey << "avg" << avr <<" max"<< maxKey << endl;
}

void MainWindow::on_split_clicked()
{
    std::string res1;
    std::string res2;

    if(ui->input->text().isEmpty())
        return;
    MergeQueue<int>* q1 = new MergeQueue<int>();
    MergeQueue<int>* q2 = new MergeQueue<int>();
    ImplicitTreapNode<int>::iterationsSplit = 0;
    for(int i=0; i<static_cast<long>(keys->size()); i++){
        queue->Split(q1, q2, keys->at(i), true);
        generateValues();
    }
    findMinIter(queue->alliterationsForSplit);
    qDebug() << "(" <<length<<";"<<avr<<")"<<" ";
    q1->PrintData(res1);
    q2->PrintData(res2);
    q1->~MergeQueue();
    q2->~MergeQueue();

    std::ofstream source("/Users/marialisok/Downloads/kurs_work_implicitTreap_4/source.txt");
    source << res1;
    source << endl;
    source << res2;
    source.close();
}

void MainWindow::getNumRand() {
    for(int i = 1; i < 10; i++) numsForRand.push_back(i);
}

void MainWindow::on_merge_clicked()
{
    bool check_print = false;
    if(ui->input->text().isEmpty())
        return;
    string str = ui->input->text().toUtf8().constData();
    this->length = stoi(str);
    MergeQueue<int>* q1 = new MergeQueue<int>();
    MergeQueue<int>* q2 = new MergeQueue<int>();

    std::string res1;

    vector<size_t>* alliterationsForMerge = new vector<size_t>();
    for(int i = 0; i<100; i++){
        if(!q1->getMRoot()){
            q1 = new MergeQueue<int>();
        }
        if(!q2->getMRoot()){
            q2 = new MergeQueue<int>();
        }
        for(int i=0; i<length; i++){
            int data = std::rand()%1000;
            q1->Push(&data);
        }
        for(int i=0; i<length; i++){
            int data = std::rand()%1000;
            q2->Push(&data);
        }
        q1->Merge(q2);
        if(check_print == false) {
            q1->PrintData(res1);
        }
        else {
            check_print = true;
        }
        alliterationsForMerge->push_back(q1->getMRoot()->iterationsMerge);
        q1->~MergeQueue();
    }
    findMinIter(alliterationsForMerge);
    qDebug() << "(" <<length*2<<";"<<avr<<")"<<" ";

    std::ofstream source("/Users/marialisok/Downloads/kurs_work_implicitTreap_4/source.txt");
    source << res1;
    source.close();
}
