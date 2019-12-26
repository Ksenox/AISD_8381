#ifndef NODE_H
#define NODE_H

#include <QColor>

struct Node {
    int data;
    int size = 1;
    Node *left = nullptr;
    Node *right = nullptr;
    QColor color = QColor::fromRgb(0, 255, 0);

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(int k) {
        data = k;
        left = nullptr;
        right = nullptr;
    }
};

#endif // NODE_H
