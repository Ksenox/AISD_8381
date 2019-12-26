#ifndef RANDOMPRIORITIESGENERATOR_H
#define RANDOMPRIORITIESGENERATOR_H
#include <random>
#include <time.h>
using namespace std;

class RandomGenerator
{
private:
    RandomGenerator();

    static int* generateUniform(int amount);

public:
    static int* getElements(int amount);

    static int* getPriorities(int amount);
};

#endif // RANDOMPRIORITIESGENERATOR_H
