#include "utils_strandsort.h"

void utils_strandsort::sort(state& s)
{
    while(!s.l1->empty())
    {
        s.l2->clean();
        s.l2->push_back(s.l1->pop_front());
        for(int i = 0; i < s.l1->size(); i++)
        {
            if(s.l1->at(i) > s.l2->back())
            {
                s.l2->push_back(s.l1->remove(i));
                i--;
            }
        }
        int j = 0;
        while (!s.l2->empty())
        {
            bool spliced = false;
            for(;j < s.l3->size(); j++)
            {
                if(s.l2->front() < s.l3->at(j))
                {
                    s.l3->insert(j, s.l2->pop_front());
                    j++;
                    spliced = true;
                    break;
                }
            }
            if(!spliced)
            {
                s.l3->push_back(s.l2->pop_front());
            }
        }
    }
}

void utils_strandsort::step(state& s)
{
    switch (s.column) {
    case 0:
        if (s.l1->empty() && s.l2->empty()) return;
        s.l2->clean();
        s.l2->push_back(s.l1->pop_front());
        s.column = 1;
        s.position = 0;
        break;
    case 1:
        if (s.position >= s.l1->size())
        {
            s.column = 2;
            s.position = 0;
            return;
        }
        while (s.position < s.l1->size())
        {
            if (s.l1->at(s.position) > s.l2->back())
            {
                s.l2->push_back(s.l1->remove(s.position));
                break;
            }
            s.position++;
        }
        break;
    case 2:
        if (s.l2->empty())
        {
            s.column = 0;
            s.position = 0;
            return;
        }
        bool spliced = false;
        for(;s.position < s.l3->size(); s.position++)
        {
            if(s.l2->front() < s.l3->at(s.position))
            {
                s.l3->insert(s.position, s.l2->pop_front());
                s.position++;
                spliced = true;
                break;
            }
        }
        if(!spliced)
        {
            s.l3->push_back(s.l2->pop_front());
        }
        break;
    }

}
