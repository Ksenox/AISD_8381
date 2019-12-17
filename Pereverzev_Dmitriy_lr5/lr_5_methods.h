#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

struct TREE;

void push(TREE* &tree, int value);
void del_elem(TREE* &tree, int value);
TREE*& find_elem(TREE* &tree, int value);
