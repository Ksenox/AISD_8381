#ifndef NODEQUEQUE_H
#define NODEQUEQUE_H
#include "binarytree.h"

class NodeQueue{
    private:
        Node** data;
        int maxSize;
        int last; //указатель на начало
    public:
        NodeQueue(int maxSize_){
            maxSize = maxSize_;
            data = new Node*[maxSize+1];
            last = 0;
        }
        ~NodeQueue(){
            delete[] data;
        }
        bool isEmpty();
        int getMaxSize();
        void addItem(Node* value);
        Node* remove();
        Node* top();
        int size();
};


#endif // NODEQUEQUE_H
