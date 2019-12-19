#ifndef TREAP_H
#define TREAP_H

#include <cmath>
#include <experimental/type_traits>
#include <stdexcept>
#include <sstream>
#include "treap_node.h"
#include "generator.h"


template<typename C>
class treap {
private:
    treap_node<C>* root = nullptr;

public:
    unsigned long max_depth();
    unsigned long theory_depth();
    unsigned long get_weight();

    treap_node<C>* get_root();

    void add(C value);
    void add(treap_node<C>* value);
    void remove(int index);

    void merge(treap<C>* another);
    bool split(int pos, treap<C>* stat, treap<C>* another);

    std::string* to_string(int pos);

    explicit treap();
};


template<typename C>
using less_than_t = decltype(std::declval<C>() < std::declval<C>());

template<typename C>
using more_than_t = decltype(std::declval<C>() > std::declval<C>());

template<typename C>
constexpr bool comparable = std::experimental::is_detected<less_than_t, C>::value &&  std::experimental::is_detected<more_than_t, C>::value;


template<typename C>
unsigned long treap<C>::max_depth() {
    return treap_node<C>::depth(root);
}

template<typename C>
unsigned long treap<C>::theory_depth() {
    unsigned long weight = get_weight();
    unsigned long grade = 0;
    unsigned int power = 0;
    while (grade < weight) {
        power++;
        grade = static_cast<unsigned long>(pow(2, power) - 1);
    }
    return power;
}

template<typename C>
unsigned long treap<C>::get_weight() {
    return root->get_weight();
}


template<typename C>
treap_node<C>* treap<C>::get_root() {
    return root;
}


template<typename C>
void treap<C>::add(C value) {
    treap_node<C>* node = new treap_node<C>(value);
    return this->add(node);
}

template<typename C>
void treap<C>::add(treap_node<C>* node) {
    if (root == nullptr) {
        root = node;
    } else {
        root = treap_node<C>::insert(root, node);
        if (root != nullptr) root->reset_weight();
    }
}

template<typename C>
void treap<C>::remove(int index) {
    root = treap_node<C>::remove(root, index);

    if (root != nullptr) root->reset_weight();
}


template<typename C>
void treap<C>::merge(treap<C>* another) {
    if (root == nullptr) {
        root = another->root;
        return;
    }
    if ((another == nullptr) || (another->root == nullptr)) return;

    root = treap_node<C>::merge(root, another->get_root());

    if (root != nullptr) root->reset_weight();
}

template<typename C>
bool treap<C>::split(int pos, treap<C>* stat, treap<C>* another) {
    if ((root == nullptr) || (static_cast<unsigned>(pos) > root->get_weight())) return false;

    treap_node<C>* first_root = new treap_node<C>;
    treap_node<C>* second_root = new treap_node<C>;

    treap_node<C>::split(root, pos, &first_root, &second_root);
    if (first_root != nullptr) first_root->reset_weight();
    if (second_root != nullptr) second_root->reset_weight();

    stat->root = first_root;
    another->root = second_root;

    return true;
}


template<typename C>
std::string* treap<C>::to_string(int pos) {
    std::string* res = new std::string();
    if (root == nullptr) {
        res->append("(0;0.0)");
        return res;
    }
    int dest = 0;
    res->append(*(root->to_string(pos, &dest)));
    *res = res->substr(0, res->length() - 2);

    return res;
}


template<typename C>
treap<C>::treap() {
    generator::ground();

    if constexpr(!comparable<C>){
        throw std::runtime_error("Treap nodes can not be compared by the key!");
    }
}


#endif //TREAP_H
