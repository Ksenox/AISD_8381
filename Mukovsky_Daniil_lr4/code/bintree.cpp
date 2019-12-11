#include "bintree.h"

void BinTree::createTree(Node*& tree, QString stringTree){

    if (!stringTree.size())
        return;
    if (stringTree.size() == 1){
        tree->data = stringTree[0];
        tree->left = nullptr;
        tree->right = nullptr;
    }
    else{
        int j = 0;
        for (int i = 0;i<stringTree.size();i++){
            if (stringTree[i] == "(")
                j++;
            if (stringTree[i] == ")" )
                j--;
            if (stringTree[i] == "," && j ==2){
                j = i;
                break;
            }
        }
        createTree(tree, QString(stringTree[0]));
        QString leftTree;
        stringTree.replace(2,j-3,leftTree);
        createTree(tree->left,leftTree);
        QString rightTree;
        stringTree.replace(j+1,stringTree.size()-j-1,rightTree);
        createTree(tree->right,rightTree);
    }
}
void Prefix(Node* tree, QString& output){
    if (!tree) return;
    output += tree->data +' ';
    Prefix(tree->left,output);
    Prefix(tree->right,output);
}



