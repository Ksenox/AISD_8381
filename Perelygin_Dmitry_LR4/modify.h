#ifndef MODIFY_H
#define MODIFY_H
#include "lab.h"

int beginning(QTextEdit *&uiInput, QTextEdit *&uiOutput, QGraphicsScene *&scene);
QString processing(QString input, BinTree *&tree);
QString modding(std::shared_ptr<Branch> root);

#endif // MODIFY_H
