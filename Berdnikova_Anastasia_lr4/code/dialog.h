#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsTextItem>
#include <QString>
#include <QPen>
#include <string>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void displaynode(char val, int deep, int maxdeep, int prevx, int prevy, int posx, int posy);
    int elemwidth = 20;
    int elemheight = 20;

private:
    Ui::Dialog *ui;


    QColor mycolor;
    QPen mypen = QPen(Qt::black,1);
    QFont myfont;
    QBrush mybrush;

    QGraphicsTextItem* mytext;


};

#endif // DIALOG_H
