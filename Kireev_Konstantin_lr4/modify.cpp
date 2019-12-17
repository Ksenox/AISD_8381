#include "modify.h"
#include "graphic.h"

int beginning(QTextEdit *&uiInput, QTextEdit *&uiOutput, QGraphicsScene *&scene)
{
    BinTree *tree = nullptr;
    QString output = processing(uiInput->toPlainText(), tree);
    uiOutput->setPlainText(output);
    if (!output.count("Error"))
        graphic(tree, scene);
    else
        scene->clear();
    return 0;
}

QString processing(QString input, BinTree *&tree)
{
    QString output;
    int err = 0;
    QStringList inArr = input.split(" ");
    tree = create(inArr, err);
    switch (err)
    {
    case 3:
        output += "Только циферки буковки скобочки\n";
        return output;
    case 4:
        output += "Постфикс не оч\n";
        return output;
    }
    output += "Инфиксная форма до преобразования:\n";
    output += getInfixNotation(tree->root); // ЛКП
    output += modding(tree->root); // замена формул
    output += "\n\nИнфиксная форма после преобразования:\n";
    output += getInfixNotation(tree->root); // ЛКП
    return output;
}

QString modding(Node *root)
{
    QString output;
    if (root == nullptr)
        return "";
    output += modding(root->left);
    output += modding(root->right);
    if (root->info == '+' && root->left && root->right)
    {
        if (root->right->info == '0' && isdigit(root->left->info))
        {
                root->info = root->left->info;
                root->left = nullptr;
                root->right = nullptr;
        }
        else if (root->left->info == '0' && isdigit(root->right->info))
        {
                root->info = root->right->info;
                root->right = nullptr;
                root->left = nullptr;
        }
    }
    else if (root->info == '-' && root->left && root->right)
    {
        if (root->right->info == '0' && isdigit(root->left->info))
        {
                root->info = root->left->info;
                root->left = nullptr;
                root->right = nullptr;
        }
    }
    else if (root->info == '*' && root->left && root->right)
    {
        if (root->right->info == '1' && isdigit(root->left->info))
        {
                root->info = root->left->info;
                root->left = nullptr;
                root->right = nullptr;
        }
        else if (root->left->info == '1' && isdigit(root->right->info))
        {
                root->info = root->right->info;
                root->right = nullptr;
                root->left = nullptr;
        }
        else if (root->left->info == '0' && isdigit(root->right->info))
        {
                root->info = '0';
                root->right = nullptr;
                root->left = nullptr;
        }
        else if (root->right->info == '0' && isdigit(root->left->info))
        {
                root->info = '0';
                root->right = nullptr;
                root->left = nullptr;
        }
    }
    return output;
}

QString getInfixNotation(Node *root)
{
    if (root == nullptr)
        return "";
    QString output;
    if (root->left || root->right)
        output += "(";
    output += getInfixNotation(root->left);
    output += " ";
    output += root->info;
    output += " ";
    output += getInfixNotation(root->right);
    if (root->left || root->right)
        output += ")";
    return output;
}
