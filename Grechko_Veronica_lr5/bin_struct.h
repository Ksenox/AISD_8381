#ifndef BIN_STRUCT_H
#define BIN_STRUCT_H
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsEffect>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextEdit>
#include <QMainWindow>
#include <QStandardPaths>
#include <QtGui>
#include <QColorDialog>
#include <QInputDialog>
#include <QPushButton>
#include <QStringList>

struct Node // структура для представления узлов дерева
{
    int key;
    int size;
    Node* left;
    Node* right;
    Node(int k) { key = k; left = right = 0; size = 1; }

};


class BinTree
{
private:
    Node* Current = nullptr;
public:
    Node* Head = nullptr;
    BinTree();
    Node* insert(Node* p, int k);
    Node* insertroot(Node* p, int k);
    Node* rotateright(Node* p);
    Node* rotateleft(Node* q);
    int max_depth(Node *hd);
    int getsize(Node* p);
    void fixsize(Node* p);
    Node* join(Node* p, Node* q);
    Node* remove(Node* p, int k);

};
int treePainter(QGraphicsScene *scene, Node *node, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth, int c);

QGraphicsScene *graphic(BinTree *tree, QGraphicsScene *scene, int depht);
#endif // BIN_STRUCT_H
