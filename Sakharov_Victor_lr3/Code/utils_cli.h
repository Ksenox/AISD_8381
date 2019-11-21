#ifndef UTILS_CLI_H
#define UTILS_CLI_H

#include <iostream>
#include <cstdlib>
#include "model.h"

using namespace std;

class utils_cli
{
public:
    static int exec(int argc, char *argv[]);
};

#endif // UTILS_CLI_H
