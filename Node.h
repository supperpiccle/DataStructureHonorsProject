#ifndef NODE_H
#define NODE_H


class Node
{
    public:
    bool red;

    Node();
    Node(int e);
    Node *Insert(Node *&n, int e);

    int getRightChildValue();
    int getLeftChildValue();
    int getValue();

    Node* getRightChild()   {return rightChild;}
    Node* getLeftChild()    {return leftChild;}

    Node *parent;
        virtual ~Node();




    Node *rightChild;
    Node *leftChild;
    int nodeValue;
    protected:
    private:


};

#endif // NODE_H
