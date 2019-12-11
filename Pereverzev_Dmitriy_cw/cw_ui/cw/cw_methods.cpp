#include "cw_methods.h"
struct TREE
{
    string value;
    unsigned int height;
    TREE *left;
    TREE *right;
    TREE(string val)
    {
        value = val;
        left = right = 0;
        height = 1;
    }
};

void bypass(TREE *&tree, string &bin_str)
{
    bin_str += tree->value;
    if (tree->left)
    {
        bin_str += "(";
        bypass(tree->left, bin_str);
    }

    if (tree->right)
    {
        bin_str += "(";
        bypass(tree->right, bin_str);
    }
    bin_str += ")";
}

unsigned char height(TREE *p)
{
    return p ? p->height : 0;
}

int bfactor(TREE *p)
{
    return height(p->right) - height(p->left);
}

void fixheight(TREE *p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

TREE *rotateright(TREE *p, int &steps) // правый поворот вокруг p
{
    steps++;
    TREE *q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

TREE *rotateleft(TREE *q, int &steps) // левый поворот вокруг q
{

    steps++;
    TREE *p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

TREE *balance(TREE *p, int &steps) // балансировка узла p
{
    fixheight(p);
    if (bfactor(p) >= 2)
    {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right, steps);
        return rotateleft(p, steps);
    }
    if (bfactor(p) <= -2)
    {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left, steps);
        return rotateright(p, steps);
    }
    return p; // балансировка не нужна
}

TREE *insert(TREE *p, string val, int &steps) // вставка ключа val в дерево с корнем p
{
    if (!p)
        return new TREE(val);
    if (strcmp(val.c_str(), p->value.c_str()) < 0)
        p->left = insert(p->left, val, steps);
    else
        p->right = insert(p->right, val, steps);
    return balance(p, steps);
}

TREE *insert_2(TREE *p, string val) // вставка ключа val в дерево с корнем p
{
    if (!p)
        return new TREE(val);
    if (strcmp(val.c_str(), p->value.c_str()) < 0)
        p->left = insert_2(p->left, val);
    else
        p->right = insert_2(p->right, val);
    return p;
}

string gen_random(int num)
{

    srand(chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
    string rand_data = "";
    int a;
    for (int i = 0; i < num; i++)
    {
        do
        {
            a = rand() % 89999 + 10000;
        } while (strstr(rand_data.c_str(), to_string(a).c_str()) != NULL);
        rand_data += to_string(a) + " ";
    }
    return rand_data;
}

//8 9 11 15 19 20 21 7 3 2 1 5 6 4 13 14 10 12 17 16 18