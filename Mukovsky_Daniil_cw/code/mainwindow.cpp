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
    this->setWindowTitle("HUFFMAN CODING/DECODING");
    this->setWindowFlags(Qt::CustomizeWindowHint);
    QMainWindow::showMaximized();
    QColor color(203,119,47);
    pen.setColor (color);
    brush.setColor(color);
    font.setFamily("Roboto");
    pen.setWidth(3);
    ui->horizontalSlider->setMinimum(1);
    ui->horizontalSlider->setValue(2);
    ui->horizontalSlider->setMaximum(5);
    ui->graphicsView->resetTransform();
    ui->graphicsView->scale(1.2/2,1.2/2);
    ui->addElement->hide();
    ui->upgradeTree->hide();
    ui->prevStep->hide();
    ui->stopButton->hide();
    ui->comboBox->addItem("Encode");
    ui->comboBox->addItem("Decode");
    ui->readBit->hide();
    ui->addElemDecode->hide();
    scrollBar =  ui->answer->verticalScrollBar();
    ui->inputStr->setText("011010000011101010001100110101100011011011100011000011000011011100100001000000000011001001110001100101110000110001110100011011111101100000110100111010100001100111");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::updateScene(){
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
    QColor colorSwap(96,63,196);
    QBrush brush(color_c);
    QPen pen(color,3);
    if (n->isLast){
        brush.setColor(Qt::blue);
        mainGraphicsScene->addEllipse(x,y,64,64,pen,brush);
    }
    else if (n->isSwapped){
        brush.setColor(colorSwap);
        mainGraphicsScene->addEllipse(x,y,64,64,pen,brush);
    }
    else if(n->isHere){
        pen.setColor(colorSwap);
        mainGraphicsScene->addEllipse(x,y,64,64,pen,brush);
    }
    else{
        pen.setColor(color);
        brush.setColor(color_c);
        mainGraphicsScene->addEllipse(x,y,64,64,pen,brush);
    }

    QGraphicsTextItem *numb = new QGraphicsTextItem();
    numb->setDefaultTextColor(Qt::white);
    numb->setPos(x+13,y+10);
    QString textRes;
    if (QChar(n->symbol)!='\n'){
        numb->setPos(x,y+10);
        textRes = QString::number(n->value)+"["+QChar(n->symbol)+"]";
    }
    else if (n->value==0){
        numb->setDefaultTextColor(Qt::yellow);
        textRes = "★";
    }
    else
        textRes = QString::number(n->value);
    numb->setPlainText(textRes);
    numb->setScale(2);
    mainGraphicsScene->addItem(numb);
    DrawNode(n->left,maxdepth,depth+1,x-offset,y+64);
    DrawNode(n->right,maxdepth,depth+1,x+offset,y+64);

}

bool MainWindow::decodeCheck(QString code){
    QRegExp reg( "^(1*0*)*$" );
    return reg.exactMatch(code);
}

QString MainWindow::deleteSpaces(QString& input){
    QString out="";
        for (auto i = 0;i < input.length();i++){
            if (input[i]!=' ' && input[i]!='\n' && input[i]!='\t' )
                out.push_back(input[i]);
        }
    return out;
}

bool MainWindow::readInput(bool isAlg){
    inputString = ui->inputStr->text();
    if (inputString.size()==0){
        QMessageBox::critical(this,"ERROR!","No massage");
        return false;
    }
    if (!isAlg){
        inputString = deleteSpaces(inputString);
        if(!decodeCheck(inputString)){
            QMessageBox::critical(this,"ERROR!","Incorrect code");
            return false;
        }
    }
    if (checkRussian(inputString)){
        QMessageBox::critical(this,"ERROR!","Text contains Russian");
        return false;
    }
    int i;
    inputLen = inputString.size();
    input = new char[inputLen+1];
    for (i =0;i<inputLen;i++){
        input[i] = inputString[i].toLatin1();
    }
    input[inputLen] = '\0';
    ui->inputStr->setText(inputString);
    return true;
}



