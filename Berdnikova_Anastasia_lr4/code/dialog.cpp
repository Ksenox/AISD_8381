#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    QGraphicsScene *scene = new QGraphicsScene;

    ui->setupUi(this);

    ui->graphicsView->setScene(scene);

    mycolor = QColor::fromRgb(rand()%255,rand()%255,rand()%255);

    myfont.setItalic(1);
    myfont.setFamily("Calibri");
    myfont.setPixelSize(14);

    mybrush = QBrush(mycolor);
}


void Dialog::displaynode(char val, int deep, int maxdeep, int prevx, int prevy, int posx, int posy)
{
//    mycolor = QColor::fromRgb(rand()%255,rand()%255,rand()%255);
//    mybrush = QBrush(mycolor);

    std::string s;
    s.insert(0, 1, val);
    QString line = QString::fromStdString(s);
    mytext = new QGraphicsTextItem(line);
    mytext->setFont(myfont);
    mytext->setPos(posx - line.length()*myfont.pixelSize()/2, posy-elemheight/2 - myfont.pixelSize()/4);
    ui->graphicsView->scene()->addLine(posx,posy-elemheight/2,prevx,prevy+elemheight/2,QPen(Qt::black,3));
    ui->graphicsView->scene()->addRect(posx-elemwidth/2,posy-elemheight/2,elemwidth,elemheight,mypen,mybrush);
    ui->graphicsView->scene()->addItem(mytext);
}


Dialog::~Dialog()
{
    delete ui;
}
