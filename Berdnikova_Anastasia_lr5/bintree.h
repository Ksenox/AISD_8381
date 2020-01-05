#ifndef BINTREE_H
#define BINTREE_H

#include <string>
#include <QColor>

#include "node.h"
#include "array_list.h"

using namespace std;

int max_depth(Node *n, int i);
bool parse_tree(Node*& n, std::string &s, int &i);
void insert_old(Node*& n, int data);
void insert_step(array_list*& arr, Node*& root, Node*& n, int data);
void remove_old(Node*& n, int data);
void remove_step(array_list*& arr, Node*& root, Node*& n, int data);
Node* copy(Node* n);
string into_string(Node* n);

int getsize(Node* p);
void fixsize(Node* p);
Node* rotateright(Node* p);
Node* rotateleft(Node* q);
Node* insert_classic(Node* p, int k);
Node* insertroot(Node* p, int k);
Node* insert(array_list*& arr, Node*& root, Node* p, int k);
Node* join(Node* p, Node* q);
Node* remove(array_list*& arr, Node*& root, Node* p, int k);

#endif // BINTREE_H
