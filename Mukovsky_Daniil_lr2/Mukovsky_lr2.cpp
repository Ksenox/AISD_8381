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

s_expr* make_list(string& arr, int& count, int& flag, stack <char>& st, int& numb, string& result_if) {
	s_expr* head = nullptr;
	s_expr* last = nullptr;
	s_expr* cur = nullptr;
	if (flag == 0) return nullptr;
	while (arr[count]) {
		if (arr[count] == '(') {
			if (count != 0 && count != arr.length() - 1) {
				st.push(arr[count]);
			}
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
			numb++;
			cur->ptr_child = make_list(arr, count,flag,st,numb,result_if);
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
					numb++;
				}
				else {
					cur = new s_expr;
					last->ptr_next = cur;
					cur->flag = 1;
					cur->ptr_next = nullptr;
					cur->atom = arr[count];
					last = cur;
					count++;
					numb++;
				}
			}
			else
				if (arr[count] == ')') {
					string arr_err;
					if (count != 0 && count != (arr.length()-1)) {
						if (st.empty()) {
							if (flag == 1) {
								result_if = "\nError: No open bracket\n";
								cout << "\nError: No open bracket\n";
								flag = 0;
							}
							return nullptr;
						}
						char top_elem = st.top();
						if (top_elem == '(') {
							st.pop();
						}					
					}
					count++;
					return head;
				}
	}
	if (st.empty())
		return head;
	if (flag == 1) {
		string arr_err;
		result_if ="\nError: No сlosed bracket\n";
		cout << "\nError: No closed bracket\n";
		flag = 0;
	}
	return nullptr;
}

void deep_rec(s_expr* cur, int count, int& answer,string& result_if) {
	if (cur) {
		if (cur->flag == 0 && cur->ptr_child) {
			count++;
			deep_rec(cur->ptr_child, count,answer,result_if);
		}
		if (cur->flag == 1) {
			string str(2 * count, '-');
			cout << "\n"<<str<<"Current depth:" << count << "\n"<<str<<"Elem:" << cur->atom << endl;
			result_if = result_if + "\n" + str + "Current depth:" + to_string(count) + '\n' + str + "Elem:" + cur->atom + '\n';
			if (answer < count) answer = count;
		}
		if (cur->flag == 0 && cur->ptr_child) {
			deep_rec(cur->ptr_next, count-1,answer,result_if);
		}
		else
			deep_rec(cur->ptr_next, count, answer,result_if);
		return;
	}
	return;
}

void free_list_mem(s_expr* cur,int & count) {
	if (cur) {
		if (!cur->flag) {
			free_list_mem(cur->ptr_child,count);
		}
		free_list_mem(cur->ptr_next,count);
		if (cur->flag)
			cout << ">>Deleted elem: " << cur->atom << endl;
		else
			cout << ">>Delited parent" << endl;
		count++;
		delete cur;
	}
	return;
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
		return 0;
	}
	while (arr.find(' ') != string::npos)		//Удаление лишних пробелов
		arr.erase(arr.find(' '), 1);											
	return 0;
}

void prints_result(int answer, string &arr,string & result_if) {
	cout << "\n>>Type 'f' if you want to save result in file output.txt"
		<< "\n>>Else type any button" << endl;
	char key = _getch();
	if (key == 'f') {
		std::ofstream out;
		out.open("output.txt");
		if (out.is_open()) {
			if (answer == -1) out << result_if;
			else {
				cout << "\n>>The depth of the hierarchical list: " << answer << endl;
				out << ">>List: " << arr << '\n';
				out << result_if;
				out << ">>The depth of the hierarchical list: " << answer << endl;
			}
			out.close();
			return;
		}
	}
	else {
		if (answer == -1) return;
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
	else if (reads_data(arr)) return 0; //если считывание прошло удачно
	int count = 0, numb = 0, flag =1;
	stack <char> st;
	string result_if;
	int answer = -1;
	if (!(isalpha(arr[0]) && arr.length() == 1))//если это не единственный атом
		if ((arr[0] != '(') || (arr[arr.length() -1] != ')')) {
			cout << "Error: incorrect input,no first and/or last bracket";
			result_if = "Error: incorrect input,no first and/or last bracket";
			prints_result(answer, arr, result_if);
			return 0;
	}
	s_expr* head = make_list(arr, count, flag, st,numb,result_if);
	if (!head) {
		prints_result(answer, arr, result_if);
		return 0;
	}
	else cout << "\n>>List:" << arr;
	count = 0;
	answer = 0;
	deep_rec(head,count,answer,result_if);
	prints_result(answer,arr,result_if);
	count = 0;
	free_list_mem(head,count);
	cout << ">>Total deleted:" << count << endl;
	if (count == numb) {
		cout << ">>Correct memory release" << endl;
	}
	else
		cout << ">>Incorrect memory release" << endl;
	return 0;
}
