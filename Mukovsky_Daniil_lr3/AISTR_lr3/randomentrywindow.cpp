#include "randomentrywindow.h"
#include "ui_randomentrywindow.h"

randomEntryWindow::randomEntryWindow(QWidget *parent):
    QDialog(parent),
    ui(new Ui::randomEntryWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Рандомная генерация");
    setAttribute(Qt::WA_DeleteOnClose);
}

randomEntryWindow::~randomEntryWindow()
{
    delete ui;
}
void randomEntryWindow::on_pushButton_clicked()
{
    srand(time(0));
    int n = 101;
    QString str_n = ui->number->text();
    n = str_n.toInt();
    if (n>100||n<1){
        QMessageBox::critical(this,"Ошибка","Неккоректно заданно число элементов, введите заново");
        ui->number->text().clear();
        return;
    }
    QVector <int> inputArray;
    QString stringArray;
    int sign = -1;
    for (int i;i<n;i++){
        sign = rand()%5;
        if (sign == 2){
            inputArray.push_back(-(rand()%100+1));
        }
        else{
            inputArray.push_back(rand()%100+1);
        }
        stringArray += QString::number(inputArray[i])+" ";
    }
    stringArray.remove(stringArray.size()-1,1);
    emit sendString(stringArray);
    close();
}
