#ifndef UTILS_TREE_H
#define UTILS_TREE_H
#include <string>
#include "utils_linked.h"
#include "utils_vector.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

template <class T = int>
class utils_tree
{
public:
    utils_tree(std::string& str);
    utils_tree(utils_tree<T>& copy);
    void clean();
    void insert(T data);
    void remove(T data);
    bool search(T key);
    bool is_bst();
    bool is_pyramid();
    int max_depth();
    ~utils_tree();
    node<T>* root;
    vector<node<T>*> undolist;
    vector<node<T>*> redolist;
    bool undo();
    bool redo();
    void save();
    void load();
    bool is_bst_stepped(utils_vector<node<T>*>& v, node<T>* n, T min, T max);
    bool is_pyramid_stepped(utils_vector<node<T>*>& v, node<T>* n, int max);
    void to_optimal();
    void insertbalanced(T data);
    void removebalanced(T data);
    void go_darker();
    std::string node_string();
    std::string node_string(node<T>* n);
private:
    bool parse_tree(node<T>*& n, std::string &s, int &i);
    void clean(node<T>* n);
    void insert(node<T>*& n, T data);
    void remove(node<T>*& n, T data);
    node<T>* search(node<T>* n, T key);
    bool is_bst(node<T>* n, T min, T max);
    bool is_pyramid(node<T>* n, int max);
    int max_depth(node<T>* n, int i);
    void get_data(utils_vector<T>& vec, node<T>* n);
    void go_darker(node<T>* n);
    //
public:
    int height(node<T>* n);
    int bfactor(node<T>* n);
    void fixheight(node<T>* n);
    node<T>* rotateleft(node<T>* n);
    node<T>* rotateright(node<T>* n);
    node<T>* balance(node<T>* n);
    node<T>* findmin(node<T>* n);
    node<T>* removemin(node<T>* n);
    node<T>* insertbalanced(node<T>* n, T data);
    node<T>* removebalanced(node<T>* n, T data);
    node<T>* save(node<T>* n);
    void go_red(node<T>* n);
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
    undolist = vector<node<T>*>();
    redolist = vector<node<T>*>();
}

