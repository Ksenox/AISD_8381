#include "FunctionTreeNode.h"
FunctionTreeNode::FunctionTreeNode()
{
    previousNode = nullptr;
    leftNode = nullptr;
    rightNode = nullptr;
    symbol = "";
}

FunctionTreeNode::~FunctionTreeNode()
{

}
