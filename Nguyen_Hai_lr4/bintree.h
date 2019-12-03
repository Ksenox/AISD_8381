#include "forest.h"


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
BinNode *createBinNode(char info, bool isAlpha);

BinTree *createBTFromForest(Forest* forest);
BinNode *ConsBT(BinNode *root, Forest *left, Forest *right);
Tree *Head(Forest *forest);
Forest *Tail(Forest *forest);
BinNode *Root(Tree* tree);
Forest *Listing(Tree *tree);
Tree *NodeToTree(Node *node);
int CountDeep(BinNode *&node);
int CountDeepOfTree(Node* root);
void takeInfoBT(BinNode *root, string &out);
void takeInfoByDeep(Node *root,int deep,string &out);

