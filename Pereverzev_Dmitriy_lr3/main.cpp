#include "lr_3_methods.h"
#include "lr_3_methods.cpp"

int main(int argc, char *argv[])
{
    bool flag_step=false;
    bool flag_gui=false;
    for(int i=1;i<argc;i++)
    {
        if(!strcmp("gui",argv[i]))
            flag_gui=true;
        if(!strcmp("step",argv[i]))
            flag_step=true;
        if(!strcmp("console",argv[i]))
            flag_gui=false;
        if(!strcmp("all_steps",argv[i]))
            flag_step=false;
    }
    
    if(flag_gui)
    {
        system("open http://163.172.163.152:3000/");
        return 0;
    }
    int i = 0;
    int *prefix_arr;
    int len;
    //input
    string prefix;

    
    while(true)
    {
        ifstream in("prefix.txt");

        cout<<"Read expression from file?(y/n): ";
        cout<<prefix;
        char y_n='y';
        cin>>y_n;
        if(y_n=='n')
            continue;
        getline(in,prefix);

        
        int err = test(prefix);
        if (!err)
        {
            i = 0;
            int j = 0;
            len = prefix.size();
            prefix_arr = new int[len];
            for (int elem : prefix)
                prefix_arr[j++] = elem;
            break;
        }
        else
        {
            system("clear");
            cout<<"#ERROR#\nWrong expression\nPlease repeat\n";
            
        }
    }
    //step
    string ret;
    if(flag_step)
    {
        do{
            ret = " ";

            char y_n;
            cout<<"Continue?(y/n)\n";
            cin>>y_n;
            if(y_n=='n')
                break;
            prefix_arr = step(prefix_arr, &i, &len);
            for (int j = 0; j < len; j++)
            {
                if (isnum(prefix_arr[j]) == 0)
                {
                    ret += (char)prefix_arr[j];
                    ret += ' ';
                }
                else
                {
                    ret += to_string(prefix_arr[j] - '0') + ' ';
                }
            }
            cout<<ret<<endl;
        }while(count(ret.begin(),ret.end(),' ')>2);
        return 0;
    }
    
    //all steps
    cout<<"Meaning of expression: "<<step_by_step(prefix_arr, &len)<<endl;



    return 0;
}









