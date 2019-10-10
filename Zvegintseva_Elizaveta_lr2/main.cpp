#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;
struct s_expr;
int c = 0;

struct  two_ptr
{
	s_expr* hd;
	s_expr* tl;
};	//end two_ptr;

struct s_expr
{
	bool tag; // true: atom, false: pair
	union
	{
		char atom;
		two_ptr pair;
	} node;		//end union node
};			//end s_expr 

typedef s_expr* lisp;
// функции 
void print_s_expr(lisp s);
// базовые функции:
lisp head(const lisp s);
lisp tail(const lisp s);
lisp cons(const lisp h, const lisp t);
lisp make_atom(const char x);
bool isAtom(const lisp s);
bool isNull(const lisp s);
void destroy(lisp s);

// функции ввода:
void read_lisp(lisp& y, istream& in = cin);			// основная
void read_s_expr(char prev, lisp& y, istream& in);
void read_seq(lisp& y, istream& in);

// функции вывода:
void write_lisp(const lisp x);		// основная
void write_seq(const lisp x);

void Space(int c) // создание отступов для вызовов/завершений фукнций
{
	for (int j = 1; j <= c; j++) cout << "__";
}

lisp head(const lisp s)
{// PreCondition: not null (s)
	if (s != NULL)
	{
		if (!isAtom(s))
		{
			return s->node.pair.hd;
		}
		else
		{
			cout << "Error: Head(atom) \n"; exit(1);
		}
	}
	else
	{
		cout << "Error: Head(nil) \n";
		return 0;
	}
}

bool isAtom(const lisp s)
{
	if (s == NULL)
	{
		return false;
	}
	else
	{
		return (s->tag);
	}
}

bool isNull(const lisp s)
{
	return s == NULL;
}

lisp tail(const lisp s)
{// PreCondition: not null (s)
	if (s != NULL)
	{
		if (!isAtom(s))
		{
			return s->node.pair.tl;
		}
		else
		{
			cout << "Error: Tail(atom) \n";
			exit(1);
		}
	}
	else
	{
		cerr << "Error: Tail(nil) \n";
		exit(1);
	}
}

lisp cons(const lisp h, const lisp t)
{// PreCondition: not isAtom (t)
	lisp p;
	if (isAtom(t))
	{
		cerr << "Error: Tail(nil) \n";
		exit(1);
	}
	else
	{
		p = new s_expr;
		//cout << "node:  " << p << endl << endl;
		if (p == NULL)
		{
			cerr << "Error: Memory not enough\n";
			exit(1);
		}
		else
		{
			p->tag = false;
			p->node.pair.hd = h;
			p->node.pair.tl = t;
			return p;
		}
	}
}

lisp make_atom(const char x)
{
	//cout << "Current simbol: " << x << endl;
	lisp s;
	s = new s_expr;
	s->tag = true;
	s->node.atom = x;
	//cout << "Addres simbol: "  <<  s <<  endl;
	return s;
}



// ввод списка с консоли
void read_lisp(lisp& y, istream& in)
{
	char x;
	do
	{
		in >> x;
	} while (x == ' ');

	read_s_expr(x, y, in);
} //end read_lisp

void read_s_expr(char prev, lisp& y, std::istream& in)
{ //prev - ранее прочитанный символ
	if (prev == ')')
	{
		cerr << " ! List.Error 1 " << endl;
		exit(1);
	}
	else
		if (prev != '(')
		{
			y = make_atom(prev);
		}
		else
		{
			read_seq(y, in);
		}
} //end read_s_expr

void read_seq(lisp& y, std::istream& in)
{
	char x;
	lisp p1, p2;
	if (!(in >> x)) x = 0;
	if ((in.eof() || (x == 0)))
	{
		cerr << " ! List.Error 2 " << endl;
		exit(1);
	}
	else
	{
		//cout << "Current simbol:" << x << endl;
		while (x == ' ')
		{
			in >> x;
		}

		if (x == ')')
		{
			y = NULL;
		}
		else
		{
			read_s_expr(x, p1, in);
			read_seq(p2, in);
			y = cons(p1, p2);
		}
	}
} //end read_seq

