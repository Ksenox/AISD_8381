#ifndef DRAWING_H
#define DRAWING_H

#include "allheaders.h"
#include "btree.h"

void graphic(struct Node* tree, QGraphicsScene *&scene);

int treePainter(QGraphicsScene *&scene, struct Node* node, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth);

void loopLatency();

void changeStepByStepMode();

void changeLoopState();

void setDisableStepMode();

#endif // DRAWING_H
