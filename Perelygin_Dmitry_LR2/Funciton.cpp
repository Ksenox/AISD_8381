#include "lisp.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

namespace h_list {

	lisp head(const lisp s) {
		if (s != NULL)
			if (!isAtom(s))
				return s->node.pair.hd;
			else { cerr << "Error: Head(atom) \n"; exit(1); }
		else {
			cerr << "Error: Head(nil) \n";
			exit(1);
		}
	}

	bool isAtom(const lisp s) {
		if (s == NULL)
			return false;
		else return (s->tag);
	}

	bool isNull(const lisp s) {
		return s == NULL;
	}

	lisp tail(const lisp s) {
		if (s != NULL)
			if (!isAtom(s))
				return s->node.pair.tl;
			else {
				cerr << "Error: Tail(atom) \n";
				exit(1);
			}
		else {
			cerr << "Error: Tail(nil) \n";
			exit(1);
		}
	}

	lisp cons(const lisp h, const lisp t) {
		lisp p;
		if (isAtom(t)) {
			cerr << "Error: Cons(*, atom)\n";
			exit(1);
		}
		else {
			p = new s_expr;
			if (p == NULL) {
				cerr << "Memory not enough\n";
				exit(1);
			}
			else {
				p->tag = false;
				p->node.pair.hd = h;
				p->node.pair.tl = t;
				return p;
			}
		}
	}

	lisp make_atom(const base x) {
		lisp s;
		s = new s_expr;
		s->tag = true;
		s->node.atom = x;
		return s;
	}

	base getAtom(const lisp s) {
		if (!isAtom(s)) {
			//cerr << "Error: getAtom(s) for !isAtom(s)" << endl;
			//exit(1);
			return '0';
		}
		else return (s->node.atom);
	}

	void read_lisp(lisp& y)
	{
		base x;
		do {
			cin >> x;
		} while (x == ' ');
		read_s_expr(x, y);
	}

	void read_s_expr(base x, lisp& y) {
		if (x == ')') {
			cerr << "Error:Missing '('" << endl;
			exit(1);
		}
		else if (x != '(')
			y = make_atom(x);
		else {
			char buffer = cin.peek();
			if (buffer == ')') {
				cout << "Error: List emtry!" << endl;
				exit(1);
			}
			read_seq(y);
		}
	}


	void read_seq(lisp& y) {
		base x;
		lisp p1, p2;
		if (!(cin >> x)) {
			cerr << " ! List.Error 2 " << endl;
			exit(1);
		}
		else {
			while (x == ' ')
				cin >> x;
			if (x == ')')
				y = NULL;
			else {
				read_s_expr(x, p1);
				read_seq(p2);
				y = cons(p1, p2);
			}
		}
	}



	void write_lisp(const lisp x) {
		if (isNull(x))
			cout << " ()";
		else if (isAtom(x))
			cout << ' ' << x->node.atom;
		else {
			cout << " (";
			write_seq(x);
			cout << " )";
		}
	}

	void write_seq(const lisp x) {
		if (!isNull(x)) {
			write_lisp(head(x));
			write_seq(tail(x));
		}
	}

	void destroy(lisp s)
	{
		if (s != NULL) {
			if (!isAtom(s)) {
				destroy(head(s));
				destroy(tail(s));
			}
			delete s;
			// s = NULL;
		}
	}


	void red(lisp s, int& flag, char& a, char& b)
	{
		//cout << getAtom(s) << endl;
		if (isNull(tail(s)) && (isAtom(head(s))))
		{
			cout << "back" << endl;
			a = getAtom(head(s));
			cout << a << endl;
			return;
		}
		if (!(isAtom(head(s))) && head(s) != NULL)
		{
			cout << "head"  << endl;
			red(head(s), flag, a, b);
		}
		else if (!(isAtom(tail(s))) && tail(s) != NULL)
		{
			cout << "tail"  << endl;
			red(tail(s), flag, a, b);
		}
		if (isAtom(head(s)))
		{
			cout << "up" << '\n' << a << '\n' << b  << endl ;

			if (getAtom(head(s)) == '-')
			{
				flag = 1;
				return;
			}

			if (getAtom(head(s)) == '&')
			{
				cout << "AND" << endl;
				if ((a == b) && flag)
				{
					cout << "1" << endl;
					head(s)->node.atom = '0';
					a = getAtom(head(s));
					b = '9';
					flag = 0;
					cout << "DESTROY" << endl;
					destroy(tail(s));
					s->node.pair.tl = NULL;
					return;
				}

				if ((a == b) && !flag)
				{
					cout << "2" << endl;
					head(s)->node.atom = a;
					a = getAtom(head(s));
					b = '9';
					flag = 0;
					cout << "DESTROY" << endl;
					destroy(tail(s));
					s->node.pair.tl = NULL;
					return;
				}

				if ((a == '1' || b == '1') && !flag)
				{
					if (a=='1')
					{
						head(s)->node.atom = b;
						a = getAtom(head(s));
					}
					else
					{
						head(s)->node.atom = a;
						a = getAtom(head(s));
					}
					b = '9';
					flag = 0;
					cout << "DESTROY" << endl;
					destroy(tail(s));
					s->node.pair.tl = NULL;
					return;
				}

				if ((a == '0' || b == '0') && !flag)
				{
						head(s)->node.atom = '0';
						a = getAtom(head(s));
					b = '9';
					flag = 0;
					cout << "DESTROY" << endl;
					destroy(tail(s));
					s->node.pair.tl = NULL;
					return;
				}
				
			}

			if (getAtom(head(s)) == '|')
			{
				cout << "OR" << endl;
				if ((a == b) && flag)
				{
					cout << getAtom(head(s)) << endl;
					head(s)->node.atom = '1';
					a = getAtom(head(s));
					b = '9';
					flag = 0;
					cout << "DESTROY" << endl;
					destroy(tail(s));
					s->node.pair.tl = NULL;
					return;
				}

				if ((a == b) && !flag)
				{
					head(s)->node.atom = a;
					a = getAtom(head(s));
					b = '9';
					flag = 0;
					cout << "DESTROY" << endl;
					destroy(tail(s));
					s->node.pair.tl = NULL;
					return;
				}

				if ((a == '1' || b == '1') && !flag)
				{
					head(s)->node.atom = '1';
					a = getAtom(head(s));
					b = '9';
					flag = 0;
					cout << "DESTROY" << endl;
					destroy(tail(s));
					s->node.pair.tl = NULL;
					return;
				}

				if ((a == '0' || b == '0') && !flag)
				{
					if (a == '0')
					{
						head(s)->node.atom = b;
						a = getAtom(head(s));
					}
					else
					{
						head(s)->node.atom = a;
						a = getAtom(head(s));
					}
					b = '9';
					flag = 0;
					cout << "DESTROY" << endl;
					destroy(tail(s));
					s->node.pair.tl = NULL;
					return;
				}
				
			}

			else
			{
				if (a == 9)
					a = getAtom(head(s));
				else
					b = getAtom(head(s));

			}

		}
		else
		{
			return;
		}
	}
}