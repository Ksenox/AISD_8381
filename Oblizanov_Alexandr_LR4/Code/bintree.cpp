#include "bintree.h"

BinTree *createBinTree()
{
    BinTree *tree = new BinTree;
    tree->root = nullptr;
    tree->deep = 0;
    return tree;
}

BinNode *createBinNode(char info, bool isNum)
{
    BinNode *node = new BinNode;
    node->info = info;
    node->isLeaf = isNum;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

BinNode *appendRight(BinNode *node, char info, bool isNum)
{
    node->right = createBinNode(info, isNum);
    return node->right;
}

BinNode *appendLeft(BinNode *node, char info, bool isNum)
{
    node->left = createBinNode(info, isNum);
    return node->left;
}

BinNode *setInfo(BinNode *node, char info, bool isNum)
{
    if (node == nullptr)
        return nullptr;
    node->info = info;
    node->isLeaf = isNum;
    return node;
}

int countDeep(BinNode *&node)
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

BinTree *getTreeFromArray(QStringList in, int &err)
{
    stack <BinNode *> BNStack;
    BinTree *tree = createBinTree();
    tree->root = createBinNode('\0', 1);
    BinNode *temp = tree->root;
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
                err = INVAL_POST;
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
        {
            setInfo(temp, qPrintable(in[i])[0], 0);
        }
        else
        {
            if (in[i].length() > 1 || ((in[i][0] < 'a' || in[i][0] > 'z') && (!in[i][0].isDigit())))
            {
                err = INVAL_ARG;
                return tree;
            }
            if (BNStack.empty())
            {
                err = INVAL_POST;
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
        err = INVAL_POST;
        return tree;
    }
    updateDeep(tree);
    return tree;
}

QString getQStrFromTree(BinNode *root)
{
    if (root == nullptr)
        return "";
    QString output;
    if (root->left || root->right)
        output += "(";
    output += getQStrFromTree(root->left);
    output += root->info;
    output += getQStrFromTree(root->right);
    if (root->left || root->right)
        output += ")";
    return output;
}

QString getListFromTree(BinNode *root, int indent)
{
    if (root == nullptr)
        return "";
    QString output;
    output += QString(indent, '.');
    output += root->info;
    output += "\n";
    output += getListFromTree(root->left, indent+3);
    output += getListFromTree(root->right, indent+3);
    return output;
}
