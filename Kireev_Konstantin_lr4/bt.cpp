#include "bt.h"

BinTree *createBinTree()
{
    BinTree *tree = new BinTree;
    tree->root = nullptr;
    tree->deep = 0;
    return tree;
}

Node *createBinNode(char info, bool isNum)
{
    Node *node = new Node;
    node->info = info;
    node->isLeaf = isNum;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

Node *appendRight(Node *node, char info, bool isNum)
{
    node->right = createBinNode(info, isNum);
    return node->right;
}

Node *appendLeft(Node *node, char info, bool isNum)
{
    node->left = createBinNode(info, isNum);
    return node->left;
}

Node *setInfo(Node *node, char info, bool isNum)
{
    if (node == nullptr)
        return nullptr;
    node->info = info;
    node->isLeaf = isNum;
    return node;
}

int countDeep(Node *&node)
{
    if (node == nullptr)
        return 0;
    int cl = countDeep(node->left);
    int cr = countDeep(node->right);
    return 1 + ((cl>cr)?cl:cr);
}

int updateDeep(BinTree *tree)
{
    tree->deep = countDeep(tree->root);
    return tree->deep;
}

BinTree *create(QStringList in, int &err)
{
    stack <Node *> BNStack;
    BinTree *tree = createBinTree();
    tree->root = createBinNode('\0', 1);
    Node *temp = tree->root;
    BNStack.push(temp);
    for (int i=0; i<in.length(); i++)
    {
        if (in[i] == "(")
        {
            BNStack.push(temp);
            temp = appendLeft(temp, '\0', 1);
        }
        else if (in[i] == ")")
        {
            if (BNStack.empty() || temp->info == '\0')
            {
                err = 4;
                return tree;
            }
            if (temp == BNStack.top()->left)
            {
                temp = BNStack.top();
                temp = appendRight(temp, '\0', 1);
            }
            else
            {
                temp = BNStack.top();
                BNStack.pop();
            }
        }
        else if (in[i] == "*" || in[i] == "/" || in[i] == "-" || in[i] == "+")
            setInfo(temp, qPrintable(in[i])[0], 0);
        else
        {
            if (in[i].length() > 1 || ((in[i][0] < 'a' || in[i][0] > 'z') && (!in[i][0].isDigit())))
            {
                err = 3;
                return tree;
            }
            if (BNStack.empty())
            {
                err = 4;
                return tree;
            }
            setInfo(temp, qPrintable(in[i])[0], 1);
            if (temp == BNStack.top()->left)
            {
                temp = BNStack.top();
                temp = appendRight(temp, '\0', 1);
            }
            else
            {
                temp = BNStack.top();
                BNStack.pop();
            }
        }
    }
    if (!BNStack.empty())
    {
        err = 4;
        return tree;
    }
    updateDeep(tree);
    return tree;
}