// Процедура вывода списка с обрамляющими его скобками - write_lisp,
void write_lisp(const lisp x)
{//пустой список выводится как () 
	if (isNull(x))
	{
		cout << " ()";
	}
	else if (isAtom(x))
	{
		cout << ' ' << x->node.atom;
	}
	else
	{ //непустой список
		cout << " (";
		write_seq(x);
		cout << " )";
	}
} // end write_lisp

void write_seq(const lisp x)
{//выводит последовательность элементов списка без обрамляющих его скобок
	if (!isNull(x))
	{
		write_lisp(head(x));
		write_seq(tail(x));
	}
}
bool Check(const lisp HierarchList, char x, bool b)
{
	if (isNull(HierarchList) || (b)) // Если список закончился или наше условие выполнено
	{
		return b;
	}
	else
	{
		if (HierarchList->tag) // Если текущий символ - атом
		{
			Space(c);
			cout << "Последний считанный символ: " << HierarchList->node.atom << endl;
			Space(c);
			cout << "Проверка на совпадение с символом " << x << endl;
			if (HierarchList->node.atom == x)//При совпадение с нашим элементом
			{
				b = true;
				return b;
			}
		}
		else
		{
			c++;
			Space(c); // Создание отступов для наглядности глубины вызова функции
			cout << "Вызов функции CHECK_HEAD_TO_ATOM_X" << endl;
			b = Check(HierarchList->node.pair.hd, x, b);
			Space(c); // Создание отступов для наглядности глубины вызова функции
			cout << "Завершение функции CHECK_HEAD_TO_ATOM_X" << endl;
			c--;
			c++;
			Space(c); // Создание отступов для наглядности глубины вызова функции
			cout << "Вызов функции CHECK_TAIL_TO_ATOM_X" << endl;
			b = Check(HierarchList->node.pair.tl, x, b);
			Space(c); // Создание отступов для наглядности глубины вызова функции
			c--;
			cout << "Завершение функции CHECK_TAIL_TO_ATOM_X" << endl;
		}
		return b;
	}
}
int main(void)
{
	setlocale(0, "");
	int i = 0;
	lisp HierarchList = NULL;
	ifstream fin;
	bool k = true;
	while (k)
	{
		cout << endl << "_________________________________________________________" << endl;
		cout << "1. Ввод списка вручную\n" << "2. Ввод списка из файла\n" << "3. Выход\n" << "Ваш выбор: ";
		cin >> i;
		while (cin.fail())// Проверка на ошибки ввода
		{
			cin.clear();
			cin.sync();
			cout << "Ошибка номера!\n";
			cout << "Ваш выбор: ";
			cin >> i;
		}
		switch (i)
		{
		case 1:
			std::cout << "Введите список:" << std::endl;
			read_lisp(HierarchList);//Считываем с консоли, поток по умолчанию cin
			break;
		case 2:
			fin.open("atom.txt");
			if (!fin.is_open())
			{
				cout << "Файл не открыт\n";
				system("pause");
				return 1;
			}
			read_lisp(HierarchList, fin);//Считываем из файла указывая поток fin
			fin.close();
			break;
		case 3:
			k = false;
			break;
		}
		if (!k) break;
		cout << "Введенный список: ";
		write_lisp(HierarchList);// Выводим список на экран
		char x;
		cout << endl << "Введите Атом x(искомый атом): ";
		cin >> x;
		cout << endl;
		bool b = false;
		Space(c); // Создание отступов для наглядности глубины вызова функции
		cout << "Вызов функции CHECK_ATOM_X" << endl;
		b = Check(HierarchList, x, b);
		Space(c); // Создание отступов для наглядности глубины вызова функции
		cout << "Завершение функции CHECK_ATOM_X" << endl;
		if (b)
		{
			cout << endl << "Атом x присутствует в списке";
		}
		else
		{
			cout << endl << "Атом x не присутствует в списке";
		}
	}
	cin.get();
	cin.get();
	return 0;
}

