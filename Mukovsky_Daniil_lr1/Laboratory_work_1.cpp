#include <iostream>
#include <cstring>
#include <fstream>
#include <windows.h>
#include "conio.h"
#include <fstream>

#define MAX_SIZE 100

using namespace std;

bool bracket(char* arr,int*i,int*numb);

bool brackets(char* arr, int* i, int* numb) {
	cout << "<зашел в brackets>\n";
	(*numb)++;
	if (arr[(*i)] == 'A') return true;                     
	if (arr[(*i)] == '('){
		(*i)++;
		if (bracket(arr,i,numb) == true)        
			if (brackets(arr, i,numb) == true) 
				return true;
	}
	return false;
}

bool bracket(char* arr, int* i, int*numb){
	cout << "<зашел в bracket>\n";
	(*numb)++;
	if (arr[(*i)] == 'B') {
		(*i)++;
		if (brackets(arr, i,numb) == true) {
			(*i)++;
			if (arr[(*i)] == ')') {
				(*i)++;
				return true;
			}
		}
	}
	return false;
}

char menu() {
	cout << "Введите '1' в случае считывания из файла\nВведите '2' в случае считывания из консоли\n";
	char key = _getch();
	return key;
}

int check(char* arr) {
	if (!(arr[0] == 'A' || arr[0] == '(')) {
		cout << "Неверные данные\n";
		delete[] arr;
		return 1;
	}
	return 0;
}

int reading_data(char** arr, char key) {
	int ch;
	if (!(key == '1' || key == '2')) {
		cout << key << "Ошибка введенного ключа\n";
		return 0;
	}
	if (key == '1') {
		ifstream fs("input.txt", ios::in | ios::binary);
		if (!fs) return 0;                                           //Считывание из файла
		fs.istream::getline(*arr, MAX_SIZE - 1, '\n');
		cout << *arr << endl;
		if (ch = check(*arr)) return 0;
		fs.close();
	}
	if (key == '2') {
		cout << "Введите скобки\n";
		fgets(*arr, MAX_SIZE, stdin);                //Считывание из консоли
		(*arr)[strlen(*arr) - 1] = '\0';
		if (ch = check(*arr)) return 0;
	}
	return 1;
}
void entry_results_in_file(char* ptr0_arr, int numb,int flag) {
	std::ofstream out;          
	out.open("output.txt"); 
	if (out.is_open()){
		if (flag) {
			out << ptr0_arr << " - это определенно скобки \n";
			out << "Количество заходов в рекурсию: " << numb;             //Вывод информации в файл
		}
		if (!flag) {
			out << "Это не скобки\nЧасть прошедшая проверку:" << ptr0_arr << "\n";
			out << "Количество заходов в рекурсию: " << numb;
		}
	}
	return;
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	char* arr;
	char* ptr0_arr;
	arr = new char[MAX_SIZE];
	if (argc > 1) {
		strcpy_s(arr, MAX_SIZE ,argv[1]);
		cout << arr;
	}
	else {
		char key = menu();
		int ret = reading_data(&arr, key);
		if (!ret) return 0;
	}
	ptr0_arr = arr;
	int flag = 0;
	int i = 0, numb = 0;
	bool answer = brackets(arr, &i,&numb);
	if (answer && arr[i + 1] != '\0') {
		arr[i+1] = '\0';                    
		cout << "Это не скобки\nЧасть прошедшая проверку:" << ptr0_arr << "\n";
		cout << "Количество заходов в рекурсию: " << numb;
		entry_results_in_file(ptr0_arr,numb,flag);
		delete[] ptr0_arr;
		return 0;
	}
	if (answer) {
		flag = 1;
		cout << ptr0_arr << " - это определенно скобки \n";
		cout << "Количество заходов в рекурсию: " <<numb;
		entry_results_in_file(ptr0_arr, numb,flag);
	}
	else {
		arr[i+1] = '\0';
		cout << "Это не скобки\nЧасть прошедшая проверку:" << ptr0_arr << "\n";
		cout << "Количество заходов в рекурсию: " <<numb;
		entry_results_in_file(ptr0_arr, numb,flag);
	}
	delete[] ptr0_arr;
	return 0;
}