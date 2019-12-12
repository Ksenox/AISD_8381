//
// Created by therealyou on 02.10.2019.
//

#include "binTree.h"

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
        root->info = x.toUtf8().data();
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
        std::cout << root->info << std::endl;
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
    n->info = s.substr(static_cast<unsigned long>(start), static_cast<unsigned long>(i) - static_cast<unsigned long>(start));
    n->left = new Node();
    n->right = new Node();
    if(parse_tree(n->left, s, i) || parse_tree(n->right, s, i)) return true;
    if (s[static_cast<unsigned long>(i)] == ')')
    {
        i++;
    }
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
            if (vec[i]->info == vec[k]->info) {
                first = vec[i];
                second = vec[k];
                return true;
            }
        }
    }
    return false;
}
