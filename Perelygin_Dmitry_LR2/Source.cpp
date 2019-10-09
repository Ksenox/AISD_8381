#include <iostream>
#include <cstdlib>
#include "lisp.h"
#include <clocale>
#include <windows.h>
#include <fstream>
using namespace h_list;
using namespace std;



int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	lisp s;
	char a = '9', b = '9';
	int flag = 0;
	
		//cout << boolalpha;
		cout << "ВВедите список:	";
		read_lisp(s);
	

	red(s, flag, a, b);
	cout << a << endl;
	write_lisp(s);
	cout << endl;

	return 0;
}
	//(&A(|B(-B)))
	//(&A(&B(-B)))
	//(&A(&B(C)))
	//(&A(&B(|CC)))