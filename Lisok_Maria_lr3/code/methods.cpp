#include "methods.h"

bool isOperation(char symbol){
    return ((symbol=='+' || symbol=='*' || symbol=='^')? true: false);
}
void step(char a, Stack<long long int>& stack, string & output, string & err){
    long result=0;
    if(!stack.isEmpty() && stack.length()>=2){
        switch(a){
            case '+':
                result+=*stack.onTop();
                output.append(to_string(*stack.onTop())+"+");
                stack.pop();
                result+=*stack.onTop();
                output.append(to_string(*stack.onTop())+"="+to_string(result)+"\n");
                stack.pop();
                stack.push(result);
                break;
            case '*':
                result=1;
                result*=*stack.onTop();
                output.append(to_string(*stack.onTop())+"*");
                stack.pop();
                result*=*stack.onTop();
                output.append(to_string(*stack.onTop())+"="+to_string(result)+"\n");
                stack.pop();
                stack.push(result);
                break;
            case '^':
                long power=*stack.onTop();
                stack.pop();
                result=pow(*stack.onTop(),power);
                output.append(to_string(*stack.onTop())+"^"+to_string(power)+"="+to_string(result)+"\n");
                stack.pop();
                stack.push(result);
                break;
        }
    }
    else{
        err.append("Uncorrect test. Check your string!\n");
    }
}
void onestep(char data, Stack<long long int>& stack, string & output, string & err){
    if(isOperation(data)){
        step(data, stack, output, err);
        if(!output.empty())
            return;
    }else{
        if(isdigit(data)){
            stack.push(data-'0');
            output.append("push "+to_string(data-'0')+"\n");
        }
        else{
            err.append("Uncorrect test. Input numbers!\n");
        }
    }
}
long long int calculation(const string& str, string & output, string & err){
    Stack<long long int> stack{};
    for(long long int i=0; i<str.length(); i++){
        onestep(str[i], stack, output, err);
    }
    long long int result = *stack.onTop();
    stack.pop();
    if(stack.isEmpty())
        return result;
    err.append("Uncorrect test. There are too much symbols in you string!\n");
    stack.clear();
    return 0;
}
