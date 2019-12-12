#ifndef CURR_TREE_NODE_H
#define CURR_TREE_NODE_H

#include "stack.h"
#include <cstdlib>
#include <random>


template<typename C>
class tree_node {
private:
    C comparable;
    double index;
    unsigned long weight = 1;

    tree_node* left = nullptr;
    tree_node* right = nullptr;

public:
    unsigned long get_weight();
    void reset_weight();

    unsigned long depth(tree_node<C>* node);

    tree_node* get_right() {
        return right;
    }

    tree_node* get_left() {
        return left;
    }

    C get_state() {
        return comparable;
    }

    double get_index() {
        return index;
    }

    tree_node<C>* trim();

    static bool is(tree_node<C>* node, C elem);

    static void split(tree_node<C>* root, C comp, tree_node<C>** left, tree_node<C>** right);
    static tree_node<C>* merge( tree_node<C>* first, tree_node<C>* second);

    static tree_node<C>* insert(tree_node<C>* first, tree_node<C>* second);

    explicit tree_node(C base);
    tree_node();
};


template<typename C>
unsigned long tree_node<C>::get_weight() {
    return weight;
}

template<typename C>
void tree_node<C>::reset_weight() {
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
unsigned long tree_node<C>::depth(tree_node<C> *node) {
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
tree_node<C>* tree_node<C>::trim() {
    auto node = new tree_node<C>();
    *node = *this;
    node->left = node->right = nullptr;

    return node;
}


template<typename C>
bool tree_node<C>::is(tree_node<C>* node, C elem) {
    if (!node) return false;
    if (elem == node->get_state())
        return true;
    if (elem < node->get_state())
        return is(node->get_left(), elem);
    else
        return is(node->get_right(), elem);
}


template<typename C>
void tree_node<C>::split(tree_node<C> *root, C comp, tree_node<C> **left, tree_node<C> **right) {
    if (root == nullptr) {
        *left = nullptr;
        *right = nullptr;
        return;
    } else if (comp > root->get_state()) {
        split(root->right, comp, left, right);
        root->right = *left;

        *left = root;
        return;
    } else {
        split(root->left, comp, left, right);
        root->left = *right;

        *right = root;
        return;
    }
}

template<typename C>
tree_node<C> *tree_node<C>::merge(tree_node<C> *first, tree_node<C> *second) {
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
tree_node<C> *tree_node<C>::insert(tree_node<C>* first, tree_node<C>* second) {
    if (first == nullptr) {
        return second;
    }
    if (second == nullptr) {
        return first;
    }

    auto left_tree = new tree_node();
    auto right_tree = new tree_node();

    split(first, second->comparable, &left_tree, &right_tree);
    left_tree = merge(left_tree, second);
    return merge(left_tree, right_tree);
}


template<typename C>
tree_node<C>::tree_node(C base) {
    this->comparable = base;
    this->left = this->right = nullptr;
    this->weight = 1;

    this->index = ((double) rand() / (RAND_MAX)) + 1;
}

template<typename C>
tree_node<C>::tree_node() {
    this->left = this->right = nullptr;
    this->weight = 1;
}


#endif //CURR_TREE_NODE_H
