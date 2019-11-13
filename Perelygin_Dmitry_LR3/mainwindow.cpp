#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <clocale>
#include <windows.h>
#include "mainwindow.h"
#include <QMessageBox>
#include <QTextBrowser>
#include <QTextEdit>
#include <vector>
#include <conio.h>
using namespace std;

string Name;
bool started = true;


template <class T>
class Stack
{
private:
    T* arr;
    int size, len;
    void new_size(int s)
    {
        if (s <= 0) return;
        T* new_arr = new T[s];
        int min_s = s < len ? s : len;
        for (int i = 0; i < min_s; i++) new_arr[i] = arr[i];
        delete[] arr;
        size = s;
        arr = new_arr;
    }

public:
    Stack()
    {
        len = 0;
        arr = new T[size = 5];
    }

    Stack(Stack& st)
    {
        arr = new T[size = st.size];
        len = st.len;
        for (int i = 0; i < len; i++) arr[i] = st.arr[i];
    }

    ~Stack()
    {
        delete[] arr;
    }

    int Size()
    {
        return len;
    }

    void Push(T x)
    {
        if (len == size) new_size(size << 1);
        arr[len++] = x;
    }
    T Pop()
    {
        if (size > 10 && len < size >> 2) new_size(size >> 1);
        if (len == 0) return arr[len];
        return arr[--len];
    }
    T Top()
    {
        return arr[--len];
    }
    void Clear()
    {
        delete arr;
        len = 0;
        arr = new T[size = 5];
    }

    bool IsEmpty()
    {
        return len == 0;
    }

};

int check()
{}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
    /*QString fileName = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),
                                QDir::currentPath(),
                                "Images (*.png *.xpm *.jpg);;All files (*.*)");*/
    QString FileName = QFileDialog::getOpenFileName(this, "OpenDialog",
    QDir::homePath(), "*.txt;; *.*");
    Name = FileName.toStdString();

}
//void QTextEdit::append ( const QString & text )
/* for( ; ; )
                {
                QApplication::processEvents();
                if(!started)break;


                }
                started = true;*/

void MainWindow::on_pushButton_clicked()
{
    using namespace std;
        ui->textBrowser->clear();
        bool correct = true;
        int i = 0, j = 0;

        string out;
        string text;
         vector<char> show;

        ifstream fin;
        //cout << Name;
        fin.open(Name);
        getline(fin, text);
        fin.close();

        cout << text << '\n';
        Stack<char> S;
        ui->textBrowser->insertPlainText("Text:\n");
        ui->textBrowser->insertPlainText(QString::fromStdString(text));
        ui->textBrowser->insertPlainText("\n\n\n");
        if(text.length()==0)
        {
            ui->textBrowser->insertPlainText("NOPE ");
            correct=false;
        }
        while (i< text.length())
        {
            ui->textBrowser->insertPlainText("Input:\n\n\n");
            while (text[i] != 'C')
            {
                if (text[i]== 'D' || i == text.length())
                {

                    ui->textBrowser->insertPlainText("NOPE ");
                    correct=false;
                    break;
                }

                S.Push(text[i]);
                show.push_back(text[i]);
                 ui->textBrowser->insertPlainText("Stack:\n");
                 for (j=show.size()-1;j>=0;j--)
                 {
                     ui->textBrowser->insertPlainText(QChar(show[j]));
                     ui->textBrowser->insertPlainText("\n");
                 }

                i++;
                //cout << i << '\n';

            }
            if (correct==false)
            break;
            i++;
            ui->textBrowser->insertPlainText("Check symbols after C:\n\n\n");
            while (i<text.length() && text[i] != 'D')
            {
                char temp;
                temp = S.Pop();
                ui->textBrowser->insertPlainText("Stack:\n");
                for (j=show.size()-1;j>=0;j--)
                {
                    ui->textBrowser->insertPlainText(QChar(show[j]));
                    ui->textBrowser->insertPlainText("\n");
                }
                ui->textBrowser->insertPlainText("Try to check:\n");
                ui->textBrowser->insertPlainText(QChar(show[show.size()-1]));
                ui->textBrowser->insertPlainText(" and ");
                ui->textBrowser->insertPlainText(QChar(text[i]));
                ui->textBrowser->insertPlainText("\n");
                if (temp != text[i])
                {
                    ui->textBrowser->insertPlainText("NOPE ");
                    cout << temp << "   " << text[i] << '\n';
                    cout << i << '\n';
                    correct = false;
                    break;
                }
                else
                {
                    show.pop_back();
                    i++;
                    ui->textBrowser->insertPlainText("Succeed check!:\n");
                }

            }
            if (correct==false)
            break;
            i++;
        }
        if (correct)
        {
        ui->textBrowser->insertPlainText("YES");
        }

}

