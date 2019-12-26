#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>
#include <QStringList>
#include <QColor>


struct Node {
    int data;
    Node *left = nullptr;
    Node *right = nullptr;
    QColor color = QColor::fromRgb(255, 0, 0);

    Node() {
        left = nullptr;
        right = nullptr;
    }
};


#endif // NODE_H
