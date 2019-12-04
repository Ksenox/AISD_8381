#ifndef BINTREE_H
#define BINTREE_H
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsEffect>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

typedef QString type;

struct Node
{

    type data = "";
    Node* left = nullptr;
    Node* right = nullptr;

};

class BinTree
{
private:
    Node* Current = nullptr;
    QString data;
public:
    Node* Head = nullptr;
    BinTree();
    Node* createTree(QStringList);
    int max_depth(Node *hd);
    int count_node(Node *hd,int level, int curr_lev, int count);
};

QGraphicsScene *graphic(BinTree *tree, QGraphicsScene *&scene, int depth);
int treePainter(QGraphicsScene *&scene, Node *node, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth, int c);



#endif // BINTREE_H
