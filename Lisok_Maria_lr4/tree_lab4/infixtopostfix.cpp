#include "allheaders.h"
#include "infixtopostfix.h"

bool isOperation(char buf)
{
    return (buf == '*' || buf=='-' || buf=='+')?  true: false;
}

void infixToPrefix(string & str, string & postfixForm, string & err)
{
    reverse(str.begin(), str.end());

    Stack<char> stack;
    for(unsigned long i=0; i<str.length(); i++){
        if(isOperation(str[i])){
            if(((i+1)!=str.length() && str[i+1]==')') || stack.isEmpty() || *stack.onTop()==')')
                stack.push(str[i]);
            else{
                if(!stack.isEmpty()){
                    postfixForm+=*stack.onTop();
                    stack.pop();
                    stack.push(str[i]);
                }else{
                    err = "check input string\n";
                    return;
                }
            }
        }else if(str[i]==')') {
            stack.push(str[i]);
        }else if(str[i]=='(') {
            char buf;
            do{
                if(!stack.isEmpty()){
                    buf = *stack.onTop();
                    stack.pop();
                    if(buf != ')')
                        postfixForm+=buf;
                }else{
                    err = "check input string\n";
                    return;
                }
            }while(buf != ')');

        }else if(str[i]==' '){
            continue;
        }else{
            postfixForm+=str[i];
        }
    }
    if(postfixForm=="" || postfixForm.empty()){
        err = "check input string\n";
        return;
    }


}
