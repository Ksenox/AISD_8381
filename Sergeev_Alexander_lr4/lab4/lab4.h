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

public:
    string base;
    string state;
    static_tree<char>* tree;

    void launch(string& str);
    void rush();
    void step(int i);
};


#endif //LAB4_LAB4_H
