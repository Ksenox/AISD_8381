#include<iostream>
#include <string>
#define ERROR "Error\n"
using namespace std;
 
int prior(char x)
{
    if ((x=='*')||(x=='/')) return 2;
    if ((x=='+')||(x=='-')) return 1;
    if ((x=='(')||(x==')')) return 0;
    return -1;
}
 
class stack
{
public :
    int top;
    string body;
    stack(){top=0;}
    bool empty(){return top==0;}
    char get_top_element(){return body[top];}
    int top_prior(){return prior(body[top]);}
    void push(char x)
    {
        top++;
        body[top]=x;
    }
    char pop()
    {
        top--;
        return body[top+1];
    }
    
};

int what(char simv)
{
	if(simv>='a'&&simv<='z')
		return 3;
	if(simv=='*'||simv=='-'||simv=='+'||simv=='/')
		return 2;
	if(simv=='('||simv==')')
		return 1;
	return 0;
}
 

void postf(string note,string &pnote,int &p, int &i,stack &s)
{
 
    
    	cout<<"\n1."<<note[i]<<"\t"<<s.get_top_element()<<"\t";

        if (note[i]=='(') s.push(note[i]);
        else if ((note[i]=='+')||(note[i]=='-')||(note[i]=='/')||(note[i]=='*'))
        {
    	//cout<<note[i]<<pnote[p]<<endl;

            while((!s.empty())&&(s.top_prior()>prior(note[i])))
            {
                p++;
                pnote[p]=s.pop();
                cout<<pnote[p];

            }
            s.push(note[i]);
        }
        else if(note[i]==')')
        {
    	//cout<<note[i]<<pnote[p]<<endl;

            while((!s.empty())&&(s.get_top_element()!='('))
            {
                p++;
                pnote[p]=s.pop();
                cout<<pnote[p];
            }
            s.pop();
        }
        else
        {
    	//cout<<note[i]<<pnote[p]<<endl;

            p++;
            pnote[p]=note[i];
            cout<<pnote[p];
        }
        if(i>=note.size())
        	return;
    i++;
 	postf(note,pnote,p,i,s);

 	if(i>=note.size())
    	while(!s.empty())
    	{
    	    p++;
    	    pnote[p]=s.pop();
    	}

    return;
}
 
 void test(string n,string p)
{
	int error=0;
 	for(int i=0;i<n.size()-1;i++)
 	{
 		if(what(n[i])==0) 
 			error+=1;
 		if(n[i]=='('&&n[i+1]==')') 
 			error+=1;
 		if(what(n[i])==what(n[i+1])&&what(n[i])!=1) 
 			error+=1;
 		if(n[i]=='/'&&n[i+1]=='0') 
 			error+=1;
 	}
 	if(p.find('(')!=-1||p.find(')')!=-1)
 			error+=1;

 	if(error)
 	{
 		cout<<ERROR;
 		exit(1);
 	}
 }
 

void input(string& note)
{

	cin>>note;

}

void output(string pnote,int p)
{
	cout<<"Ошибок не обнаружено.\nПостфиксная запись: ";
	for(int i=1;i<=p;i++)
        cout<<pnote[i];
    cout<<endl;

}


int main(int argc, char* argv[])
{
    stack s;
    string note,pnote;
    int i=0,p=0;
    cout<<"Входны данные: ";
    if(argc<2) input(note);
    else 
    {
    	note=argv[1];
    	cout<<note<<endl;
    }
 	postf(note,pnote,p,i,s);
 	test(note,pnote);
 	output(pnote,p);
    
    return 0;
}
