#include "functions.h"

hlist* r_make(string &mas, int &start, int &err){
    hlist *head = nullptr;
    hlist *last = nullptr;
    hlist *now = nullptr;
    if (err)
        return head;
    while (mas[start]){
        if (mas[start] == ' ') {
            start++;
            continue;
        }
        if (mas[start] != '(' && mas[start] != ')') {
            if(head == nullptr){
                head = new hlist;
                head->flag = 1;
                head->symb = mas[start++];
                head->ptr_next = nullptr;
                last = head;
            }
            else
            {
                now = new hlist;
                last->ptr_next = now;
                now->flag = 1;
                now->symb = mas[start++];
                now->ptr_next = nullptr;
                last = now;
            }
        }
        else if (mas[start] == '('){
            now = new hlist;
            if (head == nullptr){
                head = now;
                last = now;
            }
            else {
                last->ptr_next = now;
                last = now;
            }
            now->flag = 0;
            now->ptr_next = nullptr;
            start++;
            now->ptr_child = r_make(mas, start, err);
        }
        else if (mas[start] == ')'){
            start++;
            return head;
        }
    }
        return head;
}

hlist* del_x(hlist *now, char &x, string &output, bool info){
    int st = 1;
    hlist *head = now;
    hlist *prev = now;
    while (now) {
        if (now->flag == 1) {
            if (info){
                output += now->symb;
                if (now->symb != x){
                    output += "\t";
                }
                else {
                    output += " ";
                }
            }
            if (now->symb == x) {
                if (info){
                    output += "Delete!";
                    output += "\t";
                }
                if (st == 1) {
                    if (head->ptr_next == nullptr)
                        return nullptr;
                    head = head->ptr_next;
                    prev = head->ptr_next;
                }
                else {
                    prev->ptr_next = now->ptr_next;
                }
            }
            else {
                prev = now;
                st = 0;
            }
            now = now->ptr_next;
        }
        else{
            now->ptr_child = del_x(now->ptr_child, x, output, info);
            prev = now;
            now = now->ptr_next;
        }
    }
    return head;
}

void print_list(hlist *now, string &output){
    if(now){
        if (now->flag == 1) {
            output += now->symb;
        }
        else {
            output += "(";
            print_list(now->ptr_child, output);
            output += ")";
        }
        print_list(now->ptr_next, output);
    }
}

