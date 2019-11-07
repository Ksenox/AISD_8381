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
#define EMPTY_STACK 1
#define FULL_STACK 2
#define INVAL_ARG 3
#define INVAL_POST 4

using namespace std;


struct BinNode
{
    bool isLeaf;
    char info;
    BinNode *left;
    BinNode *right;
};

struct BinTree
{
    BinNode *root;
    int deep;
};

BinTree *createBinTree();

BinNode *createBinNode(char info, bool isNum);

BinNode *appendRight(BinNode *node, char info, bool isNum);

BinNode *appendLeft(BinNode *node, char info, bool isNum);

BinNode *setInfo(BinNode *node, char info, bool isNum);

BinTree *getTreeFromArray(QStringList in, int &err);

QString getQStrFromTree(BinNode *root);

QString getListFromTree(BinNode *root, int indent);

int countDeep(BinNode *&node);

int updateDeep(BinTree *tree);

#endif // BINTREE_H
