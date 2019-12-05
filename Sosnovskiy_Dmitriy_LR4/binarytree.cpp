#include "binarytree.h"

BinaryTree::BinaryTree(QString parenthesesTreeString, QGraphicsScene* scene):
    parenthesesTreeString(parenthesesTreeString), scene(scene)
{
    if(parenthesesTreeString == nullptr) throw "Пустая строка";
    root = new Node();

    for(int i = 0; i < this->parenthesesTreeString.size(); i++)
    {
        if(this->parenthesesTreeString[i] == ' ')
        {
            this->parenthesesTreeString.remove(i, 1);
            i--;
        }
    }
    constructTreeFromParenthesesString();    
}

BinaryTree::Node::Node()
{
}

BinaryTree::Node::~Node()
{
    if(leftNode != nullptr) delete leftNode;
    if(rightNode != nullptr) delete rightNode;
}

BinaryTree::~BinaryTree()
{
    delete root;
}


void BinaryTree::constructTreeFromParenthesesString()
{
    Node* currentNode = root;

    if(parenthesesTreeString[0] != '(' || parenthesesTreeString[parenthesesTreeString.size()-1] != ')') throw "Ошибка в строке";
    else
    {
        parenthesesTreeString.remove(0,1);
        parenthesesTreeString.remove(parenthesesTreeString.size() - 1, 1);
    }

    Stack<Node*> stack;
    for(int i = 0; i < parenthesesTreeString.size(); i++)
    {
        symbols currentSymbol = analyzeSymbol(i);
        
        switch(currentSymbol)
        {
            case VALUE: {   
                QString currentNodeValue = getCurrentNodeValue(i);
                if (currentNode->value != nullptr) throw "Ошибка в строке";
                currentNode->value = currentNodeValue;
                break;
            }
            case LEFT_BRACKET: {
                stack.add(currentNode);
                constructNewNode(currentNode);
                if(currentNode->leftNode != nullptr && currentNode->rightNode != nullptr) throw "Ошибка в строке";
                break;
            }
            case RIGHT_BRACKET: {
                if (stack.size == 0) throw "Ошибка в строке";
                currentNode = stack.get();
                break;
            }
            default: {
                break;
            }
                
        }
    }

    if(currentNode != root) throw "Ошибка в строке";

    drawTree();
}

void BinaryTree::constructNewNode(Node*& currentNode)
{
    if (currentNode->leftNode == nullptr)
    {
        currentNode->leftNode = new Node();
        currentNode = currentNode->leftNode;
    }
    else if (currentNode->rightNode == nullptr)
    {
        currentNode->rightNode = new Node();
        currentNode = currentNode->rightNode;
    }
}

QString BinaryTree::getCurrentNodeValue(int & i)
{
    QString currentNodeValue = nullptr;
    while (parenthesesTreeString[i] != ')' && parenthesesTreeString[i] != '(' && i < parenthesesTreeString.size())
    {
           currentNodeValue.append(parenthesesTreeString[i]);
           i++;
    }
    i--;
    return currentNodeValue;
}

symbols BinaryTree::analyzeSymbol(int symbolPosition)
{
    QChar currentSymbol = parenthesesTreeString[symbolPosition];
    switch (currentSymbol.unicode()) {
        case '(': {
            return LEFT_BRACKET;
        }
        case ')': {
            return RIGHT_BRACKET;
        }
        default: {
            return VALUE;
        }
    }
}

QString BinaryTree::getForestBreadthString()
{
    bool anyNodesFound = true;
    int nodeLevelCounter = 0;
    Node* currentNode = root;
    Node* temporary = root;
    QString answerString = nullptr;

    if(root->leftNode == nullptr && root->rightNode == nullptr) return root->value + ", ";

    while(anyNodesFound == true)
    {
        temporary = root;
        currentNode = root;
        anyNodesFound = false;
        while(currentNode != nullptr)
        {
            int i = 0;
            for(i = 0 ; i < nodeLevelCounter; i++)
            {
                if(currentNode->leftNode != nullptr)
                    currentNode = currentNode->leftNode;
                else
                {
                    break;
                }
            }

            if(i == nodeLevelCounter)
            {
                while(currentNode != nullptr)
                {
                    if(currentNode->value == nullptr) answerString += "#";
                    else answerString += currentNode->value;
                    answerString += ", ";
                    currentNode = currentNode->rightNode;
                }
                anyNodesFound = true;
            }

            if(nodeLevelCounter == 0) continue;

            currentNode = temporary->rightNode;
            temporary = temporary->rightNode;
        }
        nodeLevelCounter++;
    }

    return answerString;
}

void BinaryTree::drawTree()
{
    int rootAxis = 25;
    int rootOrdinate = 25;

    int leftRightMax = countMaxLenRight(root->leftNode) + 1;
    int rightLeftMax = countMaxLenLeft(root->rightNode) + 1;

    scene->addEllipse(QRectF(0, 0, 50, 50));

    QGraphicsTextItem *textItem = new QGraphicsTextItem(root->value);
    textItem->setPos(15, 15);
    scene->addItem(textItem);

    drawNode(root->leftNode, rootAxis - 100*leftRightMax, rootOrdinate + 75, rootAxis, rootOrdinate+25);
    drawNode(root->rightNode, rootAxis + 100*rightLeftMax, rootOrdinate + 75, rootAxis, rootOrdinate+25);


}

void BinaryTree::drawNode(Node *node, int axis, int ordinate, int lineStartX, int lineStartY)
{
    if(node == nullptr) return;
    else {
        scene->addEllipse(QRectF(axis-25, ordinate-25, 50, 50));
        QGraphicsTextItem *textItem = new QGraphicsTextItem(node->value);
        textItem->setPos(axis-10, ordinate-10);
        scene->addItem(textItem);

        scene->addLine(QLine(lineStartX, lineStartY, axis, ordinate-25));

        int leftRightMax = countMaxLenRight(node->leftNode) + 1;
        int rightLeftMax = countMaxLenLeft(node->rightNode) + 1;

        drawNode(node->leftNode,  axis - 100*leftRightMax, ordinate + 75, axis, ordinate+25);
        drawNode(node->rightNode, axis + 100*rightLeftMax, ordinate + 75, axis, ordinate+25);
    }
}

int BinaryTree::countMaxLenLeft(Node *node)
{
   if(node == nullptr) return 0;
   else {
       int leftcnt = countMaxLenLeft(node->leftNode) + 1;
       int rightcnt = countMaxLenLeft(node->rightNode) - 1;
       if(leftcnt > rightcnt) return leftcnt;
       else return  rightcnt;
   }
}

int BinaryTree::countMaxLenRight(Node *node)
{
    if(node == nullptr) return 0;
    else {
        int leftcnt = countMaxLenRight(node->leftNode) - 1;
        int rightcnt = countMaxLenRight(node->rightNode) + 1;
        if(leftcnt > rightcnt) return leftcnt;
        else return  rightcnt;
    }
}
