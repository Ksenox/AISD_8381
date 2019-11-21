#include "model.h"

logic_model::logic_model()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    busy = false;
    current = state();
    SetArr();
}

void logic_model::Clear()
{
    current.column = 0;
    current.position = 0;
    current.l1->clean();
    current.l2->clean();
    current.l3->clean();
}

void logic_model::SetArr()
{
    current.l1 = new utils_vector<int>();
    current.l2 = new utils_vector<int>();
    current.l3 = new utils_vector<int>();
    Clear();
}

void logic_model::SetLinked()
{
    current.l1 = new utils_linked<int>();
    current.l2 = new utils_linked<int>();
    current.l3 = new utils_linked<int>();
    Clear();
}

void logic_model::Generate(int count, int maxnum)
{
    Clear();
    for (int i = 0; i < count; i++)
    {
        current.l1->push_back(rand() % maxnum);
    }
}

void logic_model::Sort()
{
    if (current.l2->empty() && current.l3->empty())
    {
        utils_strandsort::sort(current);
    }
    else
    {
        while (!current.l1->empty() || !current.l2->empty()) utils_strandsort::step(current);
    }
    current.column = 3;
}

void logic_model::SortStep()
{
    utils_strandsort::step(current);
}

std::string logic_model::ToString()
{
    std::string res = "L1: ";
    for (int i = 0; i < current.l1->size(); i++)
    {
        res += std::to_string(current.l1->at(i)) + " ";
    }
    res += "\nL2: ";
    for (int i = 0; i < current.l2->size(); i++)
    {
        res += std::to_string(current.l2->at(i)) + " ";
    }
    res += "\nL3: ";
    for (int i = 0; i < current.l3->size(); i++)
    {
        res += std::to_string(current.l3->at(i)) + " ";
    }
    return res;
}
