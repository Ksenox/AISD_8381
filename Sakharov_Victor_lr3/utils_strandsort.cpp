#include "utils_strandsort.h"

void utils_strandsort::sort(state sta)
{
    if (sta.l1->length() <= 1)
    {
        return;
    }
    while (sta.l1->length() != 0)
    {
        int data = sta.l1->pop();
        sta.l2->push(data);
        int i = 0;
        while (i < sta.l1->length())
        {
            if ((*sta.l2)[sta.l2->length() - 1] <= (*sta.l1)[i])
            {
                int data = sta.l1->remove(i);
                sta.l2->push(data);
            }
            else
            {
                i++;
            }
        }
        i = 0;
        while (sta.l2->length() != 0)
        {
            if ((*sta.l2)[0] < (*sta.l3)[i]) {
                i++;
            }
            else {
               int data = sta.l2->remove(0);
               sta.l3->insert(i, data);
            }
        }
    }
}

void utils_strandsort::step(state sta)
{
    switch (sta.column) {
    case 0:
        if (sta.l1->length() == 0 && sta.l2->length() == 0)
        {
            sta.position = -1;
        }
        else if (sta.position >= sta.l1->length()) {
            sta.column = 1;
            sta.position = 0;
        }
        else if (sta.l2->length() == 0) {
            int data = sta.l1->remove(0);
            sta.l2->push(data);
        }
        else {
            while (sta.l1->length() > sta.position && (*sta.l2)[sta.l2->length() - 1] < (*sta.l1)[sta.position]) {
                sta.position++;
            }
            if (sta.l1->length() <= sta.position) {
                int data = sta.l1->remove(sta.position);
                sta.l2->push(data);
            }
            else {
                sta.column = 1;
                sta.position = 0;
            }
        }
        break;
    case 1:
        if (sta.l2->length() == 0) {
            sta.column = 0;
            sta.position = 0;
        }
        else {
            while (sta.l3->length() > sta.position && (*sta.l2)[0] < (*sta.l3)[sta.position]) {
                sta.position++;
            }

            int data = sta.l2->remove(0);
            if (sta.l3->length() <= sta.position) {
                sta.l3->push(data);
            }
            else {
                sta.l3->insert(sta.position, data);
            }
        }
        break;
    }
}
