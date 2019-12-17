#include "lr_5_methods.h"
struct TREE_5
{
    string value;
    TREE_5 *left;
    TREE_5 *right;
};

void push_5(TREE_5 *&tree, string value)
{
    if (tree == NULL)
    {
        tree = new TREE_5;

        tree->value = value;
        tree->left = NULL;
        tree->right = NULL;
    }
    else
    {

        if (strcmp(tree->value.c_str(), value.c_str()) < 0)
            push_5(tree->right, value);
        else if (strcmp(tree->value.c_str(), value.c_str()) > 0)
            push_5(tree->left, value);
    }

    return;
}

void del_elem_5(TREE_5 *&tree, string value)
{
    TREE_5 **buffer;
    if (tree->left)
        if (tree->left->value == value)
            buffer = &tree->left;

    if (tree->right)
        if (tree->right->value == value)
            buffer = &tree->right;

    del_help_5(buffer, value);
}

void del_help_5(TREE_5 **buffer, string value)
{
    if ((*buffer)->left == NULL && (*buffer)->right == NULL)
    {
        (*buffer) = NULL;
        return;
    }

    //2 - only left branch
    if ((*buffer)->left != NULL && (*buffer)->right == NULL)
    {
        (*buffer) = (*buffer)->left;
        return;
    }
    //3 - have right branch
    if ((*buffer)->right != NULL)
    {
        //3.1 - right leaf has no left branch
        if ((*buffer)->right->left == NULL)
        {
            (*buffer)->right->left = (*buffer)->left;
            (*buffer) = (*buffer)->right;
            return;
        }

        //3.2 - right leaf has left branch
        else
        {

            TREE_5 **to_left = &((*buffer)->right);
            while ((*to_left)->left->left != NULL)
                to_left = &((*to_left)->left);
            // _1
            TREE_5 *help = (*to_left)->left->right;
            // _2
            (*to_left)->left->left = (*buffer)->left;
            (*to_left)->left->right = (*buffer)->right;
            (*buffer) = (*to_left)->left;
            (*to_left)->left = help;
        }
        return;
    }
}

TREE_5 *&find_elem_5(TREE_5 *&tree, string value)
{
    TREE_5 *exist = NULL;
    if (tree != NULL)
    {

        if (strcmp(tree->value.c_str(), value.c_str()) < 0)
            exist = find_elem_5(tree->right, value);
        else if (strcmp(tree->value.c_str(), value.c_str()) > 0)
            exist = find_elem_5(tree->left, value);
        else if (tree->value == value)
        {
            exist = tree;
            return exist;
        }
    }
    //del elem
    if (exist != NULL)
    {
        del_elem_5(tree, value);
        exist = NULL;
    }

    return exist;
}

void bypass_5(TREE_5 *&tree, string &bin_str)
{
    bin_str += tree->value;
    if (tree->left)
    {
        bin_str += "(";
        bypass_5(tree->left, bin_str);
    }

    if (tree->right)
    {
        bin_str += "(";
        bypass_5(tree->right, bin_str);
    }
    bin_str += ")";
}

int test_5(string str)
{

    return 0;
}
//8 9 11 15 19 20 21 7 3 2 1 5 6 4 13 14 10 12 17 16 18