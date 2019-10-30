#include "functions.h"

string postfix(string inf, bool info){
    int i = 0;
    cout << info << endl;
    string stack, str, str2;
    stack = str = str2 = "";
    while (inf[i] != '\0') {
        if (isalnum(inf[i]))
            str += inf[i];
        if (inf[i] == '+' || inf[i] == '-' || inf[i] == '*' || inf[i] == '^') {
            if (inf[i] == '*') {  //Замена умножения
                inf[i] = '.';
             }
        if (stack.empty()){
             stack += inf[i];
             str2 += "Stack:  ";
             str2 += stack;
             str2 += "\t";
         }
             else {
                 while (stack.back() >= inf[i]) { //выталкиваем все элементы из стэка
                     //До тех пор, пока приоритет верхнего элемента не будет
                     str += stack.back();                                                    //ниже входящего символа
                     stack.pop_back();
                     str2 += "Stack:  ";
                     str2 += stack;
                     str2 += "\t";
                  }
                        stack += inf[i];
                        str2 += "Stack:  ";
                        str2 += stack;
                        str2 += "\t";
             }
        }
        if (inf[i] == '(') { //Если символ - открывающая скобка
            stack += inf[i];  //добавляем ее в стэк
            str2 += "Stack:  ";
            str2 += stack;
            str2 += "\t";
        }
        if (inf[i] == ')') {    //Если встречающийся символ - закрывающая скобка
            while (stack.back() != '(') { // пока в стеке не встретится открывающая скобка
                // выталкиваем в главную строку  все символы
                str += stack.back();
                stack.pop_back();
                str2 += "Stack:  ";
                str2 += stack;
                str2 += "\t";
             }
             stack.pop_back(); //Удаляем открывающую скобку из стека
             str2 += "Stack:  ";
             str2 += stack;
             str2 += "\t";
         }
         i++;
    }
    while (!stack.empty()) { //При окончании строки выталкиваем все символы из стека
        str += stack.back();
        stack.pop_back();
        str2 += "Stack:  ";
        str2 += stack;
        str2 += "\t";
    }
    if(info){
        str += "\n";
        str += str2;
    }
    return str;
}
