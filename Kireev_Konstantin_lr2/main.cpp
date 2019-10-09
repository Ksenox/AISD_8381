#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

typedef char type;
struct list{
    type atom;
    list* next;
};
struct s_expr;
struct hd_and_tl{
    s_expr* hd;
    s_expr* tl;
};  
struct s_expr{
    bool tag; 
    union{
        type atom;
        hd_and_tl pair; 
    }node;      
};
typedef s_expr* H_list;
typedef list* L_list; 

bool isNull(const H_list x);
H_list head(const H_list x);
H_list tail(const H_list x);
H_list cons(const H_list x, const H_list y);
bool isAtom(const H_list x);
H_list make_atom(const type x);
void destroy_h(H_list s);
void destroy_l(L_list b);
void read_expression(type prev_symbol, H_list& y, ifstream &infile);
void read_brackets(H_list& y, ifstream &infile);
void write_expression(const H_list x, ofstream &outfile);
void write_brackets(const H_list x, ofstream &outfile);
void output(H_list& s, L_list& b, ofstream &outfile, int &n);
void calculate(const H_list x, L_list& b, int &n);
void calc_expression(const H_list x, int & n, L_list& first_el,  L_list& el);
void calc_brackets(const H_list x, int & n, L_list& first_el,  L_list& el);

int main(){
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    H_list h;
    L_list l;
    int n = 0;

    type x;
    do 
        infile >> x;
    while (x == ' ');
    read_expression(x, h, infile);

    calculate(h, l, n);
    output(h, l, outfile, n);
    
    destroy_h(h);
    destroy_l(l);
    return 0;
}

bool isNull(const H_list x){ 
    return x == NULL;
}

H_list head(const H_list x){
    if(x == NULL){
        cerr << "! Head(Nil)\n";
        exit(1);
    }
    else
        if(isAtom(x)){
            cerr << "! Head(Atom)\n"; 
            exit(1);
        }   
        else
            return x->node.pair.hd;
}

H_list tail(const H_list x){
    if(x == NULL){
        cerr << "! Tail(Nil)\n";
        exit(1);
    }
    else
        if(isAtom(x)){
            cerr << "! Tail(Atom)\n"; 
            exit(1);
        }   
        else
            return x->node.pair.tl;
}

H_list cons(const H_list x, const H_list y){
    if(isAtom(y)){ 
        cerr << "! Cons(x,Atom)\n"; 
        exit(1);
    }
    else{   
        H_list p = new s_expr; 
        if(p != NULL){
            p->tag = false;
            p->node.pair.hd = x;
            p->node.pair.tl = y;
            return p;
        }   
        else{
            cerr << "! Exhausted memory\n"; 
            exit(1);    
        }
    }
}

bool isAtom(const H_list x){    
    if(x == NULL) 
        return false;
    else 
        return (x->tag);
}

H_list make_atom(const type x){ 
    H_list p = new s_expr;
    if(p != NULL){
        p -> tag = true;
        p->node.atom = x;
    }
    else{
        cerr << "! Exhausted memory\n"; 
        exit(1);    
    }
    return p;
}

void destroy_h(H_list s){
    if(s != NULL){
        if(!isAtom(s)){
            destroy_h(head(s));
            destroy_h(tail(s));
        }
    delete s;
    }
}

void destroy_l(L_list b){
    L_list tmp;
    while(b != NULL){
        tmp = b->next;
        delete b;
        b = tmp;    
    }
    delete b;
}

void read_expression(type prev_symbol, H_list& y, ifstream &infile){ 
    if(prev_symbol == ')'){
        cerr << " ! First symbol can't be )\n"; 
        exit(1);
    } 
    else 
        if(prev_symbol != '(') 
            y = make_atom(prev_symbol); 
        else 
            read_brackets(y, infile);
} 

void read_brackets(H_list& y, ifstream &infile){    
    type x; 
    H_list H1, H2;

    if (!(infile >> x)){
        cerr << " ! Missing characters after (" << endl; 
        exit(1);
    }
    else{
        if(x == ')')
            y = NULL;
        else{
            read_expression(x, H1, infile);
            read_brackets(H2, infile);
            y = cons(H1, H2);
        } 
    }
} 

void write_expression(const H_list x, ofstream &outfile){
    if (isNull(x)){ 
        cout << " ()";
        outfile << " ()";
    }
    else 
        if (isAtom(x)){ 
            cout << ' ' << x->node.atom;
            outfile << ' ' << x->node.atom;
        }
        else{
            cout << " (" ;
            outfile << " (" ;
            write_brackets(x, outfile);
            cout << " )";
            outfile << " )" ;
        }
} 

void write_brackets(const H_list x, ofstream &outfile){
    if (!isNull(x)){
        write_expression(head(x), outfile); 
        write_brackets(tail(x), outfile);
    }
}

void output(H_list &s, L_list &b, ofstream &outfile, int& n){
    cout << "Hierarchical list:";
    outfile << "Hierarchical list:";
    write_expression(s, outfile);
    cout << endl << "Atoms: " << n ;    
    outfile << endl << "Atoms: " << n ;
    cout << endl << "Linked list: ";
    outfile << endl << "Linked list:";
    if(b != NULL)
        while(b != NULL){
            outfile << b->atom << " ";
            cout << b->atom << " ";
            b = b->next;
        }
    else{ 
        cout << "()" << endl;
        outfile << "()" << endl;
    }
}

void calculate(const H_list x, L_list& first_el, int& n){
    L_list el;  
    if (isNull(x)) 
        first_el = NULL;
    else{
        calc_expression(x, n, first_el, el);
        el->next = NULL;
    }
}

void calc_expression(const H_list x, int& n, L_list& first_el,  L_list& el){
    if(isAtom(x)){
        n++;
        if(n == 1){
            el = new list;
            el->atom = x->node.atom;
            el->next = NULL;
            first_el = el;
        }
        else{
            el->next = new list;
            el = el->next;
            el->atom = x->node.atom;
        }           
    }
    else  
        calc_brackets(x, n, first_el, el);
}

void calc_brackets(const H_list x, int& n, L_list& first_el,  L_list& el){
    if (!isNull(x)){
        calc_expression(head(x), n, first_el, el); 
        calc_brackets(tail(x), n, first_el, el);
    }
}
