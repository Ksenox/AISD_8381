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

    QString FileName = QFileDialog::getOpenFileName(this, "OpenDialog",
    QDir::homePath(), "*.txt;; *.*");
    Name = FileName.toStdString();

}


void MainWindow::on_pushButton_clicked()
{
        using namespace std;
        ui->textBrowser->clear();
        bool correct = true, cmp = false;
        unsigned int i = 0;
        int j = 0;

        string out;
        string text;
         vector<char> show;

        ifstream fin;
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
            //ui->textBrowser->insertPlainText("NOPE ");
            correct=false;
        }
        while (i< text.length())
        {
            cmp = false;
            ui->textBrowser->insertPlainText("Input:\n\n\n");
            while (text[i] != 'C')
            {
                if (text[i]== 'D' || i == text.length())
                {

                   // ui->textBrowser->insertPlainText("NOPE ");
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

            }
            if (correct==false)
            break;
            i++;
            ui->textBrowser->insertPlainText("Check symbols after C:\n\n\n");
            while (i<text.length() && text[i] != 'D')
            {
                char temp;
                if (S.IsEmpty()==true )
                {
                    ui->textBrowser->insertPlainText("EMPTY STACK\n");
                    correct = false;
                    break;
                }
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
                    //ui->textBrowser->insertPlainText("NOPE ");
                    S.Clear();
                    correct = false;
                    break;
                }
                else
                {
                    show.pop_back();
                    i++;
                    cmp = true;
                    ui->textBrowser->insertPlainText("Succeed check!:\n");
                }

            }
            if (!S.IsEmpty())
            {
                ui->textBrowser->insertPlainText("DIF LENGTH:\n");
                correct = false;
            }
            if (correct==false)
            break;
            i++;
        }
        if (correct && cmp)
        {
        ui->textBrowser->insertPlainText("YES");
        }
        else
        ui->textBrowser->insertPlainText("NOPE ");
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
        bool correct = true, cmp = false;
        unsigned int i = 0;
        int j = 0;


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
            //ui->textBrowser->insertPlainText("NOPE ");
            correct=false;
        }
        while (i< text.length())
        {
            cmp = false;
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

                    //ui->textBrowser->insertPlainText("NOPE ");
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
                for( ; ; )
                {
                QApplication::processEvents();
                if(!started)break;


                }
                started = true;
                if (S.IsEmpty()==true)
                {
                    ui->textBrowser->insertPlainText("EMPTY STACK\n");
                    correct = false;
                    break;
                }
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
                    S.Clear();
                    correct = false;
                    break;
                }
                else
                {
                    show.pop_back();
                    i++;
                    cmp = true;
                    ui->textBrowser->insertPlainText("Succeed check!:\n");
                }

            }
            if (!S.IsEmpty())
            {
                ui->textBrowser->insertPlainText("DIF LENGTH:\n");
                correct = false;
            }
            if (correct==false)
            break;
            i++;
        }
        if (correct && cmp)
        {
        ui->textBrowser->insertPlainText("YES");
        }
        else
        ui->textBrowser->insertPlainText("NOPE ");

}
