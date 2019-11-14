#ifndef UTILS_CLI_H
#define UTILS_CLI_H

#include "iostream"
#include "mainmodel.h"

using namespace std;

class utils_cli
{
public:
    static int exec(int argc, char *argv[]);

private:
    utils_cli(){} // Static class
};

#endif // UTILS_CLI_H
