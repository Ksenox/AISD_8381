#ifndef TREE_H
#define TREE_H

#include <string>
#include <sstream>
#include <iostream>
#include <QGraphicsTextItem>
#include <cmath>

#include "dialog.h"

class Tree
{
public:
    Tree();
    void create_node(char val);

    char ret_val();
    Tree* ret_l();
    Tree* ret_r();
    Tree* ret_parent();

    void get_val(char a);
    void get_l(Tree* a);
    void get_r(Tree* a);
    void get_parent(Tree* a);
    int deepmax();
    std::string print_node();

    void displaytree(Dialog *dialog, int deep, int maxdeep, int prevx, int prevy, int posx, int posy);

    //external
    //void drawNode(QGraphicsScene* scene, x, y);

private:
    char val;
    Tree* parent = nullptr;
    Tree* left = nullptr;
    Tree* right = nullptr;

};


#endif // TREE_H