void MainWindow::on_pushButton_2_clicked()
{
    QWidget::close();
}

void MainWindow::on_pushButton_4_clicked()
{
    started=false;
}

void MainWindow::on_pushButton_5_clicked()
{
    using namespace std;
    ui->textBrowser->clear();
        bool correct = true;
        int i = 0, j = 0;

        string out;
        string text;
         vector<char> show;

        ifstream fin;
        //cout << Name;
        fin.open(Name);
        getline(fin, text);
        fin.close();

        cout << text << '\n';
        Stack<char> S;


        ui->textBrowser->insertPlainText("Text:\n");
        ui->textBrowser->insertPlainText(QString::fromStdString(text));
        ui->textBrowser->insertPlainText("\n\n\n");
        if(text.length()==0)
        {
            ui->textBrowser->insertPlainText("NOPE ");
            correct=false;
        }
        while (i< text.length())
        {
            ui->textBrowser->insertPlainText("Input:\n\n\n");
                        for( ; ; )
                        {
                        QApplication::processEvents();
                        if(!started)break;


                        }
                        started = true;
            while (text[i] != 'C')
            {
                if (text[i]== 'D' || i == text.length())
                {

                    ui->textBrowser->insertPlainText("NOPE ");
                    correct=false;
                    break;
                }

                S.Push(text[i]);
                show.push_back(text[i]);
                 ui->textBrowser->insertPlainText("Stack:\n");
                 for (j=show.size()-1;j>=0;j--)
                 {
                     ui->textBrowser->insertPlainText(QChar(show[j]));
                     ui->textBrowser->insertPlainText("\n");
                 }

                i++;
                                for( ; ; )
                                {
                                QApplication::processEvents();
                                if(!started)break;


                                }
                                started = true;

            }
            if (correct==false)
            break;
            i++;

            ui->textBrowser->insertPlainText("Check symbols after C:\n\n\n");
            while (i<text.length() && text[i] != 'D')
            {

                char temp;
                temp = S.Pop();
                                for( ; ; )
                                {
                                QApplication::processEvents();
                                if(!started)break;


                                }
                                started = true;
                ui->textBrowser->insertPlainText("Stack:\n");
                for (j=show.size()-1;j>=0;j--)
                {
                    ui->textBrowser->insertPlainText(QChar(show[j]));
                    ui->textBrowser->insertPlainText("\n");
                }
                ui->textBrowser->insertPlainText("Try to check:\n");
                ui->textBrowser->insertPlainText(QChar(show[show.size()-1]));
                ui->textBrowser->insertPlainText(" and ");
                ui->textBrowser->insertPlainText(QChar(text[i]));
                ui->textBrowser->insertPlainText("\n");
                if (temp != text[i])
                {
                    ui->textBrowser->insertPlainText("NOPE ");
                    cout << temp << "   " << text[i] << '\n';
                    cout << i << '\n';
                    correct = false;
                    break;
                }
                else
                {
                    show.pop_back();
                    i++;
                    ui->textBrowser->insertPlainText("Succeed check!:\n");
                }

            }
            if (correct==false)
            break;
            i++;
        }
        if (correct)
        {
        ui->textBrowser->insertPlainText("YES");
        }

}
