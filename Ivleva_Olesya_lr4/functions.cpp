#include "functions.h"

char share(string str, string &str1, string &str2){
    int now = 1;
    int ind_now = 0;
    int flag = 0;
    for(unsigned int i = 0; i < str.length(); i++) {
        if (str[i] == '(')
            flag = 1;
        if (str[i] == ')')
            flag = 0;
        if (flag == 0) {
            if (str[i] == '-' || str[i] == '+') {
                now = 2;
                ind_now = i;
            }
            if (str[i] == '*' || str[i] == '/') {
                if (now < 2)
                    ind_now = i;
            }
        }
    }
    for(unsigned int i = 0; i < str.length(); i++) {
        if (i < ind_now)
            str1 += str[i];
        if (i > ind_now)
            str2 += str[i];
    }
    return str[ind_now];
}

tree* maketree(string str, int flag, tree *s){
    tree *symb = new tree;
    string str1 = "";
    string str2 =  "";
    if (str[1] != '\0') {
        symb->name = share(str, str1, str2);
        if (str1[0] == '(' && str1[str1.length()-1] == ')'){
            for(int i = 1; i < str1.length()-1; i++)
                str1[i-1] = str1[i];
            //str1.pop_back();
            //str1.pop_back();
            str1[str1.length()-2] = '\0';
        }
        if (str2[0] == '(' && str2[str2.length()-1] == ')'){
            for(int i = 1; i < str2.length()-1; i++)
                str2[i-1] = str2[i];
            //str2.pop_back();
            //str2.pop_back();
            str2[str2.length()-2] = '\0';
        }
    }
    else {
        symb->name = str[0];
        symb->childLeft = nullptr;
        symb->childRight = nullptr;
        symb->parent = s;
        return symb;
    }
    if (flag == 1)
        symb->parent = s;
    symb->childLeft = maketree(str1, 1, symb);
    symb->childRight = maketree(str2, 1, symb);
    return symb;
}

void printTree(tree *symb, string &output){
    output += symb->name;
    output +="\t";
    if (symb->childLeft == nullptr)
        return;
    printTree(symb->childLeft, output);
    printTree(symb->childRight, output);
}

void calc(tree *symb){
    if (symb->childLeft == nullptr){
        symb->var = int(symb->name) - 48;
        return;
    }
    calc(symb->childLeft);
    calc(symb->childRight);
    if (symb->name == '+')
        symb->var = int(symb->childLeft->var) + int(symb->childRight->var);
    if (symb->name == '-')
        symb->var = int(symb->childLeft->var) - int(symb->childRight->var);
    if (symb->name == '*')
        symb->var = int(symb->childLeft->var) * int(symb->childRight->var);
    if (symb->name == '/')
        symb->var = int(symb->childLeft->var) / int(symb->childRight->var);
}

void derivative(string &str, string symbol){
    for(int i = 0; i < str.length(); i++){
        if(str[i] == symbol[0])
            str[i] = 1;
    }
}
