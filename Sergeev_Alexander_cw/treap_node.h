#ifndef TREAP_NODE_H
#define TREAP_NODE_H

#include <cstdlib>
#include <random>
#include <sstream>


template<typename C>
class treap_node {
private:
    C comparable;
    double index;
    unsigned long weight = 1;

    treap_node* left = nullptr;
    treap_node* right = nullptr;

public:
    unsigned long get_weight();
    void reset_weight();

    static unsigned long depth(treap_node<C>* node);

    treap_node* get_right();
    treap_node* get_left();
    C get_state();
    double get_index();

    std::string* to_string(int pos, int* curr);

    treap_node<C>* trim();

    static void split(treap_node<C>* root, int x, treap_node<C>** left, treap_node<C>** right);
    static treap_node<C>* merge( treap_node<C>* first, treap_node<C>* second);

    static treap_node<C>* insert(treap_node<C>* first, treap_node<C>* second);
    static treap_node<C>* remove(treap_node<C>* root, int x);

    treap_node(C base, double ind);
    explicit treap_node(C base);
    treap_node();
};


template<typename C>
unsigned long treap_node<C>::get_weight() {
    return weight;
}

template<typename C>
void treap_node<C>::reset_weight() {
    unsigned long right_weight = 0;
    unsigned long left_weight = 0;
    if (right != nullptr) {
        right->reset_weight();
        right_weight = right->weight;
    }
    if (left != nullptr) {
        left->reset_weight();
        left_weight = left->weight;
    }
    weight = right_weight + left_weight + 1;
}


template<typename C>
unsigned long treap_node<C>::depth(treap_node<C> *node) {
    if (node == nullptr) {
        return 0;
    } else {
        unsigned long left_depth = depth(node->left);
        unsigned long right_depth = depth(node->right);

        if (left_depth > right_depth) {
            return (left_depth + 1);
        } else {
            return (right_depth + 1);
        }
    }
}


template<typename C>
treap_node<C>* treap_node<C>::get_right() {
    return right;
}

template<typename C>
treap_node<C>* treap_node<C>::get_left() {
    return left;
}

template<typename C>
C treap_node<C>::get_state() {
    return comparable;
}

template<typename C>
double treap_node<C>::get_index() {
    return index;
}


template<typename C>
std::string* treap_node<C>::to_string(int pos, int* curr) {
    std::string* res = new std::string();

    std::stringstream ss;

    if (left != nullptr) {
        ss << *(left->to_string(pos, curr));
    }

    if ((*curr) >= pos) ss << '(' << comparable << ';' << index << "), ";
    (*curr)++;

    if (right != nullptr) {
        ss << *(right->to_string(pos, curr));
    }

    res->append(ss.str());
    return res;
}


template<typename C>
treap_node<C>* treap_node<C>::trim() {
    treap_node<C>* node = new treap_node<C>();
    *node = *this;
    node->left =node->right = nullptr;

    return node;
}


template<typename C>
void treap_node<C>::split(treap_node<C> *root, int x, treap_node<C> **left, treap_node<C> **right) {
    if (root == nullptr) {
        *left = nullptr;
        *right = nullptr;
        return;
    }

    int left_size = ((root->left == nullptr) ? (0) : (root->left->get_weight()));
    int cur_index = left_size + 1;

    if (cur_index <= x) {
        split(root->right, x - cur_index, left, right);
        root->right = *left;

        *left = root;
        return;
    } else {
        split(root->left, x, left, right);
        root->left = *right;

        *right = root;
        return;
    }
}

template<typename C>
treap_node<C> *treap_node<C>::merge(treap_node<C> *first, treap_node<C> *second) {
    if (second == nullptr) return first;
    if (first == nullptr) return second;

    if (first->index > second->index) {
        first->right = merge(first->right, second);
        return first;
    } else {
        second->left = merge(first, second->left);
        return second;
    }
}


template<typename C>
treap_node<C> *treap_node<C>::insert(treap_node<C>* first, treap_node<C>* second) {
    if (first == nullptr) {
        return second;
    }
    if (second == nullptr) {
        return first;
    }

    auto left_tree = new treap_node();
    auto right_tree = new treap_node();

    split(first, first->get_weight(), &left_tree, &right_tree);
    left_tree = merge(left_tree, second);
    return merge(left_tree, right_tree);
}

template<typename C>
treap_node<C> *treap_node<C>::remove(treap_node<C>* root, int x) {
    treap_node<C>* l;
    treap_node<C>* m;
    treap_node<C>* r;

    split(root, x - 1, &l, &r);
    split(r, x, &m, &r);
    return merge(l, r);
}


template<typename C>
treap_node<C>::treap_node(C base) {
    this->comparable = base;
    this->left = this->right = nullptr;
    this->weight = 1;

    this->index = (static_cast<double>(rand()) / (RAND_MAX)) + 1;
}

template<typename C>
treap_node<C>::treap_node() {
    this->left = this->right = nullptr;
    this->weight = 1;
}

template<typename C>
treap_node<C>::treap_node(C base, double ind) {
    this->comparable = base;
    this->index = ind;
    this->left = this->right = nullptr;
    this->weight = 1;
}


#endif //TREAP_TREAP_NODE_H
