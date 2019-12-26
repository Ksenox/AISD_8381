#ifndef TASKGENERATOR_H
#define TASKGENERATOR_H
#include <QString>
#include <randomgenerator.h>
#include <binaryrandomtreap.h>

class TaskGenerator
{
public:
    static QString generateTask(int hardness);

    TaskGenerator();
};

#endif // TASKGENERATOR_H
