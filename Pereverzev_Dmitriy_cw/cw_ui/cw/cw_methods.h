#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <chrono>
#include <random>

using namespace std;

struct TREE;

void bypass(TREE *&tree, string &bin_str);
unsigned char height(TREE *p);
int bfactor(TREE *p);
void fixheight(TREE *p);
TREE *rotateright(TREE *p, int &steps);        // правый поворот вокруг p
TREE *rotateleft(TREE *q, int &steps);         // левый поворот вокруг q
TREE *balance(TREE *p, int &steps);            // балансировка узла p
TREE *insert(TREE *p, string val, int &steps); // вставка ключа val в дерево с корнем p
TREE *insert_2(TREE *p, string val);           // вставка ключа val в дерево с корнем p
string gen_random(int num);