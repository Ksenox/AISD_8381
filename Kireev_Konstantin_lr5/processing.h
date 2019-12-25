#ifndef PROCESSING_H
#define PROCESSING_H
#include <hash.h>
#include <ctime>

int beginning(QTextEdit *&output, bool flga, QLineEdit *&input, QTextEdit *&in);

void deleteItemFromHashTable(QTextEdit *&output, QLineEdit *&input);

void createHashTable(QTextEdit *&output, QTextEdit *&in, QTextEdit *&info);

void generateAverageCase(QTextEdit *&output, QLineEdit *&sizeac);

string generateRandomString(size_t len);

#endif // PROCESSING_H
