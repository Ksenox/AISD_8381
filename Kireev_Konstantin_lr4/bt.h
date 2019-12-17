#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsEffect>
#include <QFileDialog>
#include <QStandardPaths>
#include <QtGui>
#include <QLabel>
#include <QColorDialog>
#include <QInputDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QStringList>
#include <QTextEdit>
#include <stack>
using namespace std;

struct Node
{
    bool isLeaf;
    char info;
    Node *left, *right;
};

struct BinTree
{
    Node *root;
    int deep;
};

BinTree *createBinTree();
Node *createBinNode(char info, bool isNum);
Node *appendRight(Node *node, char info, bool isNum);
Node *appendLeft(Node *node, char info, bool isNum);
Node *setInfo(Node *node, char info, bool isNum);
BinTree *create(QStringList in, int &err);
QString getInfixNotation(Node *root);
int countDeep(Node *&node);
int updateDeep(BinTree *tree);

#endif // BINTREE_H
