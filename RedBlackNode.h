#ifndef REDBLACKNODE_H
#define REDBLACKNODE_H

#include "Node.h"


class RedBlackNode: public Node
{
    public:
        bool red;
        RedBlackNode();
        virtual ~RedBlackNode();
    protected:
    private:

};

#endif // REDBLACKNODE_H
