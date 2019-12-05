#pragma once
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "Stack.hpp"
enum symbols {LEFT_BRACKET, RIGHT_BRACKET, VALUE};

class BinaryTree
{
private:
    class Node
    {
        public:
            Node();
            ~Node();
            Node* leftNode = nullptr;
            Node* rightNode = nullptr;
            QString value = nullptr;
    };

    void constructTreeFromParenthesesString();
    symbols analyzeSymbol(int symbolPosition);
    QString getCurrentNodeValue(int& valueStartPosition);



    void drawNode(Node* node, int axis, int ordinate, int lineStartX, int lineStartY);
    int countMaxLenLeft(Node* node);
    int countMaxLenRight(Node* node);

public:
    QGraphicsScene* scene;
    BinaryTree(QString parenthesesTreeString, QGraphicsScene* scene);
    ~BinaryTree();

    void constructNewNode(Node*& currentNode);

    Node* root = nullptr;

    QString parenthesesTreeString = nullptr;

    QString getForestBreadthString();

    void drawTree();
};

