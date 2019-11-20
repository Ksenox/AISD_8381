#include "quickmergesort.h"
#include "ui_quickmergesort.h"
#include <QFile>
#include <QMessageBox>
#define MAX_SIZE 100
#define MAX_GROUP_SIZE 100

QuickMergeSort::QuickMergeSort(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuickMergeSort)
{
    ui->setupUi(this);
    this->setWindowTitle("Сортировка естественным слиянием");
    ui->comboBox->addItem("Сразу результат");
    ui->comboBox->addItem("Пошагово");
    ui->pushButton->hide();
    ui->save->hide();
    ui->lineSave->hide();
    ui->labelSave->hide();
    setAttribute(Qt::WA_DeleteOnClose);
}

QuickMergeSort::~QuickMergeSort()
{
    delete ui;
    delete []inputArray;
}


void QuickMergeSort::freeFirstSecond(int** firstPart,int** secondPart) {
    for (int i = 0; i < MAX_GROUP_SIZE; i++) {
        delete[] firstPart[i];
        delete[] secondPart[i];
    }
    delete[] firstPart;
    delete[] secondPart;
}


void QuickMergeSort::Merging(int* inputArray, unsigned int size, int** firstPart, int** secondPart) {
    unsigned int firstLen = firstPart[0][0];
    unsigned int secondLen = secondPart[0][0];
    unsigned int len = 0;
    unsigned int fir = 1, sec = 1;
    bool flag = false;
    if (firstLen > secondLen) {
        len = secondLen;
        flag = true;
    }
    else len = firstLen;

    unsigned int i = 0,j=0,k=0,p=0;
    for (i = 1; i < len; i++) {
        for (j = p; j < (firstPart[i][0] + secondPart[i][0]-2)+p; j++) {
            if (fir != firstPart[i][0] && sec != secondPart[i][0] && firstPart[i][fir] <= secondPart[i][sec]) {
                inputArray[j] = firstPart[i][fir++];
                continue;
            }
            if (fir != firstPart[i][0] && sec != secondPart[i][0] && firstPart[i][fir] >= secondPart[i][sec]) {
                inputArray[j] = secondPart[i][sec++];
                continue;
            }
            if (fir == firstPart[i][0] && sec != secondPart[i][0]) {
                inputArray[j] = secondPart[i][sec++];
                continue;
            }
            if (fir != firstPart[i][0] && sec == secondPart[i][0]) {
                inputArray[j] = firstPart[i][fir++];
                continue;
            }
        }
        p = j;
        sec = 1;
        fir = 1;
    }
    fir = 1;
    if (flag)
        for (i = j; i < firstPart[len][0]; i++)
            inputArray[i++] = firstPart[len][fir++];
}


void QuickMergeSort::splitIntoTwo(int* inputArray, int** firstPart, int** secondPart, unsigned int size) {
    unsigned int i = 0;
    unsigned int fir = 1;
    unsigned int sec = 1;
    unsigned int fir_arr = 1;
    unsigned int sec_arr = 1;
    bool flag = true;
    while (i < size) {
        if (i == 0 || (inputArray[i - 1] <= inputArray[i] && flag)) {
            firstPart[fir_arr][fir++] = inputArray[i++];
        }
        else if (inputArray[i - 1] >= inputArray[i]) {
            if (flag) {
                secondPart[sec_arr][sec++] = inputArray[i++];
                firstPart[fir_arr++][0] = fir;
                fir = 1;
                flag = false;
            }
            else {
                firstPart[fir_arr][fir++] = inputArray[i++];
                secondPart[sec_arr++][0] = sec;
                sec = 1;
                flag = true;
            }
        }
        else if (inputArray[i - 1] <= inputArray[i] && !flag) {
            secondPart[sec_arr][sec++] = inputArray[i++];
        }
    }
    flag == true ? firstPart[fir_arr][0] = fir : secondPart[sec_arr][0] = sec;
    flag == true ? fir_arr++ : sec_arr++;
    firstPart[0][0] = fir_arr;
    secondPart[0][0] = sec_arr;
}


