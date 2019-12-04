#ifndef MODIFY_H
#define MODIFY_H
#include "bt.h"

int beginning(QTextEdit *&uiInput, QTextEdit *&uiOutput, QGraphicsScene *&scene);
QString processing(QString input, BinTree *&tree);
QString modding(Node *root);

#endif // MODIFY_H
