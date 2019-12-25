#include "bintree.h"


int BinTree::getMaxTreeDepth(Node* tree) const{
    if(tree == nullptr) return 0;
        else{
            int lDepth = this->getMaxTreeDepth(tree->left);
            int rDepth = this->getMaxTreeDepth(tree->right);
            if (lDepth > rDepth)  return(lDepth + 1);
            else return(rDepth + 1);
        }
}

QVector<Node*> BinTree::makeArray(){
    QQueue<Node*> queue;
    QVector<Node*> result ;
    queue.enqueue(root);
    for(;;){
        Node* current = queue.dequeue();
       (result).push_back(current);
        if (current->left==nullptr && current->right == nullptr && queue.size()==0){
            break;
        }
        if (current->right!=nullptr){
            queue.enqueue(current->right);
            current->right->level = current->level +1;
        }
        if (current->left!=nullptr){
            queue.enqueue(current->left);
            current->left->level = current->level +1;
        }
    }
    std::reverse( result.begin(), result.end());
    return result;
}

Node* BinTree::copyNode(Node* node_) {
   Node* node = new Node;
   node->isZero = node_->isZero;
   node->isRoot = node_->isRoot;
   node->isLeaf = node_->isLeaf;
   node->isSwapped = node_->isSwapped;
   node->isLast = node_->isLast;
   node->symbol = node_->symbol;
   node->value = node_->value;
   node->isHere = node_->isHere;
   return node;
}

void BinTree::freeMem(Node* tree){
    if(!tree)
        return;
    if (tree->right)
        this->freeMem(tree->right);
    if (tree->left)
        this->freeMem(tree->left);
    delete tree;
    return;
}

Node* BinTree::getRoot() const{
    return root;
}



void recalculationNodeValue(Node*currNode){
    while(!(currNode->isRoot)){
        (currNode->value)++;
         currNode = currNode->parent;
    }
    if (currNode->isRoot)
         (currNode->value)++;
}


Node* BinTree::copyRoot(Node* node, Node* parent) {
    if (node == nullptr)
        return nullptr;
    Node* newnode = copyNode(node);
    if(node!=parent)
        newnode->parent = parent;
    newnode->left = copyRoot(node->left,newnode);
    newnode->right = copyRoot(node->right,newnode);
    return newnode;
}

BinTree* BinTree::copyTree(BinTree* tree){
    Node* newroot = copyRoot(tree->root,tree->root);
    BinTree* newTree = new (BinTree);
    newTree->root = newroot;
    newTree->firstSwap = nullptr;
    newTree->secondSwap = nullptr;
    return newTree;
}



bool BinTree::needUpdateTree(){
    QVector<Node*> arr;
    Node* first;
    Node* second;
    int i =0;
    first = nullptr;
    second = nullptr;
    arr= this->makeArray();
    int min=0;
    bool flag = false;

    for (i =0;i<arr.size();i++){
        min = arr[i]->value;
        for (int j = i+1;j<arr.size()-1;j++){
            if(arr[j]->value<min){
                first = arr[i];
                flag = true;
                break;
            }
        }
        if (flag)break;
    }
    if(!first)return false;

    int fir = i;
    int max = first->value;
    for(i = fir+1;i<arr.size();i++){
        if (arr[i]->value<max){
            min = arr[i]->value;
            second = arr[i];
            break;
        }
    }
    if(!second)return false;

    for(i = fir+1;i<arr.size();i++){
        if (max>arr[i]->value && min>=arr[i]->value){
            min = arr[i]->value;
            second = arr[i];
        }
     }
    if(!second)return false;
    firstSwap = first;
    secondSwap = second;

    return true;
}

void BinTree::getZeroNode(Node* tree,Node*& zeroNode) const{
    if (tree == nullptr)
        return;
    if (tree->isZero){
        zeroNode = tree;
        return;
    }
    getZeroNode(tree->left, zeroNode);

    getZeroNode(tree->right, zeroNode);
    return;
}

void BinTree::getCurNode(Node* tree,Node*& curNode) const{
    if (tree == nullptr)
        return;
    if (tree->isHere){
        curNode = tree;
        return;
    }
    getCurNode(tree->left, curNode);

    getCurNode(tree->right, curNode);
    return;
}

bool BinTree::findNodeSymb(Node* tree, Node*& nodeSymb, char symb,bool& flag) const{
    if (nodeSymb)
        return flag;
    if (tree == nullptr)
        return flag;
    if (tree->symbol == symb ){
        nodeSymb = tree;
        flag = true;
        return flag;
    }
    findNodeSymb(tree->left, nodeSymb,symb,flag);
    findNodeSymb(tree->right, nodeSymb,symb,flag);
    return flag;
}



void BinTree::swapNodesForOrdering() {
    firstSwap->isSwapped = true;
    secondSwap->isSwapped = true;
    int diff = firstSwap->value-secondSwap->value;
    if (firstSwap==secondSwap) return;
    if (firstSwap->parent!=secondSwap->parent){
        if (firstSwap->parent->left == firstSwap) {
            firstSwap->parent->left = secondSwap;
        }
        else {
            firstSwap->parent->right = secondSwap;
        }
        if (secondSwap->parent->left == secondSwap) {
            secondSwap->parent->left = firstSwap;
        }
        else {
            secondSwap->parent->right = firstSwap;
        }
        Node* temp = firstSwap->parent;
        firstSwap->parent = secondSwap->parent;
        secondSwap->parent = temp;
        Node* s2=secondSwap->parent;
        Node *s1=firstSwap->parent;

        while(!(s2->isRoot)){
            (s2->value)-=diff;
            s2 = s2->parent;
        }
        while(!(s1->isRoot)){
            (s1->value)+=diff;
            s1 = s1->parent;
        }
    }
    else {
        if (firstSwap->parent->left ==firstSwap){
            firstSwap->parent->left = secondSwap;
            secondSwap->parent->right = firstSwap;
        }
        else{
            firstSwap->parent->right = secondSwap;
            secondSwap->parent->left = firstSwap;
        }
    }
    firstSwap = nullptr;
    secondSwap = nullptr;
    return;
}


void BinTree::setOrdinaryNodeColor(Node* tree){
    if(!tree)
        return;
    if (tree->isLast){
        tree->isLast = false;
    }
    if (tree->isSwapped){
        tree->isSwapped = false;
    }
    if (tree->isHere){
        tree->isHere = false;
    }
    if (tree->right)
        this->setOrdinaryNodeColor(tree->right);
    if (tree->left)
        this->setOrdinaryNodeColor(tree->left);
    return;
}
