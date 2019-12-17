#include "nodequeque.h"

using namespace std;

Node* BinaryTree::createTree(QStringList listTree, int& numb){
    Node* finalNode = new Node;
    if (listTree.size() == 2) return finalNode;
    QString leftTree = "",
            rightTree = "";
    int i =1;
    finalNode->info = listTree[i++];
    int indexLeftTree = i;    // Индекс открывающей скобки левого поддерева
    if (listTree[i] == "("){
        int openBrackets = 1;
        int closeBrackets = 0;
        while (openBrackets != closeBrackets){
            i++;
            if (listTree[i] == "(")
                openBrackets++;
            else if (listTree[i] == ")")
                closeBrackets++;
        }
        for (; indexLeftTree <= i; indexLeftTree++) {
            leftTree.append(listTree[indexLeftTree]);
        }
        finalNode->left = createTree(splitForTree(leftTree),numb);
        numb++;

        i++;

        if (listTree[i] == ")") { // В случае если нет правого поддерева
            return finalNode;
        }

        int indexRightTree = i;    // Индекс открывающей скобки правого поддерева
        if (listTree[i] == "("){
            int openBrackets = 1;
            int closeBrackets = 0;
            while (openBrackets != closeBrackets){
                i++;
                if (listTree[i] == "("){
                    openBrackets++;
                }
                else if (listTree[i] == ")"){
                    closeBrackets++;
                }
            }
            for (; indexRightTree <= i; indexRightTree++){
                rightTree.append(listTree[indexRightTree]);
            }
            finalNode->right = createTree(splitForTree(rightTree),numb);
            numb++;
        }
    }
    return finalNode;
}

int BinaryTree::getDepth(Node *root){
    if(root == nullptr) return 0;
    else{
        int lDepth = getDepth(root->left);
        int rDepth = getDepth(root->right);

        if (lDepth > rDepth)  return(lDepth + 1);
        else return(rDepth + 1);
    }
}



