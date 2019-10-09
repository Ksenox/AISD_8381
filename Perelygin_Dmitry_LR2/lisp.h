#pragma once
namespace h_list {
	typedef char base;

	struct s_expr;
	struct two_ptr;

	struct two_ptr {
		s_expr* hd;
		s_expr* tl;
	};

	struct s_expr {
		bool tag;
		union {
			base atom;
			two_ptr pair;
		}node;
	};

	typedef s_expr* lisp;

	lisp head(const lisp s);
	lisp tail(const lisp s);
	lisp cons(const lisp h, const lisp t);
	lisp make_atom(const base x);
	void read_lisp(lisp& y);
	void read_s_expr(base prev, lisp& y);
	void read_seq(lisp& y);
	void write_lisp(const lisp x);
	void write_seq(const lisp x);
	bool isNull(const lisp s);
	bool isAtom(const lisp s);
	void destroy(lisp s);
	void red(lisp s, int& flag, char& a, char& b);
}
