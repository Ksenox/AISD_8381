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

#define RUSSIAN "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя"

class console
{
public:
    console();
    string take_string(int *flag);
    string take_encode(int num, int random);
    string create_question_text(string str1, string str2, int fl);

    QGraphicsScene *Paint(string data);
    void treePainter(QGraphicsScene *&scene, MinHeapNode *root, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth);
    int checkErr(QString input, QString encode);
    int CountDeep(MinHeapNode *root);
    string analize(string data);
    string result(string input,string encode, string youranswer);
    void free(MinHeapNode* minheap);
    string take_encode(string input,string youranswer);

    huffman huffman;

    void free(MinHeap * a, MinHeapNode* b);
};

#endif // CONSOLE_H
