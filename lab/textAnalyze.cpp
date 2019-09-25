#include "basicComponents.h"
void symbol(string&, char&, string&, int&);
void printDepth(string&, int&);
void printDepthReverse(string&, int&);
int square(string&, char&, string&, int&, int&);
int round(string&, char&, string&, int&, int&);
int figure(string&, char&, string&, int&, int&);
void symbol(string & arr, char& a, string & result, int & pos){
    a = arr[pos];
    result+=a;
    result+='\n';
    pos++;
}
void printDepth(string & result, int & depth){
    for(int i=0; i < depth; i++){
        result.append(" ");
    }
    depth++;
}
void printDepthReverse(string & result, int & depth){
    depth--;
    for(int i=0; i < depth; i++){
        result.append(" ");
    }
}
int square(string & arr, char& a, string & result, int & pos, int & depth){
    printDepth(result, depth);
    if(a == '+'){
        depth--;
        result.append("Это квадратная скобка\n");
        return 1;
    }
    if(a == '['){
        result.append("Это квадратная скобка\n");
        symbol(arr, a, result, pos);
        if(round(arr, a, result, pos, depth)){
            symbol(arr, a, result, pos);
            if(figure(arr, a, result, pos, depth)){
                symbol(arr, a, result, pos);
                if(a == ']'){
                    printDepthReverse(result, depth);
                    result.append("Это квадратная скобка\n");
                    return 1;
                }
            }
        }
    }
    else{
        result.append("Отсутствует + или [\n");
    }
    return 0;
}
int round(string & arr, char& a, string & result, int & pos, int & depth){
    printDepth(result, depth);
    if(a == '-'){
        depth--;
        result.append("Это круглая скобка\n");
        return 1;
    }
    if(a == '('){
        result.append("Это круглая скобка\n");
        symbol(arr, a, result, pos);
        if(figure(arr, a, result, pos, depth)){
            symbol(arr, a, result, pos);
            if(square(arr, a, result, pos, depth)){
                symbol(arr, a, result, pos);
                if(a == ')'){
                    printDepthReverse(result, depth);
                    result.append("Это круглая скобка\n");
                    return 1;
                }
            }
        }
    }
    else{
        result.append("Отсутствует - или (\n");
    }
    return 0;
}
int figure(string & arr, char& a, string & result, int & pos, int & depth){
    printDepth(result, depth);
    if(a == '0'){
        depth--;
        result.append("Это фигурная скобка\n");
        return 1;
    }
    if(a == '{'){
        result.append("Это фигурная скобка\n");
        symbol(arr, a, result, pos);
        if(square(arr, a, result, pos, depth)){
            symbol(arr, a, result, pos);
            if(round(arr, a, result, pos, depth)){
                symbol(arr, a, result, pos);
                if(a == '}'){
                    printDepthReverse(result, depth);
                    result.append("Это фигурная скобка\n");
                    return 1;
                }
            }
        }
    }
    else{
        result.append("Отсутствует 0 или {\n");
    }
    return 0;
}
void brasket(string arr, string & result){
    char a;
    int b=0;
    int depth=0;
    int pos=0;
    symbol(arr, a, result, pos);
    if(a == '+' || a == '['){
        b = square(arr, a, result, pos, depth);
    }
    else if(a == '-' || a == '('){
        b = round(arr, a, result, pos, depth);
    }
    else if(a == '0' || a == '{'){
        b = figure(arr, a, result, pos, depth);
    }
    if(b && pos != arr.length()){
        result.append("Присутствуют дополнительные символы. Это не скобки\n");
    }
    else if(b){
        result.append("Это скобки\n");
    }
    else{
        result.append("Это не скобки\n");
    }
}
