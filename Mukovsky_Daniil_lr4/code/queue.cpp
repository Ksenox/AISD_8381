#include "queue.h"

#include <iostream>

using namespace std;

#define SIZE 100


class queue {
    int q[SIZE];
    int sloc, rloc;
public:
    void init ();
    void insert (int val);
    int qget ();
};

void queue::init()
{
    rloc = sloc = 0;
}

void queue::insert(int val)
{
    if ( sloc == SIZE ) {
        cout << endl << " QUEUE is full" << endl;
        return ;
    }
    q[++sloc] = val;
}

int queue::qget()
{
    if ( rloc == sloc ) {
        cout << endl << " QUEUE is empty" << endl;
        return -1;
    }
    return q[++rloc] ;
}


