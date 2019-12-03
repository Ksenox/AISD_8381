#include "functions.h"
int s = 10000;


void resize(Hash *ri, int sum){
    Hash *arr = new Hash[sum];
    for (int i=0; i < s; i++) {
        arr[i].right = ri[i].right;
    }
    //delete[] ri;
    ri = arr;
}

void open(string &str){
    ifstream fin; // создаем объект класса ifstream (считать)
    fin.open("D:\\prog\\cpp\\lab1\\text.txt"); // открываем файл для считывания
    fin >> str;
    if(!fin.is_open()) cout<<"ERROR";
    fin.close(); // закрываем файл
}

int sum(string strNew){
    int sum = 0;
    for(int i = 0; i < strNew.length(); i++){
        sum += int(strNew[i]);
    }
    return sum;
}

void do_hash_str(Hash *ri, string &str){
    string strNew = "";
    for(int i = 0; i < str.length(); i++){
        if (str[i] != '|'){
            strNew += str[i];
        }
        else {
            if(sum(strNew) > s) {
                resize(ri, sum(strNew));
                s = sum(strNew);
            }
            if (ri[sum(strNew)].right == nullptr) {
                Right *right1 = new Right;
                right1->str = strNew;
                ri[sum(strNew)].right = right1;
            }
            else{
                Right *now = ri[sum(strNew)].right;
                Right *ne = new Right;
                while (now->r){
                    now = now->r;
                }
                ne->str = strNew;
                now->r = ne;
            }
            strNew = "";
        }
    }
}

void print_hash(Hash* start, string &output){
    for (int i = 0; i < s; i++){
        if(start[i].right) {
            Right *now = start[i].right;
            while (now) {
                output+= now->str;
                output += "\t";
                now = now->r;
            }
        }
    }
}

void find_el(string input, Hash* ri, string &output){
    string strNew = "";
    for(int i = 0; i < input.length(); i++) {
        if (input[i] != '|') {
            strNew += input[i];
        }
        else {
            if (ri[sum(strNew)].right) {
                Right *now = ri[sum(strNew)].right;
                while (now->r) {
                    if (now->str == strNew) {
                        output += strNew;
                        output += "   :   yes";
                        output += "\n";
                        break;
                    }
                    now = now->r;
                    if (now->r == nullptr) {
                        Right *new1 = new Right;
                        new1->str = strNew;
                        new1->r = nullptr;
                        now->r = new1;
                        break;
                    }
                }
            } else {
                Right *right1 = new Right;
                right1->str = strNew;
                ri[sum(strNew)].right = right1;
            }
            strNew = "";
        }
    }
}
