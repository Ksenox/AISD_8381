#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //resize(360,332);
    ui->setupUi(this);
    this->setWindowTitle("Code and Decode Huffman");
    //ui->groupBox_3->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButton_4_clicked()
{
    flagEncode = true;
    flagDecode = false;
}

void MainWindow::on_radioButton_5_clicked()
{
    flagDecode = true;
    flagEncode = false;
}

void MainWindow::on_radioButton_clicked()
{
    flagEasy = true;
    flagNormal = false;
    flagHard = false;
}

void MainWindow::on_radioButton_2_clicked()
{
    flagNormal = true;
    flagHard = false;
    flagEasy = false;
}

void MainWindow::on_radioButton_3_clicked()
{
    flagHard = true;
    flagNormal = false;
    flagEasy = false;
}

void MainWindow::on_pushButton_clicked()
{
    if(flagDecode == false && flagEncode == false){
        QMessageBox::critical(this,"ERROR","Please select a method");
        return;
    }
    if(flagEasy == false && flagNormal == false && flagHard == false){
        QMessageBox::critical(this,"ERROR","Please select a level");
        return;
    }
    resize(360,640);
    int flag;
    int temp;
    if(flagEncode){
        flag = 1;

        if(flagEasy){
            temp = 11;
            input = cuaso.take_string(&temp);
        }
        else if (flagNormal){
            temp = 12;
            input = cuaso.take_string(&temp);
        }
        else{
            temp = 13;
            input = cuaso.take_string(&temp);
        }
        question_text = cuaso.create_question_text(input,"",flag);
    }

    else {
        flag = 2;
        if(flagEasy){
            temp = 11;
            int num = temp;
            input = cuaso.take_string(&temp);
            encode = cuaso.take_encode(num,temp);
        }
        else if (flagNormal) {
            temp = 12;
            int num = temp;
            input = cuaso.take_string(&temp);
            encode = cuaso.take_encode(num,temp);
        }
        else {
            temp = 13;
            int num = temp;
            input = cuaso.take_string(&temp);
            encode = cuaso.take_encode(num,temp);
        }
        question_text = cuaso.create_question_text(input,encode,flag);
    }
    ui->textEdit->setText(QString::fromStdString(question_text));

}



void MainWindow::on_pushButton_2_clicked()
{
    string youranswer =  (ui->lineEdit->text()).toStdString();
    if(youranswer == ""){
        QMessageBox::critical(this,"ERROR","Please enter your answer.");
        return;
    }
    resize(1091,728);


    //string result;
    scene = cuaso.Paint(input);
    ui->graphicsView->setScene(scene);

    analize = cuaso.analize(input);
    ui->textEdit_2->setText(QString::fromStdString(analize));
    if(flagEncode){
        result = cuaso.take_encode(input,youranswer);
        ui->textEdit_3->setText(QString::fromStdString(result));
    }
    else if(flagDecode){
        result = cuaso.result(input,encode,youranswer);
        ui->textEdit_3->setText(QString::fromStdString(result));
    }

}

void MainWindow::on_pushButton_3_clicked()
{
    string content ="";
    QString name = QInputDialog::getText(this, tr("Name"),
                                         tr("Your Name:"), QLineEdit::Normal,
                                         QDir::home().dirName());
    QDateTime dt = QDateTime::currentDateTime();
    content += "Спб - ЛЕТИ - " + (dt.toString()).toStdString();
    content += "\nYour Name: ";
    content += name.toStdString() + "\n\n";
    content += "Method : ";
    if(flagDecode)
        content += "Decode\t\tLevel  : ";
    else
        content += "Encode\t\tLevel  : ";
    if(flagEasy)
        content += "Easy\n\n";
    else if(flagNormal)
        content += "Normal\n\n";
    else
        content += "Hard\n\n";
    content+= "Question :\n" + question_text + "\n\n";
    content += analize + "\n\n";
    content += result + "\n\n";



    QString filePath = QFileDialog::getSaveFileName(this, tr("save"), "/home/nguyenhai/Desktop/result.txt", tr("*.txt"));
                if (QString::compare(filePath, QString()) != 0)
                {
                    std::ofstream ff(qPrintable(filePath));
                    ff << qPrintable(QString::fromStdString(content));// text chua noi dung cua cai can ghi
                    ff.close();
                }

}
