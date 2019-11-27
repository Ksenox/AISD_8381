#ifndef PRINTTREE_H
#define PRINTTREE_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QGraphicsTextItem"

int treePainter(QGraphicsScene *&scene, tree *symb, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth);

QGraphicsScene *graphic(tree *symb, QGraphicsScene *&scene);

#endif // PRINTTREE_H
