#include "bintree.h"

BinTree *createBinTree()
{
    BinTree *tree = new BinTree;
    tree->root = nullptr;
    tree->deep = 0;
    return tree;
}

BinNode *createBinNode(char info, bool isAlpha)
{
    BinNode *node = new BinNode;
    node->info = info;
    node->isLeaf = isAlpha;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}


BinTree *createBTFromForest(Forest* forest){
    BinTree *bintree = createBinTree();
    bintree->root = ConsBT(Root(Head(forest)),Listing(Head(forest)),Tail(forest));
    bintree->deep = CountDeep(bintree->root) - 1;
    return bintree;
}

/*checked*/
Tree *Head(Forest *forest){

    Tree *tree = new Tree;
    tree = forest->tree[0];// da bao gom deep
    return tree;
}

/*checked*/
Forest *Tail(Forest *forest){
    if(forest->count == 1)
        return nullptr;
    Forest *temp = createForest((forest->count)-1); // đã khởi tạo forest cùng forest->count
    for(int i = 0; i < (forest->count)-1; i++){
        temp->tree[i] = forest->tree[i+1];
    }
    return temp;
}

/* */
BinNode *Root(Tree* tree){// create Binnode from tree;
    if(tree == nullptr)
        return nullptr;
    BinNode *root = createBinNode(tree->root->info,tree->root->isLeaf);
    return root;
}

Forest *Listing(Tree *tree){
    if(tree->deep == 0) //
        return nullptr;
    Forest *forest = createForest((tree->root->total));
    for(int i = 0; i < forest->count; i++){
        forest->tree[i] = NodeToTree(tree->root->Tnode[i]);//da tao deepoftree
    }
    return forest;
}

Tree *NodeToTree(Node *node){
    Tree *tree = createTree();
    tree->root = node;
    tree->deep = CountDeepOfTree(node) - 1;
    return tree;
}


BinNode *ConsBT(BinNode *root, Forest *left, Forest *right){//tạo binnote* root  từ treenote thong qua ham createbinnode;

    BinNode *binnode = root;

    if(left == nullptr)
        binnode->left = nullptr;
    else
        binnode->left = ConsBT(Root(Head(left)),Listing(Head(left)),Tail(left));
    if(right == nullptr)
        binnode->right = nullptr;
    else
        binnode->right = ConsBT(Root(Head(right)),Listing(Head(right)),Tail(right));

    return binnode;
}

int CountDeep(BinNode *&node)
{
    if (node == nullptr)
        return 0;
    int cl = CountDeep(node->left);
    int cr = CountDeep(node->right);
    return 1 + ((cl>cr)?cl:cr);
}

/*checked*/
int CountDeepOfTree(Node* root){
    if(root == nullptr)
        return 0;
    int max = 0;
    for(int i = 0; i < root->total; i++){
        int count = CountDeepOfTree(root->Tnode[i]);
        max = count>max?count:max;
    }
    return max+1;
}
void takeInfoBT(BinNode *root, string &out){
    if(root == nullptr)
        return;
    out += "( ";
    out.append(1,root->info);
    out+=" ";
    takeInfoBT(root->left,out);
    takeInfoBT(root->right,out);
    out += ") ";
}
/*
void takeInfoByDeep(BinNode *root,string &out, int deep){
        if(deep == 0){
            out.append(1,root->info);
            out += " ";
        }
        else {
            takeInfoByDeep(root->left,out,deep-1);
            takeInfoByDeep(root->right,out,deep-1);
        }

}*/
void takeInfoByDeep(Node *root,int deep,string &out){// dieu kien la deep <= DeepOfTree
        if(deep == 0){
                out.append(1,root->info);
                out+= " ";
                return;
        }
        if(root->total == 0)
                return;

        for(int i = 0; i<root->total; i++){
                takeInfoByDeep(root->Tnode[i],deep-1,out);
        }
        return;
}

