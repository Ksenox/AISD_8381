#include "generator.h"


int generator::length = 12;

void generator::ground() {
    long long ltime = time(nullptr);
    unsigned int stime = static_cast<unsigned int>(ltime/2);
    srand(stime);
}

std::string* generator::generate() {
    std::stringstream result;
    double randomite = 0;
    bool two_trees = (static_cast<double>(rand()) / RAND_MAX) > 0.5;

    while (randomite < length) {
        double ran = static_cast<double>(rand());

        randomite += (ran / RAND_MAX) + 1;
        int comp = static_cast<int>(ran) % 100;

        result << comp;
        if (two_trees && (randomite > (static_cast<int>(rand()) % length))) {
            result << " = ";
            two_trees = false;
        }
        else result << ", ";
    }

    result << static_cast<int>(rand()) % 100;
    return new std::string(result.str());
}
