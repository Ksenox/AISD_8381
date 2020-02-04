#ifndef CONSOLE_H
#define CONSOLE_H
#include "huffman.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <cmath>
#include <QGraphicsTextItem>
#include <QString>
#include <QMessageBox>
#include <QLineEdit>
#define MAX_TREE_HT 100


#define RUSSIAN "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя"

class console
{
public:
    console();
    QGraphicsScene *Paint(string data);
    void treePainter(QGraphicsScene *&scene, MinHeapNode *root, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth);
    int checkErr(QString input, QString encode);
    int CountDeep(MinHeapNode *root);
    string analize(string data);
    string result(string input,string encode, int* fl);

    Huffman huffman;

    void free(MinHeap * a, MinHeapNode* b);
};

#endif // CONSOLE_H
