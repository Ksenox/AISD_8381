#ifndef UTILS_TREE_H
#define UTILS_TREE_H
#include <string>
#include "utils_linked.h"
#include "utils_vector.h"

template <class T = int>
class utils_tree
{
public:
    utils_tree(std::string& str);
    void clean();
    void insert(T data);
    void remove(T data);
    bool search(T key);
    bool is_bst();
    bool is_pyramid();
    int max_depth();
    ~utils_tree();
    node<T>* root;
    bool is_bst_stepped(utils_vector<node<T>*>& v, node<T>* n, T min, T max);
    bool is_pyramid_stepped(utils_vector<node<T>*>& v, node<T>* n, int max);
private:
    bool parse_tree(node<T>*& n, std::string &s, int &i);
    void clean(node<T>* n);
    void insert(node<T>*& n, T data);
    void remove(node<T>*& n, T data);
    node<T>* search(node<T>* n, T key);
    bool is_bst(node<T>* n, T min, T max);
    bool is_pyramid(node<T>* n, int max);
    int max_depth(node<T>* n, int i);
};


template<class T>
utils_tree<T>::utils_tree(std::string &str)
    : root(new node<T>())
{
    int i = 0;
    if(parse_tree(root, str, i))
    {
        delete root;
        root = nullptr;
    }
}

template<class T>
void utils_tree<T>::clean()
{
    clean(root);
}

template<class T>
void utils_tree<T>::insert(T data)
{
    insert(root, data);
}

template<class T>
void utils_tree<T>::remove(T data)
{
    remove(root, data);
}

template<class T>
bool utils_tree<T>::search(T key)
{
    return search(root, key) != nullptr;
}

template<class T>
bool utils_tree<T>::is_bst()
{
    return is_bst(root->left, INT_MIN, root->data) && is_bst(root->right, root->data, INT_MAX);
    // Костыль. Заменить INT_MIN/MAX на гендеро-нейтральный тип.
}

template<class T>
bool utils_tree<T>::is_pyramid()
{
    return is_pyramid(root->left, root->data) && is_pyramid(root->right, root->data);
}

template<class T>
int utils_tree<T>::max_depth()
{
    return max_depth(root, 1);
}

template<class T>
utils_tree<T>::~utils_tree()
{ // He protec
    clean(); // He attak
} // He destroy

template<class T>
bool utils_tree<T>::is_bst_stepped(utils_vector<node<T>*> &v, node<T> *n, T min, T max)
{
    if (!n) return true;
    v.push_back(n);
    if (n->data <= min || n->data >= max) return false;
    return is_bst_stepped(v, n->left, min, n->data) && is_bst_stepped(v, n->right, n->data, max);
}

template<class T>
bool utils_tree<T>::is_pyramid_stepped(utils_vector<node<T>*> &v, node<T> *n, int max)
{
    if (!n) return true;
    v.push_back(n);
    if (n->data >= max) return false;
    return is_pyramid_stepped(v, n->left, n->data) && is_pyramid_stepped(v, n->right, n->data);
}

// PRIVATE

template<class T>
bool utils_tree<T>::parse_tree(node<T>*& n, std::string &s, int &i) {
    if (i >= s.size() || s[static_cast<unsigned long>(i)] == ')')
    {
        delete n;
        n = nullptr;
        return false;
    }
    if (s[static_cast<unsigned long>(i)] == '(')
    {
        i++;
    }
    int num;
    int start = i;
    while (i != static_cast<int>(s.size()) && s[static_cast<unsigned long>(i)] != '(' && s[static_cast<unsigned long>(i)] != ')')
    {
        i++;
    }
    try
    {
        num = stoi(s.substr(static_cast<unsigned long>(start), static_cast<unsigned long>(i) - static_cast<unsigned long>(start)));
    }
    catch (...)
    {
        return true;
    }
    n->data = num;
    n->left = new node<T>();
    n->right = new node<T>();
    if(parse_tree(n->left, s, i) || parse_tree(n->right, s, i)) return true;
    if (s[static_cast<unsigned long>(i)] == ')')
    {
        i++;
    }
    return false;
}


template<class T>
void utils_tree<T>::clean(node<T> *n)
{
    if (!n) return;
    clean(n->left);
    clean(n->right);
    delete root;
}

template<class T>
void utils_tree<T>::insert(node<T>*& n, T data)
{
    if (!n)
    {
        n = new node<T>(data);
    }
    else if (n->data < data)
    {
        insert(n->left, data);
    }
    else if (n->data > data)
    {
        insert(n->right, data);
    }
}

template<class T>
void utils_tree<T>::remove(node<T>*& n, T data)
{
    if (!n) return;
    if (data < n->key)
    {
        deleteNode(n->left, data);
    }
    else if (data > n->key)
    {
        deleteNode(root->right, data);
    }
    else
    {
        if (!n->left)
        {
            node<T>* temp = n->right;
            delete n;
            n = temp;
        }
        else if (!n->right)
        {
            node<T>* temp = n->left;
            delete n;
            n = temp;
        }
        node<T>* min = n->right;
        if (!min->left)
        {
            n->right = nullptr;
        }
        else
        {
            node<T>* t = min;
            while(t->left->left)
            {
                t = n->left;
            }
            min = t->left;
            t->left = nullptr;
        }
        n->data = min->data;
        delete min;
    }
}


template<class T>
node<T>* utils_tree<T>::search(node<T> *n, T key)
{
    if (!n) return nullptr;
    if (n->data == key) return n;
    return search(n->left, key) | search(n->right, key);
}

template<class T>
bool utils_tree<T>::is_bst(node<T> *n, T min, T max)
{
    if (!n) return true;
    if (n->data <= min || n->data >= max) return false;
    return is_bst(n->left, min, n->data) && is_bst(n->right, n->data, max);
}

template<class T>
bool utils_tree<T>::is_pyramid(node<T> *n, int max)
{
    if (!n) return true;
    if (n->data >= max) return false;
    return is_pyramid(n->left, n->data) && is_pyramid(n->right, n->data);
}

template<class T>
int utils_tree<T>::max_depth(node<T> *n, int i)
{
    if (!n) return i;
    int l = max_depth(n->left, i + 1);
    int r = max_depth(n->right, i + 1);
    if (l > r) return l;
    else return r;
}


#endif // UTILS_TREE_H
