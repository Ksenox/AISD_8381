#ifndef MODEL_H
#define MODEL_H

#include <cstdlib>
#include <ctime>
#include <string>
#include "state.h"
#include "utils_vector.h"
#include "utils_linked.h"
#include "utils_strandsort.h"

class logic_model
{
public:
    logic_model();
    void Clear();
    void SetArr();
    void SetLinked();
    void Generate(int count = 15, int maxnum = 100);
    void Sort();
    void SortStep();
    std::string ToString();

    bool busy;
    state current;
};

#endif // MODEL_H
