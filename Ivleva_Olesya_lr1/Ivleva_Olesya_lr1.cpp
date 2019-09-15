#include <iostream>
#include <cstdio>
#include <cctype>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int uns_int(string, int, int);
int integ(string, int, int);
int z = 0;
int point = 0;
int e = 0;

int uns_int(string s, int kol, int start){
    if (start < kol) {
        cout << "Hi, it is uns_int" << endl;
        if (isdigit(s[start])) {
            cout << "Hi, it is isDig uns_int" << "   Now:" << s[start] << endl;
            return uns_int(s, kol, start + 1) + z;
        } else if (s[start] == '.') {
            cout << "Hi, it is .  uns_int" << "   Now:" << s[start] << endl;
            if ((point == 0) && (start != (kol-1)) && (e != 1)){
                point = 1;
                return uns_int(s, kol, start + 1) + z;
            }else return 1;
        } else if (s[start] == 'E') {
            cout << "Hi, it is E  uns_int" << "   Now:" << s[start] << endl;
            if ((e == 0) && (s[start-1] != '.')){
                e = 1;
                return integ(s, kol, start + 1) + z;
            } else return 1;
        } else if (isspace(s[start])) {
            cout << "Hi, it is isprint uns_int" << "   Now:" << s[start] << endl;
            if ((point != 0) || (e != 0))
                return 0;
            else {
                z = 1;
                return 1;}
        } else {
            cout << "Hi, it is strange" << "   Now:" << s[start] << endl;
            z = 1;
            return 1;
        }
    }
    else return 0;
}

int integ(string s, int kol, int start){
    cout << "Hi, it is integ" << endl;
    int k = 0;
    if (s[start] == '+' || s[start] == '-' || isdigit(s[start])) {
        cout << "Hi, it is + - isdig integ" << "   Now:" << s[start] << endl;
        if ((s[start] == '+' || s[start] == '-') && (start == (kol-1)) )
            return 1;
        else
            return uns_int(s, kol, start+1);
    }
    else return 1;
}

int main() {
    int f;
    int k;
    string mas;
    cout << "Do you want to read from file?" << endl;
    cin >> f;
    if (f == 1) {
        ifstream fin; // создаем объект класса ifstream (считать)
        fin.open("D:\\prog\\cpp\\lab1\\text.txt"); // открываем файл для считывания
        fin >> mas;
        if(!fin.is_open()) cout<<"ERROR";
        fin.close(); // закрываем файл
        ofstream fin2; //дозаписать
        fin2.open("D:\\prog\\cpp\\lab1\\text.txt", ios::app); // открываем файл и дозыписываем в него
        //cout << mas.length() << endl;
        k = integ(mas, mas.length(), 0);
        fin2 << endl;
        if ((k == 0) && mas.length() != 1)
            fin2 << "Yes";
        else
            fin2 << "NO";
        fin.close(); // закрываем файл
    }
    else{
        cin >> mas;
        //mas = "64";
        //cout << mas.length();
        k = integ(mas, mas.length(), 0);
        if ((k == 0) && mas.length() != 1)
            cout << "Yes";
        else
            cout << "NO";
    }
    return 0;
}