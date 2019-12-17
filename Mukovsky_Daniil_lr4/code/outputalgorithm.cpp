#include "outputalgorithm.h"

bool customAlg(Node* root, QString& out){
    CustomQueue* queque = new CustomQueue;
    root->level = 1;
    queque->addItem(root);
    Node* current;
    int lev = 0;
    queque->addItem(root);
    for(;;){
        current = queque->top();
        if (lev!=current->level){
            lev++;
            out+="Уровень:"+lev+'\n';
        }
        out+=current->info+'\t';
        if (!current->left && !current->right && queque->size()==1){
            return true;
        }
        if (current->left){
            queque->addItem(current->left);
            current->left->level = current->level +1;
        }
        if (current->right){
            queque->addItem(current->right);
            current->right->level = current->level +1;
        }
        queque->remove();
    }
    return true;
}
