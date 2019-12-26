#include "taskgenerator.h"

QString TaskGenerator::generateTask(int hardness)
{
    QString task = nullptr;
    task += "Для заданного входного набора ключей и приоритетов построить последовательность рандомизированных пирамид поиска,\nполученных поочередной вставкой данных их входного набора.\n";
    task += "Входной набор:\n";


    int* input = RandomGenerator::getElements(hardness);
    int* priorities = RandomGenerator::getPriorities(hardness);

    for(int i = 0; i < hardness; i++)
    {
        task += "(";
        task += QString::number(input[i]);
        task += " ; ";
        task += QString::number(priorities[i]);
        task += ")";
        if(i != hardness -1)  task += ", ";
    }
    task += "\n";

    BinaryRandomTreap treap(input, priorities, hardness, task);

    task += "\n";
    task += "Для полученного дерева исключить элемент ";
    int elNumb = rand()%hardness;
    task += QString::number(input[elNumb]);
    task += "\n";
    treap.removeNode(QString::number(input[elNumb]), task);

    return task;
}
