#ifndef TREAPNODE_H
#define TREAPNODE_H

#include "headers.h"


template<class T>
class TreapNode{
public:
    friend class MainWindow;
    TreapNode();
    TreapNode(ul, ul priority = std::rand() % RAND_FACTOR + 1, TreapNode* left = nullptr, TreapNode* right = nullptr);

    TreapNode* merge(TreapNode*, TreapNode*);               // Merging two treaps. Need agree with: keys of one of treaps needs to be bigger, than keys of another Treap.
    void split(ul, TreapNode*&, TreapNode*&);               // Splits up treap. First output treap has all keys smaller than keys of the second one.

    TreapNode* add(ul);                                     // Add Node to NON EMPTY Treap, using key. Priority changed by std::rand.
    TreapNode* add(ul, ul);                                 // Add Node to NON EMPTY Treap, using key and priority.
    TreapNode* remove(ul);                                  // Remove Node from NON EMPTY Treap by key.

    int exist(ul);                                          // If node exsited in treap returns way lenght to him (num of sticks), else -1
    void recalcSizeOf();                                    // Recalculate SizeOf
    size_t height();                                        // Returns way length from root the farthest node.

    static void clear(TreapNode*&);                          // Destroy root this and all childs.
    static size_t sizeOf(TreapNode*);                       // Returns mSizeOf field of treap

    ul key(size_t);                                         // Returns key of node by index in upping order of keys.
    size_t levelLenght(size_t);                             // Returns count of nodes on level height


    const int DrawingSize{28};
    const int MajorAxis{55};
    void setStartPos(int, int);
    QPoint getStartPos() const;

    // STEP-BY-STEP

    static void loopLatency();
    static void changeLoopState();
    static void changeStepByStepMode();
    static void setDisableStepMode();
    static bool stepButStepEnable;

    ul getKey() const{
        return mKey;
    }
    ul getPriority() const{
        return mPriority;
    }

    void setWidth(int w){
        width = w;
    }

    int getWidth() const{
        return width;
    }
    void setForErrors(string & str){
       forErrors += str;
    }

    const string& getForErrors() const{
        return forErrors;
    }

private:

    TreapNode* mLeft;
    TreapNode* mRight;

    ul mKey;
    ul mPriority;

    size_t mSizeOf;                                         // Count of subtreaps + 1 (root exactly)

    static bool stepLoopSwitcher;


    // DRAWING
    QPoint startPos{0, 0};
    int width;

    static string forErrors;
};

template<class T>

TreapNode<T>::TreapNode() {}

template<class T>
TreapNode<T>::TreapNode(ul key, ul priority, TreapNode* left, TreapNode* right) : TreapNode() {
    mLeft = left;
    mRight = right;
    mKey = key;
    mPriority = priority;
}

template<class T>
TreapNode<T>* TreapNode<T>::merge(TreapNode* left, TreapNode* right){
    if(!left) return right;
    if(!right) return left;

    TreapNode<T>* treap;
    if(left->mPriority > right->mPriority) {
        TreapNode<T>* new_subTreap = merge(left->mRight, right);
        treap = new TreapNode(left->mKey, left->mPriority, left->mLeft, new_subTreap);
    } else {
        TreapNode<T>* new_subTreap = merge(left, right->mLeft);
        treap = new TreapNode(right->mKey, right->mPriority, new_subTreap, right->mRight);
    }

    treap->recalcSizeOf();
    return treap;
}

template<class T>
void TreapNode<T>::split(ul key, TreapNode*& left, TreapNode*& right){
    TreapNode<T>* newTreap = nullptr;
    if(mKey <= key) {
        if(!mRight)
            right = nullptr;
        else
            mRight->split(key, newTreap, right);
        left = new TreapNode(mKey, mPriority, mLeft, newTreap);
        left->recalcSizeOf();
    }
    else {
        if(!mLeft)
            left = nullptr;
        else
            mLeft->split(key, left, newTreap);
        right = new TreapNode(mKey, mPriority, newTreap, mRight);
        right->recalcSizeOf();
    }
}

