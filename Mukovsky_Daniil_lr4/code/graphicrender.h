#ifndef GRAPHICRENDER_H
#define GRAPHICRENDER_H
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsEffect>
#include "binarytree.h"
#include<cmath>


int netTreePainter(QGraphicsScene *&scene, Node *node, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth, int color_c);

QGraphicsScene *graphicConfig(BinaryTree *tree, QGraphicsScene *&scene, int depth);

#endif // GRAPHICRENDER_H
