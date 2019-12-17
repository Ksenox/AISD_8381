#include "lr_5_methods.h"
#include "lr_5_methods.cpp"

int main(int argc, const char *argv[])
{
    TREE* tree=NULL;
    char run='y';
    int value;
    while(true)
    {
        cout<<"Add new element?(y/n)\n";
        cin>>run;
        while(run!='y'&&run!='n')
        {
            cout<<"Wrong answer, enter 'y' or 'n'.\n";
            cin>>run;
        }
        if(run=='n')
            break;
        cout<<"Enter value of new element: ";
        cin>>value;
        push(tree, value);
    }
    
    cout<<"Finde elem: ";
    cin>>value;
    if(find_elem(tree, value)!=NULL)
    tree=NULL;
    
    
    
    return 0;
}




//y1y0y86y9y26y11y2y3y8y4y6y7y5y25y13n9
