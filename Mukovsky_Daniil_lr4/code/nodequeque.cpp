#include "nodequeque.h"

bool NodeQueue::isEmpty(){ //проверка очереди на пустоту
    if (last==0) return true;
    else return false;
}


void NodeQueue::addItem(Node* value){
    if (last == maxSize){
        return;
    }
     data[last++] = value;
}


Node* NodeQueue::remove(){
    Node* elem = data[0];

    for (int i =1;i<last+1;i++){
        data[i-1] = data[i];
    }
    last--;
    return elem;
}


Node* NodeQueue::top(){
    return data[0];
}

int NodeQueue::getMaxSize(){
    return maxSize;
}

int NodeQueue::size(){ //размер очереди
    return last;
}
