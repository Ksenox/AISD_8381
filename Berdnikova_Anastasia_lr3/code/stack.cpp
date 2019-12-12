#include "stack.h"

void init(struct stack *stk) {
  stk->top = 0;
}

void push(struct stack *stk, QChar f) {
  if(stk->top < NMAX) {
    stk->elem[stk->top] = f;
    stk->top++;
  } else
    printf("Стек полон, количество элементов: %d !\n", stk->top);
}

QChar pop(struct stack *stk) {
  QChar elem;
  if((stk->top) > 0) {
    stk->top--;//
    elem = stk->elem[stk->top];
    return(elem);
  } else {
    printf("Стек пуст!\n");
    return(0);
  }
}

QChar stkTop(struct stack *stk) {
  if((stk->top) > 0) {
    return( stk->elem[stk->top-1]);
  } else {
    printf("Стек пуст!\n");
    return(0);
  }
}

int gettop(struct stack *stk) {
    return(stk->top);
}

int isempty(struct stack *stk) {
  if((stk->top) == 0)    return(1);
  else return(0);
}

void stkPrint(struct stack *stk) {
  int i;
  i=stk->top;
  if(isempty(stk)==1) return;
  do {
    i--;
    printf("%f\n", stk->elem[i]);
  }while(i>0);
}
