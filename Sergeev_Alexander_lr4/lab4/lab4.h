//
// Created by alex on 11/7/19.
//

#ifndef LAB4_LAB4_H
#define LAB4_LAB4_H

#include <bits/stdc++.h>
#include "static_tree.h"

using namespace std;

class lab4 {
private:
    string templ;

    static_tree<char>* temp;
    measuring_array<int>* locator;
    int new_pos;
    static_tree<char>* sub_tree;
    static_tree<char>* f1;
    static_tree<char>* f2;
    static_tree<char>* f3;
    static_tree<char>* f4;
    static_tree<char>* copy;
    bool first_pair_equal;
    bool second_pair_equal;

public:
    string base;
    string state;
    static_tree<char>* tree;

    void launch(string& str);
    void rush();
    void step(int* i);
};


#endif //LAB4_LAB4_H
