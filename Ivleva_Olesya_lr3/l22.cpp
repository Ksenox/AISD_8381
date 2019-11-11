#include <iostream>
#include <cstdio>
#include <cctype>
#include <string.h>

using namespace std;

struct hlist {
    int flag;
    hlist* ptr_next;
    union {
        char symb;
        hlist *ptr_child;
    };
};

hlist* r_make(string &mas, int &start, int &err);
hlist* del_x(hlist *now, char &x);
void print_list(hlist *now);


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
        cout << mas[start] << endl;
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

hlist* del_x(hlist *now, char &x){
    int st = 1;
    hlist *head = now;
    hlist *prev = now;
    while (now) {
        if (now->flag == 1) {
            if (now->symb == x) {
                if (st == 1) {
                    if (head->ptr_next == nullptr)
                        return nullptr;
                    head = head->ptr_next;
                    prev = head->ptr_next;
                }
                else {
                    prev->ptr_next = now->ptr_next;
                }
                st = 0;
            }
            else {
                prev = now;
            }
            now = now->ptr_next;
        }
        else{
            now->ptr_child = del_x(now->ptr_child, x);
            prev = now;
            now = now->ptr_next;
        }
    }
    return head;
}

void print_list(hlist *now){
    if(now){
        if (now->flag == 1) {
            cout << now->symb;
        }
        else {
            cout << "(";
            print_list(now->ptr_child);
            cout << ")";
        }
        print_list(now->ptr_next);
    }
}

int main() {
    char x;
    string mas = "(aba(adaaar)(a(a))aasda)";
    cin >> x;
    int start = 1;
    int err = 0;
    hlist *head = r_make(mas, start, err);
    hlist *del_head = del_x(head, x);
    print_list(del_head);
    return 0;
}
