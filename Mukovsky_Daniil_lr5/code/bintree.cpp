#include "bintree.h"


int BinTree::getMaxTreeDepth(Node* tree){
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
Node* BinTree::getRoot(){
    return root;
}

void BinTree::updateTree(Node*currNode){
    while(!(currNode->isRoot)){
        (currNode->value)++;
         currNode = currNode->parent;
    }
    if (currNode->isRoot)
         (currNode->value)++;
    QVector<Node*> arr;
    Node* first;
    Node* second;
    for(;;){
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
        if(!first)return;
        int fir = i;
        int max = first->value;
        for(i = fir+1;i<arr.size();i++){
            if (arr[i]->value<max){
                min = arr[i]->value;
                second = arr[i];
                break;
            }

        }
        if(!second)return;

        for(i = fir+1;i<arr.size();i++){
            if (max>arr[i]->value && min>=arr[i]->value){
                min = arr[i]->value;
                second = arr[i];
            }
        }
        if(!second)return;

        if (!swapNodes(first,second)){
            std::cout<<"ERROR NODES";
            return;
        }
    }
}


bool swapNodes(Node* n1, Node* n2) {
    int diff = n1->value-n2->value;
    if (n1==n2) return false;
    if (n1->parent!=n2->parent){
        if (n1->parent->left == n1) {
            n1->parent->left = n2;
        }
        else {
            n1->parent->right = n2;
        }
        if (n2->parent->left == n2) {
            n2->parent->left = n1;
        }
        else {
            n2->parent->right = n1;
        }
        Node* temp = n1->parent;
        n1->parent = n2->parent;
        n2->parent = temp;
        Node* s2=n2->parent;
        Node *s1=n1->parent;

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
        if (n1->parent->left ==n1){
            n1->parent->left = n2;
            n2->parent->right = n1;
        }
        else{
            n1->parent->right = n2;
            n2->parent->left = n1;
        }
    }
    return true;
}





