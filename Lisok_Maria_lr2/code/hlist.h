#ifndef HLIST_H
#define HLIST_H
#include <iostream>
#include <fstream>
using namespace std;
class HList;
class S_expr;
class Two_ptr{
public:
    S_expr* head;
    S_expr* tail;

    Two_ptr()
    :head{}, tail{}
    {
    }
    S_expr* getHead() const{
        return head;
    }
    S_expr* getTail() const{
        return tail;
    }
};
typedef union Node{
    char element;
    Two_ptr pair;
}Node;
class S_expr{
    bool flag;
public:
    Node node;
    S_expr()
    :flag{}, node{}
    {
    }
    bool getFlag() const{
        return flag;
    }
    Node getNode() const{
        return node;
    }
    void setFlag(bool flag){
        this->flag = flag;
    }
    void setNodeElement(char element){

        this->node.element = element;
    }
};
class HList{
    S_expr el;
public:
    HList():el{}
    {

    }
    S_expr* cons (S_expr* head, S_expr* tail, string&);
    void destroy (S_expr* s, string&);
    bool isAtom (const S_expr* s);
    bool isNull (const S_expr* s);
    S_expr* head (const S_expr* s, string&);
    S_expr* tail (const S_expr* s, string&);
    char getAtom (const S_expr* s, string&);
    S_expr* makeAtom (const char x);
    int read_s_expr(S_expr*& s, string, string&, int&);
    int read(char prev, S_expr*& s, string &, int&, string&);
    int read_seq (S_expr*& s, string &, int&, string&);
    S_expr* copy_list(const S_expr* x);
};
#endif
