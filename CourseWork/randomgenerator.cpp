#include "randomgenerator.h"

int* RandomGenerator::getPriorities(int amount)
{
    return generateUniform(amount);
}

int* RandomGenerator::getElements(int amount)
{
    srand(time(NULL));
    int* returnable = new int[amount];
    for(int i = 0; i < amount; i++)
    {
        returnable[i] = rand() % 100 + 1;
    }
    return returnable;
}

int* RandomGenerator::generateUniform(int amount)
{
    srand(time(NULL));
    /*std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, amount);
*/
    int* returnable = new int[amount];
    for(int i = 0; i < amount; i++)
    {
        returnable[i] = rand() % amount + 1;
    }
    return returnable;
}
