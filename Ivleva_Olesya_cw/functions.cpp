#include "functions.h"

void make_str(Hash_cl<string, string> &Hash_, string &str, string &output, int oper){
    string ke = "";
    string val = "";
    int flag = 0;
    int su;
    for (unsigned int i = 0; i < str.length(); i++) {
        if (str[i] == '|') {
            su = sum(ke);
            if (!oper){
                Hash_.do_hash_str(ke, val, su, output);
            }
            else {
                Hash_.delete_elem(ke, val, su);
            }
            flag = 0;
            ke = "";
            val = "";
            continue;
        }
        if (str[i] == ':') {
            flag = 1;
            continue;
        }
        if (flag == 0){
            ke += str[i];
        } else
            val += str[i];

    }
}

void make_str_step(Hash_cl<string, string> &Hash_st, string &str_step, string &output,int &ind_st, int oper){
    string ke = "";
    string val = "";
    int flag = 0;
    int su;
    //static unsigned int ind = 0;
    while (str_step[ind_st] != '|' && str_step[ind_st] != '\0'){
        if (str_step[ind_st] == ':') {
            flag = 1;
            ind_st++;
            continue;
        }
        if (flag == 0){
            ke += str_step[ind_st];
        } else
            val += str_step[ind_st];
        ind_st++;
    }
    su = sum(ke);
    if (!oper){
        Hash_st.do_hash_str(ke, val, su, output);
    }
    else {
        Hash_st.delete_elem(ke, val, su);
    }
    ind_st++;

}

void make_str_del(Hash_cl<string, string> &Hash_st, string &str_step, string &output,int &ind_st, int oper){
    string ke = "";
    string val = "";
    int flag = 0;
    int su;
    if (str_step[ind_st-1] == '|')
        ind_st = ind_st - 2;
    while (str_step[ind_st] != '|' && ind_st!=0){
        ind_st--;
    }
    if (ind_st!=0)
        ind_st++;
    while (str_step[ind_st] != '|' && str_step[ind_st] != '\0'){
        if (str_step[ind_st] == ':') {
            flag = 1;
            ind_st++;
            continue;
        }
        if (flag == 0){
            ke += str_step[ind_st];
        } else
            val += str_step[ind_st];
        ind_st++;
    }
    ind_st--;
    while (str_step[ind_st] != '|' && ind_st!=0){
        ind_st--;
    }
    if (ind_st!=0)
        ind_st++;
    su = sum(ke);
    if (!oper){
        Hash_st.do_hash_del(ke, val, su);
    }
    else {
        Hash_st.reset_elem(ke, val, su);
    }
}

void open(string &str) {
    ifstream fin; // создаем объект класса ifstream (считать)
    fin.open("D:\\prog\\cpp\\lab1\\text.txt"); // открываем файл для считывания
    fin >> str;
    if (!fin.is_open()) cout << "ERROR";
    fin.close(); // закрываем файл
}

int sum(string strNew) {
    int sum = 0;
    for (unsigned int i = 0; i < strNew.length(); i++) {
        sum += int(strNew[i]);
    }
    return sum;
}
