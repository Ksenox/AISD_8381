#ifndef PROCESSING_H
#define PROCESSING_H
#include <hash.h>

void deleteItemFromHashTable(QTextEdit *&output, QLineEdit *&input, QTextEdit *&info);

void insertItemToHashTable(QTextEdit *&output, QLineEdit *&input, QTextEdit *&info);

void createHashTable(QTextEdit *&output, QTextEdit *&in, QTextEdit *&info);

void generateAverageCase(QTextEdit *&output, QLineEdit *&sizeac, QLineEdit *&len);

void generateWorstCase(QTextEdit *&in, QLineEdit *&sizeac, QLineEdit *&len);

void generateWorstCase2(QTextEdit *&in, QLineEdit *&sizeac, QLineEdit *&len);

string generateRandomString(int len);

#endif // PROCESSING_H