template<class T>
TreapNode<T>* TreapNode<T>::add(ul key){
    TreapNode<T>* left = nullptr;
    TreapNode<T>* right= nullptr;
    split(key, left, right);
    TreapNode<T>* newNode = new TreapNode(key);
    return merge(merge(left, newNode), right);
}

template<class T>
TreapNode<T>* TreapNode<T>::add(ul key,  ul priority){
    if(exist(key) != -1) {
        string buf = "WARNING:Node with that _key is already existed in Treap.";
        this->setForErrors(buf);
    }else{
    TreapNode<T>* left = nullptr;
    TreapNode<T>* rigth = nullptr;
    split(key, left, rigth);
    TreapNode<T>* newNode = new TreapNode(key, priority);
    return merge(merge(left, newNode), rigth);
    }
}

template<class T>
TreapNode<T>* TreapNode<T>::remove(ul key){
    TreapNode<T>* r = nullptr;
    TreapNode<T>* l = nullptr;
    TreapNode<T>* el = nullptr;
    split(key, l, r);
    l->split(key-1, l, el);
    delete el;
    return merge(l, r);
}

template<class T>
void TreapNode<T>::clear(TreapNode*& treap){
    if(treap)
    {
        if(treap->mLeft)
            clear(treap->mLeft);
        if(treap->mRight)
            clear(treap->mRight);

        delete treap;
        treap = nullptr;
    }
}


template<class T>
size_t TreapNode<T>::sizeOf(TreapNode* treap){
    return !treap ? 0 : treap->mSizeOf;
}

template<class T>
void TreapNode<T>::recalcSizeOf()
{
    mSizeOf += sizeOf(mLeft) + sizeOf(mRight);
}


template<class T>
int TreapNode<T>::exist(ul key){
    int index = 0;
    TreapNode<T>* node = this;

    while (node)
    {
        if(node->mKey == key) return index;
        else if(node->mKey < key)
            node = node->mRight;
        else if(node->mKey > key)
            node = node->mLeft;
        index++;
    }
    return -1;
}

template<class T>
size_t TreapNode<T>::height(){
    size_t index = 0;
    TreapNode<T>* node = this;

    while(TreapNode<T>::sizeOf(node) > 1)
    {
        if(TreapNode<T>::sizeOf(node->mLeft) >= TreapNode<T>::sizeOf(node->mRight))
            node = node->mLeft;
        else
            node = node->mRight;

        index++;
    }
    return index;
}

template<class T>
ul TreapNode<T>::key(size_t idx){
    TreapNode<T>* node = this;
    while(node) {
        if(node->sizeOf(node->mLeft) == idx)
            return node->mKey;
        else if(node->sizeOf(node->mLeft) > idx)
            node = node->mLeft;
        else if (node->sizeOf(node->mLeft) < idx) {
            idx -= sizeOf(node->mLeft) + 1;
            node = node->mRight;
        }
    }
    return 0;
}

template<class T>
size_t TreapNode<T>::levelLenght(size_t level){
    size_t count = 0;
    for(size_t it = 0; it < mSizeOf; it++)
    {
        size_t cur_height = exist(key(it));
        if(cur_height == level)
            count++;
    }
    return count;
}


template<class T>
void TreapNode<T>::setStartPos(int x, int y) {
    startPos.setX(x);
    startPos.setY(y);
}

template<class T>
QPoint TreapNode<T>::getStartPos() const {
    return startPos;
}

template<class T> bool TreapNode<T> ::stepLoopSwitcher;
template<class T> bool TreapNode<T> ::stepButStepEnable;
template<class T> string TreapNode<T> ::forErrors;

template<class T>
void TreapNode<T>::changeLoopState(){
    stepLoopSwitcher = false;
}

template<class T>
void TreapNode<T>::changeStepByStepMode(){
    stepButStepEnable = true;
}

template<class T>
void TreapNode<T>::setDisableStepMode(){
    stepButStepEnable = false;
}

template<class T>
void TreapNode<T>::loopLatency(){
    qDebug() << "Loop latency for step-by-step started" << endl;
    for( ; ; ) {
        QApplication::processEvents();
        if(stepLoopSwitcher == false) break;
    }
    stepLoopSwitcher = true;
}


#endif // TREAPNODE_H
