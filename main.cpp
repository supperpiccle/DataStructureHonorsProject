#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "RedBlackTree.h"
#include "timer.h"

using namespace std;

int main()
{
    srand (time(NULL));
    RedBlackTree RBtree;
    BinarySearchTree Btree;
    Timer time;
    time.Reset();

    RBtree.Insert(80);
    RBtree.Insert(60);
    RBtree.Insert(40);
    RBtree.Insert(100);
    RBtree.Insert(90);
    RBtree.Insert(110);

    RBtree.DebugPrintInOrder();
    cout<<endl<<endl<<endl;

    RBtree.Insert(20);
    RBtree.Insert(10);
    RBtree.Insert(120);

    RBtree.DebugPrintInOrder();

    //RBtree.Insert(60);
    //RBtree.Insert(60);
    //RBtree.Insert(60);


/*
    Btree.Insert(21);
    Btree.Insert(34);
    Btree.Insert(1);
    Btree.Insert(23);
    Btree.Insert(1234);
    Btree.Insert(232);
    Btree.Insert(2);
    Btree.Insert(54);
    Btree.PrintInOrder();
*/
/*
    for(int i = 100; i <=1000; i += 100)
    {
        time.Start();
        for(int u = 0; u < 10000 * i ; u++)
        {
            int random = rand() % 10000;
            try
            {
                RBtree.Insert(random);
            }
            catch(DuplicateItemException die)
            {
            }

        }
        time.Stop();
        cout<<i<<endl;
        cout<<"It took "<< time.Seconds() << " to add "<< i * 10000<<" to the tree\n";
        time.Reset();
        time.Start();
        for(int u = 0; u < 10000 * i; u++)
        {
            int random = rand() % 10000;
            RBtree.Exists(random);
        }
        time.Stop();
        cout<<"It took " << time.Seconds() << " to search for " << i * 10000 << " to search\n";
    cout<<endl;
    cout<<endl;
    cout<<endl;
    time.Reset();
    RBtree.ClearTree();
    }


    for(int i = 100; i <=1000; i += 100)
    {
        time.Start();
        for(int u = 0; u < 10000 * i ; u++)
        {
            int random = rand() % 10000;
            try
            {
                Btree.Insert(random);
            }
            catch(DuplicateItemException die)
            {
            }

        }
        time.Stop();
        cout<<i<<endl;
        cout<<"It took "<< time.Seconds() << " to add "<< i * 10000<<" to the tree\n";
        time.Reset();
        time.Start();
        for(int u = 0; u < 10000 * i; u++)
        {
            int random = rand() % 10000;
            Btree.Exists(random);
        }
        time.Stop();
        cout<<"It took " << time.Seconds() << " to search for " << i * 10000 << " to search\n";
    cout<<endl;
    cout<<endl;
    cout<<endl;
    time.Reset();
    Btree.ClearTree();
    }

*/


    return 0;
}
