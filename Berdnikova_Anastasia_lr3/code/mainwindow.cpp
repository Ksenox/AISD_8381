#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QStringList>
#include <QTextCodec>
#include "stack.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QString readfile = QFileDialog::getOpenFileName(0, "Выберете файл для чтения", "C:/Users/nasty/source", "*.txt");

    QFile openFile(readfile);
    if(!openFile.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::information(this, "Ошибка", "Файл для чтения не удалось открыть!");
            ui->statusBar->showMessage("Ошибка");
            return;
    }
    QTextStream stream(&openFile);

    //stream.setLocale();
    QString buffer = stream.readAll();
    ui->textInput->setText(buffer);

    // Открытие файла и создание потока для записи
    QString writefile = QFileDialog::getSaveFileName(0, "Выберете файл для записи", "C:/Users/nasty/source/Desktop", "*.txt");

    QFile openFile2(writefile);
    if(!openFile2.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::information(this, "Ошибка", "Файл для записи не удалось открыть!");
            ui->statusBar->showMessage("Ошибка");
            return;
    }
    QTextStream stream2(&openFile2);

    //разбиение на строки

    QStringList list1 = buffer.split("\n");

    for (int i=0; i<list1.size(); i++) {
        QString str = list1[i];

        stack st; //переворот
        init(&st);
        for (int i=0;i<str.size();i++) {
            push(&st, str[i]);
        }
        QString str2="";

        for (int i=0;i<str.size();i++) {
            QChar symb = pop(&st);
            str2+=symb;
        }
        ui->textOutput->append(str2);
        stream2<<str2;
    }

    openFile.flush();
    openFile.close();

    openFile2.flush();
    openFile2.close();

}
/*void MainWindow::on_textInput_textChanged()
{
    can = true;
}
*/
