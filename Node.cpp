#include "Node.h"
#include <iostream>

using namespace std;

Node::Node()
{
    rightChild = 0;
    leftChild = 0;
    red = true; //for a binary search tree this means nothing (only used in red black trees)
}

Node::Node(int value)
{
    nodeValue = value;
    rightChild = 0;
    leftChild = 0;
}

Node::~Node()
{

}

int Node::getRightChildValue()
{
    return rightChild -> nodeValue;
}

int Node::getLeftChildValue()
{
    return leftChild -> getValue();
}

int Node::getValue()
{
    return nodeValue;
}
