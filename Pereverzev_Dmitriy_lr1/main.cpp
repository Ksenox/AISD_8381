#include <iostream>
#include <fstream>
#include <string>
#define FILE "./input.txt"
using namespace std;

void input(int *&v, int &len_v);
void input_f(int *&v, int &len_v);
int *add(int *arr, int &len, int k);
void output(int *v, int len_v);
int *fun(int *v, int &len_v);
ifstream in(FILE);

int main(int argc, char* argv[])
{
	int len_v = 1;
	int *v = new int[argc-1];
	if(argc>1)
	{
		len_v=argc-1;
		for(int i=0;i<argc-1;i++)
			v[i]=atoi(argv[i+1]);
	}
	else
	{
		string str;
		getline(cin,str);
		if(str=="file")
		{
			string file;
			input_f(v,len_v);
		}
		else if(str=="console")
			input(v, len_v);
		else
		{
			cout<<"Wrong word.\n";
			return 0;
		}
	}
	v = fun(v, len_v);
	output(v, len_v);
	delete[] v;
	return 0;
}

int *add(int *arr, int &len, int k)
{
	int *dop = new int[len + k];
	memcpy(dop, arr, len * sizeof(int));
	len += k;
	delete[] arr;
	return dop;
}

void input(int *&v, int &len_v)
{
	char cbuf;
	int i = 0;
	while (true)
	{
		cin >> v[i++];
		cin.get(cbuf);
		if (cbuf == '\n')
			return;
		v = add(v, len_v, 1);
	}
}

void input_f(int *&v, int &len_v)
{
	char cbuf;
	int i = 0;
	while (true)
	{
		in >> v[i++];
		in.get(cbuf);
		if (cbuf == '\n')
			return;
		v = add(v, len_v, 1);
	}
}

void output(int *v, int len_v)
{
	for (int i = 0; i < len_v; i++)
		cout << v[i] << " ";
	cout << endl;
}

int *fun(int *v, int &len_v)
{
	if(len_v>2)
	{
		int n= len_v % 2;
		int len_a = len_v / 2 + n;
		int *a = new int[len_a];
		int len_b = len_v / 2 + n;
		int *b = new int[len_b];
		memcpy(a, v, (len_a) * sizeof(int));
		memcpy(b, &v[len_a - n], (len_b) * sizeof(int));
		a = fun(a, len_a);
		b = fun(b, len_b);
		a = add(a, len_a, len_b);
		memcpy(&a[len_a / 2], b, len_b * sizeof(int));
		len_v = len_a;
		return a;
	}
	return v;
}
