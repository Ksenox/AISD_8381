#ifndef STATE_H
#define STATE_H

#include "ilist.h"

struct state
{
    int column;
    int position;
    IList<int> *l1;
    IList<int> *l2;
    IList<int> *l3;

    state ()
    {
        column = 0;
        position = 0;
    }
};

#endif // STATE_H
