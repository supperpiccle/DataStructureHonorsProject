#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree()
{
    root = 0;
}
BinarySearchTree::BinarySearchTree(int e)
{
    Insert(root, e);
}
BinarySearchTree::~BinarySearchTree()
{
    //dtor
}
int BinarySearchTree::getHeight()
{
    return getHeight(root);
}

bool BinarySearchTree::Exists(int e)
{
    if(Find(root, e) != 0) return true;
    return false;
}

void BinarySearchTree::ClearTree()
{
    ClearTree(root);
}
void BinarySearchTree::ClearTree(Node *&n)
{
    if(n == 0) return;
    ClearTree(n->leftChild);
    ClearTree(n->rightChild);
    delete n;
    n = 0;
}

void BinarySearchTree::PrintInOrder()
{
    PrintInOrder(root);
}
void BinarySearchTree::PrintInOrder(Node *n)
{
    if(n == 0) return;
    PrintInOrder(n->getLeftChild());
    cout<<n->nodeValue<<endl;
    PrintInOrder(n->getRightChild());
}

void BinarySearchTree::Insert(int e)
{
    if(IsFull()) throw TreeFullException();
    else Insert(root, e);
}
void BinarySearchTree::Insert(Node *&n, int e)
{
    if(n == 0) //root is the only thing that gets made here
    {
        n = new Node(e);
    }

    else if(n->nodeValue == e) throw DuplicateItemException(e);

    else if(e < n->nodeValue) return Insert(n->leftChild, e);
    else if(e > n->nodeValue) return Insert(n->rightChild, e);
}


void BinarySearchTree::DeleteElement(int e)
{
    Delete(root, e);
}

void BinarySearchTree::Delete(Node *&n, int e)
{
    if(n == 0) throw ItemNotFoundException(e);
    else if(e < n->nodeValue) Delete(n->leftChild, e);
    else if(e > n->nodeValue) Delete(n->rightChild, e);
    else DeleteNode(n);
}

void BinarySearchTree::DeleteNode(Node *&n)
{
    Node *rnode, *dnode;

    if(n->rightChild && n->leftChild)
    {
        rnode = n->leftChild;

        while(rnode->rightChild != 0) rnode = rnode->rightChild;
        n->nodeValue = rnode->nodeValue;
        Delete(n->leftChild, n->nodeValue);
        return;
    }
    if(n->rightChild == 0 || n->leftChild == 0)
    {
        dnode = n->leftChild;
        if(dnode == 0) dnode = n->rightChild;
        delete n;
        n = dnode;
        return;
    }
}
Node* BinarySearchTree::Find(Node* n, int e)
{
    if(n == 0) return 0;
    else if(e == n->nodeValue) return n;
    else if(e < n->nodeValue) return Find(n->leftChild, e);
    else if(e > n->nodeValue) return Find(n->rightChild, e);
}




bool BinarySearchTree::IsFull() {
	// the method attempts to allocate memory for a tree node
	// and returns false if the allocation was successful. if a
	// std::bad_alloc exception was thrown, true is returned
  Node* temp;
  try {
    temp = new Node(1);
    delete temp;
    return false;
  }
  catch(std::bad_alloc) {
    return true;
  }
}
int BinarySearchTree::getHeight(Node *n)
{
    if (n == 0) return -1;

	int rightH = 1;
	int leftH = 1;

	rightH += getHeight(n->rightChild);
	leftH += getHeight(n->leftChild);

	if (rightH > leftH) return rightH;
	return leftH;
}