bool QuickMergeSort::NaturalMergingSort(int* inputArray,unsigned int size, QString& result, bool flagStep,int step) {
    unsigned int i = 0;
    //int step =1;
    for (;;) {
        int** firstPart = new int* [MAX_GROUP_SIZE];
        int** secondPart = new int* [MAX_GROUP_SIZE];
        for (i = 0; i < MAX_GROUP_SIZE; i++) {
            firstPart[i] = new int[MAX_SIZE];
            secondPart[i] = new int[MAX_SIZE];
        }
        firstPart[0][0] = 0;
        secondPart[0][0] = 0;
        splitIntoTwo(inputArray, firstPart, secondPart, size);
        if (secondPart[0][0] == 1) {
            freeFirstSecond(firstPart,secondPart);
            return true;
        }
        result+= "Step "+QString::number(step++)+"\nfirst: ";

        for (int i = 1; i < firstPart[0][0]; i++) {
            for (int j = 1; j < firstPart[i][0]; j++) {
                result+=QString::number(firstPart[i][j])+' ';
            }
            result+="| ";
        }
        result.remove(result.size()-2,result.size()-1);
        result+="\nsecond: ";
        for (int i = 1; i < secondPart[0][0]; i++) {
            for (int j = 1; j < secondPart[i][0]; j++) {
                result+=QString::number(secondPart[i][j])+' ';
            }
            result+="| ";
        }
        result.remove(result.size()-2,result.size()-1);
        Merging(inputArray, size, firstPart, secondPart);
        result+="\nAfter merging: ";
        for (unsigned int k = 0; k < size; k++) {
            result+=QString::number(inputArray[k])+' ';
        }
        result+="\n\n";
        freeFirstSecond(firstPart, secondPart);
        if (flagStep) return false;
    }
}
void QuickMergeSort::recieveArray(QString inputArray_){
    ui->input->setText(inputArray_);
    inputArrayString = inputArray_;
}

void QuickMergeSort::on_buttonQMergeSort_clicked(){
    ui->resultText->clear();
    ui->save->hide();
    ui->lineSave->hide();
    ui->labelSave->hide();
    result.clear();
    step =1;
    lst = inputArrayString.split(" ");
    size = lst.size();
    inputArray = new int[size];
    unsigned int i =0;
    for (unsigned int i=0;i<size;i++){
        inputArray[i] = lst[i].toInt();
    }
    int value = ui->comboBox->currentIndex();
    if (!value){
            NaturalMergingSort(inputArray,size,result,false,step);
            result+= "\nRESULT: ";
            for(i=0;i<size;i++){
                result+=QString::number(inputArray[i])+' ';
            }
            ui->resultText->setText(result);
            ui->lineSave->show();
            ui->labelSave->show();
            ui->save->show();
       }
    else {
        ui->comboBox->hide();
        ui->buttonQMergeSort->hide();
        ui->pushButton->show();
    }
}

void QuickMergeSort::on_pushButton_clicked()
{
    bool flagStep = true;
    if (NaturalMergingSort(inputArray,size,result,flagStep,step)){
        result+= "\nRESULT: ";
        for(unsigned int i=0;i<size;i++){
            result+=QString::number(inputArray[i])+' ';
        }
        ui->resultText->setText(result);
        ui->comboBox->show();
        ui->buttonQMergeSort->show();
        ui->pushButton->hide();
        ui->save->show();
        ui->lineSave->show();
        ui->labelSave->show();
    }
    else{
        step++;
        ui->resultText->setText(result);
    }
}

bool QuickMergeSort::check_path(QString path){
    QRegExp reg("^((C|D):\\\\([a-zA-Z]+\\\\)+[a-zA-Z0-9_]+.txt)|[a-zA-z0-9_]+.txt$");
    return reg.exactMatch(path);
}


void QuickMergeSort::on_save_clicked()
{
    if(ui->lineSave->text().isEmpty()){
        QFile out("C:\\Users\\miair\\Desktop\\output.txt");
        if (out.open(QIODevice::WriteOnly)){
            out.write(result.toUtf8());
        }
        out.close();
        close();
    }
    else {
        QFile realOut(ui->lineSave->text());

        if (realOut.open(QIODevice::WriteOnly)&& check_path(ui->lineSave->text())){
            realOut.write(result.toUtf8());
            realOut.close();
            close();
        }
        else {
            QMessageBox::critical(this,"Ошибка","Путь к файлу указан неверно");
            ui->lineSave->clear();
        }
    }
}
