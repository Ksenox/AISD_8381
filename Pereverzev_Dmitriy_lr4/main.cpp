#include "lr_4_methods.h"
#include "lr_4_methods.cpp"

int main(int argc, const char *argv[])
{
    bool flag_bypass=false;
    bool flag_bin_str=false;
    
    
    for(int i=1;i<argc;i++)
    {
        if(!strcmp("gui",argv[i]))
        {
            system("open http://163.172.163.152:3000/");
            return 0;
        }
        if(!strcmp("bypass",argv[i]))
            flag_bypass=true;
        if(!strcmp("bin_str",argv[i]))
            flag_bin_str=true;
    }

    
    string forest;
    string bypass_width = "";
    string bin_tree = "(";
    cout<<"Введите скобочное представление леса:\n";
    cin >> forest;
    int *lvl = new int[100];
    string *arr_val = new string[100];
    int i_lvl = 1;
    int index = 1;

    TREE *tree = NULL;
    lvl[0] = -1;
    lvl[i_lvl] = -1;
    //test
    int err=test_4(forest);
    if(err)
    {
        cout << "Errors: ErrNum#" << err << endl;
        return 0;
    }
    create_4(i_lvl, lvl, arr_val, forest);

    //add(tree);
    add_4(tree, i_lvl, lvl, arr_val, index);
    
    //bypass
    if(flag_bypass)
    {
        bypass_4(tree, bin_tree);
        cout<<"Скобочное представление бинарного дерева:\n"<<bin_tree<<endl;
    }
    //bin_str
    if(flag_bin_str)
    {
        width_4(tree,bypass_width);
        cout<<"Обход в ширину бинарного дерева:\n"<<bypass_width<<endl;
    }
    return 0;
}

