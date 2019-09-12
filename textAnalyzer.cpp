#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int pos = 0;
int depth = 0;
void symbol(string , char& );
void printDepth();
void printDepthReverse();
int square(string, char&);
int round(string, char&);
int figure(string, char&);
void symbol(string arr, char& a){
    a = arr[pos];
    cout << a << endl;
    pos++;
}
void printDepth(){
    for(int i=0; i < depth; i++){
        cout << " ";
    }
    depth++;
}
void printDepthReverse(){
    depth--;
    for(int i=0; i < depth; i++){
        cout << " ";
    }
}
int square(string arr, char& a){
    printDepth();
    if(a == '+'){
        depth--;
        cout << "Это квадратная скобка" << endl;
        return 1;
    }
    if(a == '['){
        cout << "Это квадратная скобка" << endl;
        symbol(arr, a);
        if(round(arr, a)){
            symbol(arr, a);
            if(figure(arr, a)){
                symbol(arr, a);
                if(a == ']'){
                    printDepthReverse();
                    cout << "Это квадратная скобка" << endl;
                    return 1;
                }
            }
        }
    }
    else{
        cout << "Отсутствует + или [" << endl;
    }
    return 0;
}
int round(string arr, char& a){
    printDepth();
    if(a == '-'){
        depth--;
        cout << "Это круглая скобка" << endl;
        return 1;
    }
    if(a == '('){
        cout << "Это круглая скобка" << endl;
        symbol(arr, a);
        if(figure(arr, a)){
            symbol(arr, a);
            if(square(arr, a)){
                symbol(arr, a);
                if(a == ')'){
                    printDepthReverse();
                    cout << "Это круглая скобка" << endl;
                    return 1;
                }
            }
        }
    }
    else{
        cout << "Отсутствует - или (" << endl;
    }
    return 0;
}
int figure(string arr, char& a){
    printDepth();
    if(a == '0'){
        depth--;
        cout << "Это фигурная скобка" << endl;
        return 1;
    }
    if(a == '{'){
        cout << "Это фигурная скобка" << endl;
        symbol(arr, a);
        if(square(arr, a)){
            symbol(arr, a);
            if(round(arr, a)){
                symbol(arr, a);
                if(a == '}'){
                    printDepthReverse();
                    cout << "Это фигурная скобка" << endl;
                    return 1;
                }
            }
        }
    }
    else{
        cout << "Отсутствует 0 или {" << endl;
    }
    return 0;
}
void brasket(string arr){
    char a;
    int b=0, length=0;
    symbol(arr, a);
    if(a == '+' || a == '['){
        b = square(arr, a);
    }
    else if(a == '-' || a == '('){
        b = round(arr, a);
    }
    else if(a == '0' || a == '{'){
         b = figure(arr, a);
    }
    if(b && pos != arr.length()){
        cout << "Присутствуют дополнительные символы. Это не скобки" << endl;
    }
    else if(b){
        cout << "Это скобки" << endl;
    }
    else{
        cout << "Это не скобки" << endl;
    }
}

int main() {
    string arr;
    int k;
    cout<<"Анализатор скобок"<<endl;
    cout<<"Выберите каким способом осуществить ввод данных:"<<endl;
    cout<<"1. Из файла"<<endl;
    cout<<"2. Из консоли"<<endl;
    cin>>k;
    if(k==1){
        ifstream file("/Users/marialisok/source.txt");
        file >> arr;
        brasket(arr);
        file.close();
    }
    else if(k==2){
        cout<<"Введите строку, которую нужно проверить: "<<endl;
        cin >> arr;
        brasket(arr);
    }
    return 0;
}
