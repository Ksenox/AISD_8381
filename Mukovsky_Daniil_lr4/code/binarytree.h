#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include <QVector>
#include <QList>
#include "CustomSplitForTree.h"



struct Node{
    QString info ="";
    Node* left = nullptr;
    Node* right = nullptr;
    int level = 0;
    bool flag = false;
    Node(int n = 0, Node * l = nullptr, Node * r = nullptr, int lev = 0) : info(n), left(l), right(r),level(lev) {}
};

class BinaryTree
{
public:
    BinaryTree(){
        root = new Node;
        numbElem = 0;
    }
    Node* root = nullptr;
    Node* createTree(QStringList listTree,int& numb);
    void getNumbElem();
    int getDepth(Node* tree);
private:
    int numbElem;
};


#endif // BINARYTREE_H
