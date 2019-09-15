#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <clocale>
#include <windows.h>
using namespace std;

string transmute(string & out, string & text, int& deep)
{
	string buff;
	int len;
	int n = 0;
	n = text.find('/');
	//cout << n << '\n';
	if (n == -1)
	{
		cout << "на выход - " << text << '\n';
		return text;
	}
	else
	{
		deep++;
		buff = text.substr(0, n);
		cout << "Буфер - " << buff << "Глубина - " << deep <<'\n';
		len = text.length();
		text = text.substr(n + 1, len);
		cout << "Остаток - " << text << "Глубина - " << deep << '\n';
		out = transmute(out, text, deep);
		out += buff;
		cout << "получилось - " << out << '\n';
		return out;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	int deep = 0;
	int choice;
	string out;
	string text;
	cout << "Выберите метод ввода: Из файла нажмите 0, с консоли нажмите 1\n";
	cin >> choice;
	if (!choice)
	{
		ifstream fin;
		fin.open("input.txt");
		getline (fin,text);
		fin.close();
	}
	else 
		if (choice == 1)
	{
		getline(cin, text);
		cout << "Введите текст.\n";
		getline(cin, text);
	}
	ofstream fout;
	fout.open("out.txt");

	transmute(out, text, deep);
	cout << "итог - " << out << '\n';
	fout << out;
	fout.close();

}