template<class T>
utils_tree<T>::utils_tree(utils_tree<T> &copy)
{

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
bool utils_tree<T>::undo()
{
    if (undolist.empty()) return false;
    redolist.push_back(save(root));
    root = undolist.back();
    undolist.pop_back();
    return true;
}

template<class T>
bool utils_tree<T>::redo()
{
    if (redolist.empty()) return false;
    undolist.push_back(save(root));
    root = redolist.back();
    redolist.pop_back();
    return true;
}

template<class T>
void utils_tree<T>::save()
{
    if (root)
    {
        undolist.push_back(save(root));
        redolist.clear();
    }
}

template<class T>
void utils_tree<T>::load()
{
    ifstream myfile;
    myfile.open("backup.txt");
    if (myfile.is_open())
    {
        string s;
        myfile >> s;
        int i = 0;
        root = new node<T>();
        undolist.clear();
        redolist.clear();
        parse_tree(root, s, i);
    }
}

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

template<class T>
void utils_tree<T>::to_optimal()
{
    utils_vector<int> datas = utils_vector<int>();
    get_data(datas, root);
    //datas.sort();
    delete root;
    root = new node<T>(datas[0]);
    for (int i = 1; i < datas.size(); i++)
    {
        insertbalanced(datas[i]);
    }
}

template<class T>
void utils_tree<T>::insertbalanced(T data)
{
    if (search(data)) return;
    if (!root)
    {
        root = new node<T>(data);
        root->color = QColor::fromRgb(255, 0, 255);
        return;
    }
    if (data < root->data) root->left = insertbalanced(root->left, data);
    else root->right = insertbalanced(root->right, data);
    root = balance(root);
}

template<class T>
void utils_tree<T>::removebalanced(T data)
{
    root = removebalanced(root, data);
}

template<class T>
void utils_tree<T>::go_darker()
{
    go_darker(root);
}

template<class T>
std::string utils_tree<T>::node_string()
{
    return "Tree: {" + node_string(root) + "}";
}

// PRIVATE

template<class T>
bool utils_tree<T>::parse_tree(node<T>*& n, std::string &s, int &i) {
    if (i >= s.size() || s[i] == ')')
    {
        delete n;
        n = nullptr;
        return false;
    }
    if (s[i] == '(')
    {
        i++;
    }
    if (s[i] == ')')
    {
        i++;
        delete n;
        n = nullptr;
        return false;
    }
    int num;
    int start = i;
    while (i != s.size() && s[i] != '(' && s[i] != ')')
    {
        i++;
    }
    try
    {
        num = stoi(s.substr(start, i - start));
    }
    catch (...)
    {
        return true;
    }
    n->data = num;
    n->left = new node<T>();
    n->right = new node<T>();
    if(parse_tree(n->left, s, i) || parse_tree(n->right, s, i)) return true;
    if (s[i] == ')')
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
    if (data < n->data)
    {
        remove(n->left, data);
    }
    else if (data > n->data)
    {
        remove(n->right, data);
    }
    else
    {
        if (!n->left && n->right)
        {
            node<T>* temp = n->right;
            delete n;
            n = temp;
        }
        else if (!n->right && n->left)
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
    node<T>* l = search(n->left, key);
    if (l) return l;
    node<T>* r = search(n->right, key);
    if (r) return r;
    return nullptr;
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

template<class T>
void utils_tree<T>::get_data(utils_vector<T> &vec, node<T> *n)
{
    if (!n) return;
    vec.push_back(n->data);
    get_data(vec, n->left);
    get_data(vec, n->right);
}

template<class T>
void utils_tree<T>::go_darker(node<T> *n)
{
    if (!n) return;
    n->light /= 1.05f;
    //n->color.setHsv(n->color.hue(), n->color.saturation(), n->color.value() / 1.05f);
    go_darker(n->left);
    go_darker(n->right);
}

template<class T>
std::string utils_tree<T>::node_string(node<T> *n)
{
    if (!n) return "";
    return "" + std::to_string(n->data) + "(" + node_string(n->left) + ")(" + node_string(n->right) + ")";
}

//АВЛ

template<class T>
int utils_tree<T>::height(node<T> *n)
{
    return n ? n->height : 0;
}

template<class T>
int utils_tree<T>::bfactor(node<T> *n)
{
    return height(n->right) - height(n->left);
}

template<class T>
void utils_tree<T>::fixheight(node<T> *n)
{
    int hl = height(n->left);
    int hr = height(n->right);
    n->height = (hl > hr ? hl : hr) + 1;
}

template<class T>
node<T>* utils_tree<T>::rotateleft(node<T> *n)
{
    n->color.setRgb(255, 0, 0);
    n->light = 1;
    n->right->color.setRgb(255, 0, 0);
    n->right->light = 1;
    //n->right->left->color.setRgb(255, 0, 0);
    node<T>* p = n->right;
    n->right = p->left;
    p->left = n;
    fixheight(n);
    fixheight(p);
    return p;
}

template<class T>
node<T>* utils_tree<T>::rotateright(node<T> *n)
{
    n->color.setRgb(255, 0, 0);
    n->light = 1;
    n->left->color.setRgb(255, 0, 0);
    n->left->light = 1;
    //n->left->right->color.setRgb(255, 0, 0);
    node<T>* q = n->left;
    n->left = q->right;
    q->right = n;
    fixheight(n);
    fixheight(q);
    return q;
}

template<class T>
node<T>* utils_tree<T>::balance(node<T> *n)
{
    fixheight(n);
    if (bfactor(n) == 2)
    {
        if (bfactor(n->right) < 0)
            n->right = rotateright(n->right);
        return rotateleft(n);
    }
    if (bfactor(n) == -2)
    {
        if (bfactor(n->left) > 0)
            n->left = rotateleft(n->left);
        return rotateright(n);
    }
    return n;
}

template<class T>
node<T> *utils_tree<T>::findmin(node<T> *n)
{
    return n->left ? findmin(n->left) : n;
}

template<class T>
node<T> *utils_tree<T>::removemin(node<T> *n)
{
    if (!n->left) return n->right;
    n->left = removemin(n->left);
    return balance(n);
}

template<class T>
node<T> *utils_tree<T>::insertbalanced(node<T> *n, T data)
{
    if (!n)
    {
        node<T>* res = new node<T>(data);
        res->color = QColor::fromRgb(255, 0, 255);
        return res;
    }
    if (data < n->data) n->left = insertbalanced(n->left, data);
    else n->right = insertbalanced(n->right, data);
    return balance(n);
}

template<class T>
node<T> *utils_tree<T>::removebalanced(node<T> *n, T data)
{
    if (!n) return nullptr;
    if (data < n->data)
    {
        n->left = removebalanced(n->left,data);
    }
    else if (data > n->data)
    {
        n->right = removebalanced(n->right,data);
    }
    else
    {
        node<T>* l = n->left;
        node<T>* r = n->right;
        delete n;
        if (!r) return l;
        node<T>* min = findmin(r);
        min->right = removemin(r);
        min->left = l;
        return balance(min);
    }
    return balance(n);
}

template<class T>
node<T> *utils_tree<T>::save(node<T> *n)
{
    if (!n) return nullptr;
    node<T>* copy = new node<T>();
    copy->data = n->data;
    copy->left = save(n->left);
    copy->right = save(n->right);
    copy->color = n->color;
    copy->light = 1;
    return copy;
}

template<class T>
void utils_tree<T>::go_red(node<T> *n)
{
    if (!n) return;
    if (!n->left && !n->right) n->color = QColor::fromRgb(255, 0, 255);
    else n->color = QColor::fromRgb(255, 0, 0);
    go_red(n->left);
    go_red(n->right);
}


#endif // UTILS_TREE_H
