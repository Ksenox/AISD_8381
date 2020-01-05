#ifndef MAIN_FUN_H
#define MAIN_FUN_H
#include <bin_struct.h>


int treePainter(QGraphicsScene *scene, Node *node, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth);

QGraphicsScene *graphic(BinTree *tree, QGraphicsScene *scene, int depht);

#endif // MAIN_FUN_H
