#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>
#include <cstring>

using namespace std;


struct Node{
        string info;
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


Forest *takeforest(string str, int len);
Forest *createForest(int count);
Tree *createTree();
Node *AppendNode(Node *root,string str, int &index,int len,int total);
Node *createNode(string info, int total);
string takeString(string str,int &index,int len);
int BranchOfNode(string str, int index, int len);
int DeepOfTree(string str, int index, int len);
int CountTree(string str, int len);
int CheckErr(string str, int len);
void takeInfoByDeep(Node *root,int deep);
void takeInfoOfNode(Node *root, string &out);
