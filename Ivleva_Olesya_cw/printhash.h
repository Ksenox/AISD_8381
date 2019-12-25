#include "mainwindow.h"
#include "QGraphicsScene"
#include "QGraphicsTextItem"
#include <QPen>
#include <QFont>

//int size_el = 10000;

QGraphicsScene *graphic(Hash_cl<string, string> &Hash_, QGraphicsScene *&scene);
void add_rect(QGraphicsScene *&scene, Hash_cl<string, string> &Hash_, int x1, int y1, int x2, int y2, QPen &pen, QBrush &brush, QFont &font);
