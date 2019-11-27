#include <iostream>
#include <string>
#include <cctype>

using namespace std;

struct tree;
char share(string str, string &str1, string &str2);
tree* maketree(string str, int flag, tree *s);
void printTree(tree *symb, string &output);
void calc(tree *symb);
void derivative(string &str, string symbol);

struct tree{
    char name;
    int var = 0;
    tree *parent;
    tree *childLeft;
    tree *childRight;
};
