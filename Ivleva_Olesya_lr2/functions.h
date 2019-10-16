#include <string>
#include <iostream>
using namespace std;

struct hlist {
    int flag;
    hlist* ptr_next;
    union {
        char symb;
        hlist *ptr_child;
    };
};

hlist* r_make(string &mas, int &start, int &err);
hlist* del_x(hlist *now, char &x, string &output,bool info);
void print_list(hlist *now, string &output);
