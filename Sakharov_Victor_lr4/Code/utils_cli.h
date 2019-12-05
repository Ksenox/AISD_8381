#ifndef UTILS_CLI_H
#define UTILS_CLI_H
#include <string>
#include <iostream>
#include "utils_headers.h"
#include "utils_tree.h"

class utils_cli
{
public:
    static int execute(int argc, char *argv[]);
private:
    utils_cli(){}
};

#endif // UTILS_CLI_H
