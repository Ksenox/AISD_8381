#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include <QVector>
#include <QList>

struct Node{
    Node* left;
    Node* right;
    QChar data;
    Node(int n = 0, Node* l = nullptr, Node* r = nullptr): num(n),left(l),right(r){}
};

class BinTree
{
private:
    Node* root;
public:
    BinTree(){
        root = nullptr;
    }
    void createTree(Node*& tree, QString stringTree);
};

#endif // BINTREE_H
