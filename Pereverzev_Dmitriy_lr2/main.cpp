#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;
ofstream out("./out.txt");

struct ELEM
{
    ELEM *next;
    bool event;
    union {
        ELEM *down; //true
        char simb;  //false
    };

};

int what(char& simb)
{
    if((simb>='a'&&simb<='z')||(simb>='0'&&simb<='9'))
        return 3;
    else if(simb=='*'||simb=='-'||simb=='+'||simb=='/')
        return 2;
    else if(simb=='('||simb==')')
        return 1;
    else if(simb=='\n')
    {
        simb=0;
        return -1;
    }
    else if(simb>=32)
        return -2;
    return 0;
}

void push(ELEM *&head, char simb)
{
    ELEM *element = new ELEM;
    if (simb == '(')
    {
    	head->next=NULL;
        head->down = element;
        head->event = true;
    }
    else if (simb != ')')
    {
        head->next = element;
        head->simb = simb;
        head->event = false;
    }
    else if (simb == ')')
	    {
	    	head->next=element;
	    	element->simb=')';
	    	element->next=NULL;
	    	element->event=false;
	    }
}

void input(ELEM *&head, string initial, int& position)
{
    if (position+1 == initial.size())
        return;
    position++;
    push(head,initial[position]);
    if (initial[position] == '(')
    	input(head->down,initial,position);
    else if(initial[position+1]!=')')
    	input(head->next,initial,position);
    if(initial[position+1]==')')
    { 
    	if(head->event)
    	{
    		position+=1;
    		push(head,initial[position]);
    		input(head->next, initial, position);
    	}
    return;
    }
}

void test(ELEM *&head, int len, int& position,string& help,string& finish,int& error)
{
    if (position >= len)
        return;
    position++;
    if(finish.find('(')!=string::npos)
    {
        error+=1;
        return;
    }
    if(!(head->event))
        if(what(head->simb)==-2)
        {
            error+=1;
            out<<error<<". simbol:  \'"<<head->simb<<"\' (index of simbol: "<<position<<")\n";
        }
    if(!(head->event)&&head->simb<=32)
        return;
    if (head->event)
    {
        position++;
        if(what(head->down->simb)==2)
        {
            error+=1;
            out<<error<<". simbol:  \'"<<head->down->simb<<"\' (index of simbol: "<<position<<")\n";
        }
        test(head->down,len,position,help,finish,error);
    }
    if(head->next)
    {
        if(!(head->next->event))
        {
            if(what(head->simb)==what(head->next->simb))
            {
    
                error+=1;
                out<<error<<". simbol:  \'"<<head->next->simb<<"\' (index of simbol: "<<position<<")\n";
            }
            if(head->simb=='/'&&head->next->simb=='0')
            {

                error+=1;
                out<<error<<". simbols:\""<<head->simb<<head->next->simb<<"\" (index of simbol: "<<position<<")\n";
            }
        }
        test(head->next,len,position,help,finish,error);
    }
    if(finish.find(')')!=string::npos)
        error+=1;
}

int prior(char x)
{
    if ((x=='*')||(x=='/')) return 2;
    if ((x=='+')||(x=='-')) return 1;
    if ((x=='(')||(x==')')) return 0;
    return -1;
}

void postf(string& help,string& finish,char simb,int position)
{
    out<<"\n"<<position+1<<'.'<<simb<<"\t"<<help[help.size()-1]<<"\t";
	if(simb=='(')
	{
		help+=simb;
	}
	else if((simb=='+')||(simb=='-')||(simb=='/')||(simb=='*'))
	{
		while((help.size()!=0)&&(prior(help[help.size()-1])>prior(simb)))
		{
			finish+=help[help.size()-1];
			help.resize(help.size()-1);
            out<<finish[finish.size()-1];
		}
		help+=simb;
	}
	else if(simb==')')
	{
		while(help.size()&&help[help.size()-1]!='(')
		{
			finish+=help[help.size()-1];
			help.resize(help.size()-1);
            out<<finish[finish.size()-1];
		}
        help.resize(help.size()-1);
	}
	else
	{
		finish+=simb;
        out<<simb;
	}
}

void fun(ELEM *&head, int& len, int& position,string& help,string& finish)
{
	if (position+1 == len)
        return;
    position++;
    if(!(head->event))
    {
    	postf(help,finish,head->simb,position);
    }
    if(!(head->event)&&head->simb<=' ')
    {
        postf(help,finish,')',position);
        len++;
        return;
    }
    if (head->event)
    {
    	postf(help,finish,'(',position);
    	fun(head->down,len,position,help,finish);
        position++;
    }
    if(head->next)
    {
    	fun(head->next,len,position,help,finish);
    }
}



int main()
{
    string initial;
    string finish,help;
    int error=0;
    ELEM *head = new ELEM;

    //in
    cout<<"Введите выражение: ";
    cin>>initial;
    out<<"Введенное выражение: "<<initial<<"\n\n";
    int len=initial.size();
    int position = -1;
    input(head, initial, position);

    //test
    out<<"Найденные ошибки:\n";
    position=-1;
    test(head,len,position,help,finish,error);
    if(error)
    {
        out<<"-Найдено ошибок:"<<error<<endl;
        return 0;
    }
    else
    {
        out<<"-Ошибки отсутствуют\n";
    }

    //postf
    position=-1;
    fun(head,len,position,help,finish);

    //out
    for(int i=help.size()-1;i>=0;i--)
        finish+=help[i];
    out<<endl<<"-----------------\nПостфиксная форма: "<<finish<<endl;
    system("open ./out.txt");
    return 0;
}
