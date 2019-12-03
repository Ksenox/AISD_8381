#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>
#include <cstring>

using namespace std;


struct Node{
        bool isLeaf;
        char info;
        int total;
        Node **Tnode;
};
struct Tree{
        int deep;
        Node *root;
};

struct Forest{
    int count;
    Tree **tree;
};

Forest *takeForest(char* arr, int len);
Node *AppendNode(Node *node,char* arr,int& i,int len, bool isAlpha,int total);
int CountTree(char* arr, int len);
int CheckErr(char *arr, int len);
int BranchOfNode(char *arr, int i, int len);
Forest *createForest(int count);
Tree *createTree();
Node *createNode(char info,bool isAlpha, int total);
int DeepOfTree(char *arr, int i , int len);
void takeInfoOfNode(Node *root, string &out);
