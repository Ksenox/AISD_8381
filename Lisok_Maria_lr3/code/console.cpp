#include "console.h"

void startConsole(){
    string  checkInput;
    cin >> checkInput;
    string result;
    string error;

    long answer = calculation(checkInput, result, error);
    if(!error.empty()){
        cout << error;
    }else{
        string str = "Результат вычислений: ";
        str+=to_string(answer);
        cout << str;
    }
}
