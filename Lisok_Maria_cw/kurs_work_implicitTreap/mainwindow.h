#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mergequeue.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void on_actionAddRandUnit_triggered();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_split_clicked();

    void setMaxKey(long key){
        this->maxKey = key;
    }

    long getMaxKey(){
        return maxKey;
    }
    void setMinKey(long key){
        this->minKey = key;
    }

    long getMinKey(){
        return minKey;
    }
    void generateKeys();
    void generateValues();
    void findMinIter(vector<size_t>* alliterations);
    void on_merge_clicked();

private:
    Ui::MainWindow * ui;
    MergeQueue<int> * queue;

    vector<size_t>* keys;
    long long int maxKey;
    long long int minKey;
    double avr;
    long length;

    vector<int> numsForRand;
    void getNumRand();
    vector<long>* heights;
};
#endif // MAINWINDOW_H
