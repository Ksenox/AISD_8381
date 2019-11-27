#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;
struct TREE;
struct Q;

int add_4(TREE *&tree, int top, int *lvl, string *arr_val, int &index);
int push_4(TREE *&tree, int top, int *lvl, string *arr_val, int &index);
int create_4(int &ind, int *&lvl, string *&arr_val, string forest);
void bypass_4(TREE *&tree, string &bin_str);
int test_4(string forest);
void width_4(TREE *tree, string &bypass_width);