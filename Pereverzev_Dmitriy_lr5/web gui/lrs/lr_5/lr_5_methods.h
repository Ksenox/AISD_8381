#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

struct TREE_5;

void push_5(TREE_5 *&tree, int value);
void del_elem_5(TREE_5 *&tree, int value);
TREE_5 *&find_elem_5(TREE_5 *&tree, int value);
void bypass_5(TREE_5 *&tree, string &bin_str);
void del_help_5(TREE_5 **buffer, int value);
int test_5(string str);
