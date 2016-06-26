#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "BinarySearchTree.h"
#include "Node.h"



class RedBlackTree: public BinarySearchTree
{
    public:
        RedBlackTree();

        void ClearTree();
        void ClearTree(Node *&n);

        void Insert(int e);
        void DeleteElement(int e);

        void DebugPrintInOrder();
        void DebugPrintInOrder(Node *n);

        bool Exists(int e)   {if(Find(root, e) != 0) return true; return false;}

        virtual ~RedBlackTree();

    protected:
    private:
    Node* Insert(Node *&n, int e);

    void FixViolation(Node *n);
    void FixCase1(Node *n);
    void FixCase2(Node *n);
    void FixCase3(Node *n, Node *grandad);

    bool violation2Issue(Node *n, Node *grandad);
    bool violation3Issue(Node *n, Node *grandad);
    bool rightRotateFixCase2(Node *n);

    void RightRotate(Node *n);
    void LeftRotate(Node *n);

    void Delete(Node *&n, int e);
    void DeleteNode(Node *&n);

    Node* getUncle(Node *n);
    bool isUncleRed(Node *n);
    bool UncleExists(Node *n);

    Node *root;

};

#endif // REDBLACKTREE_H
