#ifndef GRAPHIC_H
#define GRAPHIC_H
#include "modify.h"

QGraphicsScene *graphic(BinTree *tree, QGraphicsScene *&scene);
int paint(QGraphicsScene *&scene, Node *node, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth);

#endif // GRAPHIC_H
