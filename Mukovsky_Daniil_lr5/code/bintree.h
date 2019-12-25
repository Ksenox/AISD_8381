#ifndef BINTREE_H
#define BINTREE_H
#include <memory>
#include <iostream>
#include <string>
#include <QString>
#include <sstream>
#include <QVector>
#include <QQueue>
#include <algorithm>

#define INVALID -1 /* setted as the symbol of the non-leaf nodes */
#define HOW_MANY_POSSIBLE_SYMBOLS 256 /* how many possible symbols */

struct Node{
    Node *left = nullptr;
    Node *right =nullptr;
    Node *parent ;
    int value;
    int isZero;
    char symbol = ' ';
    int isRoot;
    int isLeaf;
    int level = 1;
    bool isLast;
};

struct Symbol{
    char symbol;
    Node *tree;
};

class BinTree{
private:
    Node* root = nullptr;
public:
    BinTree(){
        root = new Node;
        root->isZero = 1;
        root->isRoot = 1;
        root->isLeaf = 1;

        root->parent = nullptr;
        root->left = nullptr;
        root->right = nullptr;
        root->isLast = false;

        root->symbol = '\n';
        root->value = 0;
    }
    ~BinTree(){
        this->freeMem(root);
    }
    QVector<Node*> makeArray();
    void updateTree(Node* currNode);
    int getMaxTreeDepth(Node* node );
    Node* getRoot();
    void freeMem(Node* node = nullptr);

};
bool swapNodes(Node* n1, Node* n2);


#endif // BINTREE_H
