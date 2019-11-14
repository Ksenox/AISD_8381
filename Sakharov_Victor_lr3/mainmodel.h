#pragma once
#ifndef MAINPRESENTER_H
#define MAINPRESENTER_H

#include "utils_list.h"
#include "utils_linked_list.h"

struct state
{
    int column;
    int position;
    IList<int> *l1;
    IList<int> *l2;
    IList<int> *l3;

    void SetArr()
    {
        column = 0;
        position = 0;
        l1 = new utils_list<int>();
        l2 = new utils_list<int>();
        l3 = new utils_list<int>();
    }

    void SetLinked()
    {
        column = 0;
        position = 0;
        l1 = new utils_linked_list<int>();
        l2 = new utils_linked_list<int>();
        l3 = new utils_linked_list<int>();
    }
};

struct delta
{
    int data;
    int fromcol;
    int frompos;
    int statecol;
    int statepos;
};


class mainmodel
{
public:
    mainmodel()
    {
        current_state = state();
        current_state.column = 0;
        current_state.position = 0;
        current_state.SetArr();
        undo_states = utils_list<delta>();
    }

    state current_state;
    utils_list<delta> undo_states;
};

#endif // MAINPRESENTER_H
