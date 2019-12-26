#ifndef TESTING_H
#define TESTING_H

#include <bintree.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void generate_var_insert(string& question, string& answer, binTree& qtree, binTree& aTree, int difficulty);
void generate_vars_insert(string& question, string& answer, int count, int difficulty);

void generate_var_remove(string& question, string& answer, binTree& qtree, binTree& aTree, int difficulty);
void generate_vars_remove(string& question, string& answer, int count, int difficulty);

void file_write(string filename, string& data);

#endif // TESTING_H
