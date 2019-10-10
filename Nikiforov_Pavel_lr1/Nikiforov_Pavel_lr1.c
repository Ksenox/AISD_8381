#include <stdio.h>

int AnalysOfBracket(char *str, int size, int deep, int current)//возвращает номер текущего элемента, если отрицательный - то не скобки
{	
	deep++;//Уровень глубины рекурсии повышается на 1
		while(current>0 && current<size-1)
		{
			
				for(int i=0; i<deep; i++)
					printf("\t");
				printf("Deep= %d, text=", deep);
				for (int i = 0; i<=current; i++)
           		 		printf("%c", str[i]);
           			printf("\n");
				current++;
				switch(str[current])
				{
					case('('):
						current=AnalysOfBracket(str, size, deep, current);//Если встречаем скобку - рекурсивно вызываем функцию анализа скобки 
						if(current==size-1&&deep==1)//Если вся строка прочитана, а глубина рекурсии == 1 (не равна 0)
							return -1*current;//то строка - не скобки
					break;
					case(' '):
                                                return current;
                                        break;
					case(')'):
						if(current==size-1 && deep==1 && str[current-1]!=';' && str[current-1]!='(')
							return current;
						else if(current==size-1 || str[current-1]==';' || deep<2 || str[current-1]=='(') //cимволы ';' и '(' не могут находиться перед ')'
							current*=-1;
						return current;
					break;
					case('A'):
						if(str[current-1]=='A')//cимволу 'A' не может предшествовать символ 'A'
							current*=-1;;
					break;
					case(';'):
						if(str[current-1]==';'||str[current-1]=='(')//cимволы ';' и '(' не могут находиться перед ';'
							current*=-1;
					break;

				}
			
		}
		if(current==size-1&&deep==1)//Если вся строка прочитана, а глубина рекурсии == 1 (не равна 0)
			return -1*current;//то строка - не скобки
		return current;
}

void SyntaxAnalys(char *str)//функция для обработки введенной строки
{
    int current=0;//счетчик текущего элемента
    int size=0;//счетчик размера введенного массива
    int brackets=1;//1-true, 0-false
    int result;//1-true 0-false


    while ((str[current] != '\n') &&(str[current] != '\0') && (brackets == 1))//проверка на неверный символ
    {
        if ((str[current] != ';') && (str[current] != 'A') && (str[current] != '(') && (str[current] != ')') && (str[current] != ' '))
            brackets=0;
         size++;
         current++;
    }

    if(size==0)//если нет введенных сиволов
    {
        printf("\nError: No symbols!\n");
        printf("Not brackets!\n");
        brackets=0;
    }

    else if(brackets==0)//если некорректный символ
    {
        for (int i = 0; i < size; i++)
            printf("%c", str[i]);
        printf("\nError: Incorrect symbol!\n");
        printf("Not brackets!\n");
    }

    if(brackets==1)
    {
        if(str[0]!='A')//если первый символ не А 
        {
        	printf("%c\n",str[0] );
                printf("\nIsn't brackets!\n");
        }
        else if(size==1)
        {
        	printf("A\n");
        	printf("It is brackets!\n");
        }
        else if(str[1]!='(' && str[1]!=' ')//Если второй символ не '(' и не ' '
        {
        	printf("%c%c\n",str[0], str[1] );
                printf("\nIsn't brackets!\n");
        }
        else
        {
        	current=1;
        	result=AnalysOfBracket(str,size,0,current);
        	if(result>0)
        		printf("It is brackets!\n");
        	else
        	{
        		result*=-1;
        		printf("It is not brackets\n");
        	}
        }
        	

    }
	
}

int main()
{
	char str[100];//массив для запроса

	printf("Введите строку: ");
        fgets(str,100,stdin);
        printf("\n");
        SyntaxAnalys(str);

return 0;
}