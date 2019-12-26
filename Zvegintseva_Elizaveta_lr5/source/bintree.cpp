//
// Created by therealyou on 02.10.2019.
//

#include "bintree.h"

void binTree::lkp() {
    Node* temp = root;
    if (root){
        //elems.push_back(root->info);
        root = temp->left;
        lkp();
        root = temp->right;
        lkp();
        root = temp;
    }
}

int binTree::treeInit(QStringList lst, unsigned int& index) {
    QString x = lst[index++];
    if (x == "/"){
        delete root;
        root = nullptr;
        return 1;
    } else {
        root->data = x.toInt();
        Node* temp = root;
        root = temp->left;
        root = new Node;
        temp->left = root;
        if (treeInit(lst, index)){
            temp->left = nullptr;
        }
        root = temp->right;
        root = new Node;
        temp->right = root;
        if (treeInit(lst, index)){
            temp->right = nullptr;
        }
        root = temp;
    }
    return 0;
}

int binTree::checkTwoEqualElem() {
    //elems.clear();
    lkp();
//    for (unsigned int i = 0; i < elems.size(); i++){
//        for (unsigned int j = i + 1; j < elems.size(); j++){
//            //if (elems[i] == elems[j]){
//            //    return 1;
//            //}
//        }
//    }
    return 0;
}

void binTree::printLKP() {
    Node* temp = root;
    if (root){
        std::cout << root->data << std::endl;
        root = temp->left;
        printLKP();
        root = temp->right;
        printLKP();
        root = temp;
    }
}

int binTree::max_depth(Node *n, int i)
{
    if (!n) return i;
    int l = max_depth(n->left, i + 1);
    int r = max_depth(n->right, i + 1);
    if (l > r) return l;
    else return r;
}

bool binTree::parse_tree(Node*& n, std::string &s, int &i) {
    if (s.size() < 1) return true;
    std::size_t current, previous = 0;
    current = s.find(' ');
    int num;
    while (current != std::string::npos) {
        try
        {
            num = stoi(s.substr(previous, current - previous));
        }
        catch (...)
        {
            return true;
        }
        previous = current + 1;
        current = s.find(' ', previous);
        insert(n, num);
    }
    try
    {
        num = stoi(s.substr(previous, current - previous));
    }
    catch (...)
    {
        return true;
    }
    insert(n, num);
    return false;
}

void binTree::get_elems(array_list& vec, Node *n)
{
    if (!n) return;
    vec.push_back(n);
    get_elems(vec, n->left);
    get_elems(vec, n->right);
}

bool binTree::get_duplicates(array_list& vec, Node*& first, Node*& second)
{
    int count = vec.size();
    for (int i = 0; i < count; i++) {
        for (int k = i + 1; k < count; k++) {
            if (vec[i]->data == vec[k]->data) {
                first = vec[i];
                second = vec[k];
                return true;
            }
        }
    }
    return false;
}

void binTree::insert(Node*& n, int data)
{
    if (!n)
    {
        n = new Node();
        n->data = data;
    }
    else if (n->data > data)
    {
        insert(n->left, data);
    }
    else if (n->data < data)
    {
        insert(n->right, data);
    }
}

void binTree::remove(Node *&n, int data)
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
            Node* temp = n->right;
            delete n;
            n = temp;
        }
        else if (!n->right && n->left)
        {
            Node* temp = n->left;
            delete n;
            n = temp;
        }
        else if (!n->right && !n->left)
        {
            delete n;
            n = nullptr;
        }
        else
        {
            Node* min = n->right;
            if (!min->left)
            {
                n->right = nullptr;
            }
            else
            {
                Node* t = min;
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
}

Node *binTree::copy(Node *n)
{
    if (!n) return nullptr;
    Node* co = new Node();
    co->data = n->data;
    co->left = copy(n->left);
    co->right = copy(n->right);
    co->color = n->color;
    return co;
}

string binTree::into_string(Node *n)
{
    if (!n) return "";
    else return "(" + to_string(n->data) + into_string(n->left) + into_string(n->right) + ")";
}
