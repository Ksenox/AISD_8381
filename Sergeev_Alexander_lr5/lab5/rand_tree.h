#ifndef CURR_RAND_TREE_H
#define CURR_RAND_TREE_H

#include <cmath>
#include <experimental/type_traits>
#include <stdexcept>
#include <sstream>
#include "tree_node.h"


template<typename C>
class rand_tree {
private:
    tree_node<C>* root = nullptr;

public:
    unsigned long max_depth();
    unsigned long theory_depth();
    unsigned long get_weight();

    tree_node<C>* get_root();
    tree_node<C>** get_bi_root();

    void join(tree_node<C>* node, stack<tree_node<C>*>* stck);
    void add(C value);

    explicit rand_tree();

    explicit rand_tree(std::string* tree_string, stack<C>* stck);
};


template<typename C>
using less_than_t = decltype(std::declval<C>() < std::declval<C>());

template<typename C>
using more_than_t = decltype(std::declval<C>() > std::declval<C>());

template<typename C>
constexpr bool comparable = std::experimental::is_detected<less_than_t, C>::value &&  std::experimental::is_detected<more_than_t, C>::value;


template<typename C>
unsigned long rand_tree<C>::max_depth() {
    return root->depth(root);
}

template<typename C>
unsigned long rand_tree<C>::theory_depth() {
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
unsigned long rand_tree<C>::get_weight() {
    return root->get_weight();
}


template<typename C>
tree_node<C>* rand_tree<C>::get_root() {
    return root;
}

template<typename C>
tree_node<C>** rand_tree<C>::get_bi_root() {
    return &root;
}


template<typename C>
void rand_tree<C>::join(tree_node<C>* node, stack<tree_node<C>*>* stck) {
    if (root == nullptr) {
        root = node;
    } else {
        root = tree_node<C>::insert(root, node->trim());

        if (stck == nullptr) {
            if (node->get_left() != nullptr) join(node->get_left(), stck);
            if (node->get_right() != nullptr) join(node->get_right(), stck);
        } else {
            if (node->get_right() != nullptr) stck->push(node->get_right());
            if (node->get_left() != nullptr) stck->push(node->get_left());
        }
    }
}

template<typename C>
void rand_tree<C>::add(C value) {
    auto node = new tree_node<C>(value);
    if (root == nullptr) {
        root = node;
    } else {
        if (!tree_node<C>::is(root, value)) {
            root = tree_node<C>::insert(root, node);
            root->reset_weight();
        }
    }
}


template<typename C>
rand_tree<C>::rand_tree() {
    if constexpr(!comparable<C>){
        throw std::runtime_error("Tree nodes can not be compared by the key!");
    }
}

template<typename C>
rand_tree<C>::rand_tree(std::string* tree_string, stack<C>* stck) {
    if constexpr(!comparable<C>){
        throw std::runtime_error("Tree nodes can not be compared by the key!");
    }

    try {
        std:: string delimiter = ", ";
        std::string range = " .. ";
        size_t pos = 0;
        size_t erase_pos = 0;
        std::string token;

        do {
            pos = tree_string->find(delimiter);
            erase_pos = ((pos == std::string::npos) ? tree_string->length() : pos);
            token = tree_string->substr(0, pos);

            unsigned long tos = token.find(range);
            unsigned long npos = std::string::npos;
            if (tos != npos) {
                if (std::is_same<C, std::string>::value) throw std::runtime_error("Ranges are not available for strings yet.");

                C first, second;
                std::stringstream first_part(token.substr(0, tos));
                std::stringstream second_part(token.substr(tos + range.length(), token.length() - 1));
                first_part >> first;
                second_part >> second;

                for (C i = first; i <= second; i += 1) {
                    if (stck == nullptr) {
                        this->add(i);
                    } else {
                        stck->push(i);
                    }
                }
            } else {
                C number;
                std::stringstream num(token);
                std::string str = num.str();
                num >> number;
                if (stck == nullptr) {
                    this->add(number);
                } else {
                    stck->push(number);
                }
            }

            tree_string->erase(0, erase_pos + delimiter.length());
        } while (tree_string->length() != 0);
    } catch (std::runtime_error re) {
        throw std::runtime_error(re.what());
    } catch (...) {
        throw std::runtime_error("Tree string contains error. Tree can not be built.");
    }
}


#endif //CURR_RAND_TREE_H
