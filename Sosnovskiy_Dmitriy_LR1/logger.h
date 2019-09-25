#ifndef LOGGER_H
#define LOGGER_H
#include <QString>

class Logger
{
public:
    Logger(QString logs_file_directory);
    int getCounter();
    void increaseCounter();
    QString getFunctionName();
    void setFunctionName();
private:
    int Counter;
    QString function_name;
};

#endif // LOGGER_H