void MainWindow::on_startCodingButton_clicked()
{
    int value = ui->comboBox->currentIndex();
    allClear();

    if(!value){
        setOrdinaryMode();
        if (!readInput(true)) return;
        tree = new(BinTree);
        encode(input, output, inputLen, tree,resultCode);
        delete[] input;
        tree->setOrdinaryNodeColor(tree->getRoot());
        updateScene();
        setLogs(output,resultCode);
        ui->saveButton->show();
        tree->freeMem(tree->getRoot());
    }
    else{
        setOrdinaryMode();
        if(!readInput(false)) return;

        tree = new(BinTree);
        if(!decode(input, output, inputLen, tree,resultCode)){
            QMessageBox::critical(this,"ERROR!","Wrong code!");
            on_stopButton_clicked();
            return;
        }
        delete[]input;
        tree->setOrdinaryNodeColor(tree->getRoot());
        updateScene();
        ui->saveButton->show();
        setLogs(output,resultCode);
        tree->freeMem(tree->getRoot());
    }
}

void MainWindow::allClear(){
    output.clear();
    resultCode.clear();
    ui->answer->clear();
    mainGraphicsScene->clear();
}

void MainWindow::setReadBitMode(){
    ui->readFileButton->setEnabled(false);
    ui->inputStr->setEnabled(false);
    ui->startCodingButton->hide();
    ui->stepByStepStart->hide();
    ui->addElement->hide();
    ui->stopButton->show();
    ui->upgradeTree->hide();
    ui->prevStep->show();
    ui->readBit->show();
    ui->addElemDecode->hide();
    ui->saveButton->hide();
}

void MainWindow::setAddElemDecodeMode(){
    ui->readFileButton->setEnabled(false);
    ui->inputStr->setEnabled(false);
    ui->startCodingButton->hide();
    ui->stepByStepStart->hide();
    ui->addElement->hide();
    ui->stopButton->show();
    ui->upgradeTree->hide();
    ui->prevStep->show();
    ui->readBit->hide();
    ui->addElemDecode->show();
    ui->saveButton->hide();
}

void MainWindow::setOrdinaryMode(){
    ui->readFileButton->setEnabled(true);
    ui->inputStr->setEnabled(true);
    currentInputLen = 0;
    ui->startCodingButton->show();
    ui->stepByStepStart->show();
    ui->addElement->hide();
    ui->readBit->hide();
    ui->stopButton->hide();
    ui->upgradeTree->hide();
    ui->prevStep->hide();
    ui->addElemDecode->hide();
    ui->saveButton->show();
}

void MainWindow::setStepEncodeMode(){
    ui->readFileButton->setEnabled(false);
    ui->inputStr->setEnabled(false);
    ui->startCodingButton->hide();
    ui->stepByStepStart->hide();
    ui->addElement->show();
    ui->stopButton->show();
    ui->upgradeTree->hide();
    ui->prevStep->show();
    ui->readBit->hide();
    ui->saveButton->hide();
}

void MainWindow::setUpgrTreeMode(){
    ui->upgradeTree->show();
    ui->addElement->hide();
    ui->readBit->hide();
    ui->addElemDecode->hide();
}


void MainWindow::on_stepByStepStart_clicked()
{
    currentInputLen = 0;
    int value = ui->comboBox->currentIndex();
    allClear();
    if(!value){
        if (!readInput(true)) return;
        setStepEncodeMode();
        tree = new(BinTree);
        updateScene();
        algorithm = coding;
    }
    else{
        algorithm = decoding;
        if (!readInput(false)) return;
        setReadBitMode();
        tree = new(BinTree);
        updateScene();
        curNode = tree->getRoot();
    }
}



