#ifndef BINARYRANDOMTREAP_H
#define BINARYRANDOMTREAP_H
#include <qrandom.h>
#include <QString>
#include <stdlib.h>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "queue.h"
#include <math.h>
#include "validator.h"
#include "randomgenerator.h"

class BinaryRandomTreap
{
private:
    class Node{
        public:
            QString value;
            int priority;
            Node* left;
            Node* right;
            Node(QString value, int priority);
    };

    bool isContentIntegers = true;

    Node* rotateRight(Node* root);

    Node* rotateLeft(Node* root);

    Node* insert(Node* root, QString insertingValue, int priority);

    void remove(Node* root, Node* parent, bool isLeft, QString& task, int step);

    Node* find(Node* root, QString value);

    Node* findParent(Node* root, Node* kid);

    Node* root;

    QString getPrefix(Node* root);

    void treePainter(QGraphicsScene *&scene, Node *node, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth);

    int getTreeHeight(Node* node);

    QString getStrTree(Node* node);

    void plotTreeOfIntegers(QString string);

    void plotTreeOfChars(QString string, int* priorities);

public:
    BinaryRandomTreap(QString inputString);

    void removeNode(QString value, QString& task);

    BinaryRandomTreap(int* input, int* priorities, int amount, QString & task);

    QString getFromLowestToGreatest();

    QGraphicsScene* drawTree();
};

#endif // BINARYRANDOMTREAP_H
