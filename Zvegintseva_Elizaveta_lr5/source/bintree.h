//
// Created by therealyou on 02.10.2019.
//

#ifndef LAB3_BINTREE_H
#define LAB3_BINTREE_H

#include <iostream>
#include <string>
#include <vector>
#include <QStringList>
#include <QColor>
#include <string>
#include "array_list.h"
#include "node.h"

using namespace std;

class binTree {
public:
    Node* root = new Node;

    int treeInit(QStringList lst, unsigned int& index);
    Node* enterBT();
    int checkTwoEqualElem();
    void lkp();
    void printLKP();
    //
    int max_depth(Node *n, int i);
    bool parse_tree(Node*& n, std::string &s, int &i);
    void get_elems(array_list& vec, Node* n);
    bool get_duplicates(array_list& vec, Node*& first, Node*& second);
    void insert(Node*& n, int data);
    void remove(Node*& n, int data);
    Node* copy(Node* n);
    string into_string(Node* n);
};


#endif //LAB3_BINTREE_H
