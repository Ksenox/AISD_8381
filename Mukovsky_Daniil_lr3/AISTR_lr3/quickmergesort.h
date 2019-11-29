#ifndef QUICKMERGESORT_H
#define QUICKMERGESORT_H

#include <QDialog>
#include <QStringList>
#include <QTextBrowser>
#include <iostream>
#include <algorithm>

namespace Ui {
class QuickMergeSort;
}

class QuickMergeSort : public QDialog
{
    Q_OBJECT

public:
    explicit QuickMergeSort(QWidget *parent = nullptr);
    ~QuickMergeSort();
private slots:
    void recieveArray(QString inputArray);
    void on_buttonQMergeSort_clicked();
    void on_pushButton_clicked();

    void on_save_clicked();

private:
    Ui::QuickMergeSort *ui;
    QString inputArrayString;
    int *inputArray;
    int step =1;
    QStringList lst;
    unsigned int size;
    QString result;
    bool check_path(QString path);
    void freeFirstSecond(int** firstPart,int** secondPart);
    bool NaturalMergingSort(int* inputArray,unsigned int size, QString& result,bool flagStep,int ste);
    void splitIntoTwo(int* inputArray, int** firstPart, int** secondPart, unsigned int size);
    void Merging(int* inputArray, unsigned int size, int** firstPart, int** secondPart);
};

#endif // QUICKMERGESORT_H
