#include <iostream>
#include <cstdlib>
#include "lisp.h"
using namespace h_list;
using namespace std;

int main(){
	setlocale (0,"Rus");
	lisp s;
	cout<<boolalpha;
	cout<<"Enter a hierarchical list:	";
	read_lisp(s);

	lisp z;
	z=reverse(s);
	cout<<"Reverse hierarchical list:	";
	write_lisp(z);
	cout<<endl;
	return 0;
}