void MainWindow::on_stopButton_clicked()
{
    setOrdinaryMode();
    if (tree->getRoot())
        tree->freeMem(tree->getRoot());
    delete[]input;
    while (!treeArray.isEmpty()){
        treeArray.pop_back();
    }
    while(!isPrevStep.isEmpty()){
        isPrevStep.pop_back();
    }
    while(!stepOutput.isEmpty()){
        stepOutput.pop_back();
    }
    while(!stepCode.isEmpty()){
        stepCode.pop_back();
    }
    while (!diffInputLen.isEmpty())
        diffInputLen.pop_back();
    maxTreeArrayLen = 0;
    currentInputLen = 0;
    ui->saveButton->show();
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
void MainWindow::setLogs(std::string output,std::string resultCode ){
    realOutput = output +"\nResult:\n"+resultCode+"\n";
    answ = QString::fromStdString(realOutput);
    ui->answer->setText(answ);
    scrollBar->setValue(scrollBar->maximum());
}


void MainWindow::on_saveButton_clicked()
{
    QString saveString = "Source string:\n\n"+inputString+"\n"+ui->answer->toPlainText();
    if (ui->answer->toPlainText().isEmpty()){
        QMessageBox::critical(this,"ERROR!","Nothing to save");
        return;
    }
    QString filePath = QFileDialog::getSaveFileName(this, tr("save"), QDir::homePath(), tr("*.txt"));
    if (QString::compare(filePath, QString()) != 0)
     {
        std::ofstream ff(qPrintable(filePath));
        ff << qPrintable(saveString);
        ff.close();
     }
}

void MainWindow::freeSteps(){
    BinTree* curr;
    while(maxTreeArrayLen>=5){
        curr = treeArray.last();
        curr->freeMem(curr->getRoot());
        treeArray.pop_back();
        if (!stepCode.isEmpty())
            stepCode.pop_back();
        if (!stepOutput.isEmpty())
            stepOutput.pop_back();
        if (!isPrevStep.isEmpty())
            isPrevStep.pop_back();
        if (!diffInputLen.isEmpty())
            diffInputLen.pop_back();
        maxTreeArrayLen--;
    }
}


void MainWindow::on_addElement_clicked()
{
    freeSteps();
    if (tree->needUpdateTree()){
         setUpgrTreeMode();
         return;
    }
    if (currentInputLen == inputLen){
        QMessageBox::about(this,"","Message is encoded");
        setOrdinaryMode();
        ui->saveButton->show();
        on_stopButton_clicked();
        return;
    }

    BinTree* newTree = tree->copyTree(tree);
    treeArray.push_front(newTree);
    isPrevStep.push_front(addSymb);
    stepOutput.push_front(output);
    stepCode.push_front(resultCode);

    maxTreeArrayLen++;
    char symbol = input[currentInputLen++];
    tree->getZeroNode(tree->getRoot(),zeroNode);
    addNewNode(tree,zeroNode,symbol,output,resultCode);
    setLogs(output,resultCode);
    updateScene();
    tree->setOrdinaryNodeColor(tree->getRoot());
    if (tree->needUpdateTree()){
         setUpgrTreeMode();
         return;
    }
}

void MainWindow::on_upgradeTree_clicked()
{
    freeSteps();
    if (!tree->needUpdateTree()){
        if (algorithm == coding)
            setStepEncodeMode();
        else{
            curNode = tree->getRoot();
            curNode->isHere = true;
            setReadBitMode();
        }
        return;
    }
    BinTree* newTree = tree->copyTree(tree);

    treeArray.push_front(newTree);
    isPrevStep.push_front(upgTree);
    stepOutput.push_front("");
    stepCode.push_front("");
    diffInputLen.push_front(0);
    maxTreeArrayLen++;

    tree->swapNodesForOrdering();
    updateScene();
    tree->setOrdinaryNodeColor(tree->getRoot());

    if (!tree->needUpdateTree()){
        if (algorithm == coding)
            setStepEncodeMode();
        else{
            curNode = tree->getRoot();
            curNode->isHere = true;
            setReadBitMode();
        }
        return;
    }
}


void MainWindow::on_prevStep_clicked()
{
    if(treeArray.isEmpty()){
        QMessageBox::about(this,"","Only five steps back");
        return;
    }
    BinTree* prevTree = treeArray.first();
    tree->freeMem(tree->getRoot());
    tree = prevTree;
    maxTreeArrayLen--;
    int diff = 0;
    if (!diffInputLen.isEmpty()){
        diff = diffInputLen.first();
        diffInputLen.pop_front();
    }
    int prevStep = isPrevStep.first();
    switch (prevStep) {
        case 1://addSymb
            setStepEncodeMode();
            currentInputLen--;
            output = stepOutput.first();
            resultCode = stepCode.first();
            setLogs(output,resultCode);
        break;
        case 0://upgTree
             setUpgrTreeMode();
        break;
        case 2://readBit
            setReadBitMode();
            currentInputLen-=diff;
            output = stepOutput.first();
            resultCode = stepCode.first();
            tree->getCurNode(tree->getRoot(),curNode);
            setLogs(output,resultCode);
        break;
        case 3://addEl
            setAddElemDecodeMode();
            tree->getCurNode(tree->getRoot(),curNode);
            currentInputLen-=diff;
            output = stepOutput.first();
            resultCode = stepCode.first();
            setLogs(output,resultCode);
        break;
    }
    updateScene();
    isPrevStep.pop_front();
    treeArray.pop_front();
    stepOutput.pop_front();
    stepCode.pop_front();
}

void MainWindow::on_readBit_clicked()
{
    freeSteps();
    if (currentInputLen == inputLen){
        QMessageBox::about(this,"","Message is decoded");
        setOrdinaryMode();
        on_stopButton_clicked();
        return;
    }
    if (curNode->isLeaf&&curNode->isZero&&curNode->isRoot){
        setAddElemDecodeMode();
        tree->setOrdinaryNodeColor(tree->getRoot());
        return;
    }
    if (curNode->isLeaf){
        setLogs(output,resultCode);
        setAddElemDecodeMode();
        return;
    }

    BinTree* newTree = tree->copyTree(tree);
    treeArray.push_front(newTree);
    isPrevStep.push_front(readBit);
    stepOutput.push_front(output);
    stepCode.push_front(resultCode);
    maxTreeArrayLen++;

    if(!curNode->isLeaf && currentInputLen<=inputLen){
        tree->setOrdinaryNodeColor(tree->getRoot());
        readOneBit(curNode,output,input,currentInputLen);
        diffInputLen.push_front(1);
        setLogs(output,resultCode);
        updateScene();
        if (curNode->isLeaf){
            setAddElemDecodeMode();
        }
    }
    else{
        QMessageBox::about(this,"","Incorrect code, last isn't leaf");
        on_stopButton_clicked();
    }
}

void MainWindow::on_addElemDecode_clicked()
{
    freeSteps();
    BinTree* newTree = tree->copyTree(tree);
    treeArray.push_front(newTree);
    isPrevStep.push_front(addEl);
    stepOutput.push_front(output);
    stepCode.push_front(resultCode);
    maxTreeArrayLen++;

    int diffCurentInputLen=0;
    if (!readCurNode(input,currentInputLen,inputLen,output,resultCode,curNode,tree,diffCurentInputLen)){
        QMessageBox::about(this,"","Incorrect code, need 8 bits for ASKII");
        on_stopButton_clicked();
        return;
    }
    diffInputLen.push_front(diffCurentInputLen);
    setLogs(output,resultCode);
    updateScene();
    if (currentInputLen == inputLen){
        QMessageBox::about(this,"","Message is decoded");
        setOrdinaryMode();
        on_stopButton_clicked();
        return;
    }
    if (tree->needUpdateTree()){
         setUpgrTreeMode();
         return;
    }
    setReadBitMode();
    tree->setOrdinaryNodeColor(tree->getRoot());
    curNode = tree->getRoot();
    curNode->isHere = true;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    double off = position/2.0+1;
    ui->graphicsView->resetTransform();
    ui->graphicsView->scale(1.2 / off, 1.2 / off);
}

void MainWindow::on_actionAbout_algorithm_triggered()
{
    infoForm1 = new InfoAboutAlgorithm();
    infoForm1->show();
}

void MainWindow::on_actionInstruction_triggered()
{
    infoForm2 = new Instruction();
    infoForm2->show();
}
