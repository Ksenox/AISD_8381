#ifndef UNTITLED1_TREE_ITEM_H
#define UNTITLED1_TREE_ITEM_H


#include <ostream>

template<typename T>
class tree_node {
private:
    bool isLeaf;
    T data;

public:
    explicit tree_node(T data, bool isLeaf);
    virtual ~tree_node();

    bool is_leaf();
    T get_trunk();
    void setTrunk(T item);

    template<typename V>
    friend ostream &operator<<(ostream &os, const tree_node<V> &node);
};



template<typename T>
tree_node<T>::tree_node(T data, bool isLeaf) {
    this->isLeaf = isLeaf;
    this->data = data;
}

template<typename T>
tree_node<T>::~tree_node() {}



template<typename T>
bool tree_node<T>::is_leaf() {
    return isLeaf;
}

template<typename T>
T tree_node<T>::get_trunk() {
    return data;
}

template<typename T>
void tree_node<T>::setTrunk(T item) {
    data = item;
}

template<typename T>
ostream &operator<<(ostream &os, const tree_node<T> &node) {
    return os << node.data;
}


#endif //UNTITLED1_TREE_ITEM_H
