#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "Node.h"
#include "Exceptions.h"
#include <iostream>
using namespace std;


class BinarySearchTree
{
    public:
        BinarySearchTree(int e);
        BinarySearchTree();

        void ClearTree();
        void ClearTree(Node *&n);

        void Insert(int e);

        void DeleteElement(int e);
        int getHeight();



        void PrintInOrder();
        void PrintInOrder(Node *n);


        bool Exists(int e);


        virtual ~BinarySearchTree();
    protected:
        Node *root;
        Node* Find(Node *n, int e);
    private:
        int getHeight(Node *n);
        bool IsFull();

        void Insert(Node *&n, int e);
        void Delete(Node *&n, int e);
        void DeleteNode(Node *&n);
};

#endif // BINARYSEARCHTREE_H
