#include <iostream>
#include "RedBlackTree.h"




RedBlackTree::RedBlackTree()
{
    root = 0;
}

RedBlackTree::~RedBlackTree()
{
    //dtor
}

void RedBlackTree::ClearTree()
{
    ClearTree(root);
}
void RedBlackTree::ClearTree(Node *&n)
{
    if(n == 0) return;
    ClearTree(n->leftChild);
    ClearTree(n->rightChild);
    delete n;
    n = 0;
}

void RedBlackTree::Insert(int e)
{
    Node *node = Insert(root, e);
    node->red = true;
    root->red = false;
    root->parent = 0;
    FixViolation(node); //red node cannot have red parent
}












void RedBlackTree::DebugPrintInOrder()
{
    DebugPrintInOrder(root);
}
void RedBlackTree::DebugPrintInOrder(Node *n)
{
    if(n == 0) return;
    DebugPrintInOrder(n->getLeftChild());
    cout<<n->getValue()<< "  red == 1: " << n->red<<endl;
    DebugPrintInOrder(n->getRightChild());
}


void RedBlackTree::DeleteElement(int e)
{
    Delete(root, e);
}

//BEGIN PRIVATE FUNCTIONS
//-----------------------------------------------------------------------------------------------------------------


//Insertions
Node* RedBlackTree::Insert(Node *&n, int e)
{
    if(n == 0) //root is the only thing that gets made here
    {
        n = new Node(e);
        return n;
    }
    if(n->rightChild == 0 && e > n->getValue()) //this is called for right child so we can set the parent pointers
    {
        n->rightChild = new Node(e);
        n->rightChild->parent = n;
        return n->rightChild;
    }
    else if(n->leftChild == 0 && e < n->getValue())
    {
        n->leftChild = new Node(e);
        n->leftChild->parent = n;
        return n->leftChild;
    }

    else if(e < n->nodeValue) return this->Insert(n->leftChild, e);
    else if(e > n->nodeValue) return this->Insert(n->rightChild, e);
    else if(e == n->nodeValue) throw DuplicateItemException(e);
}


//deletions
void RedBlackTree::Delete(Node *&n, int e)
{
    if(n == 0) return;

    else if(e < n->nodeValue) Delete(n->leftChild, e);
    else if(e > n->nodeValue) Delete(n->rightChild, e);
    else DeleteNode(n);
}

void RedBlackTree::DeleteNode(Node *&n)
{
    Node *rnode, *dnode;

    if(n->rightChild && n->leftChild) //degree 2
    {
        rnode = n->leftChild;

        while(rnode->rightChild != 0) rnode = rnode->rightChild;
        n->nodeValue = rnode->nodeValue;
        Delete(n->leftChild, n->nodeValue);
        FixViolation(n->leftChild);
        FixViolation(n->rightChild);
        return;
    }
    else if(n->rightChild == 0 || n->leftChild == 0) //degree 0/1
    {
        dnode = n->leftChild;
        if(dnode == 0) dnode = n->rightChild;
        delete n;
        n = dnode;
        if(n != 0)
        {
            FixViolation(n->rightChild);
            FixViolation(n->leftChild);
        }
        return;
    }
}



void RedBlackTree::FixViolation(Node *n)
{
    Node *grandad;
    if(n == 0) return;
    else if(n == this->root)
    {
        //cout<<"root node no violation lol\n";
        return;
    }
    else if(n->parent->parent == 0)
    {
        //cout<<"roots children hold off(no grandady either)\n";
        return;
    }

    //at this point we know there exists a grandad
    grandad = n->parent->parent;
    if(!n->parent->red) return;

    if(this->isUncleRed(n))
    {
        this->FixCase1(n);
    }

    else if(this->violation2Issue(n, grandad))
    {
        this->FixCase2(n);
    }
    else if(this->violation3Issue(n, grandad))
    {
        this->FixCase3(n, grandad);
    }
    FixViolation(grandad);
}

