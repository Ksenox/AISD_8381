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
    Node *parent;
    int value;
    bool isZero;
    char symbol;
    bool isRoot;
    bool isLeaf;
    int level = 1;
    bool isLast;
    bool isHere;
    bool isSwapped;
};


class BinTree{
private:
    Node* root = nullptr;
    Node* firstSwap = nullptr;
    Node* secondSwap = nullptr;
    QVector<Node*> makeArray();
    void swapNodes();
    Node* copyRoot(Node* tree, Node*parent) ;
    Node* copyNode(Node* node);
public:
    BinTree(){
        root = new Node;
        root->isZero = true;
        root->isRoot = true;
        root->isLeaf = true;
        root->isSwapped = false;
        root->isLast = false;
        root->isHere = true;
        root->parent = nullptr;
        root->left = nullptr;
        root->right = nullptr;

        root->symbol = '\n';
        root->value = 0;
    }
    ~BinTree(){
        this->freeMem(root);
    }
    bool needUpdateTree();
    void getCurNode(Node* tree,Node*& curNode) const;
    void getZeroNode(Node* tree, Node*& node) const;
    bool findNodeSymb(Node* tree, Node*& nodeSymb, char symb,bool& flag) const;
    int getMaxTreeDepth(Node* node) const;
    Node* getRoot() const;
    void freeMem(Node* node = nullptr);
    void setOrdinaryNodeColor(Node* tree);
    BinTree* copyTree(BinTree* tree);
    void swapNodesForOrdering();
};

void recalculationNodeValue(Node* node);


#endif // BINTREE_H
