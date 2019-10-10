#include <iostream>
#include <conio.h>
using namespace std;

typedef struct node
{
	int weight;
	struct node* left;
	struct node* right;
}node;

void push(int a, node **t)
{
	if ((*t) == NULL)                   
	{
		(*t) = new node;                
		(*t)->weight = a;                 
		(*t)->left = (*t)->right = NULL;      
		return;                        
	}
	
	if (a > (*t)->weight) push(a, &(*t)->right); 
	else push(a, &(*t)->left);         
}

unsigned int w(node* t)
{	
	unsigned int r = 0;
	if(t->left)
	r = r + w(t->left);
	if(t->right)
	r = r + w(t->right);
	r = r + t->weight;
	return r;
}

unsigned int ww(node* t)
{
	if (t == NULL)
		return 0;
	unsigned int r = 0;
	r = r + w(t->left);
	r = r + w(t->right);
	r = r + t->weight;
	return r;
}

void print(node *t, int u)
{
	if (t == NULL) return;                  
	else 
	{
		print(t->left, ++u);                   
		for (int i = 0; i < u - 1; ++i) cout << "->";
		cout << t->weight << endl;            
		u--;
	}
	print(t->right, ++u);                       
}

int main()
{
	setlocale(LC_ALL, "ru");
	node *tree = NULL;
	int n;                              
	int s;                             
	cout << "введите количество элементов  ";
	cin >> n;                           

	for (int i = 0; i < n; ++i)
	{
		cout << "ведите число  ";
		cin >> s;                       

		push(s, &tree);               
	}
	cout << "ваше дерево\n";
	print(tree, 0);
	unsigned int r;
	r = w(tree);
	cout << w(tree) << endl << ww(tree);
	_getch();
	return 0;
}