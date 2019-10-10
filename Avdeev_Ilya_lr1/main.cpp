#include "pch.h"
#include <iostream>
#include "fstream"
using namespace std;

int Bin(int n, int m)
{
	if (n == m)
		return 1;
	if (m == 1)
		return n;
	return Bin(n - 1, m - 1) + Bin(n - 1, m);
}

int main()
{
	ofstream lof;
	ifstream lin;
	int m;
	int n;
	lin.open("lin.txt");
	lin >> n;
	lin >> m;
	lin.close();
	if (n < 0 | m < 0)
		cout << "Numbers must be positive";
	else 
	{
		lof.open("lof.txt");
		cout << Bin(n, m);
		lof << Bin(n, m);
		lof.close();
	}
	return 0;
}