#include "binarytree.h"

bool CustomQueue::isEmpty(){ //проверка очереди на пустоту
    if (last==0) return true;
    else return false;
}


void CustomQueue::addItem(Node* value){
    if (last == maxSize){
        return;
    }
     data[last++] = value;
}


Node* CustomQueue::remove(){
    Node* elem = data[0];

    for (int i =1;i<last+1;i++){
        data[i-1] = data[i];
    }
    last--;
    return elem;
}


Node* CustomQueue::top(){
    return data[0];
}

int CustomQueue::getMaxSize(){
    return maxSize;
}

int CustomQueue::size(){ //размер очереди
    return last;
}
