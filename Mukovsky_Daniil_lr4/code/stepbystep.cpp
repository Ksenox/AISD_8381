#include "stepbystep.h"

bool stepByStepAlg(int& lev, QString& out,NodeQueue* queque_,bool flagV){
    for(;;){
        Node* current = queque_->top();
        current->flag=true;
        queque_->remove();
        if (lev!=current->level){
            lev++;
            if (lev == 1)
                out+="Level:"+QString::number(lev)+'\n';
            else
                out+="\nLevel:"+QString::number(lev)+'\n';
        }
        out+=current->info+'\t';
        if (current->left==nullptr && current->right == nullptr && queque_->size()==0){
            return true;
        }
        if (current->left!=nullptr){
            queque_->addItem(current->left);
            current->left->level = current->level +1;
        }
        if (current->right!=nullptr){
            queque_->addItem(current->right);
            current->right->level = current->level +1;
        }
        if (flagV==true) return false;
    }
}
