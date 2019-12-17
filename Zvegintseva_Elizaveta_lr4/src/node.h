#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>
#include <QStringList>
#include <QColor>


struct Node {
    std::string info;
    Node *left = nullptr;
    Node *right = nullptr;
    QColor color = QColor::fromRgb(255, 0, 0);
};


#endif // NODE_H
