#include <iostream>
#include <cstdio>
#include <string>
#include <cctype>
#include <stack>
#include "conio.h"
#include <fstream>

using namespace std;

struct s_expr {
	int flag;
	s_expr* ptr_next;
	union {										//реализация элемента иерархического списка
		char atom;
		s_expr* ptr_child;
	};

};

int is_right(string& arr) {
	stack <char> st;
	for (int i = 1; i < arr.length()-1; i++) {
		if (arr[i] == '(') {
			st.push(arr[i]);
			continue;
		}
		if (arr[i] == ')') {
			if (st.empty())								//проверка правильности скобок
				return 1;
			char top_elem = st.top();
			if (top_elem == '(')
				st.pop();
			else return 1;
		}
	}
	if (st.empty())
		return 0;
	return 1;
}

s_expr* make_list(string& arr, int& count) {
	s_expr* head = nullptr;
	s_expr* last = nullptr;
	s_expr* cur = nullptr;
	while (arr[count]) {
		if (arr[count] == '(') {
			cur = new s_expr;
			if (!head) {
				head = cur;
				last = cur;
			}
			else {
				last->ptr_next = cur;
				last = cur;
			}
			cur->flag = 0;
			cur->ptr_next = nullptr;
			count++;
			cur->ptr_child = make_list(arr, count);
		}
		else
			if (arr[count] != '(' && arr[count] != ')') {
				if (!head) {
					head = new s_expr;
					head->flag = 1;
					head->ptr_next = nullptr;
					head->atom = arr[count];
					last = head;
					count++;
				}
				else {
					cur = new s_expr;
					last->ptr_next = cur;
					cur->flag = 1;
					cur->ptr_next = nullptr;
					cur->atom = arr[count];
					last = cur;
					count++;
				}
			}
			else
				if (arr[count] == ')') {
					count++;
					return head;
				}
	}
	return head;
}


void deep_rec(s_expr* cur,int& answer,int &count) {
	if (cur) {  
		if (cur->flag == 0 && cur->ptr_child){
			count++;
			deep_rec(cur->ptr_child,answer,count);								//функция нахождения глубины иерархического списка
		}
		if (count > answer) answer = count;
		if (cur->flag == 0 && !(cur->ptr_next) && !(cur->ptr_child)) count = 0;
		if (cur->flag == 1 && !(cur->ptr_next)) count = 0;
		deep_rec(cur->ptr_next,answer,count);
	}
}

int reads_data(string& arr) {
	cout << ">>Menu:\n>>Type '1' if you want to read data from the console"
		<< "\n>>Type '2' if you want to read data from the file input.txt"
		<< "\n>>Type 'Esc' if you want to exit" << endl;
	char key = _getch();
	if (key == '1') {
		cout << ">>Enter" << endl;
		getline(cin, arr);												//Считывание из консоли
		if (!arr[0]) {
			cout << ">>\nWrong input";
			return 1;
		}
	}
	else if (key == '2') {
		ifstream fs("input.txt", ios::in | ios::binary);
		if (!fs) {
			cout << ">>Error reading file\n";							//Считывание из файла
			return 1;
		}
		getline(fs, arr);
		fs.close();
	}
	else if (key == 27){
		cout << ">>Goodbye\n";
		return 1;
	}
	else {
		cout<<">>Incorrect command, try again\n";
		reads_data(arr);
	}
	while (arr.find(' ') != string::npos)		//Удаление лишних пробелов
		arr.erase(arr.find(' '), 1);

	if (arr[0] != '(' && arr[arr.length() - 1] != ')') {
		cout << ">>\nWrong input";
		return 1;													
	}															//Проверка на корректность введенного списка
	if (is_right(arr)) {
		cout << ">>\nWrong input";
		return 1;
	}
	cout << "\n>>List:" << arr;
	return 0;
}

void prints_result(int answer, string &arr) {
	cout << "\n>>Type 'f' if you want to save result in file output.txt"
		<< "\n>>Else type any button" << endl;
	char key = _getch();
	if (key == 'f') {
		std::ofstream out;
		out.open("output.txt");
		if (out.is_open()) {																//Вывод результата в файл
			cout << "\n>>The depth of the hierarchical list: " << answer<<endl;
			out << ">>List: " << arr << '\n';
			out << ">>The depth of the hierarchical list: " << answer << endl;
			out.close();
			return;
		}
	}
	else {
		cout << "\n>>The depth of the hierarchical list: " << answer << endl;
		return;
	}
}


int main(int argc, char* argv[])
{
	string arr;
	if (argc > 1) {
		std::string arr_c(argv[1]);
		arr = arr_c;
	}
	else if (reads_data(arr)) return 0;
	int count = 0;
	s_expr* head = make_list(arr, count);
	int answer = 0;
	count = 0;
	deep_rec(head,answer,count);
	prints_result(answer,arr);
	return 0;
}
