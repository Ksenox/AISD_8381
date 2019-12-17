#include "console.h"
#include <fstream>
#include <iostream>
#include <QString>
#include <QFile>
#include "binarytree.h"
#include "nodequeque.h"
#include "stepbystep.h"

using namespace std;

int consoleMain(){
    QFile file("C:\\Users\\miair\\Desktop\\Results_lr4\\input.txt"); // создаем объект класса QFile
    QString inputTree;
    if (!file.open(QIODevice::ReadOnly))
        return 1 ;
    inputTree = file.readAll();
    int lev = 0;
    int numb = 1;
    BinaryTree* BT = new(BinaryTree);
    BT->root = BT->createTree(splitForTree(inputTree),numb);

    bool flagStep = false;
    NodeQueue* queque = new NodeQueue(numb);

    Node* currentNode = BT->root;
    queque->addItem(currentNode);
    BT->root->level =1;
    QString out_;
    stepByStepAlg(lev,out_,queque,flagStep);
    QFile out("C:\\Users\\miair\\Desktop\\Results_lr4\\output.txt");
    if (out.open(QIODevice::WriteOnly)){
        out.write(out_.toUtf8());
    }
    out.close();
    return 0;
}
