#include <iostream>
#include <string>
#include <cctype>
#include <string>
#include <fstream>
#include "h_class.h"

using namespace std;

void open(string &str);
int sum(string strNew);
void make_str(Hash_cl<string, string> &Hash_, string &str, string &output,int oper);
void make_str_step(Hash_cl<string, string> &Hash_st, string &str_step, string &output,int &ind_st, int oper);
void make_str_del(Hash_cl<string, string> &Hash_st, string &str_step, string &output,int &ind_st, int oper);
