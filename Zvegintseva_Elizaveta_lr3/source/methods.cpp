#include "methods.h"


void step(char a, Stack<int>& stack, string & output, string & err){
    int result=0;
    if(!stack.isEmpty() && stack.length()>=1){
        switch(a){
            case '!':
                result = *stack.onTop();
                output.append("!" + to_string(result));
                stack.pop();
                result = (result == 1 )? 0: 1;
                output.append("="+to_string(result)+"\n");
                stack.push(result);
                break;
            case '^':
                result = *stack.onTop();
                output.append(to_string(*stack.onTop())+"^");
                stack.pop();
                result = (result &&  *stack.onTop() )? 1: 0;
                output.append(to_string(*stack.onTop())+"="+to_string(result)+"\n");
                stack.pop();
                stack.push(result);
                break;
            case 'v':
                result = *stack.onTop();
                output.append(to_string(*stack.onTop())+"v");
                stack.pop();
                result = (result ||  *stack.onTop() )? 1: 0;
                output.append(to_string(*stack.onTop())+"="+to_string(result)+"\n");
                stack.pop();
                stack.push(result);
                break;
        }
    }
    else{
        err.append("Uncorrect test. Check your string!\n");
    }
}
void onestep(char data, Stack< int>& stack, string & output, string & err){
    if(test_operation(data)){
        step(data, stack, output, err);
        if(!output.empty())
            return;
    }else{
        if(isdigit(data) && (data == '1' || data == '0')){
            stack.push(data-'0');
            output.append("push "+to_string(data-'0')+"\n");
        }
        else{
            err.append("Uncorrect test!\n");
        }
    }
}
int calc(const string& str, string & output, string & err){
    Stack<int> stack{};
    for(int i=0; i<str.length(); i++){
        onestep(str[i], stack, output, err);
        if(!err.empty())
            return 0;
    }
    int result = *stack.onTop();
    stack.pop();
    if(stack.isEmpty())
        return result;
    err.append("Uncorrect test. There are too much symbols in you string!\n");
    stack.clear();
    return 0;
}
