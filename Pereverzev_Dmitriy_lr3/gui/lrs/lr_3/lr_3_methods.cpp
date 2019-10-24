#include "lr_3_methods.h"
void shift(int *&str, int ind, int simb, int len)
{
    str[ind] = simb;
    for (; ind < len; ind++)
        str[ind - 2] = str[ind];
}

int isnum(char simb)
{
    if (simb == '*' || simb == '+' || simb == '^' || simb == '-')
        return 0;
    return 1;
}

int which_oper(int oper, int num1, int num2)
{
    switch (oper)
    {
    case '+':
        return '0' + (num1 - '0') + (num2 - '0');
        break;
    case '-':
        return '0' + (num1 - '0') - (num2 - '0');
        break;
    case '*':
        return '0' + (num1 - '0') * (num2 - '0');
        break;
    case '^':
        return '0' + pow((num1 - '0'), (num2 - '0'));
        break;

    default:
        break;
    }
    return 0;
}

int *step(int *expression, int *j, int *l)
{
    int i = *j;
    int len = *l;
    if (len < 2)
        return expression;
    if (i == 0)
        i = len - 1;
    if (isnum(expression[i]) == 1 && isnum(expression[i - 1]) == 1 && isnum(expression[i - 2]) == 0)
    {
        shift(expression, i, which_oper(expression[i - 2], expression[i - 1], expression[i]), len);
        len -= 2;
        i -= 2;
    }
    i--;
    *j = i;
    *l = len;
    return expression;
}

int step_by_step(int *expression, int *l)
{
    int i = 0;
    int len=*l;
    int *ret = step(expression, &i, l);
    len=*l;
    while (len>1)
    {
        ret = step(ret, &i, l);
        len=*l;
    }
            return (int)ret[0] - '0';

}

int test(string str)
{

    int num_quantity = 0;
    int oper_quantity = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (isnum(str[i]) == 1 && str[i] < 48 && str[i] > 57)
        {
            cout << "Error 4\n";
            return str[i];
        }
        if (isdigit(str[i]))
            num_quantity++;
        else
        {
            oper_quantity++;
            //3
            if (str[i] != '^' && str[i] != '+' && str[i] != '*' && str[i] != '-')
            {
                cout << "Error 3\n";
                return 3;
            }
        }
    }
    //2
    if (isdigit(str[0]) && str.length() > 1)
    {
        cout << "Error 2\n";
        return 2;
    }
    //1
    if (oper_quantity + 1 != num_quantity)
    {
        cout << "Error 1\n";
        return 1;
    }
    return 0;
}