void RedBlackTree::FixCase1(Node *n) //n is the node inserted(or pushed in from delete)
{
    n->parent->red = !n->parent->red; //color parent
    n->parent->parent->red = !n->parent->parent->red;//color grandparent
    if(this->UncleExists(n)) getUncle(n)->red = !getUncle(n)->red; //color uncle(If not null)
    root->red = false;
}

void RedBlackTree::FixCase2(Node *n)
{
    Node *grandad = n->parent->parent;
    Node *newInsert = n->parent;
    if(this->rightRotateFixCase2(n)) RightRotate(newInsert);
    else LeftRotate(newInsert);

    this->FixViolation(newInsert);
}

void RedBlackTree::FixCase3(Node *n, Node *grandad)
{
    grandad->red = !grandad->red;
    n->parent->red = !n->parent->red;
    if(n->getValue() > grandad->getValue())
    {
        LeftRotate(grandad);
        if(root->parent != 0) root = root->parent;
    }
    else
    {
        RightRotate(grandad);
        if(root->parent != 0) root = root->parent;
    }
}




bool RedBlackTree::violation2Issue(Node *n, Node *grandad)
{
    Node *temp;
    if(n->getValue() > grandad->getValue())
    {
        temp = grandad->rightChild;
        if(temp != 0)
        {
            temp = temp->leftChild; //may need a checker if temp is zero here
            if(temp != 0)
                if(temp->getValue() == n->getValue()) return true;
        }
    }
    else
    {
        temp = grandad->leftChild;
        if(temp != 0)
        {
            temp = temp->rightChild;
            if(temp != 0)
                if(temp->getValue() == n->getValue()) return true;
        }
    }
    return false;
}
bool RedBlackTree::rightRotateFixCase2(Node *n)
{
    if(n->getValue() < n->parent->getValue()) return true;
    return false;
}

bool RedBlackTree::violation3Issue(Node *n, Node *grandad)
{
    Node *temp;
    if(n->getValue() < grandad->getValue())
    {
        temp = grandad->leftChild;
        if(temp != 0)
        {
            temp = temp->leftChild;
            if(temp->getValue() == n->getValue()) return true;
        }
    }
    else
    {
        temp = grandad->rightChild;
        if(temp != 0)
        {
            temp = temp->rightChild;
            if(temp->getValue() == n->getValue()) return true;
        }
    }
    return false;
}


//----------------------------------------------------------------
//uncle code
Node* RedBlackTree::getUncle(Node *n)
{
    if(n == root) return 0; //root has no parents
    if(n->parent->parent == 0) return 0; //the roots children has no grandparents

    Node* grandad = n->parent->parent; //uncle is one of grandad's children

    //Node* grandad = n->parent->parent; //uncle is one of grandad's children
    if(n->getValue() > grandad->getValue()) return grandad->getLeftChild();
    else return grandad->getRightChild();
}
bool RedBlackTree::isUncleRed(Node *n)
{
    if(!this->UncleExists(n)) return false; //null nodes are black

    Node *uncle = getUncle(n);
    return uncle->red;
}

bool RedBlackTree::UncleExists(Node *n)
{
    n = this->getUncle(n);
    if(n == 0) return false;
    return true;
}


//rotations
void RedBlackTree::RightRotate(Node *n)
{
    Node *temp = n->leftChild->rightChild;
    Node *pivot = n->leftChild;

    pivot->parent = n->parent;
    n->parent = pivot;
    if(temp != 0) temp->parent = n;

    n->leftChild = temp;
    pivot->rightChild = n;
    if(pivot->parent != 0)
    {
        if(pivot->getValue() < pivot->parent->getValue())
            pivot->parent->leftChild = pivot;
        else
            pivot->parent->rightChild = pivot;
    }
}

void RedBlackTree::LeftRotate(Node *n)
{
    Node *temp = n->rightChild->leftChild;

    Node *pivot = n->rightChild;

    pivot->parent = n->parent;
    n->parent = pivot;
    if(temp != 0) temp->parent = n;

    n->rightChild = temp;
    pivot->leftChild = n;
    if(pivot->parent != 0)
    {
        if(pivot->getValue() < pivot->parent->getValue())
            pivot->parent->leftChild = pivot;
        else
            pivot->parent->rightChild = pivot;
    }
}
