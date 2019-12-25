#ifndef CONSOLE_H
#define CONSOLE_H

#include "bintree.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <cmath>
#include <QGraphicsTextItem>
#include <QString>
#include <QMessageBox>
#include <QLineEdit>


class console
{
public:
    console();
    QGraphicsScene *Console(QString data);
    QGraphicsScene *Analize(QString data);
    int checkErr(QString data);
    void treePainter(QGraphicsScene *&scene, BinNode *binnode, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth);

};

#endif // CONSOLE_H
