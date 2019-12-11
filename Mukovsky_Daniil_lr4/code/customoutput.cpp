#include "customoutput.h"
#include "ui_customoutput.h"
#include "stepbystep.h"
customOutput::customOutput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::customOutput)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    this->setWindowTitle("Вывод дерева по уровням");
    ui->comboBox->addItem("Сразу результат");
    ui->comboBox->addItem("Пошагово");
    BT = new(BinaryTree);
    ui->nextStep->hide();
    ui->saveButton->hide();
}

customOutput::~customOutput()
{
    delete ui;
}
void customOutput::recieveArray(QString inputTree){
    ui->input->setText(inputTree);
    inputTreeString = inputTree;
}


void customOutput::on_pushButton_clicked()

{
    lev = 0;
    scene->clear();
    out.clear();
    ui->answer->clear();
    int numb = 1;


    BT->root = BT->createTree(splitForTree(inputTreeString),numb);



    flagStep = false;
    queque = new NodeQueue(numb);

    Node* currentNode = BT->root;
    queque->addItem(currentNode);
    BT->root->level =1;
    depth = BT->getDepth(BT->root);

    int value = ui->comboBox->currentIndex();
    if (!value){
        stepByStepAlg(lev,out,queque,flagStep);
        ui->answer->setText(out);
        graphicConfig(BT, scene,depth);
        ui->saveButton->show();
    }
    else{
        flagStep =true;
        ui->pushButton->hide();
        ui->comboBox->hide();
        ui->nextStep->show();
    }
}

void customOutput::on_nextStep_clicked()
{
    if (stepByStepAlg(lev,out,queque,flagStep)){
        ui->answer->setText(out);
        graphicConfig(BT,scene,depth);
        ui->nextStep->hide();
         ui->pushButton->show();
         ui->comboBox->show();
         ui->saveButton->show();
        return;
    }
    ui->answer->setText(out);
    graphicConfig(BT, scene,depth);
}

void customOutput::on_saveButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("save"), QDir::homePath(), tr("*.txt"));
        if (QString::compare(filePath, QString()) != 0)
        {
            std::ofstream ff(qPrintable(filePath));
            ff << qPrintable(out);
            ff.close();
        }
        ui->saveButton->hide();
        close();
}
