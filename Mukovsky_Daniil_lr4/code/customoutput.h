#ifndef CUSTOMOUTPUT_H
#define CUSTOMOUTPUT_H

#include <QDialog>

#include "graphicrender.h"
#include "nodequeque.h"
#include <QFileDialog>
#include <fstream>
#include <sstream>
#include <iostream>
namespace Ui {
class customOutput;
}

class customOutput : public QDialog
{
    Q_OBJECT

public:
    explicit customOutput(QWidget *parent = nullptr);
    ~customOutput();
private slots:
    void recieveArray(QString inputArray);
    void on_pushButton_clicked();

    void on_nextStep_clicked();

    void on_saveButton_clicked();

private:
    Ui::customOutput *ui;
    QString inputTreeString;
    QGraphicsScene *scene;
    int lev= 0;
    bool flagStep;
    QString out;
    BinaryTree* BT;
    NodeQueue* queque;
    int depth;
};

#endif // CUSTOMOUTPUT_H
