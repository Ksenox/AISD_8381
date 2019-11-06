#include "actions.h"

int connectUI(QTextEdit *&uiInput, QTextEdit *&uiOutput, QGraphicsScene *&scene)
{
    BinTree *tree = nullptr;
    QString output = startProcess(uiInput->toPlainText(), tree);
    uiOutput->setPlainText(output);
    if (!output.count("Error"))
        graphic(tree, scene);
    else
        scene->clear();
    return 0;
}

QString startProcess(QString input, BinTree *&tree)
{
    QString output;
    int err = 0;
    QStringList inArr = getArrayFromStr(input);
    tree = getTreeFromArray(inArr, err);
    switch (err)
    {
    case INVAL_POST:
        output += "Error!\nInvalid postfix record.\nMake sure it's: (function function operation)\n";
        return output;
    case INVAL_ARG:
        output += "Error!\nInvalid argument.\nUse only digits and ()+-*/ divided by one space\n";
        return output;
    }
    output += "Tree was created...\n\nInfix form of tree-function:\n";
    output += getQStrFromTree(tree->root);
    output += "\n\nList form of tree-function:\n";
    output += getListFromTree(tree->root, 0);
    output += "\nTree depth: ";
    output += QString::number(tree->deep);
    output += "\nModify started...\n";
    output += modBinTree(tree->root);
    output += "\n\nInfix form of tree-function:\n";
    output += getQStrFromTree(tree->root);
    output += "\n\nList form of tree-function:\n";
    output += getListFromTree(tree->root, 0);
    return output;
}

QString modBinTree(BinNode *root)
{
    QString output;
    if (root == nullptr)
        return "";
    if (root->info == '+' && root->left && root->right)
    {
        if (root->left->info == '*' && root->right->info == '*')
        {
            if (!QString::compare(getQStrFromTree(root->left->left), getQStrFromTree(root->right->left)))
            {
                output += "\nBefore: ";
                output += getQStrFromTree(root);
                root->info = '*';
                root->right->left = root->left->right;
                root->left = root->left->left;
                root->right->info = '+';
                output += "\nAfter: ";
                output += getQStrFromTree(root);
                output += "\n";
            }
            else if (!QString::compare(getQStrFromTree(root->left->right), getQStrFromTree(root->right->right)))
            {
                output += "\nBefore: ";
                output += getQStrFromTree(root);
                root->info = '*';
                root->right->right = root->left->left;
                root->left = root->left->right;
                root->right->info = '+';
                output += "\nAfter: ";
                output += getQStrFromTree(root);
                output += "\n";
            }
        }
    }
    output += modBinTree(root->left);
    output += modBinTree(root->right);
    return output;
}

QGraphicsScene *graphic(BinTree *tree, QGraphicsScene *&scene)
{
    if (tree == nullptr)
        return scene;
    scene->clear();
    QPen pen;
    QColor color;
    color.setRgb(220, 220, 220);
    pen.setColor(color);
    QBrush brush (color);
    QFont font;
    font.setFamily("Tahoma");
    pen.setWidth(3);
    int wDeep = static_cast<int>(pow(2, tree->deep)+2);
    int hDelta = 70;
    int wDelta = 15;
    font.setPointSize(wDelta);
    int width = (wDelta*wDeep)/2;
    treePainter(scene, tree->root, width/2, hDelta, wDelta, hDelta, pen, brush, font, wDeep);
    return scene;
}

int treePainter(QGraphicsScene *&scene, BinNode *node, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth)
{
    if (node == nullptr)
        return 0;
    QString out;
    out += node->info;
    QGraphicsTextItem *textItem = new QGraphicsTextItem;
    textItem->setPos(w, h);
    textItem->setPlainText(out);
    textItem->setFont(font);
    scene->addEllipse(w-wDelta/2, h, wDelta*5/2, wDelta*5/2, pen, brush);
    if (node->left != nullptr)
        scene->addLine(w+wDelta/2, h+wDelta, w-(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    if (node->right != nullptr)
        scene->addLine(w+wDelta/2, h+wDelta, w+(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    scene->addItem(textItem);
    treePainter(scene, node->left, w-(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2);
    treePainter(scene, node->right, w+(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2);
    return 0;
}
