#include <iostream>
#include <string>
#include <cctype>
#include <string>
#include <fstream>

using namespace std;

struct Right;
struct Hash;
void open(string &str);
void do_hash_str(Hash *ri, string &str);
void print_hash(Hash start[],string &output);
void resize(Hash *ri, int sum);
void find_el(string input, Hash* ri, string &output);

struct Right{
    Right *r = nullptr;
    string str = "";
};

struct Hash{
    Right *right = nullptr;
};
