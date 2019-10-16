#include "mainwindow.h"
#define BAD_PARENT 11
#define BAD_CHILD 12
#define NO_CLOSE 1
#define EXTRA_SYMB 2
#define EMPTY 3
#define NO_OPERATOR 4
#define NO_OPERAND 5
#define BAD_OPERAND 6
#define BAD_EQUIVALENT 7

struct HieElem
{
    bool haveChild;
    HieElem *prev;
    HieElem *next;
    union
    {
        char info;
        HieElem *child;
    };
    HieElem *parent;
    int depth;
};

struct HieList
{
    HieElem *head;
    HieElem *last;
};

int createHieList(HieList *list);
int appendNext(HieList *list, char in);
int appendChild(HieList *list, HieElem *child, int &err);
HieElem *createHieFromStr(string &in, unsigned long long &ptr, int &err);

int checkPrefix(HieElem *head, int &err);

int printRecursion(HieElem *temp, string &out);
string getList(HieElem *head);
int deleteList(HieElem *head);
