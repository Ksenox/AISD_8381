#ifndef CUSTOMQUEUE_H
#define CUSTOMQUEUE_H


using namespace std;

class CustomQueue{
    private:
        Node** data;
        int maxSize;
        int last; //указатель на начало
    public:
        CustomQueue(int maxSize_){
            maxSize = maxSize_;
            data = new Node*[maxSize+1];
            last = 0;
        }
        ~CustomQueue(){
            delete[] data;
        }
        bool isEmpty();
        int getMaxSize();
        void addItem(Node* value);
        Node* remove();
        Node* top();
        int size();
};

#endif // CUSTOMQUEUE_H
