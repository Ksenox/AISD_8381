#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

void shift(int *&str, int ind, char simb, int len);

int isnum(char simb);

int which_oper(int oper, int num1, int num2);

void calculator(string &expression);

int *step(int *expression, int *j, int *l);

int step_by_step(int *expression, int *len);

int test(string str);