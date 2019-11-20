#include "lr_4_methods.h"

//(1(2(4))(3))(ab)(cd)

struct TREE
{
    string value;
    TREE *left;
    TREE *right;
};

struct Q
{
    TREE **leaf;
    int size;
};

int test_4(string forest)
{
    int open = 0;
    int close = 0;

    for (int i = 0; i < forest.size(); i++)
    {
        //	2(1)
        if (forest[i] == '(')
            open++;
        if (forest[i] == ')')
            close++;
    }
    for (int i = 0; i < forest.size() - 1; i++)
    {
        //	1
        if (forest[i] == '(' && (forest[i + 1] == '(' || forest[i + 1] == ')'))
        {
            return 1;
        }
        //4
        if (forest[i] == ')' && (forest[i + 1] != '(' && forest[i + 1] != ')'))
        {
            return 4;
        }
    }

    //	2(2)
    if (open != close)
        return 2;

    //	3
    if (forest[0] != '(')
        return 3;
    return 0;
}

void bypass_4(TREE *&tree, string &bin_str)
{
    cout << tree->value;
    bin_str += tree->value;
    if (tree->left)
    {
        cout << '(';
        bin_str += "(";
        bypass_4(tree->left, bin_str);
    }

    if (tree->right)
    {
        cout << '(';
        bin_str += "(";
        bypass_4(tree->right, bin_str);
    }
    cout << ')';
    bin_str += ")";
}
//(1(2(3(4(5(6(7(8(9(10)(23))))(19(20(24)(21)))))(18)))(11(12(13(14(16))(15(17(20))))))))
//(1(2(3(4(5(6(7(8(9(10(23))))(19(20(24(21))))))(18)))(11(12(13(14(16)(15(17(20)))))))))
//(1(2)(3(5)(6))(4))(11(22(33(44)(55))))
//(1(2(3(5(6))(4))(11(22(33(44(55)))))))
//(1(2(3(5(6))(4))(11(22(33(44(55))))))))
int create_4(int &ind, int *&lvl, string *&arr_val, string forest)
{
    string value;
    char buffer;
    int i = 0;
    for (; i < forest.length(); i++)
    {
        buffer = forest[i];
        if (value != "" && (buffer == ')' || buffer == '('))
        {
            lvl[ind + 1] = lvl[ind];
            arr_val[ind] = value;
            value = "";
            ind++;
            cout << lvl[ind - 1] << endl;
        }
        if (buffer == '(')
            lvl[ind] += 1;
        if (buffer == ')')
            lvl[ind] -= 1;
        if (buffer != ')' && buffer != '(')
            value += buffer;
        /*
        if (lvl[ind] < 0)
        {
            return 0;
        }
        */
    }
    return 0;
}
int add_4(TREE *&tree, int top, int *lvl, string *arr_val, int &index)
{
    int lvl_index = lvl[index];
    int next_lvl = -2;
    while (true)
    {
        if (index == top)
            return -2;
        if (lvl[index] >= lvl[index - 1])
        {
            next_lvl = push_4(tree, top, lvl, arr_val, index);
            if (lvl_index == next_lvl && index != top)
                next_lvl = push_4(tree->right, top, lvl, arr_val, index);
        }
        else
            return lvl[index];

        if (next_lvl == lvl_index && index != top)
        {
            next_lvl = push_4(tree->right, top, lvl, arr_val, index);
        }
        else
            return lvl[index];
    }
}

int push_4(TREE *&tree, int top, int *lvl, string *arr_val, int &index)
{
    TREE *NEW = new TREE;
    NEW->left = NULL;
    NEW->right = NULL;
    NEW->value = arr_val[index];
    if (tree == NULL)
    {
        tree = NEW;
    }
    else
    {
        if (tree->left == NULL)
            tree->left = NEW;
        else
            tree->right = NEW;
    }
    index += 1;
    int next_lvl = add_4(NEW, top, lvl, arr_val, index);
    return next_lvl;
}

void width_4(TREE *tree, string &bypass_width)
{
    if (tree == NULL)
        return;
    Q q;
    q.leaf = new TREE *[100];
    q.leaf[0] = tree;
    q.size = 1;
    while (q.size != 0)
    {
        TREE **new_leaf = new TREE *[100];
        int new_size = 0;
        for (int i = 0; i < q.size; i++)
        {
            if (q.leaf[i]->left != NULL)
            {
                new_leaf[new_size] = q.leaf[i]->left;
                new_size++;
                if (q.leaf[i]->right != NULL)
                {
                    new_leaf[new_size] = q.leaf[i]->right;
                    new_size++;
                }
            }
            cout << q.leaf[i]->value << " | ";
            bypass_width += q.leaf[i]->value;
            bypass_width += "\n";
        }
        q.size = new_size;
        q.leaf = new_leaf;
    }
}
