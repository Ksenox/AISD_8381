#ifndef ACTIONS_H
#define ACTIONS_H
#include "inout.h"
#include "bintree.h"

int connectUI(QTextEdit *&uiInput, QTextEdit *&uiOutput, QGraphicsScene *&scene);

QString startProcess(QString input, BinTree *&tree);

QString modBinTree(BinNode *root);

int treePainter(QGraphicsScene *&scene, BinNode *node, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth);

QGraphicsScene *graphic(BinTree *tree, QGraphicsScene *&scene);

#endif // ACTIONS_H
