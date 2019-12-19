#ifndef GENERATOR_H
#define GENERATOR_H

#include <cstdlib>
#include <string>
#include <time.h>
#include <sstream>


class generator {
public:
    static std::string* generate();
    static void ground();

private:
    static int length;
};

#endif // GENERATOR_H
