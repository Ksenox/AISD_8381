#ifndef BTREE_H
#define BTREE_H

#include "stack.h"
#include "infixtopostfix.h"

struct Node {
    char value;
    struct Node* left, *right;
};

struct BinTree {
    struct Node *root;
    int deep;
};

struct Node* constructTree(string & postfix);
int countDeep(struct Node *&node);
string inorder(struct Node *t);
void postorder(struct Node *t, Stack<char>&, vector<string>&,string &);
int eval(struct Node* root, string &);

void calc(char value, Stack<char>& stack, vector<string>&, string&);
string Diff (struct Node *root, char var);
void simplifying(string & str);

#endif // BTREE_H
