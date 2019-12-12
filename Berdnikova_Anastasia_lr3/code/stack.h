#ifndef SYNTAX_H
#define SYNTAX_H

#include <cstdio>
#include <QChar>

#define NMAX 10000

struct stack {
  QChar elem[NMAX];
  int top;
};

void init(struct stack *stk);
void push(struct stack *stk, QChar f);
QChar pop(struct stack *stk);
QChar stkTop(struct stack *stk);
int gettop(struct stack *stk);
int isempty(struct stack *stk);
void stkPrint(struct stack *stk);

#endif // SYNTAX_H
